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

    if (id(send_state).is_running())
    {
      continue;
    }

    id(send_state).execute();

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
  if (id(send_state).is_running())
  {
    id(send_state).stop();
  }

  vTaskDelete(svitlobot_handle);  // OTA: Avoid crash due to angry watchdog
  svitlobot_handle = nullptr;
}
