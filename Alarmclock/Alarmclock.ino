

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int starttime;
int activetime;
int prevoustime = 0;

int hours = 0;
int mins = 0;
int secs = 0;

int ahours = 0;
int amins = 0;

void setup() {
 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();

  Serial.begin(9600);

  pinMode(13, INPUT_PULLUP); // time mode
  pinMode(11, INPUT_PULLUP); // min
  pinMode(10, INPUT_PULLUP); // hr
  pinMode(8, INPUT_PULLUP);  //alarm mode
  
  pinMode(9, OUTPUT);
  starttime = millis() / 1000;
}

void loop() {
  while (digitalRead(8) == LOW) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(40, 0);  
    display.print("Alarm Clock");
    display.setCursor(10, 20); 

    if (digitalRead(11) == LOW) {
      amins++;
    } else if (digitalRead(10) == LOW) {
      ahours++;
    }

    if (ahours < 10) {
      display.print("0");
      display.print(ahours);
    } else {
      display.print(ahours);
    }

    display.print(":");

    if (amins < 10) {
      display.print("0");
      display.print(amins);
    } else {
      display.print(amins);
    }

    display.print(":00"); 

    display.setCursor(30, 40);  
    display.print("Alarm Mode");

    if (amins > 59) {
      ahours++;
      amins = 0;
    }
    if (ahours > 23) {
      ahours = 0;
    }

    display.display();
    delay(500);
  }

  if (digitalRead(13) == LOW) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(40, 0);  
    display.print("Alarm Clock");
    display.setCursor(10, 20); 

    if (digitalRead(11) == LOW) {
      mins++;
    } else if (digitalRead(10) == LOW) {
      hours++;
    }

    display.display();
  }

  activetime = (millis() / 1000) - starttime;
  secs = activetime % 60;
  if (prevoustime < (activetime - 59)) {
    mins++;
    prevoustime = activetime;
  }

  if (mins > 59) {
    hours++;
    mins = 0;
  }

  if (hours > 23) {
    hours = 0;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 0);  
  display.print("Alarm Clock");
  display.setCursor(10, 20); 

  if (hours < 10) {
    display.print("0");
    display.print(hours);
  } else {
    display.print(hours);
  }

  display.print(":");

  if (mins < 10) {
    display.print("0");
    display.print(mins);
  } else {
    display.print(mins);
  }

  display.print(":");

  if (secs < 10) {
    display.print("0");
    display.print(secs);
  } else {
    display.print(secs);
  }

  display.display();

  if (ahours == hours && amins == mins && amins != 0) {
    tone(9, 1000, 200);
    delay(200);
    noTone(9);
    delay(200);
  } else {
    delay(300);
  }

  Serial.println(mins);
  Serial.println(hours);
  Serial.println("");
  Serial.println(amins);
  Serial.println(ahours);
  Serial.println("");
  Serial.println(activetime);
  Serial.println(prevoustime);
  Serial.println(starttime);
  Serial.println("");
}
