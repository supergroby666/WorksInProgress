#include "FTD.h"

using namespace USB;














//wenn Daten im RX Buffer -> diese Lesen
//return: Anzahl gelesener Bytes




//Buffer mit RX Daten im max Zeitfenster timeOutMS bef�llen
//Paramter:
//p_data:	Pointer auf Buffer in den die Empfangenen Daten abegelegt werden sollen
//p_maxLength:	max. Anzahl der zu empfangenden Daten
//p_timeOutMs:  ms in denen Abgebrochen werden soll wenn keine Daten mehr eingehen
//
//Return: Anzahl der �bermittelten Bytes


//bei Verwendung der Wlan-Br�cke die per RS232 bzw FTDI am PC angeschlossen ist:
//diese Funktion  anstelle des der Hardware Baud-Raten-Wechsels aufrufen 
//die PC-Schnittstelle und das pc-seitige Modul m�ssen dabei auf eine gemeinsame feste Rate eingestellt werden 
//(idealer Weise 115200 Baud um die �bertragung nicht zu bremsen)
// Parameter: p_baud=Bautrate
// Return:    Befehl erfolgreich �bermittelt


//empfange Daten durchgehen und aus 0xff 0xff nur 0xff machen 
//return: ggf. reduzierte L�nge


//empfange Daten durchgehen und aus 0xff 0xff nur 0xff machen 
//return: ggf. reduzierte L�nge

//wandelt die in den zu sendenden Daten enthaltene 0xff in 0xff 0xff um damit sie von der 
//gegenseite nicht als rfc befehl aufgefasst werden
