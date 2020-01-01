////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!
////////////////////////////////////////////////////////////////////DO NOT EXPERIMENT!! UPLOAD ONLY!!!!!!!!!!!!!!

#include <FastLED.h>   
#define NUM_LEDS 46   
#define DATA_PIN_1 8
#define DATA_PIN_2 9
#define DATA_PIN_3 10
#define DATA_PIN_4 11
#define COLOR_ORDER RGB
#define BRIGHTNESS 255
CRGB leds[NUM_LEDS];

int currentMode = 0;    
int modeChangePin = 13;
int changeWaitTime = 1000;  

unsigned long buttonCurrentMillis = 0;    
unsigned long buttonPreviousMillis = 0;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;
int redPot = A3;
int greenPot = A4;
int bluePot = A5;

int micPin = A0;
int micValue = 0;
int peakToPeak = 0;
int sampleMax = 0;
int sampleMin = 1024;
unsigned long sampleTime = 50;
unsigned long musicCurrentMillis = 0;
unsigned long musicPreviousMillis = 0;
int micLights = 0;
int musicRedValue = 0;
int musicGreenValue = 0;
int musicBlueValue = 0;

int cometLead = 0;
int cometDirection = 1;
unsigned long cometCurrentMillis = 0;
unsigned long cometPreviousMillis = 0;

int pulseBrightness = 0;
int pulseDirection = 1;
unsigned long pulseCurrentMillis = 0;
unsigned long pulsePreviousMillis = 0;
int pulseWaitTime = 20;
int pulseRedValue = 0;
int pulseGreenValue = 0;
int pulseBlueValue = 0;

int firePause = 50;
unsigned long fireCurrentMillis = 0;
unsigned long firePreviousMillis = 0;
CRGBPalette16 gPal;

int seasonPotValue = 0;
int season = 0;
int previousSeason = 0;
unsigned long seasonCurrentMillis = 0;
unsigned long seasonPreviousMillis = 0;
int seasonCurrentTime = 0;
int seasonBrightness = 0;
int seasonCurrentColor = 0;
int seasonRedValue = 0;
int seasonGreenValue = 0;
int seasonBlueValue = 0;
int hasBeenRunning = 0;



void setup() {                                           
  //Telling the FastLED library the type of LEDs
  FastLED.addLeds<WS2812B, DATA_PIN_1>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, DATA_PIN_2>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, DATA_PIN_3>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, DATA_PIN_4>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  gPal = HeatColors_p;
  pinMode(modeChangePin, INPUT);
  pinMode(micPin, INPUT);
  pinMode(redPot, INPUT);
  pinMode(greenPot, INPUT);
  pinMode(bluePot, INPUT);
  //Serial.begin(9600);
  for (int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void loop() {
  redValue = analogRead(redPot) / 4;
  greenValue = analogRead(greenPot) / 4;
  blueValue = analogRead(bluePot) / 4;
  buttonCurrentMillis = millis();
  if (digitalRead(modeChangePin) == HIGH && buttonCurrentMillis - buttonPreviousMillis >= changeWaitTime) {
    currentMode++;
    if (currentMode > 6) {
      currentMode = 0;                                   
    }                                                    
    Serial.print("Mode ");
    Serial.println(currentMode);
    buttonPreviousMillis = buttonCurrentMillis;
  }

  switch (currentMode) {                                

    case 0:
      fireCurrentMillis = millis();
      if (fireCurrentMillis - firePreviousMillis >= firePause) {
        random16_add_entropy(random());
        Fire2012WithPalette();
        FastLED.show();
        firePreviousMillis = fireCurrentMillis;
      }
      break;

    
    case 1:  
      for (int dot = 0; dot < NUM_LEDS; dot++) {
        leds[dot] = CRGB(greenValue, redValue, blueValue);
      }
      FastLED.show();
      break;


    case 2:
      cometCurrentMillis = millis();
      if (cometLead == 0) {
        cometDirection = 1;
      } else if (cometLead == NUM_LEDS - 1) {
        cometDirection = 0;
      }
      if (cometDirection == 1 && cometCurrentMillis - cometPreviousMillis >= 75) {
        leds[cometLead] = CRGB(greenValue, redValue, blueValue);
        FastLED.show();
        for (int dot = 0; dot < NUM_LEDS; dot++) {
          leds[dot].fadeToBlackBy(32);
        }
        cometPreviousMillis = cometCurrentMillis;
        cometLead++;
      }
      if (cometDirection == 0 && cometCurrentMillis - cometPreviousMillis >= 75) {
        leds[cometLead] = CRGB(greenValue, redValue, blueValue);
        FastLED.show();
        for (int dot = 0; dot < NUM_LEDS; dot++) {
          leds[dot].fadeToBlackBy(32);
        }
        cometPreviousMillis = cometCurrentMillis;
        cometLead--;
      }
      break;

    case 3:
      pulseCurrentMillis = millis();
      if (pulseBrightness == 0) {
        pulseDirection = 1;
      } else if (pulseBrightness == 125) {
        pulseDirection = 0;
      }
      pulseRedValue = map(redValue, 0, 125, 0, pulseBrightness);
      pulseGreenValue = map(greenValue, 0, 125, 0, pulseBrightness);
      pulseBlueValue = map(blueValue, 0, 125, 0, pulseBrightness);
      if (pulseDirection == 1 && pulseCurrentMillis - pulsePreviousMillis >= pulseWaitTime) {
        for (int dot = 0; dot < NUM_LEDS; dot++) {
          leds[dot] = CRGB(pulseGreenValue, pulseRedValue, pulseBlueValue);
        }
        FastLED.show();
        pulseBrightness++;
        pulsePreviousMillis = pulseCurrentMillis;
      }
      if (pulseDirection == 0 && pulseCurrentMillis - pulsePreviousMillis >= pulseWaitTime) {
        for (int dot = 0; dot < NUM_LEDS; dot++) {
          leds[dot] = CRGB(pulseGreenValue, pulseRedValue, pulseBlueValue);
        }
        FastLED.show();
        pulseBrightness--;
        pulsePreviousMillis = pulseCurrentMillis;
      }
      break;

    case 4:
      musicCurrentMillis = millis();
      micValue = analogRead(micPin);
      if (micValue < 1024) {
        if (micValue > sampleMax) {
          sampleMax = micValue;
        } else if (micValue < sampleMin) {
          sampleMin = micValue;
        }
      }
      if (musicCurrentMillis - musicPreviousMillis >= sampleTime) {
        peakToPeak = sampleMax - sampleMin;
        if (peakToPeak < 400) {
          micLights = map(peakToPeak, 0, 400, 0, NUM_LEDS - 1);
        }
        for (int dot = 0; dot < NUM_LEDS; dot++) {
          if (dot <= micLights) {
            leds[dot] = CRGB(greenValue, redValue, blueValue);
          } else {
            leds[dot] = CRGB(0, 0, 0);
          }
        }
        musicPreviousMillis = musicCurrentMillis;
        sampleMin = 1024;
        sampleMax = 0;
        FastLED.show();
      }
      break;

    case 5:
      musicCurrentMillis = millis();
      micValue = analogRead(micPin);
      if (micValue < 1024) {
        if (micValue > sampleMax) {
          sampleMax = micValue;
        } else if (micValue < sampleMin) {
          sampleMin = micValue;
        }
      }
      if (musicCurrentMillis - musicPreviousMillis >= sampleTime) {
        peakToPeak = sampleMax - sampleMin;
        if (peakToPeak < 400) {
          micLights = map(peakToPeak, 0, 400, 0, 254);
        }
        musicRedValue = map(redValue, 0, 255, 0, micLights);
        musicGreenValue = map(greenValue, 0, 255, 0, micLights);
        musicBlueValue = map(blueValue, 0, 255, 0, micLights);
        for (int dot = 0; dot < NUM_LEDS; dot++) {
          leds[dot] = CRGB(musicGreenValue, musicRedValue, musicBlueValue);
        }
        musicPreviousMillis = musicCurrentMillis;
        sampleMin = 1024;
        sampleMax = 0;
        FastLED.show();
      }
      break;

    case 6:                
      seasonPotValue = analogRead(redPot);
      season = map(seasonPotValue, 0, 1028, 0, 4);
      if (season != previousSeason) {
        seasonPreviousMillis = seasonCurrentMillis;
        previousSeason = season;
        //hasBeenRunning ++;
      }
      switch (season) {
        case 0:                        //Christmas/winter
          if (seasonCurrentColor == 1) {
            seasonRedValue = 255;           
            seasonGreenValue = 0;
            seasonBlueValue = 0;
          } else if (seasonCurrentColor == 2) {
            seasonRedValue = 0;             
            seasonGreenValue = 255;
            seasonBlueValue = 0;
          } else if (seasonCurrentColor == 3) {
            seasonRedValue = 255;           
            seasonGreenValue = 255;
            seasonBlueValue = 255;
          }
          break;

        case 1:                        //Halloween/fall
          if (seasonCurrentColor == 1) {
            seasonRedValue = 255;           
            seasonGreenValue = 85;
            seasonBlueValue = 0;
          } else if (seasonCurrentColor == 2) {
            seasonRedValue = 255;           
            seasonGreenValue = 0;
            seasonBlueValue = 0;
          } else if (seasonCurrentColor == 3) {
            seasonRedValue = 255;           
            seasonGreenValue = 150;
            seasonBlueValue = 0;
          }
          break;

        case 2:                        //Spring/easter
          if (seasonCurrentColor == 1) {
            seasonRedValue = 255;           
            seasonGreenValue = 0;
            seasonBlueValue = 255;
          } else if (seasonCurrentColor == 2) {
            seasonRedValue = 0;             
            seasonGreenValue = 200;
            seasonBlueValue = 255;
          } else if (seasonCurrentColor == 3) {
            seasonRedValue = 0;             
            seasonGreenValue = 255;
            seasonBlueValue = 50;
          }
          break;

        case 3:                        //Summer/4th of July
          if (seasonCurrentColor == 1) {
            seasonRedValue = 0;             
            seasonGreenValue = 0;
            seasonBlueValue = 255;
          } else if (seasonCurrentColor == 2) {
            seasonRedValue = 255;           
            seasonGreenValue = 0;
            seasonBlueValue = 0;
          } else if (seasonCurrentColor == 3) {
            seasonRedValue = 255;           
            seasonGreenValue = 255;
            seasonBlueValue = 255;
          }
          break;
      }

      seasonCurrentMillis = millis();
      seasonCurrentTime = seasonCurrentMillis - seasonPreviousMillis;
      if (seasonCurrentTime <= 1024) {
        seasonCurrentColor = 1;
        seasonBrightness = map(seasonCurrentTime, 0, 1024, 0, 255);
      } else if (seasonCurrentTime <= 8976) {
        seasonBrightness = 255;
      } else if (seasonCurrentTime <= 10000) {
        seasonBrightness = map(seasonCurrentTime, 8976, 10000, 255, 0);
      } else if (seasonCurrentTime <= 11024) {
        seasonCurrentColor = 2;
        seasonBrightness = map(seasonCurrentTime, 10000, 11024, 0, 255);
      } else if (seasonCurrentTime <= 18976) {
        seasonBrightness = 255;
      } else if (seasonCurrentTime <= 20000) {
        seasonBrightness = map(seasonCurrentTime, 18976, 20000, 255, 0);
      } else if (seasonCurrentTime <= 21024) {
        seasonCurrentColor = 3;
        seasonBrightness = map(seasonCurrentTime, 20000, 21024, 0, 255);
      } else if (seasonCurrentTime <= 28976) {
        seasonBrightness = 255;
      } else if (seasonCurrentTime <= 30000) {
        seasonBrightness = map(seasonCurrentTime, 28976, 30000, 255, 0);
      } else {
        seasonPreviousMillis = seasonCurrentMillis;
      }

      for (int dot = 0; dot < NUM_LEDS; dot++) {
        leds[dot] = CRGB(seasonGreenValue, seasonRedValue, seasonBlueValue);
      }
      FastLED.setBrightness(seasonBrightness);
      FastLED.show();

  }
}



#define COOLING 55
#define SPARKING 80

void Fire2012WithPalette() {
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);


    leds[j] = color;
    int fireRed = leds[j].green;
    int fireGreen = leds[j].red;
    int fireBlue = leds[j].blue;
    leds[j] = CRGB(fireRed, fireGreen, fireBlue);
  }
}
