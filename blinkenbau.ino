#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>

#define MIC_PIN A0
#define LED_PIN 7

#define NUM_LEDS 38
#define BOTTOM_LED 11

CRGB leds[NUM_LEDS];

/*
const int readnum = 500;
int readindex = 0;
int readmin;
int readmax;
const int commitnum = 25;
int commitindex = 0;
int commitmin[commitnum];
int commitmax[commitnum];
*/

int dummyval = 0;
bool dummyup = true;

void setup() {
  Serial.begin(57600);
  
  LEDS.addLeds<WS2812,LED_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(255);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(180); } }

/*
int getcommitminavg() {
  int avg = 0;
  for(int i = 0; i < commitnum; i++) {
    avg = (avg + commitmin[i]) / 2;
  }
  return avg;
}
int getcommitmaxavg() {
  int avg = 0;
  for(int i = 0; i < commitnum; i++) {
    avg = (avg + commitmax[i]) / 2;
  }
  return avg;
}
*/

void loop() {
//Rotating

  for(int i = 0; i < NUM_LEDS/2 ; i++) {
    leds[i] = CRGB(255, 255, 255);
    leds[(NUM_LEDS/2)+i] = CRGB(0, 255, 0);
    FastLED.show(); 
    fadeall();

  int value = analogRead(MIC_PIN);
  int temp = map(value, 0, 1024, 1, 5);
  int ledvalue = map(temp, 1, 5, 25, 55);
    
    delay(ledvalue);
  }

/*
  if (dummyup) {
    dummyval++;
  } else {
    dummyval--;
  }

  if (dummyval == 0 || dummyval == 1020) {
    dummyup = !dummyup;
  }
  */
  /*if(readindex == 0) {
    //Serial.println("roll it");
    readmin = readmax = analogRead(MIC_PIN);
    readindex++;
  } else if(readindex <= readnum) {
    int readnow = analogRead(MIC_PIN);
    readmin = min(readmin, readnow);
    readmax = max(readmax, readnow);
    readindex++;
  } else if (readindex >= readnum) {
    commitmin[commitindex] = readmin -50;
    commitmax[commitindex] = readmax +50;
    readindex = 0;

    int minavg = getcommitminavg();
    int maxavg = getcommitmaxavg();

    Serial.print(commitindex);
    Serial.print(",");
    Serial.print(commitmin[commitindex]);
    Serial.print(",");
    Serial.print(commitmax[commitindex]);
    Serial.print(",");
    Serial.print(minavg);
    Serial.print(",");
    Serial.print(maxavg);
    Serial.print(",");
    Serial.print((minavg + maxavg) / 2);
    Serial.print(",");
    Serial.print(maxavg - minavg);
    Serial.println();

    commitindex++;
    if (commitindex >= commitnum) {
      commitindex = 0;
    }
  }*/
  
  /*
// current state
  int value = analogRead(MIC_PIN);//dummyval;
  int ledvalue = map(value, 200, 900, 0, NUM_LEDS/2);

  Serial.println(value);

  int ledforceone, ledforcetwo;
  ledforceone = BOTTOM_LED+1;
  ledforcetwo = BOTTOM_LED;
  
  for(int i = 0; i <= ledvalue; i++) {
    leds[ledforceone] = CRGB(0, 255, 0);
    leds[ledforcetwo] = CRGB(0, 255, 0);

    if(ledforceone != NUM_LEDS - 1) {
      ledforceone++;
    } else {
      ledforceone = 0;
    }

    if(ledforcetwo != 0) {
      ledforcetwo--;
    } else {
      ledforcetwo = NUM_LEDS - 1;
    }
  }

  FastLED.show();
  fadeall();*/
}
