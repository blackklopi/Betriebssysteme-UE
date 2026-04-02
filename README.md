# Betriebssysteme-UE

# ccut – CSV Field Extractor

`ccut` ist ein C-Konsolenprogramm, das CSV-artige Textdaten von `stdin` oder aus einer Datei einliest und ausgewählte Felder auf `stdout` ausgibt. Es verhält sich wie ein klassisches Unix-Werkzeug und erweitert das Standard-`cut`-Kommando um korrekte Behandlung von Textfeldern in doppelten Anführungszeichen.

---

## Kompilierung

```bash
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```

---

## Verwendung

```
ccut [OPTION]... [DATEINAME]
```

Wenn kein `DATEINAME` angegeben wird oder `-` als Dateiname verwendet wird, liest `ccut` von `stdin`.

---

## Optionen

| Option | Beschreibung |
|---|---|
| `-f fields` | Felder, die ausgegeben werden sollen (z. B. `1`, `1,3,5`, `2,4`). Feldnummern beginnen bei **1**. |
| `-d delimiter` | Eingabe-Trennzeichen (Standard: `,`) |
| `-o delimiter` | Ausgabe-Trennzeichen (Standard: `,`) |
| `-q` | Aktiviert Anführungszeichen-Behandlung: Trennzeichen innerhalb von `"..."` werden nicht als Feldgrenzen interpretiert. `""` innerhalb eines Feldes wird als wörtliches `"` behandelt. |
| `-H`, `--header` | Erste Zeile wird als Kopfzeile interpretiert und entsprechend der Feldauswahl ausgegeben |
| `-s` | Unterdrückt Zeilen, die das Trennzeichen nicht enthalten |
| `--strict` | Bricht bei fehlerhafter Eingabe mit Fehlermeldung (auf `stderr`) und Fehlercode ab |
| `-h`, `--help` | Gibt eine Hilfeinformation aus und beendet das Programm |
| `--version` | Gibt die Versionsinformation aus und beendet das Programm |

---

## Beispiele

```bash
# Felder 1 und 3 aus einer Datei ausgeben
ccut -f 1,3 personen.csv

# Feld 2 von stdin lesen, Anführungszeichen-Behandlung aktiviert
cat personen.csv | ccut -f 2 -q

# Felder 1 und 4 mit Semikolon als Ausgabe-Trennzeichen in Datei schreiben
ccut -f 1,4 -q -o ';' adressen.csv > ausgabe.txt

# Felder 2 und 5 aus Pipe lesen, strenge Fehlerprüfung
cat daten.csv | ccut -f 2,5 -q --strict

# Kopfzeile mitausgeben
ccut -f 1,2,3 -H daten.csv

# Semikolon als Eingabe-Trennzeichen verwenden
ccut -f 1,2 -d ';' daten.csv

# Von stdin lesen (explizit mit -)
ccut -f 1,3 -
```

---

## CSV-Format

Das Programm unterstützt folgende Vereinfachungen des CSV-Formats:

- Eine Zeile entspricht genau einem Datensatz.
- Felder sind standardmäßig durch ein Komma getrennt.
- Mit `-q`: Felder dürfen in doppelte Anführungszeichen eingeschlossen sein – Trennzeichen darin gelten nicht als Feldgrenzen.
- Mit `-q`: Zwei aufeinanderfolgende Anführungszeichen (`""`) innerhalb eines Feldes werden als ein wörtliches `"` interpretiert.
- Zeilenumbrüche innerhalb von Feldern werden **nicht** unterstützt.

---

## Rückgabewerte

| Code | Bedeutung |
|---|---|
| `0` | Erfolgreiche Verarbeitung |
| `1` | Fehler (ungültige Parameter, nicht lesbare Datei, ungültiges Eingabeformat bei `--strict`) |

> Alle Fehlermeldungen und Diagnoseinformationen werden ausschließlich auf `stderr` ausgegeben.

---

## Implementierungshinweise

- Kommandozeilenargumente werden mit `argc` und `argv` ausgewertet.
- Sowohl `stdin` als auch Datei-Eingabe via Dateihandling werden unterstützt.
- Die Ausgabe der extrahierten Felder erfolgt ausschließlich über `stdout`.

---

## Autor

Entwickelt im Rahmen des Betriebssysteme-Labors, ITS SS2026, FH Salzburg.
@ChristophOberreiter
@MaxBüsching
