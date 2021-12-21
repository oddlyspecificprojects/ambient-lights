#include "ota_handle.h"
#include "config.h"

/**
 * @brief Callback function when OTA request is recevied
 * 
 */
static void cb_on_start()
{
	// TODO kill other tasks?
	if (ArduinoOTA.getCommand() == U_SPIFFS)
	{
		// TODO Add unmount of SPIFFS?
	}
	Serial.println("OTA Started");
}

/**
 * @brief Called on cleanup before reboot
 * 
 */
static void cb_on_end()
{
	// Nothing to do on end?
	Serial.println("OTA End");
}

/**
 * @brief Called every chunk of data is sent
 * 
 * @param progress how much data has been sent
 * @param total overall size
 */
static void cb_on_progress(uint progress, uint total)
{
	Serial.printf("%u / %u\r", progress, total);
}

/**
 * @brief Called whenever errors were encountered
 * 
 * @param error_num what error
 */
static void cb_on_error(ota_error_t error_num)
{
	Serial.printf("Error%d\r", error_num);
}

/**
 * @brief Setup OTA callbacks
 * 
 */
void ota_setup()
{
	ArduinoOTA.setHostname(OTA_HOSTNAME);
	ArduinoOTA.setPort(OTA_PORT);
	ArduinoOTA.onStart(cb_on_start);
	ArduinoOTA.onEnd(cb_on_end);
	ArduinoOTA.onProgress(cb_on_progress);
	ArduinoOTA.onError(cb_on_error);
	ArduinoOTA.begin();
}

/**
 * @brief Handle OTA loop
 * 
 */
void ota_loop()
{
	ArduinoOTA.handle();
}