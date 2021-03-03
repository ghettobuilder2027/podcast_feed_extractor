#include "Arduino.h"
#include <WiFi.h>              
#include <HTTPClient.h>


const char* ssid     = "Freebox-1BF387";
const char* password = "reformator*-adaquemus2-vineias-saporata29";
 

String mp3_from_rss ( String rssUrl) {

  HTTPClient http;
  String mp3;
  Serial.println(rssUrl);
  http.begin(rssUrl);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String rss;
      rss=http.getString();
      mp3 = rss.substring(rss.indexOf("<enclosure url=")+16,rss.indexOf("length=")-2);
      Serial.println(mp3);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    mp3 ="";
  }
  http.end();
  return mp3;
}




void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  String url1 = "http://radiofrance-podcast.net/podcast09/rss_10241.xml";
  String url2 = "http://feeds.djpod.com/upcast";
  String url3 = "http://radiofrance-podcast.net/podcast09/rss_14007.xml";
  mp3_from_rss (url1);
  mp3_from_rss (url2);
  mp3_from_rss (url3);
  
}


void loop() {
}
