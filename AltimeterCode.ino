/*   
To measure maximum altitude and display on LCD screen
- use to attach to projectile and see how high it goes
- displays max height, initial height, difference in initial/max height
*/ 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();
float high = 0;
float initial = 0;
float diff=0;
// Power by connecting Vin to 3-5V, GND to GND
// Uses I2C - connect SCL to the SCL pin, SDA to SDA pin


void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit_MPL3115A2 test!");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  baro.begin();
  float altm = baro.getAltitude();
  initial = altm; //update variable to store only the initial value
  Serial.print("Initial:");
  Serial.println(initial);
}

void loop() {
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  float altm = baro.getAltitude();
  if (altm > high){
    high = altm;
  }
  //set up screen and display the alues
  display.setTextSize(3);
  display.println(high);
  display.setTextSize(2);
  diff = high - initial;
  display.setTextSize(2);
  display.println("~~ QFI ~~ ");
  display.setTextSize(1);
  display.print("initial: ");
  display.println(initial);
  display.print("diff: ");
  display.println(diff);
  display.display();
  Serial.print(altm); Serial.println("   meters\t");
  display.clearDisplay();
  delay(100);
 }
