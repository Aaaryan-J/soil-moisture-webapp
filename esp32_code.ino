#include <WiFi.h>
#include <HTTPClient.h>

const char* scriptURL = "https://script.google.com/macros/s/AKfycbxvQm6XL1bY1cTnODpYPkq3SBQGanmC6chraO_cd9LNI_jlEeOSqPwAbnEOs1ikwTV6tg/exec";  
const char* ssid = "hp";      
const char* password = "12345678";  

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) { // Prevent infinite loop
        delay(1000);
        Serial.println("Connecting to WiFi...");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to WiFi");
    } else {
        Serial.println("Failed to connect to WiFi. Check credentials!");
    }
}

void loop() {
    int moistureValue = analogRead(34);  

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String fullURL = String(scriptURL) + "?moisture=" + String(moistureValue);

        http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
        http.begin(fullURL);

        String postData = "{\"moisture\":" + String(moistureValue) + "}";

http.begin(scriptURL);
http.addHeader("Content-Type", "application/json");
int httpResponseCode = http.POST(postData);


    //2900 and above means DRY
    //~900 means Wettest = to water

    //2400 above needs water immediatley
    //2100 needs water
    //1700-1900 and above means will need water after sometime
    //1500 above wet but could be better
    //1200-1400 best does'nt need water

        Serial.print("Server Response: ");
        Serial.println(httpResponseCode);
        Serial.print("Sending request: ");
        Serial.println(fullURL);


        http.end();
    } else {
        Serial.println("WiFi Disconnected! Retrying...");
    }

    delay(500); 
}
