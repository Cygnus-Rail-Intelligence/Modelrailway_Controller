# CYGNUS-RAIL IR-STEUERUNG MIT TFT-DISPLAY
## Professionelle Modellbahn-Steuerung mit Arduino Mega 2560

**Version:** 2.3b  
**Datum:** Februar 2026  
**Status:** Produktionsreif  
**Autor:** Gregor

---

## 📋 INHALTSVERZEICHNIS

1. [Projektübersicht](#projektübersicht)
2. [Features](#features)
3. [Hardware-Komponenten](#hardware-komponenten)
4. [Software-Features](#software-features)
5. [Dokumentations-Übersicht](#dokumentations-übersicht)
6. [Quick Start](#quick-start)
7. [Versionshistorie](#versionshistorie)

---

## 🎯 PROJEKTÜBERSICHT

Dieses Projekt realisiert eine professionelle Steuerung für Cygnus-Rail Modellbahnen mit folgenden Hauptfunktionen:

- **IR-Fernsteuerung** über RC5-Protokoll-Fernbedienung
- **Motorsteuerung** mit 31kHz PWM für vier verschiedene Motortypen
- **4 Abstellgleise** mit individueller Relais-Steuerung
- **TFT-Display** (1.8", 128x160) für visuelle Statusanzeige
- **Zwei Betriebsmodi:** Motortyp-Auswahl und Abstellgleis-Steuerung

### Hauptmerkmale

✅ **Laufruhige Motorsteuerung** durch 31kHz PWM-Frequenz  
✅ **Flackerfreies Display** durch intelligentes Update-Management  
✅ **Flexible Motortypen** mit angepassten Kennlinien  
✅ **Einfache Bedienung** über RC5-Fernbedienung (kompatibel mit Modellbahn-Systemen)  
✅ **Visuelle Rückmeldung** über Farb-TFT-Display  
✅ **Robuste Relais-Steuerung** für Weichen/Abstellgleise  

---

## 🎨 FEATURES

### Motorsteuerung
- **4 Motortypen** mit spezifischen Kennlinien:
  - 3-Pol Motor (Linear, 95-255 PWM)
  - 5-Pol Motor (Quadratisch, 75-255 PWM)
  - Glockenanker (Potenz 1.6, 45-220 PWM)
  - Hochleistung (Potenz 1.3, 60-240 PWM)
- **31kHz PWM** für lauflosen Betrieb
- **Stufenlose Geschwindigkeitsregelung** (0-100%)
- **Richtungsumkehr** auf Knopfdruck
- **TB6612 Motortreiber** für zuverlässige Leistung

### Abstellgleis-Steuerung
- **4 unabhängige Relais** (Pins 10, 11, 24, 25)
- **Toggle-Funktion:** Ein/Aus bei jedem Tastendruck
- **Dauerhafte Schaltung:** Relais bleiben in Position
- **Status-Anzeige** auf Display (Grün=EIN, Rot=AUS)

### Display-System
- **AZDelivery ST7735 v1.2** (1.8" TFT, 128x160)
- **Farb-Codierung:**
  - Cyan: Modus-Überschrift
  - Gelb: Geschwindigkeit, Hinweise
  - Grün: Richtung Vorwärts, Abstellgleis EIN
  - Rot: Abstellgleis AUS
  - Magenta: Tastenbelegung
  - Weiß: Allgemeine Infos
- **Flackerfreies Update** (kein fillScreen)
- **Intelligentes Change-Detection** (nur bei Änderungen)
- **Update-Rate:** 300ms

### Bedienung
- **Licht-Taste:** Modusumschaltung (Motortyp ↔ Abstellgleis)
- **Tasten 1-4:**
  - Motortyp-Modus: Motorauswahl
  - Abstellgleis-Modus: Gleis 1-4 schalten
- **Taste +/-:** Geschwindigkeit anpassen
- **Taste Richtung:** Vorwärts/Rückwärts umschalten

---

## 🔧 HARDWARE-KOMPONENTEN

### Hauptkomponenten

| Komponente | Typ/Modell | Funktion |
|-----------|------------|----------|
| Mikrocontroller | Arduino Mega 2560 | Hauptsteuerung |
| Display | AZDelivery ST7735 v1.2 (1.8", 128x160) | Statusanzeige |
| Motortreiber | TB6612FNG | Motorsteuerung mit 31kHz PWM |
| IR-Empfänger | TSOP38238 o.ä. | RC5 Signal-Empfang |
| Fernbedienung | Cygnus-Rail IR-Fernbedienung | Bedienung |
| Relais-Module | 4x 5V Relais | Abstellgleis-Schaltung |
| Netzteil Arduino | 9V/1A DC | Arduino-Versorgung |
| Netzteil Motor | 12-24V DC | Motor-Versorgung |

### Technische Spezifikationen

**Arduino Mega 2560:**
- Microcontroller: ATmega2560
- Operating Voltage: 5V
- Input Voltage: 7-12V (empfohlen: 9V)
- Digital I/O Pins: 54
- PWM Pins: 15
- Flash Memory: 256 KB

**AZDelivery ST7735 Display:**
- Größe: 1.8 Zoll
- Auflösung: 128x160 Pixel
- Farben: 65K (16-bit RGB)
- Interface: SPI (4-Wire)
- Controller: ST7735S
- Betriebsspannung: 3.3V/5V

**TB6612 Motortreiber:**
- Dual Motor Driver
- Operating Voltage: 4.5V - 13.5V
- Output Current: 1.2A (Average), 3.2A (Peak)
- PWM Frequency: 31kHz (konfiguriert)
- Built-in Thermal Shutdown

**Relais-Module:**
- Typ: 5V Relais-Module
- Schaltspannung: 250V AC / 30V DC
- Schaltstrom: 10A
- Ansteuerung: Aktiv LOW
- Isolation: Optokoppler

---

## 💻 SOFTWARE-FEATURES

### Betriebsmodi

#### 1. MOTORTYP-MODUS (Standard)
Auswahl und Steuerung verschiedener Motortypen:
- Taste 1: 3-Pol Motor
- Taste 2: 5-Pol Motor (Standard)
- Taste 3: Glockenanker
- Taste 4: Hochleistung

#### 2. ABSTELLGLEIS-MODUS
Steuerung von 4 Abstellgleisen:
- Taste 1-4: Toggle Gleis 1-4 (EIN/AUS)
- Status-Anzeige: Grün=EIN, Rot=AUS

### PWM-Kennlinien

```cpp
// 3-Pol Motor (Linear)
PWM = map(speed, 5%, 100%, 95, 255)

// 5-Pol Motor (Quadratisch)
PWM = map(speed², 0%, 100%, 75, 255)

// Glockenanker (Potenz 1.6)
PWM = map(speed^1.6, 0%, 100%, 45, 220)

// Hochleistung (Potenz 1.3)
PWM = map(speed^1.3, 0%, 100%, 60, 240)
```

### IR-Protokoll (RC5)

**Address:** 0x18 (Cygnus-Rail Standard)

| Taste | Command | Funktion |
|-------|---------|----------|
| Taste 1 | 0x51 | Motor 3-Pol / Gleis 1 |
| Taste 2 | 0x52 | Motor 5-Pol / Gleis 2 |
| Taste 3 | 0x53 | Motor Glockenanker / Gleis 3 |
| Taste 4 | 0x54 | Motor Hochleistung / Gleis 4 |
| Licht | 0x50 | Modus umschalten |
| + | 0x10 | Geschwindigkeit +5% |
| - | 0x11 | Geschwindigkeit -5% |
| Richtung | 0x0D | Vorwärts ↔ Rückwärts |

---

## 📚 DOKUMENTATIONS-ÜBERSICHT

Das Projekt umfasst folgende Dokumentations-Dateien:

### Haupt-Dokumentation
- **README_KOMPLETT.md** (diese Datei) - Projektübersicht
- **HARDWARE_DOKUMENTATION.md** - Detaillierte Hardware-Beschreibung
- **SOFTWARE_DOKUMENTATION.md** - Code-Struktur und Funktionen
- **BEDIENUNGSANLEITUNG.md** - Benutzerhandbuch

### Installations-Anleitungen
- **VERKABELUNGS_CHECKLISTE.txt** - Schritt-für-Schritt Verkabelung
- **AZDELIVERY_PIN_BELEGUNG.txt** - Display-spezifische Pins
- **SCHNELLSTART.txt** - Quick Start Guide

### Spezial-Anleitungen
- **AZDELIVERY_ANLEITUNG.txt** - Display-spezifische Optimierungen
- **DISPLAY_ABSCHNITT_BEHOBEN.txt** - Layout-Optimierungen
- **CHANGELOG.txt** - Versionshistorie

---

## 🚀 QUICK START

### 1. Hardware aufbauen
```
1. Arduino Mega mit Netzteil (9V/1A)
2. Display anschließen (8 Pins - siehe VERKABELUNGS_CHECKLISTE.txt)
3. TB6612 Motortreiber verbinden (Pins 5-8)
4. IR-Empfänger an Pin 22
5. 4 Relais an Pins 10, 11, 24, 25
6. Motor an TB6612 (A01/A02)
```

### 2. Software installieren
```
1. Arduino IDE installieren
2. Libraries installieren:
   - IRremote (v3.x+)
   - Adafruit GFX Library
   - Adafruit ST7735
3. Cygnus_Rail_Controller.ino öffnen
4. Board: Arduino Mega 2560 auswählen
5. Port auswählen
6. Upload
```

### 3. Testen
```
1. Display zeigt: "CYGNUS-RAIL IR-Steuer." → "AZDelivery v1.2"
2. Nach 2 Sek: "MOTOR MODUS" mit allen Infos
3. Licht-Taste drücken → Modus wechselt
4. +/- Tasten → Geschwindigkeit ändert sich
5. Richtungstaste → Motor dreht um
6. Tasten 1-4 → Motortyp/Abstellgleis schalten
```

### Erwartetes Display
```
┌────────────────────────┐
│ MOTOR MODUS            │
│ Speed: 0% (0)          │
│ Richtung: Vorwaerts    │
│ Motortyp: 5-Pol        │
│ Tasten:                │
│ 1:3Pol 2:5Pol          │
│ 3:Glock 4:High         │
│                        │
│ Licht=Wechsel          │
└────────────────────────┘
```

---

## 📊 VERSIONSHISTORIE

### Version 2.3b (Februar 2026) - AKTUELL
✅ Display-Layout optimiert (Y-Positionen kompakter)
✅ Unterste Zeile "Licht=Wechsel" jetzt vollständig sichtbar
✅ Alle Texte innerhalb 128px Höhe
✅ AZDelivery ST7735 v1.2 vollständig unterstützt

### Version 2.3 (Februar 2026)
✅ Optimierung für AZDelivery ST7735 v1.2
✅ invertDisplay(true) für AZDelivery aktiviert
✅ SPI_CLOCK_DIV8 für schnellere Updates
✅ Pin-Belegung dokumentiert (LED, SCK, SDA, A0, Reset, CS, GND, VCC)

### Version 2.2 (Februar 2026)
✅ DollaTek ST7735 Unterstützung
✅ Offset-Korrektur Optionen
✅ Compilerfehler behoben (setColStart/setRowStart)

### Version 2.1 (Februar 2026)
✅ Relais Toggle-Funktion (dauerhaftes Halten)
✅ Display-Stabilität verbessert (kein fillScreen mehr)
✅ Hardware-Reset implementiert
✅ Abstellgleis 3&4 auf Pins 24&25 geändert

### Version 2.0 (Februar 2026)
✅ TFT Display Integration
✅ Zwei Betriebsmodi (Motortyp/Abstellgleis)
✅ 4 Abstellgleis-Relais
✅ Licht-Taste für Modusumschaltung
✅ 4 Motortypen statt 2

### Version 1.0 (Original)
- 31kHz PWM Motorsteuerung
- IR-Fernbedienung
- 2 Weichen-Relais
- Serielle Ausgabe

---

## 🎯 ANWENDUNGSBEREICHE

Dieses System eignet sich für:

✅ **Cygnus-Rail H0 Anlagen** mit digitalen und analogen Loks  
✅ **Rangier-Betrieb** mit präziser Geschwindigkeitskontrolle  
✅ **Abstellbahnhöfe** mit mehreren Gleisen  
✅ **Testaufbauten** für verschiedene Motortypen  
✅ **Modellbahn-Shows** mit visueller Statusanzeige  

---

## 📞 SUPPORT & WEITERENTWICKLUNG

### Mögliche Erweiterungen
- [ ] Stromverbrauch-Messung und Anzeige
- [ ] Temperatur-Überwachung TB6612
- [ ] EEPROM-Speicherung der letzten Einstellungen
- [ ] Akustisches Feedback über Buzzer
- [ ] Mehrere Lokomotiven (Adressierung)
- [ ] PC-Anbindung über USB/Serial
- [ ] WiFi-Modul für Smartphone-Steuerung

### Bekannte Einschränkungen
- Display-Update alle 300ms (ausreichend für Modellbahn)
- Maximale Motor-Spannung: 13.5V (TB6612 Limit)
- IR-Reichweite: ca. 5-8 Meter
- Keine Rückmeldung von Gleisbesetzung

---

## 📄 LIZENZ

Open Source - Frei verwendbar für private und kommerzielle Modellbahn-Projekte.

Bei Veröffentlichung bitte Autor nennen.

---

## ✅ QUALITÄTSSICHERUNG

Dieses Projekt wurde getestet mit:
- Arduino Mega 2560 R3
- AZDelivery ST7735 v1.2 Display
- Cygnus-Rail IR-Fernbedienung (RC5)
- Verschiedene Cygnus-Rail Motoren (3-Pol, 5-Pol, Glockenanker)
- 5V Relais-Module (aktiv LOW)
- TB6612FNG Motortreiber

**Status:** Produktionsreif ✅  
**Letzte Tests:** Februar 2026  
**Stabilität:** Hoch  

---

**Ende der Hauptdokumentation**

Siehe separate Dateien für detaillierte Hardware-, Software- und Bedienungs-Dokumentation.
