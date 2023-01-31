/**
 * @file temp_sensor_manager.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-05
 */

//--------------------------------------------------------------------------------

#include <temp_sensor_manger.h>

//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------

Temperature::Temperature()
{
    one_wire = new OneWire();
    temp_sensor = new DallasTemperature(one_wire);
    initialized = false;
}

Temperature::~Temperature()
{
    delete one_wire;
    delete temp_sensor;
}

void Temperature::init(uint8_t pin)
{
    one_wire->begin(pin);
    temp_sensor->begin();
    initialized = temp_sensor->getAddress(&this->device_address, 0);
    initialized &= temp_sensor->setResolution(&this->device_address, DS18B20_RESOLUTION, false);
    temp_sensor->setWaitForConversion(true);
    initialized &= temp_sensor->requestTemperaturesByAddress(&this->device_address);

    LOG("[TEMP_SENSOR_MANAGER] DS18B20 Sensor initialization : " + String(this->initialized ? " successful" : " failed"));
}

float Temperature::get_temp()
{
    if (!this->initialized)
    {
        LOG("[TEMP_SENSOR_MANAGER] Temperature cannot be retrieved. Sensor is not initialized. ");
        return -127;
    }
    
    temp_sensor->requestTemperaturesByIndex(0);
    float temp = temp_sensor->getTempCByIndex(0);

    if (temp == -85)
    {
        LOG("[TEMP_SENSOR_MANAGER] Temperature conversion problem.");
        return temp;
    }

    if (temp == DEVICE_DISCONNECTED_C)
    {
        LOG("[TEMP_SENSOR_MANAGER] Temperature sensor disconnected!");
        return temp;
    }

    LOG("[TEMP_SENSOR_MANAGER] Temperature read :" + String(temp));

    return (temp + TEMPERATURE_OFFSET);
}

void Temperature::sleep()
{
    this->one_wire->depower();
}