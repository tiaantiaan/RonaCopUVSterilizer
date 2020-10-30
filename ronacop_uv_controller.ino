/**
 *
 * Created by Tiaan M
 *
 * Documentation: https://github.com/tiaantiaan/RonaCopUVSterilizer/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the MIT License as published by the 
 * Free Software Foundation.
 *
 *******************************
 */


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
#include <math.h>
#include <EEPROM.h>
#include <jled.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

const byte UVC_LIGHT_PIN = 10;
const byte TEMP_SENSOR_PIN = A0; //LM35
const byte LIGHT_ON_INDICATOR_PIN = 11;
const byte LIGHT_ON_SENSOR_PIN = 12;
const byte BUZZER_PIN = A2;
const unsigned long TEMP_SENSOR_UPDATE_TIME = 5000;
const unsigned long SCREEN_UPDATE_TIME = 50;
byte buttonPins[] = {6, 7, 8};
const byte noButtons = 3;
byte pressedButton, screenMode, previousScreenMode;
int t;
unsigned long timerEndTime = 0;
unsigned long timer = 0;
unsigned long timerPausedTime = 0;
unsigned long lampTurnOnTime;
unsigned long tempLastUpdateTime = millis() - TEMP_SENSOR_UPDATE_TIME;
unsigned long screenLastUpdateTime = millis() - SCREEN_UPDATE_TIME;
int temperature;
Bounce * buttons = new Bounce[noButtons];
long lampSeconds;
auto shortBeep = JLed(BUZZER_PIN).Blink(50, 50).Repeat(2);
auto startBeep = JLed(BUZZER_PIN).Blink(500, 200).Repeat(2);
auto doneBeep = JLed(BUZZER_PIN).Blink(100, 300).Repeat(5);
auto clearBeep = JLed(BUZZER_PIN).Blink(500, 200).Repeat(1);
auto errorBeep = JLed(BUZZER_PIN).Blink(1000, 500).Repeat(4);

void setup()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();

  for (t = 0; t < noButtons; t++) {
    buttons[t].attach( buttonPins[t] , INPUT_PULLUP  );
    buttons[t].interval(25);
  }

  pinMode(UVC_LIGHT_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LIGHT_ON_INDICATOR_PIN, OUTPUT);
  pinMode(LIGHT_ON_SENSOR_PIN, INPUT_PULLUP); // V++ -> LDR -> PIN -> 20kOhm -> Gnd

  setScreenMode(0);

  EEPROM.get(0, lampSeconds);

  startBeep.Stop();
  doneBeep.Stop();
  clearBeep.Stop();
  errorBeep.Stop();
}

void loop()
{
  updateTimer();

  updateTemperature();

  showLightStatus();

  pressedButton = checkButtonPress();

  if (screenMode == 0) { // Select time menu
    if (pressedButton != 0) {
      switch (pressedButton) {
        case 1:
          startTimer(7.5*60);
          setScreenMode(1);
          turnOnLight();
          break;
        case 2:
          startTimer(15 * 60);
          setScreenMode(1);
          turnOnLight();
          break;
        case 3:
          startTimer(30 * 60);
          setScreenMode(1);
          turnOnLight();
          break;
      }
      startBeep.Reset();
    }
  }
  else if (screenMode == 1) { // Light ON and timer running
    if (timer <= 0) {
      turnOffLight();
      setScreenMode(3);
      doneBeep.Reset();
    }
    if (pressedButton == 3) { // Button 3 stops light
      turnOffLight();
      setScreenMode(3);
      clearBeep.Reset();
    }
    if (digitalRead(LIGHT_ON_SENSOR_PIN) == 0) { // Error: Light is not shining
      errorBeep.Reset();
      setScreenMode(2);
      renderScreen();
    }

  }
  else if (screenMode == 2) { // Error state: Light is not ON
    if (digitalRead(LIGHT_ON_SENSOR_PIN) == 1) { // Light is shining
      setScreenMode(1); // Continue with timer
      errorBeep.Stop();
      renderScreen();
    }
    if (pressedButton != 0) { // Stop and exit to done screen
      turnOffLight();
      setScreenMode(3);
      errorBeep.Stop();
      clearBeep.Reset();
    }
  }
  else if (screenMode == 3) { // Done screen
    if (pressedButton != 0) {
      setScreenMode(0);
      shortBeep.Reset();
    }
  }

  if (pressedButton != 0 || (millis() - screenLastUpdateTime > SCREEN_UPDATE_TIME)) {
    renderScreen();
  }

  updateBeep();
}

void updateBeep() {
  shortBeep.Update();
  startBeep.Update();
  doneBeep.Update();
  clearBeep.Update();
  errorBeep.Update();

}

void updateTemperature() {
  if ((unsigned long)(millis() - tempLastUpdateTime) > TEMP_SENSOR_UPDATE_TIME) {
    int value = analogRead(TEMP_SENSOR_PIN);
    temperature = (int)round((value / 1024.0) * 500);
    tempLastUpdateTime = millis();
  }
}

void showLightStatus() {
  digitalWrite(LIGHT_ON_INDICATOR_PIN, digitalRead(LIGHT_ON_SENSOR_PIN));
}

void turnOffLight() {
  digitalWrite(UVC_LIGHT_PIN, false);
  writeLampTimeToEEPROM();
}

void writeLampTimeToEEPROM() {
  unsigned long sessionSeconds = (millis() - lampTurnOnTime) / 1000;
  lampSeconds = lampSeconds + sessionSeconds;
}

void turnOnLight() {
  digitalWrite(UVC_LIGHT_PIN, true);
  lampTurnOnTime = millis();
}

void updateTimer() {
  timer = timerEndTime - (millis() / 1000);
}

void setScreenMode(int mode) {
  screenMode = mode;
}

void startTimer(unsigned long seconds) {
  timerEndTime = millis() / 1000 + seconds;
}

void renderScreen() {
  if (screenMode != previousScreenMode) {
    lcd.clear();
    previousScreenMode = screenMode;
  }
  if (screenMode == 0) {
    lcd.setCursor(3, 0);
    lcd.print("Kies Tyd:");

    lcd.setCursor(0, 1);
    lcd.print("7.5m   15m   30m");
  }
  else if (screenMode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Tyd Oor:");

    lcd.setCursor(11, 0);
    if (timer / 60 < 10) {
      lcd.print("0");
      lcd.setCursor(12, 0);
    }
    lcd.print((int)timer / 60);

    lcd.setCursor(13, 0);
    lcd.print(":");
    lcd.setCursor(14, 0);
    if (timer % 60 < 10) {
      lcd.print("0");
      lcd.setCursor(15, 0);
    }
    lcd.print((int)timer % 60);

    lcd.setCursor(0, 1);
    lcd.print("Temp:");

    lcd.setCursor(6, 1);
    lcd.print(temperature);

    lcd.setCursor(8, 1);
    lcd.print((char)223);
    lcd.setCursor(9, 1);
    lcd.print("C");

    lcd.setCursor(12, 1);
    lcd.print("STOP");

  }
  else if (screenMode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("ERROR: Light OFF");
    lcd.setCursor(0, 1);
    lcd.print("Check lid closed");
  }
  else if (screenMode == 3) {
    lcd.setCursor(0, 0);
    lcd.print("KLAAR!!");

    lcd.setCursor(12, 0);
    lcd.print(temperature);

    lcd.setCursor(14, 0);
    lcd.print((char)223);
    lcd.setCursor(15, 0);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Lamp ure: ");
    lcd.setCursor(9, 1);
    lcd.print(round(lampSeconds / 60 / 60));

    lcd.setCursor(14, 1);
    lcd.print("OK");
  }
  screenLastUpdateTime = millis();
}

byte checkButtonPress() {
  byte pressedButton = 0;
  for (t = 0; t < noButtons; t++) {
    buttons[t].update();
    if ( buttons[t].fell() ) {
      pressedButton = t + 1;
      break;
    }
  }
  return pressedButton;
}
