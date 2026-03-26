# BEDIENUNGSANLEITUNG
## Cygnus-Rail Controller mit TFT-Display

**Version:** 2.3b  
**Datum:** Februar 2026

---

## 📋 INHALTSVERZEICHNIS

1. [Erste Schritte](#erste-schritte)
2. [Bedien-Elemente](#bedien-elemente)
3. [Display-Anzeige](#display-anzeige)
4. [Betriebsmodi](#betriebsmodi)
5. [Motortypen](#motortypen)
6. [Abstellgleis-Steuerung](#abstellgleis-steuerung)
7. [Tipps & Tricks](#tipps--tricks)
8. [Fehlerbehebung](#fehlerbehebung)

---

## 🚀 ERSTE SCHRITTE

### System einschalten

1. **Stromversorgung anschließen:**
   - Arduino-Netzteil einstecken (9V)
   - Motor-Netzteil einstecken (12-24V je nach Motor)
   
2. **System startet:**
   - Display leuchtet auf
   - Zeigt "CYGNUS-RAIL IR-Steuer."
   - Dann "AZDelivery v1.2"
   - Nach 2 Sekunden: Hauptbildschirm

3. **Hauptbildschirm erscheint:**
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

4. **Fernbedienung prüfen:**
   - Schieber auf Position 1
   - Batterien eingelegt? (2x AAA)
   - Taste drücken → Display reagiert?

**System ist bereit!** ✅

---

## 🎮 BEDIEN-ELEMENTE

### Cygnus-Rail IR-Fernbedienung

```
┌─────────────────────┐
│   CYGNUS-RAIL           │
│                     │
│   [1] [2] [3] [4]   │  ← Funktionstasten
│                     │
│      [Licht]        │  ← Modus umschalten
│                     │
│   [+]       [-]     │  ← Geschwindigkeit
│                     │
│   [Richtung]        │  ← Vorw./Rückw.
│                     │
│  Schieber: [Pos 1]  │  ← WICHTIG!
└─────────────────────┘
```

### Tasten-Funktionen (abhängig vom Modus)

| Taste | MOTOR MODUS | ABSTELLGLEIS MODUS |
|-------|-------------|-------------------|
| **Taste 1** | Motor 3-Pol | Gleis 1 AN/AUS |
| **Taste 2** | Motor 5-Pol | Gleis 2 AN/AUS |
| **Taste 3** | Motor Glockenanker | Gleis 3 AN/AUS |
| **Taste 4** | Motor Hochleistung | Gleis 4 AN/AUS |
| **Licht** | → Wechsel zu ABSTELLGLEIS | → Wechsel zu MOTOR |
| **+** | Geschwindigkeit +5% | Geschwindigkeit +5% |
| **-** | Geschwindigkeit -5% | Geschwindigkeit -5% |
| **Richtung** | Vorwärts ↔ Rückwärts | Vorwärts ↔ Rückwärts |

---

## 📺 DISPLAY-ANZEIGE

### Display-Layout Übersicht

**Zeile 1: Modus-Anzeige (CYAN)**
- Zeigt aktuellen Betriebsmodus
- "MOTOR MODUS" oder "ABSTELLGLEIS"

**Zeile 2: Geschwindigkeit (GELB)**
- Format: "Speed: XX% (PWM)"
- Beispiel: "Speed: 45% (150)"
- 0-100% in 5%-Schritten

**Zeile 3: Richtung (GRÜN)**
- "Richtung: Vorwaerts" oder
- "Richtung: Rueckwaerts"

**Zeile 4-7: Modus-abhängig**
- Im MOTOR MODUS: Motortyp + Tastenbelegung
- Im ABSTELLGLEIS MODUS: Gleis-Status

**Zeile 8: Hinweis (GELB)**
- "Licht=Wechsel"
- Erinnerung an Modus-Umschaltung

### Farb-Bedeutung

| Farbe | Bedeutung |
|-------|-----------|
| 🔵 CYAN | Überschrift (Modus) |
| 🟡 GELB | Geschwindigkeit, Hinweise |
| 🟢 GRÜN | Richtung Vorwärts, Gleis EIN |
| 🔴 ROT | Gleis AUS |
| 🟣 MAGENTA | Tasten-Hilfe |
| ⚪ WEISS | Allgemeine Informationen |

---

## ⚙️ BETRIEBSMODI

### Modus 1: MOTORTYP (Standard)

**Zweck:** Auswahl und Steuerung verschiedener Motortypen

**Display-Anzeige:**
```
┌────────────────────────┐
│ MOTOR MODUS            │
│ Speed: 45% (150)       │
│ Richtung: Vorwaerts    │
│ Motortyp: 5-Pol        │  ← Aktueller Motor
│ Tasten:                │
│ 1:3Pol 2:5Pol          │  ← Auswahl
│ 3:Glock 4:High         │
│                        │
│ Licht=Wechsel          │
└────────────────────────┘
```

**Bedienung:**
1. **Taste 1:** 3-Pol Motor auswählen
2. **Taste 2:** 5-Pol Motor auswählen (Standard)
3. **Taste 3:** Glockenanker auswählen
4. **Taste 4:** Hochleistung auswählen
5. **+/-:** Geschwindigkeit anpassen
6. **Richtung:** Vorwärts/Rückwärts umschalten

**Anwendungsfall:**
- Testen verschiedener Lokomotiven
- Optimale Kennlinie finden
- Feinabstimmung der Geschwindigkeit

---

### Modus 2: ABSTELLGLEIS

**Zweck:** Steuerung von 4 unabhängigen Abstellgleisen/Weichen

**Display-Anzeige:**
```
┌────────────────────────┐
│ ABSTELLGLEIS           │
│ Speed: 30% (90)        │
│ Richtung: Rueckwaerts  │
│ Abstellgleise:         │
│ Gleis 1: EIN           │  ← Grün
│ Gleis 2: AUS           │  ← Rot
│ Gleis 3: EIN           │  ← Grün
│ Gleis 4: AUS           │  ← Rot
│ Licht=Wechsel          │
└────────────────────────┘
```

**Bedienung:**
1. **Taste 1:** Gleis 1 AN ↔ AUS (Toggle)
2. **Taste 2:** Gleis 2 AN ↔ AUS (Toggle)
3. **Taste 3:** Gleis 3 AN ↔ AUS (Toggle)
4. **Taste 4:** Gleis 4 AN ↔ AUS (Toggle)
5. **+/-:** Geschwindigkeit (Motor läuft weiter!)
6. **Richtung:** Vorwärts/Rückwärts (Motor läuft weiter!)

**Anwendungsfall:**
- Lok in Abstellgleis rangieren
- Mehrere Weichen schalten
- Rangier-Betrieb

---

### Modus wechseln

**Licht-Taste drücken:**
```
MOTOR MODUS
     ↓
[Licht-Taste]
     ↓
ABSTELLGLEIS
     ↓
[Licht-Taste]
     ↓
MOTOR MODUS
     ↓
[...]
```

**Display zeigt sofort den neuen Modus!**

---

## 🚂 MOTORTYPEN

### 1. 3-Pol Motor (Linear)

**Eigenschaften:**
- Alte, robuste Motoren
- Lineare Kennlinie
- Höherer Mindestwert nötig
- PWM-Bereich: 95-255

**Ideal für:**
- Ältere Cygnus-Rail-Loks
- Robuste Antriebe
- Gleichmäßige Geschwindigkeit

**Einstellung:**
```
MOTOR MODUS → Taste 1
Display zeigt: "Motortyp: 3-Pol"
```

---

### 2. 5-Pol Motor (Standard)

**Eigenschaften:**
- Moderne Standard-Motoren
- Quadratische Kennlinie
- Sanfter Anlauf
- PWM-Bereich: 75-255

**Ideal für:**
- Aktuelle Cygnus-Rail-Loks
- Präzises Anfahren
- Gute Kontrolle bei niedrigen Geschwindigkeiten

**Einstellung:**
```
MOTOR MODUS → Taste 2 (Standard beim Start)
Display zeigt: "Motortyp: 5-Pol"
```

---

### 3. Glockenanker

**Eigenschaften:**
- Präzisions-Motoren
- Potenz 1.6 Kennlinie
- Sehr niedriger Anlauf
- PWM-Bereich: 45-220

**Ideal für:**
- Hochwertige Loks
- Rangierbetrieb
- Sehr langsame Geschwindigkeiten
- Präzisions-Steuerung

**Einstellung:**
```
MOTOR MODUS → Taste 3
Display zeigt: "Motortyp: Glockenank."
```

---

### 4. Hochleistung

**Eigenschaften:**
- Leistungsstarke Motoren
- Potenz 1.3 Kennlinie
- Kompromiss zwischen Linear und Quadratisch
- PWM-Bereich: 60-240

**Ideal für:**
- Schwere Züge
- Steigungen
- Hohe Zugkraft bei mittleren Geschwindigkeiten

**Einstellung:**
```
MOTOR MODUS → Taste 4
Display zeigt: "Motortyp: Hochleist."
```

---

## 🔀 ABSTELLGLEIS-STEUERUNG

### Toggle-Funktion

Jedes Gleis hat zwei Zustände:

**AUS (Rot):**
- Relais aus (HIGH)
- Weiche in Standard-Position
- oder: Kein Strom auf Gleis

**EIN (Grün):**
- Relais ein (LOW)
- Weiche umgeschaltet
- oder: Strom auf Gleis

**Umschalten:**
```
Taste drücken → Zustand wechselt
Taste erneut  → Zustand wechselt zurück
```

### Mehrere Gleise gleichzeitig

Sie können beliebige Kombinationen schalten:

**Beispiel:**
```
Gleis 1: EIN  ← Lok steht hier
Gleis 2: AUS
Gleis 3: EIN  ← Weiche umgelegt
Gleis 4: AUS
```

**Alle unabhängig steuerbar!**

### Anwendungs-Beispiel: Rangierbetrieb

1. **Ausgangslage:**
   ```
   Alle Gleise: AUS
   Lok auf Hauptgleis
   ```

2. **Lok in Gleis 1 rangieren:**
   ```
   Taste 1 drücken → Gleis 1: EIN (Weiche stellt um)
   + drücken       → Lok fährt langsam
   ```

3. **Lok abstellen:**
   ```
   - drücken       → Lok steht
   Taste 1 drücken → Gleis 1: AUS (Weiche zurück)
   ```

4. **Nächste Lok in Gleis 2:**
   ```
   Taste 2 drücken → Gleis 2: EIN
   + drücken       → Lok fährt
   ```

---

## 💡 TIPPS & TRICKS

### Schnellstart

**Motor sofort losfahren:**
```
1. Richtung prüfen (Display)
2. 5x auf + drücken → 25% Geschwindigkeit
3. Lok fährt an
```

**Sanfter Anlauf:**
```
1. Motortyp wählen (5-Pol oder Glockenanker)
2. 1x auf + drücken → 5%
3. Langsam weiter erhöhen
```

### Geschwindigkeits-Stufen

**Empfohlene Stufen:**
- **Rangieren:** 10-25% (2-5x +)
- **Langsam:** 30-50% (6-10x +)
- **Normal:** 55-75% (11-15x +)
- **Schnell:** 80-100% (16-20x +)

### Richtungswechsel

**WICHTIG:** Erst anhalten, dann Richtung wechseln!

**Richtig:**
```
1. Mit - auf 0% bremsen
2. Lok steht
3. Richtung drücken
4. Mit + beschleunigen
```

**Falsch (schadet Motor!):**
```
❌ Bei voller Fahrt Richtung drücken
❌ Sofort Vollgas in andere Richtung
```

### Motortyp finden

**Nicht sicher welcher Motor?**

1. **Start mit 5-Pol (Standard)**
2. **Test:**
   - + drücken bis Lok anläuft
   - Fährt Lok ruckelig? → 3-Pol probieren
   - Fährt Lok sehr zögerlich? → Glockenanker probieren
   - Braucht Lok viel Kraft? → Hochleistung probieren

### Display-Helligkeit

**Display zu hell/dunkel?**

Das Backlight ist fest an 5V.
Für Dimmen: LED-Pin an PWM-Pin anschließen (im Code anpassen).

---

## 🔧 FEHLERBEHEBUNG

### Problem: Display bleibt schwarz

**Checkliste:**
- [ ] LED-Pin mit 5V verbunden?
- [ ] VCC mit 5V verbunden?
- [ ] Alle 8 Pins angeschlossen?
- [ ] Arduino hat Strom?

**Lösung:**
1. LED-Verbindung prüfen (Backlight)
2. Display-Kabel kontrollieren
3. Arduino-Reset drücken

---

### Problem: Fernbedienung funktioniert nicht

**Checkliste:**
- [ ] Schieber auf Position 1?
- [ ] Batterien voll? (2x AAA)
- [ ] IR-Empfänger richtig angeschlossen?
- [ ] Sichtverbindung frei?

**Test:**
- Serieller Monitor öffnen (9600 Baud)
- Taste drücken
- Sollte Meldung zeigen

**Lösung:**
1. Batterien wechseln
2. Schieber auf Position 1
3. IR-Empfänger Verkabelung prüfen

---

### Problem: Motor läuft nicht

**Checklichte:**
- [ ] Motor-Netzteil eingeschaltet?
- [ ] Geschwindigkeit > 0%?
- [ ] Motor-Kabel richtig angeschlossen?
- [ ] TB6612 STBY auf HIGH?

**Test:**
- Display zeigt Geschwindigkeit?
- + Taste mehrmals drücken
- Motor-Netzteil Spannung messen

**Lösung:**
1. Geschwindigkeit erhöhen (mindestens 20%)
2. Motor-Verkabelung prüfen
3. TB6612 STBY-Pin kontrollieren

---

### Problem: Relais schalten nicht

**Checkliste:**
- [ ] Relais-LED leuchtet?
- [ ] Richtige Taste im richtigen Modus?
- [ ] Relais an 5V angeschlossen?

**Test:**
- Modus wechseln zu ABSTELLGLEIS
- Taste 1 drücken
- Relais-LED sollte leuchten

**Lösung:**
1. Modus prüfen (ABSTELLGLEIS)
2. Relais-Verkabelung kontrollieren
3. Relais-Modul testen (mit 5V direkt)

---

### Problem: Display flackert

**Ursache:** Sollte nicht mehr auftreten (behoben in v2.3b)

**Falls doch:**
- Update-Intervall erhöhen (im Code)
- Kabel kürzer machen (< 20cm)
- SPI-Geschwindigkeit reduzieren

---

### Problem: Falsche Motortyp-Kennlinie

**Symptome:**
- Lok fährt zu früh/spät an
- Geschwindigkeit nicht linear
- Ruckeln bei niedrigen Drehzahlen

**Lösung:**
1. Anderen Motortyp probieren
2. 5-Pol → 3-Pol (wenn zu zögerlich)
3. 5-Pol → Glockenanker (wenn zu früh)
4. Custom-Kennlinie im Code anpassen

---

## 📞 SUPPORT

### Weitere Hilfe

**Dokumentation:**
- README_KOMPLETT.md - Übersicht
- HARDWARE_DOKUMENTATION.md - Hardware-Details
- SOFTWARE_DOKUMENTATION.md - Code-Erklärung

**Serieller Monitor:**
```
Tools → Serial Monitor (9600 Baud)
Zeigt Status-Meldungen in Echtzeit
```

**Test-Modus:**
- Komponenten einzeln testen
- Verkabelung schrittweise aufbauen
- Mit einfachstem Setup beginnen

---

## ✅ WARTUNG

### Regelmäßige Prüfung

**Monatlich:**
- [ ] Fernbedienung Batterien prüfen
- [ ] Display auf Kratzer prüfen
- [ ] Relais-Funktion testen
- [ ] Motor-Kabel auf Bruch prüfen

**Jährlich:**
- [ ] Alle Lötstellen kontrollieren
- [ ] Staubentfernung (Druckluft)
- [ ] Netzteil-Spannung messen
- [ ] Backup der Software anlegen

### Software-Update

**Bei neuer Version:**
1. Alte .ino Datei sichern
2. Neue .ino Datei herunterladen
3. Arduino IDE öffnen
4. Upload
5. Funktionstest durchführen

---

## 🎯 BEST PRACTICES

### Für optimalen Betrieb

✅ **Motor:**
- Langsam anfahren (nicht sofort Vollgas)
- Vor Richtungswechsel anhalten
- Richtigen Motortyp wählen
- Motor nicht überhitzen lassen

✅ **Abstellgleis:**
- Lok langsam in Gleis fahren
- Nach Abstellen Gleis abschalten
- Nicht mehrere Weichen gleichzeitig schalten
- Relais-Zustand im Display beachten

✅ **Display:**
- Nicht mit spitzen Gegenständen berühren
- Vor direkter Sonneneinstrahlung schützen
- Nicht bei extremer Kälte/Hitze betreiben

✅ **Fernbedienung:**
- Batterien rechtzeitig wechseln
- Nicht fallen lassen
- Trocken lagern

---

**Viel Spaß mit Ihrer Cygnus-Rail Controller!** 🚂✨

Bei Fragen: Siehe Dokumentation oder seriellen Monitor für Debug-Infos.
