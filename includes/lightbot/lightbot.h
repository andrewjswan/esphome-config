#pragma once

TaskHandle_t svitlobot_handle = nullptr;

// SvitloBot Main code
void svitlobot(void * parameter) 
{
  for(;;)
  {
    delay_microseconds_safe(60000000);

    if (!id(bot_wifi).is_connected())
    {
      continue;
    }

    if (!id(my_key).has_state())
    {
      continue;
    }

    HTTPClient http;
    WiFiClient client;
    if (http.begin(client, ("https://api.svitlobot.in.ua/channelPing?channel_key=" + id(my_key).state).c_str()))
    {
      int start = millis();
      int httpResponseCode = http.GET();
      int end = millis();
      if (httpResponseCode == HTTP_CODE_OK)
      {
        ESP_LOGD("SvitloBot", "Send status - success (%dms)", end - start);
        id(send_status).publish_state(true);
        id(ok)++;
      }
      else
      {
        ESP_LOGD("SvitloBot", "Send status - not success with response code: %d - %s", httpResponseCode, http.errorToString(httpResponseCode).c_str());
        id(send_status).publish_state(false);
        id(error)++;
      }
      id(quality).update();
    }
    else
    {
      ESP_LOGD("SvitloBot", "Connect failed...");
    }
    http.end();
  } // for(;;)
} // svitlobot()

// SvitloBot Init
void svitlobot_init()
{
  xTaskCreate(
    svitlobot,                    // Function to implement the task
    "SvitloBot",                  // Name of the task
    5000,                         // Stack size in words
    NULL,                         // Task input parameter
    1,                            // Priority of the task
    &svitlobot_handle);           // Task handle
}

// SvitloBot Stop
void svitlobot_stop()
{
  vTaskDelete(svitlobot_handle);  // OTA: Avoid crash due to angry watchdog
  svitlobot_handle = nullptr;
}
