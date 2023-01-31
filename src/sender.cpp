/**
 * @file sender.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2023-01-11
 */

//--------------------------------------------------------------------------------

#include <sender.h>

//--------------------------------------------------------------------------------

Sender::Sender()
{
    database = new FB_RTDB;
    fbdo = new FirebaseData;
    auth = new FirebaseAuth;
    fb_config = new FirebaseConfig;
#if LOG_DEBUG == LOG_WIFI
    is_path = false;
#endif
}

Sender::~Sender()
{
    delete database;
    delete fbdo;
    delete auth;
    delete fb_config;
#if LOG_DEBUG == LOG_WIFI
    if (log_buf != nullptr)
        delete log_buf;
#endif
}

Sender& Sender::get_instance()
{
  return instance;
}

void Sender::init()
{
    ConfigManager& config = ConfigManager::get_instance();

    if (!WiFi.isConnected() || !config.is_device_configured())
    {
        LOG("[SENDER] Initialization failed!");
        initialized = false;
        return;
    }

    config.get(API_KEY, this->api_key);
    config.get(EMAIL, this->email);
    config.get(FIREBASE_PASSWORD, this->password);
    config.get(DATABASE_URL, this->database_url);

    fb_config->api_key = this->api_key;
    auth->user.email = this->email;
    auth->user.password = this->password;
    fb_config->database_url = this->database_url;
    fbdo->setResponseSize(4096);
    Firebase.RTDB.setMaxRetry(fbdo, 5);
    Firebase.reconnectWiFi(true);
    Firebase.begin(fb_config, auth);

    unsigned long ms = millis();
    while ((auth->token.uid) == "") 
    {
        delay(300);
        if (millis() - ms >= 5000)
        {
            LOG("[SENDER] Getting User UID timeout!");
            initialized = false;
            return;
        }
    }

    String uid = auth->token.uid.c_str();
    this->database_path = "UsersData/" + uid + "/readings";
#if LOG_DEBUG == LOG_WIFI
    this->log_path = "UsersData/" + uid + "/logs/";
#endif
    this->initialized = true;
    LOG("[SENDER] Firebase sender : successful initialization.");
}

void Sender::send_data(data *measurement)
{
    ConfigManager& config = ConfigManager::get_instance();
    bool status = true;

    if(data_waiting_to_sent())
    {
        std::vector <data> data_vector;
        uint64_t time_interval;
        time_t time;

        this->parse_data_files(&data_vector);
        config.get(SLEEP_TIME, &time_interval);
        time = get_time_since_epoch() - ((time_interval / 1000000) * (data_vector.size()));

        for (data it : data_vector)
        {
            status &= this->send_temperature(it.temperature)         &&
                      this->send_battery_voltage(it.battery_voltage) &&
                      this->send_plato(it.plato)                     &&
                      this->send_time(time);

            time += (time_interval / 1000000);
        }
    }

    status &= this->send_temperature(measurement->temperature)          &&
              this->send_battery_voltage(measurement->battery_voltage)  &&
              this->send_plato(measurement->plato)                      &&
              this->send_time();

    LOG("[SENDER] Data sent" + String(status ? " successfully." : " unsuccessfully."));
}

bool Sender::data_waiting_to_sent()
{
    return LittleFS.exists("/data/0.txt");
}

void Sender::save_data(data &measurement)
{
    char file_path[16];
    uint32_t number_of_files = 0;
    Dir dir = LittleFS.openDir("/data");

    while(dir.next())
        number_of_files++;

    if (number_of_files >= SENDER_DATA_FILES_MAX)
    {
        Serial.println("[SENDER] Max files");
        return;
    }

    sprintf(file_path, "/data/%hd.txt", number_of_files);

    File data_file = LittleFS.open(file_path, "w");
    data_file.write((byte *)&measurement, sizeof(measurement));
    data_file.close();
}

void Sender::parse_data_files(std::vector <data> *data_vector)
{
    data temp;
    Dir dir = LittleFS.openDir("/data");
    
    while(dir.next())
    {
        File data_file = dir.openFile("r");
        data_file.read((byte *)&temp, sizeof(temp));
        data_vector->push_back(temp);
        data_file.close();
        LittleFS.remove("/data/" + String(dir.fileName()));
    }
}

bool Sender::send_temperature(float temperature)
{
    if (!this->initialized)
        init();

    if (!Firebase.ready())
    {
        LOG("[SENDER] Firebase is not ready!");
        return false;
    }

    this->parent_path = this->database_path + "/temperature";
    if (database->pushFloatAsync(fbdo, parent_path, temperature))
        return true;
    else
    {
        LOG("[SENDER] Temperature send failed, reason: " + fbdo->errorReason());
        return false;
    }
}

bool Sender::send_plato(float plato)
{
    if (!this->initialized)
        init();

    if (!Firebase.ready())
    {
        LOG("[SENDER] Firebase is not ready!");
        return false;
    }

    this->parent_path = this->database_path + "/plato";
    if (database->pushFloatAsync(fbdo, parent_path, plato))
        return true;
    else
    {
        LOG("[SENDER] Plato send failed, reason: " + fbdo->errorReason());
        return false;
    }
}

bool Sender::send_time(time_t time)
{
    if (time == 0)
        return false;

    if (!this->initialized)
        init();

    if (!Firebase.ready())
    {
        LOG("[SENDER] Firebase is not ready!");
        return false;
    }
        
    this->parent_path = this->database_path + "/time";
    if (database->pushFloatAsync(fbdo, parent_path, time))
        return true;
    else
    {
        LOG("[SENDER] Time send failed, reason: " + fbdo->errorReason());
        return false;
    }
}

bool Sender::send_time()
{
    if (!this->initialized)
        init();

    if (!Firebase.ready())
    {
        LOG("[SENDER] Firebase is not ready!");
        return false;
    }

    time_t time = get_time_since_epoch();
    if (time == 0)
    {
        LOG("[SENDER] The time value cannot be retrieved.");
        return false;
    }

    this->parent_path = this->database_path + "/time";
    if (database->pushIntAsync(fbdo, parent_path, time))
        return true;
    else
    {
        LOG("[SENDER] Time send failed, reason: " + fbdo->errorReason());
        return false;
    }
}

bool Sender::send_battery_voltage(float voltage)
{
    if (!this->initialized)
        init();

    if (!Firebase.ready())
    {
        LOG("[SENDER] Firebase is not ready!");
        return false;
    }

    parent_path = database_path + "/voltage";
    if (database->pushFloatAsync(fbdo, parent_path, voltage))
        return true;
    else
    {
        LOG("[SENDER] Voltage send failed, reason: " + fbdo->errorReason());
        return false;
    }
}

#if LOG_DEBUG == LOG_WIFI
void Sender::send_message_log(const String &log)
{
    if (!Firebase.ready() || log_path.isEmpty())
    {
        if (log_buf == nullptr)
            log_buf = new FirebaseJsonArray;

        is_path = false;
        log_buf->add(log);
        return;
    }
    
    if (!is_path)
    {
        log_path += get_utc_time_format_();
        is_path = true;
    }

    log_buf->add(log);
    database->setArray(fbdo, log_path, log_buf);
}
#endif

Sender Sender::instance;