Version:
CsvToImgWrapper v1.1

Beschreibung:
CsvToImgWrapper wandelt eine beliebige CSV-Datei in eine Bilddatei um.
Die XY/YT Punkte werden in einem Liniendiagramm grafisch dargestellt.
Die CSV-Datei muss über das Programm geöffnet werden.
Das Programm erstellt im Hintergrund ein Image und behandelt im Anschluss
die CSV, so wie in den Einstellungen eingestellt ist.

Eistellungen:
In der Datei "config.cfg" können diverse Einstellungen vorgenomen werden.
Die Datei befindet sich im Installationsverzeichnis.

Die Datei ist wie folgt aufgebaut:
{
    "delimiter": "SEMICOLON",
    "imageWidth": 1200,
    "imageHight": 600,
    "imageExtension": ".png",
    "chartTheme": 2,
    "csvHandlingModeAfterConvert": 1
}

- delimeter: Die CSV-Datei kann auf verschiedene Art und Weise aufgebaut sein.
Die Werte werden mit einem Zeichen voneinander getrennt.
Die gängigste Art im europäischen Raum ist das SEMICOLON (;) oder TAB (\t).
Im amerikanischen Raum wird gerne ein COMMA (,) verwendet.

- imageWidth: Die Breite des Images in px.

- imageHight: Die Höhe des Images in px.

- imageExtension: Das Format des Images. Muss mit einem Punkt (.) beginnen.

- chartTheme: Hier kann der Stil geändert werden.
    0 = Light
    1 = Dark
    2 = BlueCerulean
    3 = BrownSand
    4 = BlueNsc
    5 = HighContrast
    6 = BlueIcy

- csvHandlingModeAfterConvert: Hier kann die Art für die Behandlung der CSV-Datei nach dem Umwandeln eingestellt werden.
    0 = Keine Behandlung
    1 = Verschiebe die CSV-Datei in einen Unterordner namens "Csv-Files"
    2 = Lösche die CSV-Datei












