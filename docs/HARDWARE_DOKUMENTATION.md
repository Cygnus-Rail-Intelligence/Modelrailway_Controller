# HARDWARE-DOKUMENTATION
## Cygnus-Rail Controller - Komponenten & Verdrahtung

**Version:** 2.3b  
**Datum:** Februar 2026

---

## 📋 INHALTSVERZEICHNIS

1. [Komponenten-Übersicht](#komponenten-übersicht)
2. [Detaillierte Spezifikationen](#detaillierte-spezifikationen)
3. [Pin-Belegung Arduino Mega](#pin-belegung-arduino-mega)
4. [Verdrahtungsplan](#verdrahtungsplan)
5. [Stromversorgung](#stromversorgung)
6. [Schaltplan](#schaltplan)
7. [Montage-Hinweise](#montage-hinweise)

---

## 🔧 KOMPONENTEN-ÜBERSICHT

### Erforderliche Komponenten

| Nr | Komponente | Typ/Spezifikation | Anzahl | Preis ca. |
|----|-----------|-------------------|--------|-----------|
| 1 | Mikrocontroller | Arduino Mega 2560 R3 | 1 | 35€ |
| 2 | TFT Display | AZDelivery ST7735 v1.2, 1.8", 128x160 | 1 | 10€ |
| 3 | Motortreiber | TB6612FNG Breakout Board | 1 | 8€ |
| 4 | IR-Empfänger | TSOP38238 oder ähnlich (38kHz) | 1 | 2€ |
| 5 | Relais-Module | 5V Relais-Modul, 1-Kanal | 4 | 8€ |
| 6 | Fernbedienung | IR-Fernbedienung (RC5) | 1 | vorhanden |
| 7 | Netzteil Arduino | 9V/1A DC, 2.1mm Hohlstecker | 1 | 8€ |
| 8 | Netzteil Motor | 12-24V DC, je nach Motor | 1 | 15€ |
| 9 | Steckbrett | 830 Pins (optional, für Tests) | 1 | 5€ |
| 10 | Jumper-Kabel | Dupont Kabel M-M, M-F | 1 Set | 5€ |

**Gesamt-Kosten:** ca. 96€ (ohne RC5-Fernbedienung (kompatibel mit Modellbahn-Systemen))

---

## 📐 DETAILLIERTE SPEZIFIKATIONEN

### 1. Arduino Mega 2560 R3

**Technische Daten:**
```
Microcontroller:     ATmega2560
Operating Voltage:   5V
Input Voltage:       7-12V (recommended: 9V)
Digital I/O Pins:    54 (15 PWM)
Analog Input Pins:   16
DC per I/O Pin:      40mA
DC for 3.3V Pin:     50mA
Flash Memory:        256 KB (8 KB Bootloader)
SRAM:               8 KB
EEPROM:             4 KB
Clock Speed:        16 MHz
```

**Verwendete Pins:**
- Pin 5: PWM Motor (Timer3, 31kHz)
- Pin 6: STBY (Motor Standby)
- Pin 7: AIN1 (Motor Richtung A)
- Pin 8: AIN2 (Motor Richtung B)
- Pin 10, 11: Relais Abstellgleis 1 & 2
- Pin 22: IR-Empfänger
- Pin 24, 25: Relais Abstellgleis 3 & 4
- Pin 47: Display DC (A0)
- Pin 48: Display CS
- Pin 49: Display Reset
- Pin 51: Display SDA (MOSI)
- Pin 52: Display SCK (SCLK)

### 2. AZDelivery ST7735 Display v1.2

**Spezifikationen:**
```
Display:             1.8 Zoll TFT LCD
Auflösung:           128 x 160 Pixel
Farben:              65K (16-bit RGB565)
Controller:          ST7735S
Interface:           SPI (4-Wire)
Betriebsspannung:    3.3V/5V (mit Level Shifter)
Stromaufnahme:       ~60mA (Backlight an)
Backlight:           LED (fest oder PWM-dimmbar)
SD-Card:             Micro SD (nicht genutzt)
Abmessungen:         51mm x 35mm x 5mm
```

**Pin-Beschriftung (von oben nach unten):**
1. LED - Backlight (an 5V)
2. SCK - SPI Clock (Pin 52)
3. SDA - SPI Data/MOSI (Pin 51)
4. A0 - Data/Command (Pin 47)
5. Reset - Reset (Pin 49)
6. CS - Chip Select (Pin 48)
7. GND - Masse
8. VCC - Stromversorgung 5V

**Besonderheit:** Pin "A0" ist NICHT Analog-Pin A0 vom Arduino!
A0 = DC (Data/Command Select)

### 3. TB6612FNG Motortreiber

**Spezifikationen:**
```
Chip:                TB6612FNG
Kanäle:              2 (Dual H-Bridge)
Operating Voltage:   4.5V - 13.5V (VM)
Logic Voltage:       2.7V - 5.5V (VCC)
Output Current:      1.2A (Average per channel)
Peak Current:        3.2A (per channel)
PWM Frequency:       Max 100kHz (configured: 31kHz)
Thermal Shutdown:    Ja (TSD)
Protection:          Short-Circuit, Thermal
Abmessungen:         20mm x 20mm
```

**Pin-Out:**
```
VM   - Motor Versorgung (12-24V)
VCC  - Logic Versorgung (5V vom Arduino)
GND  - Gemeinsame Masse
PWMA - PWM Signal (Pin 5, 31kHz)
AIN1 - Richtung A (Pin 7)
AIN2 - Richtung B (Pin 8)
STBY - Standby (Pin 6, HIGH = aktiv)
A01  - Motor Ausgang +
A02  - Motor Ausgang -
```

**Funktionsweise:**
- STBY HIGH: Treiber aktiv
- AIN1=HIGH, AIN2=LOW: Vorwärts
- AIN1=LOW, AIN2=HIGH: Rückwärts
- PWMA: Geschwindigkeit (0-255)

### 4. TSOP38238 IR-Empfänger

**Spezifikationen:**
```
Typ:                 IR Receiver Module
Carrier Frequency:   38kHz
Protocol:            RC5, RC6, NEC, etc.
Operating Voltage:   2.5V - 5.5V
Current:             ~0.4mA
Range:               bis 8m
View Angle:          ±45°
Output:              Active LOW
Pin-Out:             1-OUT, 2-GND, 3-VCC
```

**Anschluss:**
```
Pin 1 (OUT)  → Arduino Pin 22
Pin 2 (GND)  → Arduino GND
Pin 3 (VCC)  → Arduino 5V
```

**Wichtig:** 
- Nicht in Metallgehäuse einbauen (IR-Störungen!)
- Mindestens 10cm Abstand zu Motor/Relais
- Freie Sicht zur Fernbedienung

### 5. 5V Relais-Module (4 Stück)

**Spezifikationen:**
```
Coil Voltage:        5V DC
Contact Rating:      10A @ 250V AC / 30V DC
Contact Type:        SPDT (Single Pole Double Throw)
Trigger:             Aktiv LOW (LOW = geschaltet)
LED Indicator:       Ja (schaltet bei LOW)
Protection:          Flyback Diode
Isolation:           Optokoppler
Dimensions:          38mm x 15mm x 18mm
```

**Anschluss (pro Relais):**
```
VCC  → Arduino 5V
GND  → Arduino GND
IN   → Arduino Pin (10, 11, 24, 25)
COM  → Weichen-Stromversorgung
NO   → Weiche Richtung A (Normally Open)
NC   → Weiche Richtung B (Normally Closed)
```

**Funktionsweise:**
- IN = HIGH: Relais aus, COM-NC verbunden
- IN = LOW: Relais ein, COM-NO verbunden
- LED leuchtet wenn Relais ein (LOW)

### 6. Cygnus-Rail IR-Fernbedienung

**Protokoll:**
```
Standard:            Philips RC5
Carrier:             36kHz (kompatibel mit 38kHz Empfänger)
Address:             0x18 (Cygnus-Rail Standard)
Data Bits:           7 Bit Command
Toggle Bit:          Ja (für Repeat-Detection)
```

**Tasten-Codes:**
```
Taste 1:      0x51
Taste 2:      0x52
Taste 3:      0x53
Taste 4:      0x54
Licht:        0x50
Plus (+):     0x10
Minus (-):    0x11
Richtung:     0x0D
```

**Batterie:** 2x AAA (nicht im Lieferumfang)

---

## 📍 PIN-BELEGUNG ARDUINO MEGA

### Komplette Übersicht

```
═══════════════════════════════════════════════════════════════
                    ARDUINO MEGA 2560 PIN-MAP
═══════════════════════════════════════════════════════════════

POWER PINS:
  5V     → Display VCC, IR VCC, Relais VCC, TB6612 VCC
  GND    → Gemeinsame Masse (alle Komponenten)
  Vin    → Nicht verwendet (9V über DC-Buchse)

MOTOR CONTROL (TB6612):
  Pin 5  (PWM)  → TB6612 PWMA (31kHz Timer3)
  Pin 6  (Dig)  → TB6612 STBY
  Pin 7  (Dig)  → TB6612 AIN1
  Pin 8  (Dig)  → TB6612 AIN2

RELAIS ABSTELLGLEISE:
  Pin 10 (Dig)  → Relais 1 IN (Abstellgleis 1)
  Pin 11 (Dig)  → Relais 2 IN (Abstellgleis 2)
  Pin 24 (Dig)  → Relais 3 IN (Abstellgleis 3)
  Pin 25 (Dig)  → Relais 4 IN (Abstellgleis 4)

IR-EMPFÄNGER:
  Pin 22 (Dig)  → TSOP38238 OUT

TFT DISPLAY (SPI):
  Pin 47 (Dig)  → Display A0 (DC - Data/Command)
  Pin 48 (Dig)  → Display CS (Chip Select)
  Pin 49 (Dig)  → Display Reset
  Pin 51 (MOSI) → Display SDA (SPI Data)
  Pin 52 (SCK)  → Display SCK (SPI Clock)

UNUSED PINS:
  Pin 50 (MISO) → Frei (für SD-Card verwendbar)
  Pin 53 (SS)   → Frei (für weitere SPI-Geräte)

═══════════════════════════════════════════════════════════════
```

### Pin-Gruppen nach Funktion

**SPI-Bus (Display):**
- MOSI (Pin 51), SCK (Pin 52) = Shared SPI
- CS (Pin 48), DC (Pin 47), RST (Pin 49) = Display-spezifisch

**PWM-fähige Pins:**
- Pin 5 = Motor PWM (Timer3, 31kHz konfiguriert)
- Andere PWM-Pins bleiben frei für Erweiterungen

**Digital I/O:**
- Pins 6-8: Motor-Steuerung
- Pins 10-11, 24-25: Relais
- Pin 22: IR-Empfänger

---

## 🔌 VERDRAHTUNGSPLAN

### Komplett-Übersicht Verdrahtung

```
┌──────────────────────────────────────────────────────────────┐
│                     ARDUINO MEGA 2560                        │
├──────────────────────────────────────────────────────────────┤
│                                                              │
│  5V  ─┬─── Display VCC                                      │
│       ├─── Display LED                                      │
│       ├─── IR-Empfänger VCC                                 │
│       ├─── Relais 1-4 VCC                                   │
│       └─── TB6612 VCC                                       │
│                                                              │
│  GND ─┴─── Gemeinsame Masse (alle Komponenten)             │
│                                                              │
│  Pin 5  ───── TB6612 PWMA                                   │
│  Pin 6  ───── TB6612 STBY                                   │
│  Pin 7  ───── TB6612 AIN1                                   │
│  Pin 8  ───── TB6612 AIN2                                   │
│                                                              │
│  Pin 10 ───── Relais 1 IN                                   │
│  Pin 11 ───── Relais 2 IN                                   │
│  Pin 24 ───── Relais 3 IN                                   │
│  Pin 25 ───── Relais 4 IN                                   │
│                                                              │
│  Pin 22 ───── IR-Empfänger OUT                              │
│                                                              │
│  Pin 47 ───── Display A0 (DC)                               │
│  Pin 48 ───── Display CS                                    │
│  Pin 49 ───── Display Reset                                 │
│  Pin 51 ───── Display SDA                                   │
│  Pin 52 ───── Display SCK                                   │
│                                                              │
└──────────────────────────────────────────────────────────────┘

┌──────────────────┐       ┌──────────────────┐
│  TB6612          │       │  MOTOR           │
├──────────────────┤       ├──────────────────┤
│ VM  ← 12-24V DC  │       │                  │
│ VCC ← 5V Arduino │       │                  │
│ GND ← GND        │       │                  │
│ A01 ────────────────────→│ +                │
│ A02 ────────────────────→│ -                │
└──────────────────┘       └──────────────────┘

┌──────────────────┐       ┌──────────────────┐
│  RELAIS 1-4      │       │  ABSTELLGLEIS    │
├──────────────────┤       ├──────────────────┤
│ COM ← Versorg. + │       │                  │
│ NO  ────────────────────→│ Weiche Richt. A  │
│ NC  ────────────────────→│ Weiche Richt. B  │
└──────────────────┘       └──────────────────┘
```

### Schritt-für-Schritt Verkabelung

#### SCHRITT 1: Stromversorgung (WICHTIG: ZUERST!)

```
1. Arduino GND → Gemeinsame Masse-Schiene
2. Arduino 5V → 5V-Schiene
3. Display GND → Masse-Schiene
4. Display VCC → 5V-Schiene
5. Display LED → 5V-Schiene (oder PWM für Dimmen)
6. IR GND → Masse-Schiene
7. IR VCC → 5V-Schiene
8. Relais 1-4 GND → Masse-Schiene
9. Relais 1-4 VCC → 5V-Schiene
10. TB6612 VCC → 5V-Schiene
11. TB6612 GND → Masse-Schiene
```

**Prüfung:** LED am Display sollte leuchten (blau/weiß)

#### SCHRITT 2: Display-Verbindungen (SPI)

```
Display SCK   → Arduino Pin 52 (SCLK)
Display SDA   → Arduino Pin 51 (MOSI)
Display A0    → Arduino Pin 47 (DC)
Display Reset → Arduino Pin 49 (RST)
Display CS    → Arduino Pin 48 (CS)
```

**Kabellänge:** Max. 20cm für stabiles SPI-Signal

#### SCHRITT 3: Motor-Treiber (TB6612)

```
TB6612 PWMA → Arduino Pin 5
TB6612 AIN1 → Arduino Pin 7
TB6612 AIN2 → Arduino Pin 8
TB6612 STBY → Arduino Pin 6
TB6612 VM   → Motor-Netzteil + (12-24V)
TB6612 GND  → Motor-Netzteil - UND Arduino GND
TB6612 A01  → Motor +
TB6612 A02  → Motor -
```

**WICHTIG:** Gemeinsame Masse zwischen Arduino und Motor-Netzteil!

#### SCHRITT 4: Relais-Module

```
Relais 1 IN → Arduino Pin 10
Relais 2 IN → Arduino Pin 11
Relais 3 IN → Arduino Pin 24
Relais 4 IN → Arduino Pin 25

Je Relais:
  COM → Weichen-Stromversorgung +
  NO  → Weiche Spule Richtung A
  NC  → Weiche Spule Richtung B
```

#### SCHRITT 5: IR-Empfänger

```
IR OUT → Arduino Pin 22
IR GND → Masse
IR VCC → 5V
```

**Position:** Freie Sicht zur Fernbedienung, min. 10cm von Relais

---

## ⚡ STROMVERSORGUNG

### Spannungs-Übersicht

```
┌─────────────────────────────────────────────────────────────┐
│  KOMPONENTE          │  SPANNUNG  │  STROM      │  QUELLE   │
├─────────────────────────────────────────────────────────────┤
│  Arduino Mega        │  9V        │  ~200mA     │  Netzteil │
│  Display (5V Logik)  │  5V        │  ~60mA      │  Arduino  │
│  IR-Empfänger        │  5V        │  ~0.4mA     │  Arduino  │
│  Relais (4x)         │  5V        │  ~280mA     │  Arduino  │
│  TB6612 Logik        │  5V        │  ~10mA      │  Arduino  │
│  TB6612 Motor        │  12-24V    │  bis 1.2A   │  Extern   │
├─────────────────────────────────────────────────────────────┤
│  GESAMT 5V           │  5V        │  ~550mA     │           │
└─────────────────────────────────────────────────────────────┘
```

### Netzteile

**Arduino-Netzteil:**
- Spannung: 9V DC (7-12V möglich)
- Strom: min. 1A (empfohlen: 1.5A)
- Anschluss: 2.1mm DC-Hohlstecker (Center Positive)
- Typ: Schaltnetzteil oder Trafo

**Motor-Netzteil:**
- Spannung: 12-24V DC (je nach Motor)
- Strom: min. 1.5A (je nach Motor)
- Gemeinsame Masse mit Arduino!
- Typ: Schaltnetzteil (stabilisiert)

### Stromverbrauch-Kalkulation

```
5V Rail (vom Arduino):
  Display:      60mA
  IR:            0.4mA
  4x Relais:    280mA (70mA je)
  TB6612 Logik: 10mA
  Reserve:      150mA
  ─────────────────
  GESAMT:       ~500mA

Arduino Mega kann liefern: max. 800mA (über Vin)
→ Ausreichend! ✅
```

**Bei mehr als 4 Relais:** Externes 5V Netzteil empfohlen!

### Masse-Verbindung (KRITISCH!)

```
                   ┌─────────────┐
                   │  Masse-Rail │
                   └──────┬──────┘
                          │
          ┌───────────────┼───────────────┐
          │               │               │
     Arduino GND    Motor-Netzteil    Relais-GND
                         GND
```

**Alle GND-Pins MÜSSEN verbunden sein!**

---

## 📊 SCHALTPLAN

### Vereinfachter Schaltplan

```
                    ┌────────────────────┐
                    │  ARDUINO MEGA 2560 │
                    └─────────┬──────────┘
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
        │                     │                     │
   ┌────▼────┐           ┌───▼───┐            ┌────▼────┐
   │ TB6612  │           │  TFT  │            │ IR-RX   │
   │ Motor   │           │ SPI   │            │ Pin 22  │
   │ Driver  │           │Display│            │ RC5     │
   └────┬────┘           └───────┘            └─────────┘
        │
   ┌────▼────┐
   │  MOTOR  │
   │ 12-24V  │
   └─────────┘

        │
   ┌────┴────┬─────────┬─────────┬─────────┐
   │         │         │         │         │
┌──▼──┐  ┌──▼──┐  ┌──▼──┐  ┌──▼──┐
│ REL │  │ REL │  │ REL │  │ REL │
│  1  │  │  2  │  │  3  │  │  4  │
└──┬──┘  └──┬──┘  └──┬──┘  └──┬──┘
   │        │        │        │
   ▼        ▼        ▼        ▼
Gleis 1  Gleis 2  Gleis 3  Gleis 4
```

---

## 🔨 MONTAGE-HINWEISE

### Reihenfolge der Montage

1. **Testaufbau auf Steckbrett**
   - Alle Komponenten testen
   - Software debuggen
   - Kabel-Längen ermitteln

2. **Gehäuse vorbereiten**
   - Ausschnitte für Display
   - Bohrungen für Arduino-Befestigung
   - Kabelkanäle planen

3. **Komponenten fixieren**
   - Arduino mit Abstandsbolzen
   - Display von vorne einsetzen
   - TB6612 nahe Motor-Anschluss
   - Relais gruppiert montieren

4. **Verkabelung**
   - Gemeinsame Masse-Schiene
   - Stromversorgung zuerst
   - Signal-Kabel danach
   - Beschriftung anbringen

5. **Tests**
   - Einzelne Funktionen testen
   - Volltest mit allen Komponenten
   - Langzeittest (24h)

### Kabel-Organisation

```
FARB-CODE (Empfehlung):
  ROT    → +5V / VCC
  SCHWARZ→ GND / Masse
  GELB   → PWM-Signale
  GRÜN   → Digital Signale
  BLAU   → SPI (Display)
  ORANGE → Motor-Anschluss
  WEISS  → Relais
```

### Schutz-Maßnahmen

✅ **Trennen der Masse-Ebenen:**
- Logik-Masse (Arduino, Display, IR)
- Leistungs-Masse (Motor, Relais)
- Verbunden nur an einem Punkt (Star-Ground)

✅ **EMI-Schutz:**
- Motor-Kabel verdrillen
- Relais-Kabel von Signal-Leitungen trennen
- Ferrit-Ringe an Motor-Leitungen

✅ **Schutz-Dioden:**
- Bereits in Relais-Modulen (Flyback)
- TB6612 hat interne Schutzschaltung

✅ **Sicherungen:**
- 1A Sicherung auf 5V-Schiene (optional)
- 2A Sicherung auf Motor-Netzteil

---

## 📏 ABMESSUNGEN & PLATZBEDARF

```
Komponente           L x B x H (mm)      Montage
─────────────────────────────────────────────────
Arduino Mega         101 x 54 x 15      4x M3 Bohrung
Display TFT          51 x 35 x 5        2x M2 Bohrung
TB6612 Board         20 x 20 x 5        2x M2.5 Bohrung
Relais-Modul (je)    38 x 15 x 18       2x M3 Bohrung
IR-Empfänger         6 x 6 x 7          Durchsteckmontage

GESAMT-PLATZBEDARF:
  Grundfläche: ~15cm x 12cm
  Höhe: ~4cm (ohne Kabel)
```

### Empfohlenes Gehäuse

```
Mindestgröße: 20cm x 15cm x 6cm
Material: ABS oder Aluminium
Features:
  - Lüftungsschlitze für TB6612
  - Display-Ausschnitt vorne
  - Kabelausgang hinten
  - Befestigungslöcher
```

---

## ⚠️ SICHERHEITSHINWEISE

### WARNUNG - ELEKTRISCHE SICHERHEIT

⚠️ **Netzspannung (230V):**
- Niemals Relais-Kontakte direkt an 230V!
- Nur niedrige Spannungen schalten (12-24V)
- Bei 230V: Optokoppler + professionelles Relais

⚠️ **Kurzschluss-Schutz:**
- Niemals Motor-Spannung (VM) mit 5V verbinden
- Polarität bei DC-Netzteilen beachten
- Sicherungen verwenden

⚠️ **Wärmeentwicklung:**
- TB6612 kann bei >1A warm werden
- Ausreichende Belüftung
- Optional: Kühlkörper auf TB6612

⚠️ **ESD-Schutz:**
- Vor Arbeit an Komponenten erden
- Display ist empfindlich gegen statische Entladung

---

**Ende der Hardware-Dokumentation**

Bei Fragen zur Hardware-Konfiguration siehe auch:
- VERKABELUNGS_CHECKLISTE.txt
- AZDELIVERY_PIN_BELEGUNG.txt
