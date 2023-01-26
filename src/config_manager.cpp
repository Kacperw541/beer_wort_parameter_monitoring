/**
 * @file config_manager.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-08
 */

//--------------------------------------------------------------------------------

#include <config_manager.h>

//--------------------------------------------------------------------------------

ConfigManager::ConfigManager()
{
    LittleFS.begin();
    this->ssid = new char[32];
    this->pass = new char[32];
    this->api_key = new char[64];
    this->email = new char[64];
    this->firebase_password = new char[32];
    this->database_url = new char[128];
}

ConfigManager::~ConfigManager()
{
    delete[] this->ssid;
    delete[] this->pass;
    delete[] this->api_key;
    delete[] this->email;
    delete[] this->firebase_password;
    delete[] this->database_url;
}

ConfigManager& ConfigManager::get_instance()
{
    return instance;
}

void ConfigManager::init()
{
    int cnt = 0;
    while(!load())
    {
        LOG("[CONFIG MANAGER] Config load failed, retry :" + String(++cnt));
        if (cnt == 3)
        {
            LOG("[CONFIG MANAGER] Could not load config!"); // JAKOŚ INACZEJ TO OBSŁUŻYĆ
            ESP.deepSleep(ESP.deepSleepMax());
        }
    }

    if(!is_device_configured())
    {
        LOG("CONFIG MANAGER] Config file is incomplete!");
        ESP.deepSleep(ESP.deepSleepMax());
    }

    LOG("[CONFIG MANAGER] Config loaded");
}

bool ConfigManager::load()
{
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile)
    {
        LOG("[CONFIG_MANAGER] Could not open config.json file!");
        return false;
    }
    
    size_t size = configFile.size();
    char *buf = new char[size];
    
    configFile.readBytes(buf, size);
    
    StaticJsonBuffer <200> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf);
    
    if (!json.success())
    {
        delete buf;
        configFile.close();
        LOG("[CONFIG_MANAGER] JSON parsing failed");
        return false;
    }

    strcpy(this->ssid, json["ssid"]);
    strcpy(this->pass, json["pass"]);
    strcpy(this->api_key, json["api_key"]);
    strcpy(this->email, json["email"]);
    strcpy(this->firebase_password, json["firebase_password"]);
    strcpy(this->database_url, json["database_url"]);
    this->sleep_time = strtoull(json["sleep_time"], NULL, 10);
    this->coeff_a = strtod(json["coeff_a" ], NULL);
    this->coeff_b = strtod(json["coeff_b" ], NULL);
    this->coeff_c = strtod(json["coeff_c" ], NULL);
    this->coeff_d = strtod(json["coeff_d" ], NULL);
    this->coeff_e = strtod(json["coeff_e" ], NULL);

    delete buf;
    configFile.close();
    return true;
}

bool ConfigManager::save()
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["ssid"] = this->ssid;
    json["pass"] = this->pass;
    json["api_key"] = this->api_key;
    json["email"] = this->email;
    json["firebase_password"] = this->firebase_password;
    json["database_url"] = this->database_url;
    json["sleep_time"] = this->sleep_time;
    json["coeff_a"] = this->coeff_a;
    json["coeff_b"] = this->coeff_b;
    json["coeff_c"] = this->coeff_c;
    json["coeff_d"] = this->coeff_d;
    json["coeff_e"] = this->coeff_e;
    
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      return false;
    }
    json.printTo(configFile);
    configFile.close();
    return true; 
}

bool ConfigManager::is_device_configured()
{
    return ((this->ssid[0] != '\0')             &&
           (this->pass[0] != '\0')              &&
           (this->email[0] != '\0')             &&
           (this->firebase_password[0] != '\0') &&
           (this->api_key[0] != '\0')           &&
           (this->database_url[0] != '\0'));
}

void ConfigManager::get(setting setting, char *&buf)
{
    switch (setting)
    {
    case WIFI_PASSWOWRD:    buf = this->pass; break;
    case WIFI_SSID:         buf = this->ssid; break;
    case EMAIL:             buf = this->email; break;
    case FIREBASE_PASSWORD: buf = this->firebase_password; break;
    case API_KEY:           buf = this->api_key; break;
    case DATABASE_URL:      buf = this->database_url; break;
    default: 
        break;
    }
}

void ConfigManager::get(setting setting, uint64_t *buf)
{
    switch (setting)
    {
    case SLEEP_TIME:
        *buf = this->sleep_time; break;
    default: 
        break;
    }
}

void ConfigManager::get(setting setting, double *buf)
{
    switch (setting)
    {
    case COEFFICIENT_A:     *buf = this->coeff_a; break;
    case COEFFICIENT_B:     *buf = this->coeff_b; break;
    case COEFFICIENT_C:     *buf = this->coeff_c; break;
    case COEFFICIENT_D:     *buf = this->coeff_d; break;
    case COEFFICIENT_E:     *buf = this->coeff_e; break;
    default:
        break;
    }
}

void ConfigManager::set(setting setting, const char *cfg)
{
    switch (setting)
    {
    case WIFI_PASSWOWRD:    strcpy(this->pass, cfg); break;
    case WIFI_SSID:         strcpy(this->ssid, cfg); break;
    case EMAIL:             strcpy(this->email, cfg); break;
    case FIREBASE_PASSWORD: strcpy(this->firebase_password, cfg); break;
    case API_KEY:           strcpy(this->api_key, cfg); break;
    case DATABASE_URL:      strcpy(this->database_url, cfg); break;
    default: 
        break;
    }
}

void ConfigManager::set(setting setting, uint64_t buf)
{
    switch (setting)
    {
    case SLEEP_TIME:
        this->sleep_time = buf; break;
    default:
        break;
    }
}

void ConfigManager::set(setting setting, double buf)
{
    switch (setting)
    {
    case COEFFICIENT_A:     this->coeff_a = buf; break;
    case COEFFICIENT_B:     this->coeff_b = buf; break;
    case COEFFICIENT_C:     this->coeff_c = buf; break;
    case COEFFICIENT_D:     this->coeff_d = buf; break;
    case COEFFICIENT_E:     this->coeff_e = buf; break;
    default:
        break;
    }
}

ConfigManager ConfigManager::instance;
