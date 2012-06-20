
#include "FTD.h"
#include "ftd2xx.h"

FTD::FTD()
:a_tagetDevice(0),
a_recvCnt(0),
a_bits(8),
a_numDevices(1),
testCnt(0),
stopThread(0)
{		

	lib= new QLibrary("C:/i386/FTD2XX.dll");
	if(lib->load())
		std::cout<<"done"<<std::endl;
	else
		std::cout<<"error"<<std::endl;
	//FT_Open=(FT_OpenProto) lib->resolve("FT_Open");
	//FT_ListDevices=(FT_ListDevicesProto) lib->resolve("FT_ListDevices");
	//FT_Close=(FT_CloseProto) lib->resolve("FT_Close");
	//
	//FT_SetRts=(FT_SetRtsProto) lib->resolve("FT_SetRts");
	//FT_ClrRts=(FT_ClrRtsProto) lib->resolve("FT_ClrRts");

	//FT_Write=(FT_WriteProto) lib->resolve("FT_Write");
	//FT_Read=(FT_ReadProto) lib->resolve("FT_Read");
	//FT_SetBitmode=(FT_SetBitmodeProto) lib->resolve("FT_SetBitmode");
	//FT_GetBitmode=(FT_GetBitmodeProto) lib->resolve("FT_GetBitmode");

	txbuffer=new unsigned char [buffersize];
	rxbuffer=new unsigned char [buffersize];
	threadBuffer=new unsigned char [buffersize];

	FT_STATUS ftStatus = FT_OK;

	void * p1; unsigned int numDevs;
	p1 = (void*)&numDevs;
	ftStatus = FT_ListDevices(p1, NULL, FT_LIST_NUMBER_ONLY);
	a_numDevices=numDevs;
	//ftStatus = FT_Open(a_tagetDevice, &handle);

}


FTD::~FTD()
{		


	lib->unload();
	delete lib;
	delete txbuffer;
	delete rxbuffer;
	delete threadBuffer;

}

//Rts High, Thread Stoppen, Verbindung beenden 
void FTD::close(void)
{

	FT_ClrRts(handle);


	FT_Close(handle);


}



//taget device öffnen, kurzes Reset des Masters, Rts low um per Funkmodul dein einschaltbefehl 
//fürden Slave zu übermitteln
void FTD::open(void)
{
	FT_STATUS ftStatus = FT_OK;

	if(a_numDevices>0)
	{
		void * p1; unsigned int numDevs;
		p1 = (void*)&numDevs;
		//ftStatus = FT_ListDevices(p1, NULL, FT_LIST_NUMBER_ONLY);
		Sleep(20);

		ftStatus = FT_Open(a_tagetDevice, &handle); //immer erstes FTDI device öffenen 
		//Sleep(200);


		FT_ClrRts(handle);//für dennn fall das Programm vorher unerwartet vendet wurde und RTS schon low ist
		Sleep(100);
		FT_SetRts(handle);

		ftStatus =FT_SetDataCharacteristics(handle,a_bits,0,0);
		ftStatus = FT_SetBaudRate(handle, a_baud);

	}

	Sleep(10);

}




//Daten Senden und event aktivieren, welches Reciver-Thread aufweckt, sobald RX-Aktivität
int FTD::sendData(unsigned char* p_data, int p_length)
{
			DWORD ret;
			FT_STATUS ftStatus = FT_OK;			
			FT_Write(handle, p_data, p_length, &ret);
			return (int) ret;
}

//Liest die Daten aus dem Softwarebuffer, die vom Thread aus dem Gerät gelesen wurden
//wenn im Threadbuffer nicht die geforderte Anzahl an Daten vorliegt wird nicht gelesen,
// so kann von außen anhand des Returns die funktion bis zum gewünschten Datenpacketes ausgelesen 
//werden 
int FTD::recvData(unsigned char* p_data,unsigned int p_maxLength)
{	
	unsigned int i=0;
	if (a_recvCnt<p_maxLength) return 0;
	for( i=0;i<a_recvCnt;i++)
	{
		p_data[i]=threadBuffer[i];
	}
	i=a_recvCnt;
	a_recvCnt=0;

	return i;
}




void FTD::setBit(unsigned char mask)
{

	//In the case of CBUS Bit Bang, the upper nibble of this value controls 
	//which pins are inputs and outputs, while the lower nibble controls which 
	//of the outputs are high and low.

	FT_STATUS ftStatus = FT_OK;
	//0x20 cbus bitbang 
	ftStatus=FT_SetBitMode(handle,mask,0x20);

}

unsigned char FTD::getBit(void)
{	
	FT_STATUS ftStatus = FT_OK;


	unsigned char mask=0;
	FT_GetBitMode(handle,&mask);
	return mask;
}


//liest gewünschte Anzahl an Daten aus,
//tut dies bis Anzahl ausgelesen oder Timeout erreicht
int FTD::recvBuffer(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs)
{


	unsigned int num=0;
	unsigned int res=0;
	unsigned char* tmp;
	tmp=p_data;
	//this->recvDat(tmp,maxLength);
	bool done=0;	
	DWORD readBytes = 0;
	unsigned int cnt=0;
	do{


		if(num+a_recvCnt>=p_maxLength){
			readBytes=p_maxLength-num; //den rest einsammeln
			done=1;
		}
		else
			readBytes=a_recvCnt;


		res=this->recvData(tmp,readBytes);
		num+=res;
		tmp+=res;

		if(num<p_maxLength)
		{
			Sleep(1);

			cnt++;
		}
		if(cnt==p_timeOutMs)
		{
			done=1;
		}


	}while(!done);
	return num;
}



//////////////////////////////////////////////////////////////////////	
//für rfc notwendige Functionen
/////////////////////////////////////////////////////////////////////


//aufrufe des Normalen Recv, die empfangenen Daten werden auf 0xFF untersucht
// zwei aufeinanderfolgende 0xff werden auf eines reduziert 
int FTD::recvBufferRFC(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs)
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

//nicht benötigt 
int FTD::recvDataRFC(unsigned char* p_data,unsigned int p_maxLength)
{

	return 0;
}




//im Datensatz enthaltene 0xff werden verdoppelt um nicht als RFC-Command interpretiert zu werden
int FTD::sendDataRFC(unsigned char* p_data, int p_length)
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


//der Wechsel der Baudrate wird als RFC Commando ausgegeben,
bool FTD::setBaudRFC(int p_baud)
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

	int num=0;
	while (!num)
	{
		this->sendData(txbuffer,10);
		//Thread::Sleep(200);
		//Lies Antwort
		num=this->recvData(rxbuffer,10);
	}


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
	//if(num!=10) return 0;
	a_recvCnt=0;
	return 1; //befehl übermittelt und korrekt beantwortet
}


//nicht benötigt 
bool FTD::flush()
{
	return 0;
}









void FTD::toggleRTS(bool state)
{



	if(state)
		FT_ClrRts(handle);
	else
		FT_SetRts(handle);
}




void FTD::process()
{


	FT_STATUS status;
	bool on=true;
	while(!stopThread)
	{
		DWORD dwRead, dwRXBytes;
		if(handle) 
		{
			status = FT_GetQueueStatus(handle, &dwRead);
			if(status != FT_OK)  continue;	
			while(dwRead && bContinue)
			{
				status = FT_Read(handle, threadBuffer+a_recvCnt, 1, &dwRXBytes);
				a_recvCnt++;
				if(a_recvCnt==buffersize) a_recvCnt=0; 
				if(status != FT_OK) continue;						
				status = FT_GetQueueStatus(handle, &dwRead);
			}
		}
		Sleep(1);
		testCnt++;

	}
	emit finished();
}

//SPI rouitinen imbitBang mode
//CB00		enable ausgang
//CB01		RX
//CB02		TX
//CB03		CLK
unsigned char  FTD::sendBBSpi(unsigned char data)
{



	return 0;
}

void FTD::initBBSpi(void)
{
		unsigned char mask=this->getBit(); //hier auslesen 
		this->setBit(mask|0x20);  //ausgang cb01 als eingang rest als eingang 
}


void  FTD::enableSpiDevice(bool enable)
{
	unsigned char mask=this->getBit(); //hier auslesen 
	if(enable)
		this->setBit(mask|0x01);
	else 
		this->setBit(mask&~0x01);

}

void FTD::setBaud(int P_baud,bool reinit)
{
	a_baud=P_baud;
//	if(reinit)
		FT_SetBaudRate(handle, a_baud);
}



