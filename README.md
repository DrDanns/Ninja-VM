# Ninja-VM
Eine Virtuelle Maschine die zur Ausführung von Programmen der kleinen Programmiersprache Ninja ("Ninja is not Java") gedacht ist.  

# Vorbereitung
Im Verzeichnis *./NJVM_APPS* stehen ein paar Ninja Programme zur Verfügung.  

## Kompilieren mit njc (*.nj -> *.asm)
Unter *./NJVM_APPS/Ninja Compiler* kriegt man mit **./njc [INPUT]** z.B ``./njc ../ggT.nj`` den
Assemblercode auf die Standardausgabe ausgegeben.  
Ausgabeumlenkung ist hier von Nützen, z.B. ``./njc ../ggT.nj > ../ggT.asm`` 
 
## Assemblieren mit nja (*.asm -> *.bin)
Mit **./nja [INPUT] [OUTPUT]** z.B. ``./nja ../ggT.asm ../ggT.bin``  
wird eine Binär Datei assembliert die später in der Virtuellen Maschine ausgeführt werden kann.

# Verwendung der virtuellen Maschine
* Provisorisches "Make-File" ``./mknjvm`` zum kompilieren ausführen
* Mit z.B. ``./njvm ./NJVM_APPS/ggT.bin```das Programm ausführen / laden

# Debugen der virtuellen Maschine
Der Debuger kann interaktiv in das Geschehen der Maschine eingreifen.  
Mit der Option **--debug** wird der Debuger gestartet -> ``./njvm --debug ./NJVM_APPS/ggT.bin``

Folgende Optionen sind möglich:
* inspect
  * stack: Der komplette Stack wird ausgegeben
  * data: Die statischen Daten werden ausgegeben
  * object: Mit Eingabe der Objekt Referenz wird der Wert des Objektes ausgegeben
* quit: Die Virtuelle Maschine wird beendet
* run: Das Programm läuft weiter und endet entweder beim vorher gesetzten BreakPoint oder wenn es das Ende erreicht hat
* list: Die Befehle im Programmspeicher werden aufgelistet
* step: Der angezeigte Befehl wird ausgeführt und springt zum nächsten weiter
* breakpoint: Das Programm setzt einen BreakPoint

Die Option wird ausgewählt, sobald davon der Anfangsbuchstabe gedrückt wird

# Contributing
* Prof. Dr. Hellwig Geisse

# Lizenz
[![Creative Commons Lizenzvertrag](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-sa/4.0/)