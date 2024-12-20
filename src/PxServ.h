#ifndef PxServ_h
#define PxServ_h

#include <Arduino_JSON.h>
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

class PxServ
{
public:
    struct Callback
    {
        int status;
        String message;
        String data;
    };

    PxServ(String apiKey);
    Callback setData(String key, String value);
    Callback getData(String key);
    Callback removeData(String key);

private:
    String _apiKey;
};

#endif