/***
 *       ____   _____
 *    U /"___|u|"_  /u
 *    \| |  _ /U / //
 *     | |_| | \/ /_
 *      \____| /____|
 *      _)(|_  _//<<,-
 *     (__)__)(__) (_/
 */
// -----------------------------------------------------------------------------
// Soft access point
// -----------------------------------------------------------------------------
//libraries
#include <ESP8266WiFi.h>

//create credentials.h file in src folder with ssid and pass formated like:
// const char* esp_ssid = "your ssid";
// const char* esp_password = "your password";
#include "credentials.h"  //ignored by git

// -----------------------------------------------------------------------------
#define FIRMWARE_VERSION "1.0.1"  //MAJOR.MINOR.PATCH more info on: http://semver.org

/* Set these to your desired network parameters, credentials in separate file  */
IPAddress esp_IP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress mask(255,255,255,0);

// PRODUCTION, remove comments below to stop serial debuging
//#define PRODUCTION_SERIAL true
#define SERIAL_SPEED 115200
//------------------------------------------------------------------------------

extern "C" {
#include "user_interface.h"  //NOTE needed for esp info
}

void setup()
{
  // Initialize the Serial (debuging use only, not need in production)
  #ifndef PRODUCTION_SERIAL // Not in PRODUCTION
          Serial.begin(SERIAL_SPEED);
  // compiling and esp info
          Serial.println("\r\n---------------------------------------"); //NOTE \r\n - new line, return
          Serial.println("Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__);
          Serial.print("Version: "); Serial.print(FIRMWARE_VERSION); Serial.println("       by Grzegorz Zajac");
          Serial.println("---------------------------------------");
          Serial.print( F("\r\n--- ESP Info --- ") );
          Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size()); //IDEA add code size and free ram info
          Serial.print( F("Boot Vers: ") ); Serial.println(system_get_boot_version());
          Serial.print( F("CPU: ") ); Serial.println(system_get_cpu_freq());
          Serial.print( F("SDK: ") ); Serial.println(system_get_sdk_version());
          Serial.print( F("Chip ID: ") ); Serial.println(system_get_chip_id());
          Serial.print( F("Flash ID: ") ); Serial.println(spi_flash_get_id());
          Serial.print( F("Flash Size: ") ); Serial.println(ESP.getFlashChipRealSize());
          Serial.print( F("Vcc: ") ); Serial.println(ESP.getVcc());
          Serial.println();
  #endif

  #ifndef PRODUCTION_SERIAL // Not in PRODUCTION
    Serial.print("\r\Setting up access point for wifi network ... ");
  #endif
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(esp_IP, gateway, mask);

  /***
  WiFi.softAP(ssid, password, channel, hidden)
  ssid - character string containing network SSID (max. 63 characters)
  password - optional character string with a password. For WPA2-PSK network it should be at least 8 character long. If not specified, the access point will be open for anybody to connect.
  channel - optional parameter to set Wi-Fi channel, from 1 to 13. Default channel = 1.
  hidden - optional parameter, if set to true will hide SSID
  ***/

  boolean result = WiFi.softAP(esp_ssid, esp_password);
  if(result == true)
  {
    #ifndef PRODUCTION_SERIAL // Not in PRODUCTION
      Serial.println("Ready");
    #endif
  }
  else
  {
    #ifndef PRODUCTION_SERIAL // Not in PRODUCTION
      Serial.println("Failed!");  //TODO led status?
    #endif
  }

  #ifndef PRODUCTION_SERIAL // Not in PRODUCTION
    IPAddress accessIP = WiFi.softAPIP();
    Serial.print("ESP AccessPoint IP address: ");
    Serial.println(accessIP);
  #endif

}

void loop()
{
  #ifndef PRODUCTION_SERIAL // Not in PRODUCTION
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
  #endif
}
