# 📚 DOKUMENTATIONS-INDEX
## Cygnus-Rail Controller - Komplette Projekt-Dokumentation

**Version:** 2.3b  
**Stand:** Februar 2026  
**Status:** Produktionsreif ✅

---

## 🎯 SCHNELLZUGRIFF

Wählen Sie das passende Dokument für Ihre Bedürfnisse:

| Ich möchte... | Dokument | Beschreibung |
|--------------|----------|--------------|
| **Projekt-Übersicht** | [README_KOMPLETT.md](README_KOMPLETT.md) | Gesamtüberblick, Features, Quick Start |
| **Hardware aufbauen** | [HARDWARE_DOKUMENTATION.md](HARDWARE_DOKUMENTATION.md) | Komponenten, Verdrahtung, Schaltplan |
| **Code verstehen** | [SOFTWARE_DOKUMENTATION.md](SOFTWARE_DOKUMENTATION.md) | Funktionen, Code-Struktur, Anpassungen |
| **System bedienen** | [BEDIENUNGSANLEITUNG.md](BEDIENUNGSANLEITUNG.md) | Benutzerhandbuch, Tipps, Troubleshooting |
| **Display anschließen** | [AZDELIVERY_PIN_BELEGUNG.txt](AZDELIVERY_PIN_BELEGUNG.txt) | Pin-für-Pin Anleitung |
| **Schritt-für-Schritt** | [VERKABELUNGS_CHECKLISTE.txt](VERKABELUNGS_CHECKLISTE.txt) | Verkabelung zum Abhaken |
| **Schnellstart** | [AZDELIVERY_SCHNELLSTART.txt](AZDELIVERY_SCHNELLSTART.txt) | In 3 Schritten zum Ziel |

---

## 📂 DATEI-STRUKTUR

```
DOKUMENTATION/
│
├── README_KOMPLETT.md                  ← START HIER!
│   └─ Projekt-Übersicht, Features, Versionshistorie
│
├── HARDWARE_DOKUMENTATION.md
│   ├─ Komponenten-Liste mit Spezifikationen
│   ├─ Vollständiger Verdrahtungsplan
│   ├─ Pin-Belegung Arduino Mega
│   ├─ Stromversorgungs-Schema
│   └─ Montage-Hinweise
│
├── SOFTWARE_DOKUMENTATION.md
│   ├─ Code-Struktur & Organisation
│   ├─ Funktions-Übersicht & Details
│   ├─ PWM-Konfiguration (31kHz)
│   ├─ Display-Update-Logik
│   ├─ IR-Protokoll-Handler
│   └─ Anpassungs-Möglichkeiten
│
├── BEDIENUNGSANLEITUNG.md
│   ├─ Erste Schritte
│   ├─ Bedien-Elemente
│   ├─ Display-Anzeige Erklärung
│   ├─ Motortypen-Übersicht
│   ├─ Abstellgleis-Steuerung
│   ├─ Tipps & Tricks
│   └─ Fehlerbehebung
│
├── VERKABELUNGS_CHECKLISTE.txt
│   └─ Schritt-für-Schritt Verkabelung zum Abhaken
│
├── AZDELIVERY_PIN_BELEGUNG.txt
│   └─ Exakte Pin-Zuordnung für AZDelivery Display
│
├── AZDELIVERY_SCHNELLSTART.txt
│   └─ Quick Start in 3 Schritten
│
├── AZDELIVERY_ANLEITUNG.txt
│   └─ Display-spezifische Details
│
├── CHANGELOG.txt
│   └─ Versions-Historie & Änderungen
│
└── Cygnus_Rail_Controller.ino
    └─ HAUPT-PROGRAMM (Arduino Sketch)
```

---

## 🚀 QUICK START - 3 SCHRITTE

### 1️⃣ Hardware aufbauen
```
→ Siehe: VERKABELUNGS_CHECKLISTE.txt
→ Dauer: 30-60 Minuten
```

### 2️⃣ Software installieren
```
→ Siehe: README_KOMPLETT.md → Quick Start
→ Dauer: 10 Minuten
```

### 3️⃣ System testen
```
→ Siehe: BEDIENUNGSANLEITUNG.md → Erste Schritte
→ Dauer: 5 Minuten
```

**Gesamt-Zeit:** ~1 Stunde bis zum laufenden System!

---

## 📖 LESE-REIHENFOLGE (Empfohlen)

### Für Erstbauer:

1. **README_KOMPLETT.md** (Überblick gewinnen)
2. **HARDWARE_DOKUMENTATION.md** (Komponenten verstehen)
3. **VERKABELUNGS_CHECKLISTE.txt** (Hardware aufbauen)
4. **AZDELIVERY_PIN_BELEGUNG.txt** (Display anschließen)
5. **README_KOMPLETT.md → Quick Start** (Software installieren)
6. **BEDIENUNGSANLEITUNG.md** (Bedienung lernen)

### Für Entwickler:

1. **README_KOMPLETT.md** (Features & Struktur)
2. **SOFTWARE_DOKUMENTATION.md** (Code-Details)
3. **HARDWARE_DOKUMENTATION.md** (Pin-Belegung)
4. **Cygnus_Rail_Controller.ino** (Code-Review)

### Für Benutzer (System fertig):

1. **BEDIENUNGSANLEITUNG.md** (Komplett-Anleitung)
2. Bei Problemen: **BEDIENUNGSANLEITUNG.md → Fehlerbehebung**

---

## 🔧 PROJEKT-DETAILS

### Hardware-Komponenten

```
✓ Arduino Mega 2560 R3
✓ AZDelivery ST7735 v1.2 Display (1.8", 128x160)
✓ TB6612FNG Motortreiber
✓ TSOP38238 IR-Empfänger
✓ 4x 5V Relais-Module
✓ Cygnus-Rail IR-Fernbedienung
✓ Netzteile (Arduino 9V, Motor 12-24V)
```

→ Details: **HARDWARE_DOKUMENTATION.md**

### Software-Features

```
✓ 2 Betriebsmodi (Motortyp / Abstellgleis)
✓ 4 Motortypen mit spezifischen Kennlinien
✓ 4 Abstellgleis-Relais (Toggle-Funktion)
✓ 31kHz PWM für lauflosen Motorbetrieb
✓ Flackerfreies TFT-Display
✓ RC5 IR-Protokoll (Cygnus-Rail)
✓ Serielle Debug-Ausgabe
```

→ Details: **SOFTWARE_DOKUMENTATION.md**

### Pin-Belegung (Überblick)

```
MOTOR:      Pins 5, 6, 7, 8 (TB6612)
RELAIS:     Pins 10, 11, 24, 25
IR:         Pin 22
DISPLAY:    Pins 47, 48, 49, 51, 52 (SPI)
```

→ Vollständig: **HARDWARE_DOKUMENTATION.md → Pin-Belegung**

---

## 📊 DOKUMENT-ÜBERSICHT

### README_KOMPLETT.md (Haupt-Doku)
**Umfang:** 400+ Zeilen  
**Inhalt:**
- Projekt-Übersicht & Features
- Komponenten-Liste
- Software-Features
- Quick Start Guide
- Versionshistorie
- Anwendungsbereiche

**Für:** Projektleiter, Übersicht-Sucher

---

### HARDWARE_DOKUMENTATION.md
**Umfang:** 600+ Zeilen  
**Inhalt:**
- Detaillierte Komponenten-Spezifikationen
- Vollständiger Verdrahtungsplan
- Pin-Belegung Arduino Mega
- Schaltplan & Stromversorgung
- Montage-Hinweise & Sicherheit

**Für:** Hardware-Entwickler, Aufbauer

---

### SOFTWARE_DOKUMENTATION.md
**Umfang:** 700+ Zeilen  
**Inhalt:**
- Code-Struktur & Bibliotheken
- Funktions-Übersicht mit Details
- PWM-Konfiguration (Timer3, 31kHz)
- Display-Update-Optimierung
- IR-Protokoll-Handler
- Anpassungs-Möglichkeiten

**Für:** Programmierer, Code-Verstehende

---

### BEDIENUNGSANLEITUNG.md
**Umfang:** 500+ Zeilen  
**Inhalt:**
- Erste Schritte & Einschalten
- Bedien-Elemente Übersicht
- Display-Anzeige Erklärung
- Motortypen-Details
- Abstellgleis-Steuerung
- Tipps & Tricks
- Fehlerbehebung

**Für:** End-Benutzer, Bediener

---

## 🎯 HÄUFIGE FRAGEN

### "Wo finde ich die Pin-Belegung?"
→ **HARDWARE_DOKUMENTATION.md** → Pin-Belegung Arduino Mega  
→ **AZDELIVERY_PIN_BELEGUNG.txt** (für Display)

### "Wie schließe ich das Display an?"
→ **VERKABELUNGS_CHECKLISTE.txt** → Schritt 2  
→ **AZDELIVERY_PIN_BELEGUNG.txt** (detailliert)

### "Welche Motortypen gibt es?"
→ **BEDIENUNGSANLEITUNG.md** → Motortypen  
→ **SOFTWARE_DOKUMENTATION.md** → calculatePWM()

### "Wie funktioniert die Abstellgleis-Steuerung?"
→ **BEDIENUNGSANLEITUNG.md** → Abstellgleis-Steuerung  
→ **README_KOMPLETT.md** → Features

### "Display flackert / Streifen"
→ **BEDIENUNGSANLEITUNG.md** → Fehlerbehebung  
→ **AZDELIVERY_ANLEITUNG.txt** (Display-spezifisch)

### "Wie ändere ich die PWM-Frequenz?"
→ **SOFTWARE_DOKUMENTATION.md** → PWM-Konfiguration  
→ **SOFTWARE_DOKUMENTATION.md** → Anpassungen

### "Motor läuft nicht"
→ **BEDIENUNGSANLEITUNG.md** → Fehlerbehebung  
→ **HARDWARE_DOKUMENTATION.md** → Stromversorgung

---

## 💾 WICHTIGE DATEIEN

### Zum Bearbeiten:
```
Cygnus_Rail_Controller.ino  ← Arduino-Programm
```

### Nur Lesen (Dokumentation):
```
README_KOMPLETT.md
HARDWARE_DOKUMENTATION.md
SOFTWARE_DOKUMENTATION.md
BEDIENUNGSANLEITUNG.md
[alle .txt Dateien]
```

---

## 📝 VERSION & STATUS

**Projekt-Version:** 2.3b  
**Letztes Update:** Februar 2026  
**Status:** ✅ Produktionsreif

**Getestet mit:**
- Arduino Mega 2560 R3
- AZDelivery ST7735 v1.2 Display
- Cygnus-Rail IR-Fernbedienung (RC5)
- TB6612FNG Motortreiber
- Verschiedene Cygnus-Rail-Motoren

**Dokumentations-Umfang:**
- 4 Haupt-Dokumente (Markdown)
- 8 Hilfs-Dokumente (TXT)
- 1 Programm-Datei (INO)
- **Gesamt:** ~2500+ Zeilen Dokumentation

---

## 🚀 NÄCHSTE SCHRITTE

1. **Neu im Projekt?**
   → Start mit **README_KOMPLETT.md**

2. **Hardware aufbauen?**
   → **VERKABELUNGS_CHECKLISTE.txt**

3. **Programm verstehen?**
   → **SOFTWARE_DOKUMENTATION.md**

4. **System bedienen?**
   → **BEDIENUNGSANLEITUNG.md**

---

## 📞 SUPPORT

**Bei Problemen:**
1. **BEDIENUNGSANLEITUNG.md** → Fehlerbehebung
2. Seriellen Monitor öffnen (9600 Baud)
3. Spezifische Dokumentation konsultieren
4. Schritt-für-Schritt Anleitungen nutzen

**Alle Dokumente enthalten:**
- ✅ Schritt-für-Schritt Anleitungen
- ✅ Checklisten zum Abhaken
- ✅ Beispiele & Screenshots
- ✅ Troubleshooting-Abschnitte

---

**Viel Erfolg mit dem Projekt!** 🚂✨

Autor: Gregor  
Projekt: Cygnus-Rail Controller mit TFT-Display  
Repository: Lokale Entwicklung  
Status: Produktionsreif seit Februar 2026
