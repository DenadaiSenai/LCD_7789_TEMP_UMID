#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
float temp = 0;
float hum = 0;
float pretemp = 0;
float prehum = 0;
float currtemp = 50;
float currhum = 100;
float i = 0;
float j = 0;

void setup(void) {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486;  // write-only shield
  tft.begin(ID);
  tft.setRotation(1);  //PORTRAIT
  tft.fillScreen(BLACK);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(2);
  // testing();
  tft.setTextSize(2);
  tft.setCursor(15, 240);
  tft.setTextColor(GREEN, BLACK);
  tft.print("Teach Me Something");
  // delay(1000);
  tft.fillScreen(BLACK);
  tft.setTextColor(GREEN, BLACK);
  tft.setCursor(55, 180);
  tft.print("0");
  tft.setCursor(85, 180);
  tft.print("50");
  tft.setCursor(55, 120);
  tft.print("TEMP");
  tft.setTextColor(WHITE, BLACK);
  tft.setCursor(215, 180);
  tft.print("0");
  tft.setCursor(237, 180);
  tft.print("100");
  tft.setCursor(193, 120);
  tft.print("Humidity");
  tft.setCursor(30, 5);
  tft.fillRect(0, 0, 320, 45, BLACK);
  tft.setTextColor(YELLOW, BLACK);
  tft.print("Temperature & Humidity");
  tft.setCursor(120, 25);
  tft.print("Monitor");
  tft.setTextColor(WHITE, BLACK);
}


void loop(void) {
  tft.fillRect(55, 150, 60, 20, BLACK);
  tft.fillRect(212, 150, 60, 20, BLACK);
  tft.setCursor(55, 150);
  tft.print(temp);
  tft.setCursor(212, 150);
  tft.print(hum);
  i = map(pretemp, 0, 50, 0, 300);
  j = map(currtemp, 0, 50, 0, 300);
  for (i; i <= j; i = i + 0.1) {
    float j = i - 150;
    float angle = (j / 57.2958) - 1.57;
    float x1 = 80 + cos(angle) * 55;
    float y1 = 130 + sin(angle) * 55;
    float x2 = 80 + cos(angle) * 75;
    float y2 = 130 + sin(angle) * 75;
    tft.drawLine(x1, y1, x2, y2, GREEN);
  }
  i = map(pretemp, 0, 50, 0, 300);
  j = map(currtemp, 0, 50, 0, 300);
  for (i - 2; i >= j; i = i - 0.05) {
    float j = i - 150;
    float angle = (j / 57.2958) - 1.57;
    float x1 = 80 + cos(angle) * 55;
    float y1 = 130 + sin(angle) * 55;
    float x2 = 80 + cos(angle) * 75;
    float y2 = 130 + sin(angle) * 75;
    tft.drawLine(x1, y1, x2, y2, BLACK);
    // tft.drawLine(x1+160, y1,x2+160,y2, MAGENTA);
  }

  i = map(prehum, 0, 100, 0, 300);
  j = map(currhum, 0, 100, 0, 300);
  for (i; i <= j; i = i + 0.1) {
    float j = i - 150;
    float angle = (j / 57.2958) - 1.57;
    float x1 = 80 + cos(angle) * 55;
    float y1 = 130 + sin(angle) * 55;
    float x2 = 80 + cos(angle) * 75;
    float y2 = 130 + sin(angle) * 75;

    tft.drawLine(x1 + 160, y1, x2 + 160, y2, MAGENTA);
  }
  i = map(prehum, 0, 100, 0, 300);
  j = map(currhum, 0, 100, 0, 300);
  for (i - 2; i >= j; i = i - 0.05) {
    float j = i - 150;
    float angle = (j / 57.2958) - 1.57;
    float x1 = 80 + cos(angle) * 55;
    float y1 = 130 + sin(angle) * 55;
    float x2 = 80 + cos(angle) * 75;
    float y2 = 130 + sin(angle) * 75;

    tft.drawLine(x1 + 160, y1, x2 + 160, y2, BLACK);
  }

  pretemp = currtemp;
  prehum = currhum;

  temp = random(0, 50);
  hum = random(0, 100);
  Serial.println("TEMP:" + String(temp));
  Serial.println("Hum" + String(hum));
  currtemp = temp;
  currhum = hum;
  delay(1000);
}
