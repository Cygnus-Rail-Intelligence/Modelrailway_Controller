/*
 * CYGNUS-RAIL CONTROLLER
 * 
 * Arduino-basierte Modellbahn-Steuerung mit TFT-Display
 * Version: 2.3b
 * Datum: Februar 2026
 * 
 * Projekt: Cygnus-Rail Intelligence
 * Repository: https://github.com/[IhrBenutzername]/Cygnus-Rail-Intelligence
 * 
 * Hardware:
 * - Arduino Mega 2560
 * - TB6612 Motortreiber (31kHz PWM auf Timer3, Pin 5)
 * - TSOP38238 IR-Empfänger (Pin 22, RC5-Protokoll)
 * - ST7735 TFT Display 1.8" (128x160, SPI)
 * - 4x 5V Relais-Module
 * 
 * Lizenz: CC BY-NC-SA 4.0 (privat) / Kommerzielle Lizenz (gewerblich)
 * Siehe LICENSE.txt für Details
 * 
 * Kompatibel mit RC5-basierten Modellbahn-Fernbedienungen
 */

#include <Arduino.h>
#include <IRremote.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// ================= TB6612 =================

#define PWMA 5      // Timer3 OC3A
#define AIN1 7
#define AIN2 8
#define STBY 6

// ================= IR =================

#define IR_PIN 22
#define RC5_ADDRESS 0x18

// ================= RELAIS FÜR ABSTELLGLEISE =================

#define RELAY_ABSTELLGLEIS_1  10
#define RELAY_ABSTELLGLEIS_2  11
#define RELAY_ABSTELLGLEIS_3  24  // Geändert auf Pin 24
#define RELAY_ABSTELLGLEIS_4  25  // Geändert auf Pin 25

// ================= TFT DISPLAY =================

#define TFT_CS     48
#define TFT_RST    49
#define TFT_DC     47
#define TFT_MOSI   51  // Standard SPI MOSI
#define TFT_SCLK   52  // Standard SPI SCK

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// ================= BETRIEBSMODI =================

enum OperationMode {
  MODE_MOTORTYPE,
  MODE_ABSTELLGLEIS
};

OperationMode currentMode = MODE_MOTORTYPE;

// ================= MOTOR =================

enum MotorType {
  MOTOR_3POL,
  MOTOR_5POL,
  MOTOR_GLOCKENANKER,
  MOTOR_HOCHLEISTUNG
};

MotorType currentMotor = MOTOR_5POL;

bool directionForward = true;
int speedPercent = 0;

// ================= ABSTELLGLEIS STATUS =================

bool abstellgleis[4] = {false, false, false, false};

// ================= RELAIS STEUERUNG =================
// Relais halten dauerhaft bis zum erneuten Tastendruck

// ================= STATUS =================

unsigned long lastPrint = 0;
unsigned long lastDisplayUpdate = 0;
const unsigned long DISPLAY_UPDATE_INTERVAL = 2000;  // 2 Sekunden - viel langsamer!

// Display nur bei Änderungen updaten
int lastSpeedPercent = -1;
bool lastDirectionForward = true;
MotorType lastMotorType = MOTOR_5POL;
OperationMode lastMode = MODE_MOTORTYPE;
bool lastAbstellgleis[4] = {false, false, false, false};
bool displayNeedsUpdate = true;

// ================= TIMER3 31kHz =================

void setupPWM_Timer3() {

  pinMode(PWMA, OUTPUT);

  // Fast PWM 8bit, no prescaler → 31kHz
  TCCR3A = _BV(COM3A1) | _BV(WGM30);
  TCCR3B = _BV(WGM32) | _BV(CS30);

  OCR3A = 0;
}

void setPWM(uint8_t value) {
  OCR3A = value;
}

// ================= TFT DISPLAY =================

void setupDisplay() {
  
  // ===== HARDWARE-RESET =====
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, HIGH);
  delay(100);
  digitalWrite(TFT_RST, LOW);   // Reset aktivieren
  delay(100);
  digitalWrite(TFT_RST, HIGH);  // Reset deaktivieren
  delay(200);
  
  // ===== SPI INITIALISIEREN =====
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // Für AZDelivery kann schneller sein
  
  delay(500);  // Warten auf Display-Stromversorgung
  
  // ===== DISPLAY INIT - AZDELIVERY ST7735 v1.2 =====
  // AZDelivery 1.8" ST7735 128x160 v1.2 benötigt BLACKTAB
  
  tft.initR(INITR_BLACKTAB);
  delay(200);
  
  // ===== FARB-INVERSION für AZDelivery =====
  // AZDelivery Displays benötigen oft invertDisplay!
  tft.invertDisplay(true);
  delay(100);
  
  tft.setRotation(1);  // Landscape
  delay(100);
  
  // Schwarzen Hintergrund
  tft.fillScreen(ST77XX_BLACK);
  delay(500);
  
  // Willkommensnachricht
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, 20);
  tft.print("MAERKLIN");
  tft.setCursor(10, 42);
  tft.print("IR-Steuer.");
  
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(10, 70);
  tft.print("AZDelivery v1.2");
  
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
  delay(200);
}

void updateDisplay(int pwm) {
  
  // Prüfen ob sich etwas geändert hat
  bool hasChanged = false;
  
  if (speedPercent != lastSpeedPercent) hasChanged = true;
  if (directionForward != lastDirectionForward) hasChanged = true;
  if (currentMotor != lastMotorType) hasChanged = true;
  if (currentMode != lastMode) hasChanged = true;
  for (int i = 0; i < 4; i++) {
    if (abstellgleis[i] != lastAbstellgleis[i]) hasChanged = true;
  }
  
  // Nur updaten wenn sich was geändert hat UND genug Zeit vergangen ist
  if (!hasChanged && !displayNeedsUpdate) return;
  if (millis() - lastDisplayUpdate < DISPLAY_UPDATE_INTERVAL) return;
  
  lastDisplayUpdate = millis();
  displayNeedsUpdate = false;
  
  // Werte speichern
  lastSpeedPercent = speedPercent;
  lastDirectionForward = directionForward;
  lastMotorType = currentMotor;
  lastMode = currentMode;
  for (int i = 0; i < 4; i++) {
    lastAbstellgleis[i] = abstellgleis[i];
  }
  
  // WICHTIG: Kein fillScreen() mehr! Stattdessen Text mit schwarzem Hintergrund überschreiben
  
  // ===== ÜBERSCHRIFT =====
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);  // Text Cyan, Hintergrund Schwarz
  tft.setCursor(5, 2);  // Y=2 statt 5 (höher)
  
  if (currentMode == MODE_MOTORTYPE) {
    tft.print("MOTOR MODUS ");  // Extra Leerzeichen zum Überschreiben
  } else {
    tft.print("ABSTELLGLEIS");
  }
  
  // ===== GESCHWINDIGKEIT =====
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.setCursor(5, 24);  // Y=24 statt 30 (kompakter)
  tft.print("Speed: ");
  tft.print(speedPercent);
  tft.print("% (");
  tft.print(pwm);
  tft.print(")   ");  // Extra Leerzeichen
  
  // ===== RICHTUNG =====
  tft.setCursor(5, 37);  // Y=37 statt 45 (kompakter)
  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  tft.print("Richtung: ");
  tft.print(directionForward ? "Vorwaerts  " : "Rueckwaerts");
  
  // ===== MODUS-SPEZIFISCHE ANZEIGE =====
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  
  if (currentMode == MODE_MOTORTYPE) {
    // Motortyp anzeigen
    tft.setCursor(5, 53);  // Y=53 statt 65 (kompakter)
    tft.print("Motortyp:           ");  // Zeile löschen
    tft.setCursor(5, 53);
    tft.print("Motortyp: ");
    
    switch (currentMotor) {
      case MOTOR_3POL:
        tft.print("3-Pol       ");
        break;
      case MOTOR_5POL:
        tft.print("5-Pol       ");
        break;
      case MOTOR_GLOCKENANKER:
        tft.print("Glockenank.");
        break;
      case MOTOR_HOCHLEISTUNG:
        tft.print("Hochleist. ");
        break;
    }
    
    // Tastenbelegung
    tft.setCursor(5, 71);  // Y=71 statt 85 (kompakter)
    tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
    tft.print("Tasten:          ");
    tft.setCursor(5, 83);  // Y=83 statt 95
    tft.print("1:3Pol 2:5Pol    ");
    tft.setCursor(5, 95);  // Y=95 statt 105
    tft.print("3:Glock 4:High   ");
    
    // Abstellgleis-Zeilen löschen
    tft.setCursor(5, 107);  // Y=107 statt 115
    tft.print("                 ");
    
  } else {
    // Motortyp-Zeile löschen
    tft.setCursor(5, 53);
    tft.print("                 ");
    
    // Abstellgleis-Status anzeigen
    tft.setCursor(5, 62);  // Y=62 statt 75 (kompakter)
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.print("Abstellgleise:   ");
    
    for (int i = 0; i < 4; i++) {
      tft.setCursor(5, 75 + i * 10);  // Y=75,85,95,105 statt 88,99,110,121 (kompakter)
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.print("Gleis ");
      tft.print(i + 1);
      tft.print(": ");
      
      if (abstellgleis[i]) {
        tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
        tft.print("EIN ");
      } else {
        tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
        tft.print("AUS ");
      }
    }
    
    // Tasten-Zeilen löschen
    tft.setCursor(5, 83);
    tft.setTextColor(ST77XX_BLACK, ST77XX_BLACK);
    tft.print("                 ");
    tft.setCursor(5, 95);
    tft.print("                 ");
  }
  
  // ===== HINWEIS MODUSUMSCHALTUNG =====
  tft.setCursor(2, 115);  // Y=115 statt 125 (sichtbar!)
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.print("Licht=Wechsel    ");
}

// ================= SETUP =================

void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

  // Relais-Pins für Abstellgleise
  pinMode(RELAY_ABSTELLGLEIS_1, OUTPUT);
  pinMode(RELAY_ABSTELLGLEIS_2, OUTPUT);
  pinMode(RELAY_ABSTELLGLEIS_3, OUTPUT);
  pinMode(RELAY_ABSTELLGLEIS_4, OUTPUT);

  digitalWrite(RELAY_ABSTELLGLEIS_1, HIGH);
  digitalWrite(RELAY_ABSTELLGLEIS_2, HIGH);
  digitalWrite(RELAY_ABSTELLGLEIS_3, HIGH);
  digitalWrite(RELAY_ABSTELLGLEIS_4, HIGH);

  setupPWM_Timer3();

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  Serial.begin(9600);
  
  setupDisplay();

  digitalWrite(STBY, HIGH);

  Serial.println("=== Mega Enhanced Version mit Display ===");
  Serial.println("Modus: MOTORTYPE");
}

// ================= LOOP =================

void loop() {

  handleIR();

  int pwm = calculatePWM(speedPercent / 100.0);

  setDirection(directionForward);
  setPWM(pwm);

  printStatus(pwm);
  updateDisplay(pwm);
}

// ================= IR =================

void handleIR() {

  if (!IrReceiver.decode())
    return;

  if (IrReceiver.decodedIRData.protocol != RC5 ||
      IrReceiver.decodedIRData.address != RC5_ADDRESS) {
    IrReceiver.resume();
    return;
  }

  uint8_t cmd = IrReceiver.decodedIRData.command;
  bool repeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

  switch (cmd) {

    case 0x10:  // +
      speedPercent = min(100, speedPercent + 5);
      break;

    case 0x11:  // -
      speedPercent = max(0, speedPercent - 5);
      break;

    case 0x0D:  // Richtung
      if (!repeat)
        directionForward = !directionForward;
      break;

    case 0x50:  // LICHT - MODUS UMSCHALTEN
      if (!repeat) {
        if (currentMode == MODE_MOTORTYPE) {
          currentMode = MODE_ABSTELLGLEIS;
          Serial.println("\n>>> MODUS: ABSTELLGLEIS <<<");
        } else {
          currentMode = MODE_MOTORTYPE;
          Serial.println("\n>>> MODUS: MOTORTYPE <<<");
        }
      }
      break;

    case 0x51:  // Taste 1
      if (!repeat) {
        if (currentMode == MODE_MOTORTYPE) {
          currentMotor = MOTOR_3POL;
          Serial.println("Motor: 3-Pol");
        } else {
          abstellgleis[0] = !abstellgleis[0];
          digitalWrite(RELAY_ABSTELLGLEIS_1, abstellgleis[0] ? LOW : HIGH);
          Serial.print("Abstellgleis 1: ");
          Serial.println(abstellgleis[0] ? "EIN" : "AUS");
        }
      }
      break;

    case 0x52:  // Taste 2
      if (!repeat) {
        if (currentMode == MODE_MOTORTYPE) {
          currentMotor = MOTOR_5POL;
          Serial.println("Motor: 5-Pol");
        } else {
          abstellgleis[1] = !abstellgleis[1];
          digitalWrite(RELAY_ABSTELLGLEIS_2, abstellgleis[1] ? LOW : HIGH);
          Serial.print("Abstellgleis 2: ");
          Serial.println(abstellgleis[1] ? "EIN" : "AUS");
        }
      }
      break;

    case 0x53:  // Taste 3
      if (!repeat) {
        if (currentMode == MODE_MOTORTYPE) {
          currentMotor = MOTOR_GLOCKENANKER;
          Serial.println("Motor: Glockenanker");
        } else {
          abstellgleis[2] = !abstellgleis[2];
          digitalWrite(RELAY_ABSTELLGLEIS_3, abstellgleis[2] ? LOW : HIGH);
          Serial.print("Abstellgleis 3: ");
          Serial.println(abstellgleis[2] ? "EIN" : "AUS");
        }
      }
      break;

    case 0x54:  // Taste 4
      if (!repeat) {
        if (currentMode == MODE_MOTORTYPE) {
          currentMotor = MOTOR_HOCHLEISTUNG;
          Serial.println("Motor: Hochleistung");
        } else {
          abstellgleis[3] = !abstellgleis[3];
          digitalWrite(RELAY_ABSTELLGLEIS_4, abstellgleis[3] ? LOW : HIGH);
          Serial.print("Abstellgleis 4: ");
          Serial.println(abstellgleis[3] ? "EIN" : "AUS");
        }
      }
      break;
  }

  IrReceiver.resume();
}

// ================= MOTOR =================

void setDirection(bool forward) {
  digitalWrite(AIN1, forward ? HIGH : LOW);
  digitalWrite(AIN2, forward ? LOW : HIGH);
}

int calculatePWM(float speed) {

  if (speed <= 0.0) return 0;

  switch (currentMotor) {

    case MOTOR_3POL:
      return map(constrain(speed * 100, 5, 100), 5, 100, 95, 255);

    case MOTOR_5POL:
      return map(constrain(speed * speed * 100, 0, 100), 0, 100, 75, 255);

    case MOTOR_GLOCKENANKER:
      return map(constrain(pow(speed, 1.6) * 100, 0, 100), 0, 100, 45, 220);

    case MOTOR_HOCHLEISTUNG:
      return map(constrain(pow(speed, 1.3) * 100, 0, 100), 0, 100, 60, 240);
  }

  return 0;
}

// ================= STATUS =================

void printStatus(int pwm) {

  if (millis() - lastPrint < 500) return;
  lastPrint = millis();

  Serial.print("Mode:");
  Serial.print(currentMode == MODE_MOTORTYPE ? "MOTOR" : "GLEIS");
  Serial.print(" Speed:");
  Serial.print(speedPercent);
  Serial.print("% PWM:");
  Serial.print(pwm);
  Serial.print(" Dir:");
  Serial.print(directionForward ? "V" : "R");
  
  if (currentMode == MODE_MOTORTYPE) {
    Serial.print(" Motor:");
    Serial.println(currentMotor);
  } else {
    Serial.print(" Gleise:");
    for (int i = 0; i < 4; i++) {
      Serial.print(abstellgleis[i] ? "1" : "0");
    }
    Serial.println();
  }
}
