#ifndef FTD_H_
#define FTD_H_
#pragma once
//#include "stdafx.h"
#include "RS232.h"

//Klasse zum dierkt auslesen des FTDI-Chips
//mit integrierten RFC-Erweiterungen und Steuerung des Wlan-Modulsvia RTS und DTR
//das Auslesen wird (änhlich wie im ftdichip Programmierbeispiel) nicht direkt, sondern
//mit einem Abholthread bewerkstelligt. 
//!!Achtung!! das Threading war nur zu Testzwecken verwendet wurden, nicht 100% sauber,
//da der Threadingbuffer während des Lesens nicht fürs beschreiben gesperrt wird

namespace USB
{




	using namespace System;

	using namespace System::Threading;

	const UInt32 FT_LIST_NUMBER_ONLY = 0x80000000;
	const UInt32 FT_LIST_BY_INDEX	= 0x40000000;
	const UInt32 FT_LIST_ALL			= 0x20000000;
	const UInt32 FT_OPEN_BY_SERIAL_NUMBER = 1;
	const UInt32 FT_OPEN_BY_DESCRIPTION    = 2;

	const UInt32 FT_EVENT_RXCHAR		= 1;
	const UInt32 FT_EVENT_MODEM_STATUS  = 2;
#define FT_PREFIX [DllImport("FTD2XX.dll")]

	enum {
		FT_OK,
		FT_INVALID_HANDLE,
		FT_DEVICE_NOT_FOUND,
		FT_DEVICE_NOT_OPENED,
		FT_IO_ERROR,
		FT_INSUFFICIENT_RESOURCES,
		FT_INVALID_PARAMETER,
		FT_INVALID_BAUD_RATE,

		FT_DEVICE_NOT_OPENED_FOR_ERASE,
		FT_DEVICE_NOT_OPENED_FOR_WRITE,
		FT_FAILED_TO_WRITE_DEVICE,
		FT_EEPROM_READ_FAILED,
		FT_EEPROM_WRITE_FAILED,
		FT_EEPROM_ERASE_FAILED,
		FT_EEPROM_NOT_PRESENT,
		FT_EEPROM_NOT_PROGRAMMED,
		FT_INVALID_ARGS,
		FT_NOT_SUPPORTED,
		FT_OTHER_ERROR
	};

	typedef void * FT_HANDLE;
	typedef unsigned long DWORD;
	typedef unsigned long FT_STATUS;
	typedef void * LPVOID;
	typedef void * PVOID;
	typedef DWORD * LPDWORD;
	typedef DWORD ULONG;
	typedef unsigned short USHORT;
	typedef unsigned char UCHAR;
	typedef unsigned short WORD;
	typedef WORD * LPWORD;
	typedef unsigned char UCHAR;
	typedef UCHAR * PUCHAR;
	typedef char CHAR;
	typedef CHAR * PCHAR;
	typedef ULONG FT_DEVICE;
	typedef void *HANDLE;
	typedef int BOOL;
#define FALSE   0
#define TRUE    1


	using namespace System::Runtime::InteropServices;
	FT_PREFIX FT_STATUS FT_Open(int deviceNumber, FT_HANDLE * pHandle);
	FT_PREFIX FT_STATUS FT_OpenEx(PVOID pArg1, DWORD Flags, FT_HANDLE *pHandle);
	FT_PREFIX FT_STATUS FT_ListDevices(PVOID pArg1, PVOID pArg2, DWORD Flags);
	FT_PREFIX FT_STATUS FT_ListDevices(UInt32 pvArg1, void * pvArg2, UInt32 dwFlags);	// FT_ListDevcies by serial number or description by index only
	FT_PREFIX FT_STATUS FT_Close(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_Read(FT_HANDLE ftHandle, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesReturned);
	FT_PREFIX FT_STATUS FT_Write(FT_HANDLE ftHandle, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesWritten);
	FT_PREFIX FT_STATUS FT_SetBaudRate(FT_HANDLE ftHandle,	ULONG BaudRate);
	FT_PREFIX FT_STATUS FT_SetDivisor(FT_HANDLE ftHandle,USHORT Divisor);
	FT_PREFIX FT_STATUS FT_SetDataCharacteristics(FT_HANDLE ftHandle, UCHAR WordLength, UCHAR StopBits, UCHAR Parity);
	FT_PREFIX FT_STATUS FT_SetFlowControl(FT_HANDLE ftHandle, USHORT FlowControl, UCHAR XonChar, UCHAR XoffChar	);
	FT_PREFIX FT_STATUS FT_ResetDevice(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_SetDtr(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_ClrDtr(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_SetRts(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_ClrRts(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_GetModemStatus(FT_HANDLE ftHandle,	ULONG *pModemStatus);
	FT_PREFIX FT_STATUS FT_SetChars(FT_HANDLE ftHandle, UCHAR EventChar, UCHAR EventCharEnabled, UCHAR ErrorChar, UCHAR ErrorCharEnabled);
	FT_PREFIX FT_STATUS FT_Purge(FT_HANDLE ftHandle, ULONG Mask);
	FT_PREFIX FT_STATUS FT_SetTimeouts(FT_HANDLE ftHandle,	ULONG ReadTimeout,	ULONG WriteTimeout);
	FT_PREFIX FT_STATUS FT_GetQueueStatus(FT_HANDLE ftHandle, DWORD *dwRxBytes);
	FT_PREFIX FT_STATUS FT_SetEventNotification(FT_HANDLE ftHandle, DWORD Mask,	PVOID Param	);
	FT_PREFIX FT_STATUS FT_GetStatus(FT_HANDLE ftHandle, DWORD *dwRxBytes, DWORD *dwTxBytes, DWORD *dwEventDWord);
	FT_PREFIX FT_STATUS FT_SetBreakOn(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS FT_SetBreakOff(FT_HANDLE ftHandle);	
	FT_PREFIX FT_STATUS FT_SetWaitMask(FT_HANDLE ftHandle, DWORD Mask);
	FT_PREFIX FT_STATUS FT_WaitOnMask(FT_HANDLE ftHandle, DWORD *Mask);
	FT_PREFIX FT_STATUS FT_GetEventStatus(FT_HANDLE ftHandle, DWORD *dwEventDWord);
	FT_PREFIX FT_STATUS FT_ReadEE(FT_HANDLE ftHandle, DWORD dwWordOffset, LPWORD lpwValu);
	FT_PREFIX FT_STATUS FT_WriteEE(FT_HANDLE ftHandle,	DWORD dwWordOffset, WORD wValue);
	FT_PREFIX FT_STATUS FT_EraseEE(FT_HANDLE ftHandle);

	FT_PREFIX FT_STATUS FT_SetBitmode(FT_HANDLE ftHandle,UCHAR ucMask, UCHAR ucMode);
	FT_PREFIX FT_STATUS FT_GetBitmode(FT_HANDLE ftHandle, PUCHAR pucMode);
	// Missed out the programming stuff +++  kabel

	FT_PREFIX FT_STATUS  FT_EE_UASize(FT_HANDLE ftHandle, LPDWORD lpdwSize);
	FT_PREFIX FT_STATUS  FT_EE_UAWrite(FT_HANDLE ftHandle, PUCHAR pucData, DWORD dwDataLen	);
	FT_PREFIX FT_STATUS  FT_EE_UARead(FT_HANDLE ftHandle, PUCHAR pucData, DWORD dwDataLen, LPDWORD lpdwBytesRead);
	FT_PREFIX FT_STATUS  FT_SetLatencyTimer(FT_HANDLE ftHandle, UCHAR ucLatency);
	FT_PREFIX FT_STATUS  FT_GetLatencyTimer(FT_HANDLE ftHandle, PUCHAR pucLatency);
	FT_PREFIX FT_STATUS  FT_SetBitMode(FT_HANDLE ftHandle, UCHAR ucMask, UCHAR ucEnable);
	FT_PREFIX FT_STATUS  FT_GetBitMode(FT_HANDLE ftHandle, PUCHAR pucMode);
	FT_PREFIX FT_STATUS  FT_SetUSBParameters(FT_HANDLE ftHandle, ULONG ulInTransferSize, ULONG ulOutTransferSize);
	FT_PREFIX FT_STATUS  FT_GetDeviceInfo(FT_HANDLE ftHandle, FT_DEVICE *lpftDevice, LPDWORD lpdwID, PCHAR SerialNumber, PCHAR Description,	LPVOID Dummy);
	FT_PREFIX FT_STATUS  FT_StopInTask(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS  FT_RestartInTask(FT_HANDLE ftHandle);
	FT_PREFIX FT_STATUS  FT_SetResetPipeRetryCount(FT_HANDLE ftHandle, DWORD dwCount);
	FT_PREFIX FT_STATUS  FT_ResetPort(FT_HANDLE ftHandle);
	[DllImport("Kernel32.dll")] DWORD WaitForSingleObject(HANDLE hHandle,  DWORD dwMilliseconds);
	[DllImport("Kernel32.dll")] HANDLE CreateEvent(void * pNULL, BOOL bManualReset, BOOL bInitialState, char * pcNULL);
	[DllImport("Kernel32.dll")] BOOL SetEvent(HANDLE hEvent);

	FT_HANDLE handle;
	HANDLE hEvent;

	public __gc class FTD
	{
	public: 
		//Konstruktur: Anlegen der variablen, Arrays und events. Abfragen der FTi-Devices mittels
		//Anzahl angeschlossener Devices. Alternativ kann man geziehlt die Infromationen mit 
		// GetDeviceInfolist abfragen und bestimme Geräte öffnen 
		FTD()
			:a_tagetDevice(0),
			a_recvCnt(0),
			a_bits(8),
			a_numDevices(0)
		{		

			txbuffer=new unsigned char [2048];
			rxbuffer=new unsigned char [2048];
			threadBuffer=new unsigned char [2048];
			hEvent = CreateEvent(NULL, FALSE, FALSE, "");
			FT_STATUS ftStatus = FT_OK;
			void * p1; UInt32 numDevs;
			p1 = (void*)&numDevs;
			ftStatus = FT_ListDevices(p1, NULL, FT_LIST_NUMBER_ONLY);
			a_numDevices=numDevs;

		}


		~FTD()
		{		

			delete txbuffer;
			delete rxbuffer;
			delete threadBuffer;

		}

		//Rts High, Thread Stoppen, Verbindung beenden 
		void close(void)
		{
			//sendet das ausschaltsignal
			FT_ClrRts(handle);

			//FT_SetDtr(handle); //reset des Master ausführen, ->schneller und zuverlässigere Verbindung 
			//	Sleep(200);
		 //    FT_ClrDtr(handle); //reset des Master ausführen, ->schneller und zuverlässigere Verbindung 
			
			StopThread();
			
			FT_Close(handle);
		}



		//taget device öffnen, kurzes Reset des Masters, Rts low um per Funkmodul dein einschaltbefehl 
		//fürden Slave zu übermitteln
		void open(void)
		{
			FT_STATUS ftStatus = FT_OK;

			if(a_numDevices>0)
			{
		
				ftStatus = FT_Open(a_tagetDevice, &handle); //immer erstes FTDI device öffenen 
				Sleep(100);
				//FT_SetDtr(handle); //reset des Master ausführen, ->schneller und zuverlässigere Verbindung 
				Sleep(200);
				FT_ClrRts(handle);//für dennn fall das Programm vorher unerwartet vendet wurde und RTS schon low ist
				Sleep(100);
				FT_SetRts(handle);
				Sleep(1000);
				//FT_ClrDtr(handle); 
				
				//Datenlänge, Stopbit(0=1, 2=2), Parität(0=0) 
				ftStatus =FT_SetDataCharacteristics(handle,a_bits,0,0);


				FT_SetBitMode(handle,0xff,0x20);
				FT_SetBitMode(handle,0xf0,0x20);
				FT_SetBitMode(handle,0xff,0x20);
				FT_SetBitMode(handle,0x0f,0x20);
				FT_SetBitMode(handle,0xff,0x20);

				

			}
			ftStatus = FT_SetBaudRate(handle, a_baud);		
			Sleep(10);
			StartThread();
		}

	


		//Daten Senden und event aktivieren, welches Reciver-Thread aufweckt, sobald RX-Aktivität
		int sendData(unsigned char* p_data, int p_length)
		{
			DWORD ret;
			FT_STATUS ftStatus = FT_OK;
			ftStatus = FT_SetEventNotification(handle, FT_EVENT_RXCHAR, hEvent);
			FT_Write(handle, p_data, p_length, &ret);
			return (int) ret;
		}

		//Liest die Daten aus dem Softwarebuffer, die vom Thread aus dem Gerät gelesen wurden
		//wenn im Threadbuffer nicht die geforderte Anzahl an Daten vorliegt wird nicht gelesen,
		// so kann von außen anhand des Returns die funktion bis zum gewünschten Datenpacketes ausgelesen 
		//werden 
		int recvData(unsigned char* p_data,unsigned int p_maxLength)
		{	
			int i=0;
			if (a_recvCnt<p_maxLength) return 0;
			for( i=0;i<a_recvCnt;i++)
			{
				p_data[i]=threadBuffer[i];
			}
			i=a_recvCnt;
			a_recvCnt=0;

			return i;
		}

		//liest gewünschte Anzahl an Daten aus,
		//tut dies bis Anzahl ausgelesen oder Timeout erreicht
		int recvBuffer(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs)
		{


			int num=0;
			int res=0;
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
					Thread::Sleep(1);
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
		int recvBufferRFC(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs)
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
		int recvDataRFC(unsigned char* p_data,unsigned int p_maxLength)
		{

			return 0;
		}

		
	

		//im Datensatz enthaltene 0xff werden verdoppelt um nicht als RFC-Command interpretiert zu werden
		int sendDataRFC(unsigned char* p_data, int p_length)
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
		bool setBaudRFC(int p_baud)
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
				Thread::Sleep(200);
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
			if(num!=10) return 0;
			return 1; //befehl übermittelt und korrekt beantwortet
		}


		//nicht benötigt 
		bool flush()
		{
			return 0;
		}

		
		//Setter/Getter
		virtual void setBaud(int P_baud,bool reinit);
		virtual void setDevice(int P_dev);
		virtual void setBits(int p_bits);
		virtual void setPort(int p_port);
		virtual unsigned int getDeviceNumber(void);

	protected:

	private:

		//Routinen zum Threadmanagement
		void StartThread()
		{

			thrdReader = new Thread(new ThreadStart(this,&FTD::ReadingProc));
			bContinue = true;
			thrdReader->Start();
			while (!thrdReader->IsAlive);	// wait for the thread to start
			Thread::Sleep(1000);
		}
		Void StopThread()
		{
			bContinue = false;
			if(hEvent)		// let the thread come out of waiting for infinite time
				SetEvent(hEvent);
			if(thrdReader && thrdReader->IsAlive) {	// stop it
				TimeSpan waitTime = TimeSpan(0, 0, 1);	// 1 second timeout
				if(thrdReader->Join(waitTime) != true) {
					thrdReader->Abort();	// didnt stop the thread - take more drastic action
				}
			}
		}
		void ReadingProc()
		{

			TimeSpan waitTime = TimeSpan(0, 0, 1);	// 1 second timeout
			static char c = 0;
			char* pstr6 = &c;
			FT_STATUS status;

			while(bContinue) {				
				DWORD dwRead, dwRXBytes;
				//Byte b;
				WaitForSingleObject(hEvent, -1);
				if(handle) {
					status = FT_GetQueueStatus(handle, &dwRead);
					if(status != FT_OK)  continue;	
					while(dwRead && bContinue) {
						status = FT_Read(handle, threadBuffer+a_recvCnt, 1, &dwRXBytes);
						a_recvCnt++;
						if(status != FT_OK) continue;						
						status = FT_GetQueueStatus(handle, &dwRead);
					}
				}
				Thread::Sleep(0);
			}
			if(handle) {
				FT_Close(handle);
			}
		}

		char* buffer;
		unsigned int a_recvCnt;
		int a_baud;
		int a_bits;
		int a_portNum;
		int a_tagetDevice;
		unsigned int a_numDevices;
		unsigned char* txbuffer;//[buffersize]
		unsigned char* rxbuffer;//[buffersize];
		unsigned char* threadBuffer;//[buffersize];
		System::Threading::Thread* thrdReader;
		bool bContinue;

		UInt32 dwOpenFlags;


	};

	inline void FTD::setBaud(int P_baud,bool reinit)
	{
		a_baud=P_baud;
		if(reinit)
			FT_SetBaudRate(handle, a_baud);
	};
	inline void FTD::setDevice(int P_dev)
	{
		a_baud=P_dev;
	};
	inline void FTD::setBits(int p_bits)
	{
		a_bits=p_bits;
	};
	inline void FTD::setPort(int p_port)
	{
		a_portNum=p_port;
	};

   inline unsigned int  FTD::getDeviceNumber(void)
	{
		return a_numDevices;
	};

}


#endif 