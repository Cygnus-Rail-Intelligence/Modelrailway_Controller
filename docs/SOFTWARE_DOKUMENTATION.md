# SOFTWARE-DOKUMENTATION
## Cygnus-Rail Controller - Code-Struktur & Funktionen

**Version:** 2.3b  
**Datum:** Februar 2026  
**Programmiersprache:** C++ (Arduino)

---

## 📋 INHALTSVERZEICHNIS

1. [Projekt-Struktur](#projekt-struktur)
2. [Bibliotheken](#bibliotheken)
3. [Globale Variablen](#globale-variablen)
4. [Funktions-Übersicht](#funktions-übersicht)
5. [Detaillierte Funktions-Beschreibung](#detaillierte-funktions-beschreibung)
6. [PWM-Konfiguration](#pwm-konfiguration)
7. [Display-Update-Logik](#display-update-logik)
8. [IR-Protokoll-Handler](#ir-protokoll-handler)
9. [Anpassungen & Erweiterungen](#anpassungen--erweiterungen)

---

## 📁 PROJEKT-STRUKTUR

### Datei-Übersicht

```
Cygnus_Rail_Controller/
│
├── Cygnus_Rail_Controller.ino   (Haupt-Programm)
│
└── README_KOMPLETT.md                     (Diese Doku)
```

**Wichtig:** Nur EINE .ino Datei pro Ordner!

### Code-Abschnitte

Das Programm ist in folgende Abschnitte gegliedert:

```cpp
// 1. INCLUDES & DEFINES
//    - Bibliotheken
//    - Pin-Definitionen
//    - Konstanten

// 2. GLOBALE VARIABLEN
//    - Zustands-Variablen
//    - Display-Objekt
//    - Status-Speicher

// 3. HILFSFUNKTIONEN
//    - PWM-Setup
//    - Display-Funktionen
//    - Motor-Steuerung

// 4. SETUP()
//    - Hardware-Initialisierung
//    - Display-Willkommens-Screen

// 5. LOOP()
//    - IR-Handler
//    - Motor-Update
//    - Display-Update
//    - Status-Ausgabe

// 6. IR-HANDLER
//    - RC5-Decode
//    - Tasten-Funktionen

// 7. DISPLAY-FUNKTIONEN
//    - Layout-Rendering
//    - Update-Optimierung
```

---

## 📚 BIBLIOTHEKEN

### Erforderliche Libraries

```cpp
#include <Arduino.h>          // Arduino Core
#include <IRremote.h>         // IR-Empfang (v3.x+)
#include <Adafruit_GFX.h>     // Grafik-Basis
#include <Adafruit_ST7735.h>  // ST7735 Display-Treiber
#include <SPI.h>              // SPI-Kommunikation
```

### Library-Versionen (getestet)

| Library | Version | Repository |
|---------|---------|------------|
| IRremote | 4.x | https://github.com/Arduino-IRremote/Arduino-IRremote |
| Adafruit GFX | 1.11.x | https://github.com/adafruit/Adafruit-GFX-Library |
| Adafruit ST7735 | 1.10.x | https://github.com/adafruit/Adafruit-ST7735-Library |
| SPI | Built-in | Arduino Core |

### Installation

```
Arduino IDE → Tools → Manage Libraries...

1. Suche: "IRremote" → Install (von shirriff/z3t0)
2. Suche: "Adafruit GFX" → Install
3. Suche: "Adafruit ST7735" → Install
```

---

## 🔧 GLOBALE VARIABLEN

### Pin-Definitionen

```cpp
// ===== TB6612 MOTORTREIBER =====
#define PWMA 5      // Timer3 OC3A (31kHz PWM)
#define AIN1 7      // Richtung A
#define AIN2 8      // Richtung B
#define STBY 6      // Standby (HIGH = aktiv)

// ===== IR-EMPFÄNGER =====
#define IR_PIN 22           // IR-Signal Eingang
#define RC5_ADDRESS 0x18    // RC5-Protokoll Adresse

// ===== RELAIS ABSTELLGLEISE =====
#define RELAY_ABSTELLGLEIS_1  10
#define RELAY_ABSTELLGLEIS_2  11
#define RELAY_ABSTELLGLEIS_3  24
#define RELAY_ABSTELLGLEIS_4  25

// ===== TFT DISPLAY =====
#define TFT_CS     48       // Chip Select
#define TFT_RST    49       // Reset
#define TFT_DC     47       // Data/Command (Display-Pin "A0")
// MOSI = Pin 51 (SDA)
// SCLK = Pin 52 (SCK)
```

### Enumerationen

```cpp
// Betriebsmodi
enum OperationMode {
  MODE_MOTORTYPE,      // Motortyp-Auswahl
  MODE_ABSTELLGLEIS    // Abstellgleis-Steuerung
};

// Motortypen
enum MotorType {
  MOTOR_3POL,          // 3-Pol Motor (linear)
  MOTOR_5POL,          // 5-Pol Motor (quadratisch)
  MOTOR_GLOCKENANKER,  // Glockenanker (Potenz 1.6)
  MOTOR_HOCHLEISTUNG   // Hochleistung (Potenz 1.3)
};
```

### Status-Variablen

```cpp
// Aktueller Zustand
OperationMode currentMode = MODE_MOTORTYPE;
MotorType currentMotor = MOTOR_5POL;
bool directionForward = true;
int speedPercent = 0;

// Abstellgleis-Status
bool abstellgleis[4] = {false, false, false, false};

// Display-Update-Management
unsigned long lastDisplayUpdate = 0;
const unsigned long DISPLAY_UPDATE_INTERVAL = 300;  // ms

// Change Detection (für effizientes Display-Update)
static int lastSpeedPercent = -1;
static bool lastDirectionForward = true;
static MotorType lastMotorType = MOTOR_5POL;
static OperationMode lastMode = MODE_MOTORTYPE;
static bool lastAbstellgleis[4] = {false, false, false, false};
static bool displayNeedsUpdate = true;
```

### Display-Objekt

```cpp
// TFT Display Objekt
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
```

---

## 📊 FUNKTIONS-ÜBERSICHT

### Haupt-Funktionen

| Funktion | Zweck | Aufgerufen von |
|----------|-------|---------------|
| `setup()` | Hardware-Initialisierung | Arduino Core |
| `loop()` | Haupt-Schleife | Arduino Core |
| `handleIR()` | IR-Signal verarbeiten | loop() |
| `updateDisplay(int pwm)` | Display aktualisieren | loop() |
| `printStatus(int pwm)` | Serieller Status | loop() |

### Motor-Funktionen

| Funktion | Parameter | Rückgabe | Zweck |
|----------|-----------|----------|-------|
| `setupPWM_Timer3()` | - | void | 31kHz PWM konfigurieren |
| `setPWM(uint8_t)` | value (0-255) | void | PWM-Wert setzen |
| `setDirection(bool)` | forward | void | Motor-Richtung setzen |
| `calculatePWM(float)` | speed (0.0-1.0) | int | PWM aus Geschwindigkeit berechnen |

### Display-Funktionen

| Funktion | Parameter | Rückgabe | Zweck |
|----------|-----------|----------|-------|
| `setupDisplay()` | - | void | Display initialisieren |
| `updateDisplay(int)` | pwm | void | Display-Inhalt aktualisieren |

---

## 🔍 DETAILLIERTE FUNKTIONS-BESCHREIBUNG

### setup()

**Zweck:** Initialisierung aller Hardware-Komponenten beim Start

```cpp
void setup() {
  // 1. Motor-Pins konfigurieren
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, LOW);    // Motor initial aus
  
  // 2. Relais-Pins konfigurieren
  pinMode(RELAY_ABSTELLGLEIS_1, OUTPUT);
  // ... (alle 4 Relais)
  digitalWrite(RELAY_ABSTELLGLEIS_1, HIGH);  // Relais aus (aktiv LOW)
  
  // 3. PWM konfigurieren
  setupPWM_Timer3();  // 31kHz auf Pin 5
  
  // 4. IR-Empfänger starten
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  
  // 5. Serielle Kommunikation
  Serial.begin(9600);
  
  // 6. Display initialisieren
  setupDisplay();
  
  // 7. Motor aktivieren
  digitalWrite(STBY, HIGH);  // TB6612 einschalten
  
  Serial.println("=== System bereit ===");
}
```

**Wichtige Schritte:**
1. Alle Outputs initialisieren (LOW/HIGH)
2. PWM-Timer konfigurieren (31kHz)
3. IR-Library starten
4. Display mit Willkommens-Screen
5. Motor-Treiber aktivieren

---

### loop()

**Zweck:** Haupt-Schleife, wird kontinuierlich ausgeführt

```cpp
void loop() {
  // 1. IR-Befehle verarbeiten
  handleIR();
  
  // 2. PWM-Wert berechnen
  int pwm = calculatePWM(speedPercent / 100.0);
  
  // 3. Motor-Richtung setzen
  setDirection(directionForward);
  
  // 4. PWM-Wert an Motor
  setPWM(pwm);
  
  // 5. Serielle Statusausgabe
  printStatus(pwm);
  
  // 6. Display aktualisieren
  updateDisplay(pwm);
}
```

**Ablauf:**
1. IR → Befehle empfangen und verarbeiten
2. PWM → Aus Prozent (0-100%) PWM-Wert (0-255) berechnen
3. Richtung → Motor-Richtung setzen (H-Bridge)
4. PWM → Motor mit berechneter Geschwindigkeit ansteuern
5. Serial → Status-Info ausgeben (alle 500ms)
6. Display → Anzeige aktualisieren (alle 300ms)

---

### setupPWM_Timer3()

**Zweck:** Konfiguriert Timer3 für 31kHz PWM auf Pin 5

```cpp
void setupPWM_Timer3() {
  pinMode(PWMA, OUTPUT);
  
  // Fast PWM, 8-bit, no prescaler
  // Frequenz = 16MHz / (1 * 256) = 62.5kHz / 2 = 31.25kHz
  TCCR3A = _BV(COM3A1) | _BV(WGM30);   // Non-inverting, Fast PWM 8-bit
  TCCR3B = _BV(WGM32) | _BV(CS30);     // Fast PWM, No prescaler
  
  OCR3A = 0;  // Initial PWM = 0
}
```

**Register-Konfiguration:**
- `TCCR3A`: Timer/Counter Control Register A
  - `COM3A1`: Non-Inverting Mode (Clear on match)
  - `WGM30`: Fast PWM Mode (Part 1)
  
- `TCCR3B`: Timer/Counter Control Register B
  - `WGM32`: Fast PWM Mode (Part 2)
  - `CS30`: No Prescaler (clk/1)

**Ergebnis:** 31.25kHz PWM-Frequenz (unhörbar für Menschen)

---

### calculatePWM(float speed)

**Zweck:** Berechnet PWM-Wert basierend auf Motortyp und Geschwindigkeit

```cpp
int calculatePWM(float speed) {
  if (speed <= 0.0) return 0;
  
  switch (currentMotor) {
    case MOTOR_3POL:
      // Linear: y = 95 + (255-95) * x/100
      return map(constrain(speed * 100, 5, 100), 
                 5, 100, 95, 255);
    
    case MOTOR_5POL:
      // Quadratisch: y = 75 + (255-75) * (x²/100²)
      return map(constrain(speed * speed * 100, 0, 100), 
                 0, 100, 75, 255);
    
    case MOTOR_GLOCKENANKER:
      // Potenz 1.6: y = 45 + (220-45) * (x^1.6/100^1.6)
      return map(constrain(pow(speed, 1.6) * 100, 0, 100), 
                 0, 100, 45, 220);
    
    case MOTOR_HOCHLEISTUNG:
      // Potenz 1.3: y = 60 + (240-60) * (x^1.3/100^1.3)
      return map(constrain(pow(speed, 1.3) * 100, 0, 100), 
                 0, 100, 60, 240);
  }
  
  return 0;
}
```

**Kennlinien-Grafik:**
```
PWM
255 │                              ╱───  3-Pol (Linear)
    │                          ╱───
    │                      ╱───
200 │                  ╱───
    │              ╱───────────────────  5-Pol (Quadr.)
    │          ╱───
150 │      ╱───  
    │  ╱─────────────────────────────── Glockenanker
100 │╱─────────────────────────────────  Hochleistung
    │
  0 └────────────────────────────────────────────
    0%        25%        50%        75%       100%
                    Geschwindigkeit
```

**Warum verschiedene Kennlinien?**
- **3-Pol:** Robuste, alte Motoren → höherer Mindestwert
- **5-Pol:** Moderne Motoren → sanfter Anlauf (quadratisch)
- **Glockenanker:** Präzisions-Motoren → sehr niedriger Start
- **Hochleistung:** Kompromiss zwischen Linear und Quadratisch

---

### handleIR()

**Zweck:** IR-Signale empfangen und verarbeiten

```cpp
void handleIR() {
  // Auf neue Daten warten
  if (!IrReceiver.decode()) return;
  
  // Protokoll und Adresse prüfen
  if (IrReceiver.decodedIRData.protocol != RC5 ||
      IrReceiver.decodedIRData.address != RC5_ADDRESS) {
    IrReceiver.resume();
    return;
  }
  
  uint8_t cmd = IrReceiver.decodedIRData.command;
  bool repeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;
  
  // Befehle verarbeiten
  switch (cmd) {
    case 0x10:  // + Taste
      speedPercent = min(100, speedPercent + 5);
      displayNeedsUpdate = true;
      break;
      
    case 0x11:  // - Taste
      speedPercent = max(0, speedPercent - 5);
      displayNeedsUpdate = true;
      break;
      
    case 0x0D:  // Richtung
      if (!repeat) {
        directionForward = !directionForward;
        displayNeedsUpdate = true;
      }
      break;
      
    case 0x50:  // Licht (Modus umschalten)
      if (!repeat) {
        currentMode = (currentMode == MODE_MOTORTYPE) 
                      ? MODE_ABSTELLGLEIS 
                      : MODE_MOTORTYPE;
        displayNeedsUpdate = true;
      }
      break;
      
    case 0x51:  // Taste 1
      if (!repeat) {
        if (currentMode == MODE_MOTORTYPE) {
          currentMotor = MOTOR_3POL;
        } else {
          abstellgleis[0] = !abstellgleis[0];
          digitalWrite(RELAY_ABSTELLGLEIS_1, 
                       abstellgleis[0] ? LOW : HIGH);
        }
        displayNeedsUpdate = true;
      }
      break;
      
    // ... (Tasten 2-4 analog)
  }
  
  IrReceiver.resume();  // Bereit für nächstes Signal
}
```

**Wichtige Konzepte:**
1. **Repeat-Detection:** `!repeat` verhindert Mehrfach-Auslösung
2. **Modus-abhängig:** Gleiche Taste, andere Funktion
3. **displayNeedsUpdate:** Markiert, dass Display aktualisiert werden muss

---

### updateDisplay(int pwm)

**Zweck:** Display-Inhalt aktualisieren (nur bei Änderungen)

```cpp
void updateDisplay(int pwm) {
  // Change Detection - nur updaten wenn nötig
  bool hasChanged = false;
  
  if (speedPercent != lastSpeedPercent) hasChanged = true;
  if (directionForward != lastDirectionForward) hasChanged = true;
  if (currentMotor != lastMotorType) hasChanged = true;
  if (currentMode != lastMode) hasChanged = true;
  
  for (int i = 0; i < 4; i++) {
    if (abstellgleis[i] != lastAbstellgleis[i]) hasChanged = true;
  }
  
  // Nur updaten wenn Änderung UND genug Zeit vergangen
  if (!hasChanged && !displayNeedsUpdate) return;
  if (millis() - lastDisplayUpdate < DISPLAY_UPDATE_INTERVAL) return;
  
  lastDisplayUpdate = millis();
  displayNeedsUpdate = false;
  
  // Werte für nächsten Vergleich speichern
  lastSpeedPercent = speedPercent;
  // ... (alle anderen auch)
  
  // === DISPLAY RENDERING ===
  // Text mit schwarzem Hintergrund überschreiben (kein fillScreen!)
  
  // Überschrift
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
  tft.setCursor(5, 2);
  tft.print(currentMode == MODE_MOTORTYPE 
            ? "MOTOR MODUS " 
            : "ABSTELLGLEIS");
  
  // ... (alle weiteren Texte)
}
```

**Optimierungen:**
1. **Change Detection:** Nur bei Änderung updaten
2. **Time-Throttling:** Max. alle 300ms
3. **Kein fillScreen():** Flackern vermeiden
4. **Text mit Hintergrund:** Überschreibt alte Zeichen sauber

---

## ⚙️ PWM-KONFIGURATION

### Timer3 Register-Details

**Timer3 auf Arduino Mega:**
- **Output Pin:** OC3A (Pin 5)
- **Modus:** Fast PWM, 8-bit
- **Prescaler:** 1 (kein Prescaler)
- **Frequenz:** 16MHz / 256 / 1 = 62.5kHz → durch Toggle auf 31.25kHz

**Register-Bits:**

```cpp
// TCCR3A (Timer/Counter Control Register A)
Bit 7-6: COM3A[1:0] = 10 (Non-inverting mode)
Bit 5-4: COM3B[1:0] = 00 (Not used)
Bit 3-2: Reserved
Bit 1-0: WGM3[1:0] = 01 (Fast PWM, Part 1)

// TCCR3B (Timer/Counter Control Register B)
Bit 7: Reserved
Bit 6-5: Reserved
Bit 4-3: WGM3[3:2] = 01 (Fast PWM, Part 2)
Bit 2-0: CS3[2:0] = 001 (No prescaler)

// OCR3A (Output Compare Register A)
0-255: PWM Duty Cycle
```

**Warum 31kHz?**
- Oberhalb menschlichem Hörbereich (20kHz)
- Laufruhiger Motorbetrieb
- Weniger Vibrationen
- Bessere Effizienz

---

## 🖥️ DISPLAY-UPDATE-LOGIK

### Flacker-freies Update

**Problem bei fillScreen():**
```
Zeit →
 0ms: fillScreen(BLACK)  ← Display schwarz (sichtbar!)
50ms: Text schreiben     ← Text erscheint
100ms: fillScreen(BLACK) ← Display schwarz (Flackern!)
150ms: Text schreiben
...
```

**Lösung: Text mit Hintergrund:**
```cpp
// FALSCH (flackert):
tft.setTextColor(ST77XX_CYAN);
tft.fillScreen(ST77XX_BLACK);  // ← Komplett löschen
tft.print("MOTOR MODUS");

// RICHTIG (kein Flackern):
tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);  // ← Mit Hintergrund!
tft.print("MOTOR MODUS   ");  // ← Leerzeichen überschreiben alte Zeichen
```

### Layout-Positionierung

**Y-Positionen (kompakt für 128px Höhe):**
```
Y-Pos  | Element                  | Textgröße
─────────────────────────────────────────────
Y=2    | Überschrift (Modus)      | 2 (16px)
Y=24   | Geschwindigkeit          | 1 (8px)
Y=37   | Richtung                 | 1 (8px)
Y=53   | Motortyp/Gleis-Header    | 1 (8px)
Y=71   | Tasten-Header            | 1 (8px)
Y=83   | Tasten Zeile 1           | 1 (8px)
Y=95   | Tasten Zeile 2           | 1 (8px)
Y=107  | (Reserve)                | 1 (8px)
Y=115  | Licht=Wechsel            | 1 (8px)
Y=123  | (Ende Text bei Y=115+8)
Y=128  | (Display-Ende)
```

**Gesamt:** 115 + 8 = 123px → passt in 128px Display! ✅

---

## 📡 IR-PROTOKOLL-HANDLER

### RC5-Protokoll Details

**RC5 Format:**
```
┌─────┬─────┬─────────┬──────────────┐
│ S1  │ S2  │ Toggle  │   Address    │   Command   │
│ (1) │ (1) │  (1)    │    (5)       │    (6)      │
└─────┴─────┴─────────┴──────────────┴─────────────┘
  13    12      11        10-6            5-0

Gesamt: 14 Bits (inkl. Start-Bits)
```

**Cygnus-Rail-Spezifikation:**
- Address: 0x18 (binär: 11000)
- Commands: siehe Tabelle
- Toggle-Bit: Wechselt bei jedem Tastendruck

**Repeat-Detection:**
```cpp
bool repeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

if (!repeat) {
  // Nur bei NEUEM Tastendruck ausführen
  directionForward = !directionForward;
}
```

**Warum wichtig?**
- Vermeidet ungewollte Mehrfach-Auslösung
- Taste gedrückt halten = mehrere Signale
- Toggle-Funktionen nur bei neuem Tastendruck

---

## 🔨 ANPASSUNGEN & ERWEITERUNGEN

### Eigene Motortypen hinzufügen

```cpp
// 1. Enum erweitern
enum MotorType {
  MOTOR_3POL,
  MOTOR_5POL,
  MOTOR_GLOCKENANKER,
  MOTOR_HOCHLEISTUNG,
  MOTOR_CUSTOM  // ← Neu
};

// 2. calculatePWM() erweitern
case MOTOR_CUSTOM:
  // Eigene Kennlinie
  return map(constrain(pow(speed, 1.8) * 100, 0, 100), 
             0, 100, 30, 200);
  
// 3. Display-Text hinzufügen
case MOTOR_CUSTOM:
  tft.print("Custom    ");
  break;
```

### Mehr Abstellgleise

```cpp
// 1. Pins definieren
#define RELAY_ABSTELLGLEIS_5  26
#define RELAY_ABSTELLGLEIS_6  27

// 2. Array erweitern
bool abstellgleis[6] = {false, false, false, false, false, false};

// 3. Setup erweitern
pinMode(RELAY_ABSTELLGLEIS_5, OUTPUT);
pinMode(RELAY_ABSTELLGLEIS_6, OUTPUT);

// 4. handleIR() erweitern (weitere IR-Codes)
case 0x55:  // Neue Taste
  abstellgleis[4] = !abstellgleis[4];
  digitalWrite(RELAY_ABSTELLGLEIS_5, abstellgleis[4] ? LOW : HIGH);
  break;
```

### Geschwindigkeits-Schritte ändern

```cpp
// Aktuell: ±5%
case 0x10:  // +
  speedPercent = min(100, speedPercent + 5);
  break;

// Feiner (±1%):
case 0x10:
  speedPercent = min(100, speedPercent + 1);
  break;

// Gröber (±10%):
case 0x10:
  speedPercent = min(100, speedPercent + 10);
  break;
```

### Display-Update-Rate ändern

```cpp
// Aktuell: 300ms
const unsigned long DISPLAY_UPDATE_INTERVAL = 300;

// Schneller (200ms):
const unsigned long DISPLAY_UPDATE_INTERVAL = 200;

// Langsamer (500ms, schont Display):
const unsigned long DISPLAY_UPDATE_INTERVAL = 500;
```

### PWM-Frequenz ändern

```cpp
// Aktuell: 31kHz (Prescaler 1, 8-bit)
void setupPWM_Timer3() {
  TCCR3A = _BV(COM3A1) | _BV(WGM30);
  TCCR3B = _BV(WGM32) | _BV(CS30);  // CS30 = Prescaler 1
}

// 15.6kHz (Prescaler 2):
TCCR3B = _BV(WGM32) | _BV(CS31);

// 7.8kHz (Prescaler 4):
TCCR3B = _BV(WGM32) | _BV(CS30) | _BV(CS31);

// 3.9kHz (Prescaler 8):
TCCR3B = _BV(WGM32) | _BV(CS32);
```

**Achtung:** Niedrigere Frequenzen können hörbar werden!

---

## 📈 PERFORMANCE-OPTIMIERUNG

### Aktueller Ressourcen-Verbrauch

```
Flash Memory:    ~18KB / 256KB (7%)
SRAM:           ~1.2KB / 8KB (15%)
Loop Time:      ~2-5ms (ohne Display-Update)
                ~50-80ms (mit Display-Update)
```

### Optimierungs-Möglichkeiten

**1. String-Konstanten in PROGMEM:**
```cpp
const char msg_motor[] PROGMEM = "MOTOR MODUS";
// Spart SRAM, nutzt Flash
```

**2. Display-Buffer reduzieren:**
```cpp
// Nur geänderte Bereiche updaten
if (speedPercent != lastSpeedPercent) {
  // Nur Geschwindigkeits-Zeile updaten
}
```

**3. Loop-Optimierung:**
```cpp
// Nicht in jedem Loop-Durchlauf:
if (millis() - lastCheck > 100) {
  // Nur alle 100ms
}
```

---

## 🐛 DEBUGGING

### Serial Debug Output

**Aktivieren:**
```cpp
#define DEBUG 1  // Am Anfang der .ino

#ifdef DEBUG
  Serial.print("Speed: ");
  Serial.println(speedPercent);
#endif
```

**Status-Ausgabe:**
```
Mode:MOTOR Speed:45% PWM:150 Dir:V Motor:1
Mode:GLEIS Speed:30% PWM:90 Dir:R Gleise:1010
```

### Häufige Fehler

**1. Display flackert:**
→ `fillScreen()` entfernen, Text mit Hintergrund schreiben

**2. Relais schalten nicht:**
→ Prüfen: Aktiv LOW? `digitalWrite(pin, LOW)` schaltet ein

**3. Motor läuft nicht:**
→ Prüfen: `STBY` auf HIGH? PWM > 0?

**4. IR funktioniert nicht:**
→ Prüfen: RC5 Address 0x18? Batterie in Fernbedienung?

---

**Ende der Software-Dokumentation**

Für Code-Beispiele siehe:
- Cygnus_Rail_Controller.ino (Haupt-Code)
- Arduino Reference: https://www.arduino.cc/reference/en/
