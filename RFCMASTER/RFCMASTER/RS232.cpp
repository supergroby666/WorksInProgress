#include "RS232.h"



unsigned char RS232::txbuffer[buffersize]={255,250,44,01,00,00,00,00,255,240};
	unsigned char RS232::rxbuffer[buffersize];


RS232::RS232()
:a_baud(9600),
a_bits(8),
a_portNum(4)
{

	buffer =new char[buffersize];
	


}
//seprates Init, nicht im Const. aufrufen, da sonst default Com-port initialisiert 
//vorher die Setter aufrufen
void RS232::init(void)
{

	std::wostringstream str; // <sstream> inkludieren 
	str << a_portNum; 

	std::wstring comPrefix = L"\\\\.\\COM";
	std::wstring comID(str.str());
	std::wstring COM=comPrefix+comID;
	hSerial = CreateFile(COM.c_str(),  GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if ( INVALID_HANDLE_VALUE == hSerial) {

		std::cout<<"COM"<<std::dec<<a_portNum<<" konnte nicht geoeffnet werden!!!"<<std::endl<<std::endl;
		return ;
	}
	else
		std::cout<<"COM"<<std::dec<<a_portNum<<" geoeffnet!!!"<<std::endl<<std::endl;

	DCB dcbSerialParams={0};
	COMMTIMEOUTS timeouts={0};

	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate=a_baud;
	dcbSerialParams.ByteSize=a_bits;
	dcbSerialParams.StopBits=ONESTOPBIT;
	dcbSerialParams.Parity=NOPARITY;
	dcbSerialParams.XoffChar=13;
	dcbSerialParams.XonChar=11;
	dcbSerialParams.XoffLim=4096;
	dcbSerialParams.fDtrControl=DTR_CONTROL_DISABLE;
	dcbSerialParams.fRtsControl=RTS_CONTROL_DISABLE;
	SetCommState(hSerial, &dcbSerialParams);

	timeouts.ReadIntervalTimeout=100;		
	timeouts.ReadTotalTimeoutConstant=100;
	timeouts.ReadTotalTimeoutMultiplier=20; 
	SetCommTimeouts(hSerial, &timeouts);
	EscapeCommFunction (hSerial, SETRTS);

}

// Reinit Funktion die Aufgerufen werden muss sobald Baudrate geändert wird
void RS232::reinit(void)
{
	DCB dcbSerialParams={0};
	COMMTIMEOUTS timeouts={0};

	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate=a_baud;
	dcbSerialParams.ByteSize=a_bits;
	dcbSerialParams.StopBits=ONESTOPBIT; 
	dcbSerialParams.Parity=NOPARITY;
	dcbSerialParams.XoffChar=13;
	dcbSerialParams.XonChar=11;
	dcbSerialParams.XoffLim=4096;
	dcbSerialParams.fDtrControl=DTR_CONTROL_DISABLE;
	dcbSerialParams.fRtsControl=RTS_CONTROL_DISABLE;
	SetCommState(hSerial, &dcbSerialParams);

	timeouts.ReadIntervalTimeout=100;		
	timeouts.ReadTotalTimeoutConstant=100;
	timeouts.ReadTotalTimeoutMultiplier=20; 
	SetCommTimeouts(hSerial, &timeouts);
	EscapeCommFunction (hSerial, SETRTS);



}

RS232::~RS232()
{
	EscapeCommFunction (hSerial, CLRRTS);
	CloseHandle(hSerial);
	delete buffer;

}


//Daten Senden
//Return: Anzahl gesendeter Bytes

int RS232::sendData(unsigned char* p_data, int p_length)
{
	int res=0;

	DWORD written = 0;
	//EscapeCommFunction (hSerial, SETRTS);
	WriteFile(hSerial, p_data, p_length, &written, NULL);
	Sleep(20);
	//EscapeCommFunction (hSerial, CLRRTS);
	//EscapeCommFunction (hSerial, SETDTR);

	return res=(int)written;
}

bool RS232::flush()
{
	return FlushFileBuffers(hSerial);
}


//wenn Daten im RX Buffer -> diese Lesen
//return: Anzahl gelesener Bytes

int RS232::recvData(unsigned char* p_data,unsigned int p_maxLength)
{

	DWORD read = 0;
	DWORD readBytes = 0;
	DWORD test = 0;
	COMSTAT comStat;
	ClearCommError(hSerial,(LPDWORD)test,&comStat) ;

	if(comStat.cbInQue>=p_maxLength)
		readBytes=p_maxLength;
	else
		readBytes=comStat.cbInQue;
	if(readBytes==0)
		return 0;
	ReadFile(hSerial, p_data, readBytes, &read, NULL);
	return (int)read;

}


//Buffer mit RX Daten im max Zeitfenster timeOutMS befüllen
//Paramter:
//p_data:	Pointer auf Buffer in den die Empfangenen Daten abegelegt werden sollen
//p_maxLength:	max. Anzahl der zu empfangenden Daten
//p_timeOutMs:  ms in denen Abgebrochen werden soll wenn keine Daten mehr eingehen
//
//Return: Anzahl der übermittelten Bytes
int RS232::recvBuffer(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs)
{

	int num=0;
	int res=0;
	unsigned char* tmp;
	tmp=p_data;
	//this->recvData(tmp,maxLength);
	bool done=0;
	COMSTAT comStat;
	DWORD test = 0;
	DWORD readBytes = 0;
	ClearCommError(hSerial,(LPDWORD)test,&comStat) ;
	unsigned int cnt=0;
	do{

		ClearCommError(hSerial,(LPDWORD)test,&comStat) ;
		if(num+comStat.cbInQue>=p_maxLength){
			readBytes=p_maxLength-num; //den rest einsammeln
			done=1;
		}
		else
			readBytes=readLength;


		res=this->recvData(tmp,readBytes);


		if(res<readLength)
		{
			Sleep(1);
			cnt++;
		}
		if(cnt==p_timeOutMs)
		{
			done=1;
		}
		num+=res;
		tmp+=res;

	}while(!done);


	return num;


}

//bei Verwendung der Wlan-Brücke die per RS232 bzw FTDI am PC angeschlossen ist:
//diese Funktion  anstelle des der Hardware Baud-Raten-Wechsels aufrufen 
//die PC-Schnittstelle und das pc-seitige Modul müssen dabei auf eine gemeinsame feste Rate eingestellt werden 
//(idealer Weise 115200 Baud um die übertragung nicht zu bremsen)
// Parameter: p_baud=Bautrate
// Return:    Befehl erfolgreich übermittelt
bool RS232::setBaudRFC(int p_baud)
{	
	txbuffer[0]=255;
	txbuffer[1]=250;
	txbuffer[2]=44;
	txbuffer[3]=01;
	txbuffer[4]=00;
	txbuffer[5]=00;
	txbuffer[6]=00;
	txbuffer[7]=00;
	txbuffer[8]=255;
	txbuffer[9]=240;
	
	//BaudRate schiften
	int i=0;
	for(i=0;i<4; i++)
	{	
		txbuffer[7-i]=p_baud;
		p_baud>>=8;
	}
	//sende RFC Befehl
	this->sendData(txbuffer,10);
	Sleep(200);
	//Lies Antwort
	int num=this->recvData(rxbuffer,10);


	//int num=this->recvBuffer(rxbuffer,buffersize,1000);
	//antwort abfrage == gesendeter Befehl? incl byte3+100	
	for(i=0;i<10; i++)
	{
		if(i==3)
		{
			if(rxbuffer[i]!=txbuffer[i]+100)
				return 0; //falsche Rückantwort
		}
		else
		{
			if(rxbuffer[i]!=txbuffer[i])
				return 0;		//falsche Rückantwort
		}
	}
	if(num!=10) return 0;
	return 1; //befehl übermittelt und korrekt beantwortet
}


//empfange Daten durchgehen und aus 0xff 0xff nur 0xff machen 
//return: ggf. reduzierte Länge

int RS232::recvBufferRFC(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs)
{
	int x= this->recvBuffer(p_data,p_maxLength,p_timeOutMs);
	int res=x;
	unsigned char* write; write=p_data;
	unsigned char prevF=0;
	for(int i=0;i<x;i++)
	{
		if(prevF&&p_data[i]==0xff) //zwei aufeinander folgende 0xff
		{
			//write++;
			res--;
			prevF=0;
			continue;
		}
		else
		{		
			(*write)=p_data[i];
			write++;
		}
		if(p_data[i]==0xff)
			prevF=1;
		else prevF=0;
	}
	return res;
}

//empfange Daten durchgehen und aus 0xff 0xff nur 0xff machen 
//return: ggf. reduzierte Länge
int RS232::recvDataRFC(unsigned char* p_data,unsigned int p_maxLength)
{
	int x= this->recvData(p_data,p_maxLength);
	int res=x;
	unsigned char* write; write=p_data;
	unsigned char prevF=0;
	for(int i=0;i<x;x++)
	{
		if(prevF&&p_data[i]==0xff) //zwei aufeinander folgende 0xff
		{
			write++;
			res--;
		}
		else
		{		
			(*write)=p_data[i];
			write++;
		}
		if(p_data[i]==0xff)
			prevF=1;
		else prevF=0;
	}
	return res;
}


//wandelt die in den zu sendenden Daten enthaltene 0xff in 0xff 0xff um damit sie von der 
//gegenseite nicht als rfc befehl aufgefasst werden
int RS232::sendDataRFC(unsigned char* p_data, int p_length)
{
	int j=0;
	for(int i=0; i<p_length;i++)
	{
		txbuffer[j]=p_data[i];
		if(txbuffer[j]==0xff)
		{
			j++;
			txbuffer[j]=0xff;
		}
		j++;
		if(j>buffersize) break;
	}
	
	//Datein ausweiten
	return this->sendData(txbuffer,j);

}