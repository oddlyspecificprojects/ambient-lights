
#include "ota_handle.h"
#include "lights.h"

#include "creds.h"
#include "config.h"

ulong last_lights_update = 0;

void setup()
{
	Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASS);

	auto conn_res = WiFi.waitForConnectResult();
	if (conn_res != WL_CONNECTED)
	{
		Serial.println(conn_res);
		delay(10000);
		ESP.restart();
	}
	Serial.println(WiFi.localIP());
	ota_setup();
    delay( 3000 ); // power-up safety delay
	lights_setup();
	last_lights_update = millis();
}


void loop()
{
	ota_loop();
	if ((millis() - last_lights_update) > LIGHTS_PERIOD)
	{
		last_lights_update = millis();
		lights_loop();
	}	
}