# 🚂 Cygnus-Rail Controller mit TFT-Display

**Arduino-basierte Steuerung für Analoge N und Z Modellbahnen mit TFT-Display**

Videolink per klick auf das Bild: [![Demo](https://img.youtube.com/vi/od9ymYdIktI/maxresdefault.jpg)](https://www.youtube.com/watch?v=od9ymYdIktI)

![Version](https://img.shields.io/badge/version-2.3b-blue.svg)
![License](https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-green.svg)
![Arduino](https://img.shields.io/badge/Arduino-Mega%202560-00979D.svg)
![Status](https://img.shields.io/badge/status-production%20ready-brightgreen.svg)

---

## 📋 Übersicht

Dieses Projekt realisiert eine vollständige IR-Fernsteuerung für Cygnus-Rail Modellbahnen mit visueller Rückmeldung über ein Farb-TFT-Display. Die Steuerung bietet präzise Geschwindigkeitsregelung für verschiedene Motortypen und individuelle Kontrolle von bis zu 4 Abstellgleisen.

### ✨ Hauptmerkmale

- 🎛️ **4 Motortypen** mit optimierten PWM-Kennlinien (3-Pol, 5-Pol, Glockenanker, Hochleistung)
- 🖥️ **1.8" Farb-TFT-Display** (128x160) mit flackerfreier Anzeige
- 📡 **IR-Fernbedienung** (RC5-Protokoll)
- 🔀 **4 Abstellgleise** mit individueller Relais-Steuerung / Alternativ Weichensteuerung
- ⚡ **31kHz PWM** für laufruhigen Motorbetrieb
- 🔄 **2 Betriebsmodi** (Motortyp-Auswahl / Abstellgleis-Steuerung)
- 📊 **Echtzeit-Statusanzeige** mit Farb-Codierung

---

## 🖼️ Screenshots

### Display-Modi

**Motor-Modus:**
```
┌────────────────────────┐
│ MOTOR MODUS            │ ← Cyan
│ Speed: 45% (150)       │ ← Gelb
│ Richtung: Vorwaerts    │ ← Grün
│ Motortyp: 5-Pol        │ ← Weiß
│ Tasten:                │
│ 1:3Pol 2:5Pol          │ ← Magenta
│ 3:Glock 4:High         │
│                        │
│ Licht=Wechsel          │ ← Gelb
└────────────────────────┘
```

**Abstellgleis-Modus:**
```
┌────────────────────────┐
│ ABSTELLGLEIS           │ ← Cyan
│ Speed: 30% (90)        │ ← Gelb
│ Richtung: Rueckwaerts  │ ← Grün
│ Abstellgleise:         │
│ Gleis 1: EIN           │ ← Grün
│ Gleis 2: AUS           │ ← Rot
│ Gleis 3: EIN           │ ← Grün
│ Gleis 4: AUS           │ ← Rot
│ Licht=Wechsel          │ ← Gelb
└────────────────────────┘
```

---

## 🔧 Hardware-Komponenten

| Komponente | Typ/Modell | Funktion | Kosten ca. |
|-----------|------------|----------|------------|
| Mikrocontroller | Arduino Mega 2560 | Hauptsteuerung | 35€ |
| Display | AZDelivery ST7735 v1.2 (1.8") | Statusanzeige | 10€ |
| Motortreiber | TB6612FNG | PWM-Motorsteuerung | 8€ |
| IR-Empfänger | TSOP38238 | RC5-Empfang | 2€ |
| Relais | 4x 5V Relais-Module | Abstellgleis-Schaltung | 8€ |
| Netzteile | 9V/1A + 12-24V | Stromversorgung | 20€ |
| **Gesamt** | | | **~85€** |

Kompatibel mit Infrarot-Fernbedienungen (z. B. Märklin* 00748)

* Märklin ist eine eingetragene Marke der Gebr. Märklin & Cie. GmbH.
Dieses Projekt steht in keiner Verbindung zu Märklin.
---

## 🚀 Quick Start

### 1. Hardware aufbauen

Siehe [HARDWARE_DOKUMENTATION.md](docs/HARDWARE_DOKUMENTATION.md) für detaillierte Verdrahtung.

**Minimal-Setup:**
```
Arduino Mega 2560
├── Display (Pins 47, 48, 49, 51, 52)
├── TB6612 Motortreiber (Pins 5, 6, 7, 8)
├── IR-Empfänger (Pin 22)
└── 4x Relais (Pins 10, 11, 24, 25)
```

### 2. Software installieren

**Bibliotheken (Arduino IDE):**
```
Tools → Manage Libraries...

1. IRremote (v4.x+)
2. Adafruit GFX Library
3. Adafruit ST7735
```

**Code hochladen:**
```
1. Cygnus_Rail_Controller.ino öffnen
2. Board: Arduino Mega 2560 auswählen
3. Port auswählen
4. Upload
```

### 3. Testen

1. Display zeigt: "CYGNUS-RAIL IR-Steuer."
2. Fernbedienung: Schieber auf Position 1
3. Taste + drücken → Motor fährt an
4. Fertig! 🎉

**Komplette Anleitung:** [BEDIENUNGSANLEITUNG.md](docs/BEDIENUNGSANLEITUNG.md)

---

## 📚 Dokumentation

| Dokument | Beschreibung |
|----------|--------------|
| [HARDWARE_DOKUMENTATION.md](docs/HARDWARE_DOKUMENTATION.md) | Komponenten, Verdrahtung, Schaltplan |
| [SOFTWARE_DOKUMENTATION.md](docs/SOFTWARE_DOKUMENTATION.md) | Code-Struktur, Funktionen, Anpassungen |
| [BEDIENUNGSANLEITUNG.md](docs/BEDIENUNGSANLEITUNG.md) | Benutzerhandbuch, Tipps, Troubleshooting |
| [VERKABELUNGS_CHECKLISTE.txt](docs/VERKABELUNGS_CHECKLISTE.txt) | Schritt-für-Schritt Verkabelung |
| [LICENSE.txt](LICENSE.txt) | Lizenzinformationen |

**Word-Dokument:** [CYGNUS-RAIL_IR_STEUERUNG_KOMPLETT.docx](docs/CYGNUS-RAIL_IR_STEUERUNG_KOMPLETT.docx) - Alle Dokumente zusammengefasst

---

## 🎨 Features im Detail

### Motorsteuerung

**4 optimierte Motortypen:**

| Motortyp | Kennlinie | PWM-Bereich | Ideal für |
|----------|-----------|-------------|-----------|
| 3-Pol | Linear | 95-255 | Ältere Cygnus-Rail-Loks |
| 5-Pol | Quadratisch | 75-255 | Moderne Standard-Motoren |
| Glockenanker | Potenz 1.6 | 45-220 | Präzisions-Rangierbetrieb |
| Hochleistung | Potenz 1.3 | 60-240 | Schwere Züge, Steigungen |

**31kHz PWM-Frequenz:**
- Unhörbar für Menschen (>20kHz)
- Laufruhiger Motorbetrieb
- Keine Vibrationen
- Timer3-basiert (Pin 5)

### Display-System

**Farb-Codierung:**
- 🔵 Cyan: Modus-Überschrift
- 🟡 Gelb: Geschwindigkeit, Hinweise
- 🟢 Grün: Richtung Vorwärts, Gleis EIN
- 🔴 Rot: Gleis AUS
- 🟣 Magenta: Tasten-Hilfe
- ⚪ Weiß: Allgemeine Infos

**Optimierungen:**
- Flackerfrei (kein fillScreen())
- Change Detection (nur bei Änderung)
- 300ms Update-Intervall
- Kompaktes Layout (alle Zeilen sichtbar)

### Controller

**RC5-Protokoll-Protokoll:**
- Address: 0x18
- Commands: 0x50-0x54, 0x0D, 0x10-0x11
- Repeat-Detection (Toggle-Bit)
- Reichweite: 5-8 Meter

**Tastenbelegung:**
- Taste 1-4: Motortyp / Gleis 1-4
- Licht: Modus umschalten
- +/-: Geschwindigkeit ±5%
- Richtung: Vorwärts ↔ Rückwärts

---

## 🛠️ Anpassungen

### Eigene Motortypen hinzufügen

```cpp
// In calculatePWM() ergänzen:
case MOTOR_CUSTOM:
  return map(constrain(pow(speed, 1.8) * 100, 0, 100), 
             0, 100, 30, 200);
```

### Mehr Abstellgleise

```cpp
#define RELAY_ABSTELLGLEIS_5  26
#define RELAY_ABSTELLGLEIS_6  27
// Array erweitern auf [6]
```

### Geschwindigkeits-Schritte ändern

```cpp
case 0x10:  // + Taste
  speedPercent = min(100, speedPercent + 10);  // ±10% statt ±5%
```

Siehe [SOFTWARE_DOKUMENTATION.md](docs/SOFTWARE_DOKUMENTATION.md) für Details.

---

## 📊 Versionshistorie

### Version 2.3b (Februar 2026) - **AKTUELL**
- ✅ Display-Layout optimiert (alle Zeilen sichtbar)
- ✅ Y-Positionen kompakter (128px Höhe)
- ✅ AZDelivery ST7735 v1.2 vollständig unterstützt

### Version 2.3 (Februar 2026)
- ✅ AZDelivery-spezifische Optimierungen
- ✅ invertDisplay(true) für korrekte Farben
- ✅ SPI_CLOCK_DIV8 für schnellere Updates

### Version 2.1 (Februar 2026)
- ✅ Relais Toggle-Funktion (dauerhaftes Halten)
- ✅ Display-Stabilität (kein Flackern)
- ✅ Hardware-Reset implementiert

### Version 2.0 (Februar 2026)
- ✅ TFT-Display Integration
- ✅ 2 Betriebsmodi
- ✅ 4 Motortypen
- ✅ 4 Abstellgleise

### Version 1.0 (Original)
- 31kHz PWM
- Controller
- 2 Weichen

Siehe [CHANGELOG.txt](CHANGELOG.txt) für Details.

---

## 🐛 Troubleshooting

### Display bleibt schwarz
→ LED-Pin mit 5V verbinden (Backlight)

### Motor läuft nicht
→ Geschwindigkeit > 20%, STBY auf HIGH prüfen

### Fernbedienung funktioniert nicht
→ Schieber auf Position 1, Batterien prüfen

### Relais schalten nicht
→ Modus = ABSTELLGLEIS, Verkabelung prüfen

**Mehr Hilfe:** [BEDIENUNGSANLEITUNG.md](docs/BEDIENUNGSANLEITUNG.md) → Fehlerbehebung

---

## 📜 Lizenz

Dieses Projekt steht unter **Dual-Lizenz**:

### ✅ Private Nutzung (Kostenlos)
**Creative Commons BY-NC-SA 4.0**
- Privater Nachbau erlaubt
- Anpassungen erlaubt
- Weitergabe unter gleicher Lizenz
- **Keine** kommerzielle Nutzung

### 💼 Kommerzielle Nutzung (Lizenzgebühr)
- Separate kommerzielle Lizenz erforderlich
- Kontakt: gregor.adis@me.com

**Details:** [LICENSE.txt](LICENSE.txt)

---

## 🤝 Beitragen

**Verbesserungen willkommen!**

1. Fork das Repository
2. Branch erstellen (`git checkout -b feature/verbesserung`)
3. Änderungen committen (`git commit -m 'Beschreibung'`)
4. Push zum Branch (`git push origin feature/verbesserung`)
5. Pull Request erstellen

**Bitte beachten:**
- Code-Style beibehalten
- Dokumentation aktualisieren
- Tests durchführen

---

## 📞 Kontakt & Support

**Autor:** Gregor Adis
**E-Mail:** gregor.adis@me.com
**GitHub:** https://github.com/Cygnus-Rail-Intelligence/Modelrailway_Controller

**Bei Fragen:**
- GitHub Issues für Bug-Reports
- Discussions für Fragen


---

## 🙏 Danksagungen

**Verwendete Bibliotheken:**
- [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) - MIT License
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) - BSD License
- [Adafruit ST7735](https://github.com/adafruit/Adafruit-ST7735-Library) - BSD License

**Inspiration:**
- Cygnus-Rail Modellbahn-Community
- Arduino-Community

---

## ⭐ Star History

Wenn Ihnen dieses Projekt gefällt, geben Sie ihm einen Stern! ⭐

---

## 📈 Status

![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Last Commit](https://img.shields.io/badge/last%20commit-Februar%202026-blue.svg)
![Downloads](https://img.shields.io/github/downloads/[IhrBenutzername]/Cygnus-Rail-Intelligence/total.svg)

**Projekt-Status:** ✅  
**Letzte Tests:** Februar 2026  
**Stabilität:** Hoch

---

## ⚠️ Haftungsausschluss

Die Nutzung dieses Projekts erfolgt auf eigene Gefahr.
Der Autor übernimmt keine Haftung für Schäden an Hardware, Anlagen oder Personen.

---

**Viel Erfolg mit Ihrer Cygnus-Rail-Steuerung!** 🚂✨

Made with ❤️ for the model railway community
