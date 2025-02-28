#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <DHT.h>

#define TFT_CS     10
#define TFT_RST    9  // optional
#define TFT_DC     8
#define DHT_PIN    7
#define DHT_TYPE   DHT22

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  
  tft.initR(INITR_BLACKTAB);  // Initialisiere das Display
  tft.setRotation(1);          // Display-Rotation einstellen (je nach Ausrichtung des Displays)
  
  dht.begin();  // Starte den DHT-Sensor
  
  tft.fillScreen(ST7735_BLACK); // Displayhintergrund Schwarz setzen
  
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 10);
  tft.println("Temp:");
  tft.setCursor(10, 60);
  tft.println("Hum:");
}

void loop() {
  // Sensordaten lesen
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Daten auf dem Display anzeigen
  tft.setTextSize(3); // Textgröße für Luftfeuchtigkeit reduziert

  tft.fillRect(30, 25, 80, 40, ST7735_BLACK); // Alten Temperaturwert löschen
  tft.setCursor(30, 25);
  tft.setTextColor(ST7735_GREEN);
  tft.print(temperature);
  tft.println(" C");

  tft.fillRect(30, 80, 80, 30, ST7735_BLACK); // Alten Luftfeuchtigkeitswert löschen
  tft.setCursor(30, 80);
  tft.setTextColor(ST7735_BLUE);
  tft.print(humidity);
  tft.println(" %");

  delay(2000); // Pause zwischen den Messungen
}
