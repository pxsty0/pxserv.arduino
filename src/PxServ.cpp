#include "PxServ.h"

PxServ::PxServ(String apiKey)
{
    _apiKey = apiKey;
}

void PxServ::connectWifi(String ssid, String password)
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("[PxServ] Connecting to WiFi...");
    }

    Serial.println("[PxServ] Connected to WiFi");
}

PxServ::Callback PxServ::setData(String key, String value)
{
    WiFiClientSecure *client = new WiFiClientSecure;
    Callback callback;

    callback.status = -1;
    callback.message = "failed to send request";
    callback.data = "";

    if (client)
    {
        client->setInsecure();

        HTTPClient https;

        if (https.begin(*client, "https://api.pxserv.net/database/setData"))
        {
            https.addHeader("Content-Type", "application/json");
            https.addHeader("apikey", _apiKey);

            StaticJsonDocument<512> body;
            body["key"] = key;
            body["value"] = value;
            String bodyStr;
            serializeJson(body, bodyStr);

            int httpCode = https.POST(bodyStr);
            if (httpCode > 0)
            {
                String payload = https.getString();
                DynamicJsonDocument result(payload.length() + 256);
                DeserializationError error = deserializeJson(result, payload);

                if (error || !result.is<JsonObject>())
                {
                    callback.status = 400;
                    callback.message = "Response format not appropriate";
                }
                else
                {
                    callback.status = result["status"].as<int>();
                    callback.message = result["message"].as<String>();
                }

                https.end();
            }
        }
    }

    delete client;
    return callback;
}

PxServ::Callback PxServ::toggleData(String key)
{
    WiFiClientSecure *client = new WiFiClientSecure;
    Callback callback;

    callback.status = -1;
    callback.message = "failed to send request";
    callback.data = "";

    if (client)
    {
        client->setInsecure();

        HTTPClient https;

        if (https.begin(*client, "https://api.pxserv.net/database/toggleData"))
        {
            https.addHeader("Content-Type", "application/json");
            https.addHeader("apikey", _apiKey);

            StaticJsonDocument<256> body;
            body["key"] = key;
            String bodyStr;
            serializeJson(body, bodyStr);

            int httpCode = https.POST(bodyStr);
            if (httpCode > 0)
            {
                String payload = https.getString();
                DynamicJsonDocument result(payload.length() + 256);
                DeserializationError error = deserializeJson(result, payload);

                if (error || !result.is<JsonObject>())
                {
                    callback.status = 400;
                    callback.message = "Response format not appropriate";
                }
                else
                {
                    callback.status = result["status"].as<int>();
                    callback.message = result["message"].as<String>();
                }

                https.end();
            }
        }
    }

    delete client;
    return callback;
}

PxServ::Callback PxServ::getData(String key)
{
    WiFiClientSecure *client = new WiFiClientSecure;
    Callback callback;

    callback.status = -1;
    callback.message = "failed to send request";
    callback.data = "";

    if (client)
    {
        client->setInsecure();

        HTTPClient https;

        if (https.begin(*client, "https://api.pxserv.net/database/getData"))
        {
            https.addHeader("Content-Type", "application/json");
            https.addHeader("apikey", _apiKey);

            StaticJsonDocument<256> body;
            body["key"] = key;
            String bodyStr;
            serializeJson(body, bodyStr);

            int httpCode = https.POST(bodyStr);
            if (httpCode > 0)
            {
                String payload = https.getString();
                DynamicJsonDocument result(payload.length() + 256);
                DeserializationError error = deserializeJson(result, payload);

                if (error || !result.is<JsonObject>())
                {
                    callback.status = 400;
                    callback.message = "Response format not appropriate";
                }
                else
                {
                    int status = result["status"].as<int>();
                    String message = result["message"].as<String>();

                    if (status == 200)
                    {
                        callback.data = result["data"]["value"].as<String>();
                    }

                    callback.status = status;
                    callback.message = message;
                }

                https.end();
            }
        }
    }

    delete client;
    return callback;
}

PxServ::Callback PxServ::removeData(String key)
{
    WiFiClientSecure *client = new WiFiClientSecure;
    Callback callback;

    callback.status = -1;
    callback.message = "failed to send request";
    callback.data = "";

    if (client)
    {
        client->setInsecure();

        HTTPClient https;

        if (https.begin(*client, "https://api.pxserv.net/database/removeData"))
        {
            https.addHeader("Content-Type", "application/json");
            https.addHeader("apikey", _apiKey);

            StaticJsonDocument<256> body;
            body["key"] = key;
            String bodyStr;
            serializeJson(body, bodyStr);

            int httpCode = https.POST(bodyStr);
            if (httpCode > 0)
            {
                String payload = https.getString();
                DynamicJsonDocument result(payload.length() + 256);
                DeserializationError error = deserializeJson(result, payload);

                if (error || !result.is<JsonObject>())
                {
                    callback.status = 400;
                    callback.message = "Response format not appropriate";
                }
                else
                {
                    callback.status = result["status"].as<int>();
                    callback.message = result["message"].as<String>();
                }

                https.end();
            }
        }
    }

    delete client;
    return callback;
}
