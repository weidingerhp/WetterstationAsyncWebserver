# Einfacher Webserver mit WebSockets für die Coderdojo - Wetterstation

Einfacher Webserver - der Code für die Messung selbst fehlt hier und ist noch einzufügen.

Bitte auch den WLAN Namen und das Passwort eintragen.

Der Code is in 4 teile aufgeteilt

1. *Oben:* die setup und loop - funktion für den Arduion-Code
1. *Danach:* die einzelnen Teile des Setups (wurde gemacht, damit die `setup` - Funktion selbst nicht zu riesig wird)
1. *Vorletzter Teil:* Hilfsfunktionen wie z.B. das JSON-Dokument für die Messungen zusammenbauen
1. *Letzter Teil:* Die aktuelle Messung

### Wie bekomme ich das auf den ESP8266 rauf?

* im VS-Code eine `PlattformIO Core CLI` aufmachen und dort das Kommando `pio run -t uploadfs` eintippen.
* Code bauen und Upload durchführen

Danach kann man auf die IP des ESP8266 zugreifen und seine Messwerte im Browser anzeigen lassen.



