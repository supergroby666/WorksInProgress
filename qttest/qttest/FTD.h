#ifndef FTD_H_
#define FTD_H_

 #include <Qt/QLibrary.h>
 #include <Qt/QThread.h>
 #include "windows.h"
#include <iostream>
#define buffersize (2048*2)
#define readLength (32)
 #include <Qt/Qdatetime.h>


//Klasse zum dierkt auslesen des FTDI-Chips
//mit integrierten RFC-Erweiterungen und Steuerung des Wlan-Modulsvia RTS und DTR
//das Auslesen wird (änhlich wie im ftdichip Programmierbeispiel) nicht direkt, sondern
//mit einem Abholthread bewerkstelligt. 
//!!Achtung!! das Threading war nur zu Testzwecken verwendet wurden, nicht 100% sauber,
//da der Threadingbuffer während des Lesens nicht fürs beschreiben gesperrt wird
const unsigned int FT_LIST_NUMBER_ONLY = 0x80000000;


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

	
	typedef unsigned long FT_STATUS;
	typedef void * FT_HANDLE;
	class FTD: public QObject 
	{

		Q_OBJECT
	public: 
		//Konstruktur: Anlegen der variablen, Arrays und events. Abfragen der FTi-Devices mittels
		//Anzahl angeschlossener Devices. Alternativ kann man geziehlt die Infromationen mit 
		// GetDeviceInfolist abfragen und bestimme Geräte öffnen 
		
		
		/*typedef unsigned long (*FT_ListDevicesProto)(void * ,unsigned int,unsigned int);
		FT_ListDevicesProto FT_ListDevices;

		typedef unsigned long (*FT_CloseProto)(FT_HANDLE);
		FT_CloseProto FT_Close;

		typedef unsigned long (*FT_OpenProto)(int, FT_HANDLE * );
		FT_OpenProto FT_Open;

			typedef unsigned long (*FT_SetRtsProto)( FT_HANDLE);
		FT_SetRtsProto FT_SetRts;

			typedef unsigned long (*FT_ClrRtsProto)( FT_HANDLE);
		FT_ClrRtsProto FT_ClrRts;
		
		
		typedef unsigned long (*FT_WriteProto)( FT_HANDLE, LPVOID , DWORD , LPDWORD );
		FT_WriteProto FT_Write;
		
		typedef unsigned long (*FT_ReadProto)( FT_HANDLE, LPVOID , DWORD , LPDWORD );
		FT_ReadProto FT_Read;


				
		typedef FT_STATUS (*FT_SetBitmodeProto)( FT_HANDLE, unsigned char , unsigned char );
		FT_SetBitmodeProto FT_SetBitmode;
		
		typedef FT_STATUS (*FT_GetBitmodeProto)( FT_HANDLE,  unsigned char*);
		FT_GetBitmodeProto FT_GetBitmode;*/

		
		FTD();

		void toggleRTS(bool state);

		~FTD();
		//Rts High, Thread Stoppen, Verbindung beenden 
		void close(void);

	


		void setBit(unsigned char mask);
		unsigned char getBit(void);

		//taget device öffnen, kurzes Reset des Masters, Rts low um per Funkmodul dein einschaltbefehl 
		//fürden Slave zu übermitteln
		void open(void);

	


		//Daten Senden und event aktivieren, welches Reciver-Thread aufweckt, sobald RX-Aktivität
		int sendData(unsigned char* p_data, int p_length);

		//Liest die Daten aus dem Softwarebuffer, die vom Thread aus dem Gerät gelesen wurden
		//wenn im Threadbuffer nicht die geforderte Anzahl an Daten vorliegt wird nicht gelesen,
		// so kann von außen anhand des Returns die funktion bis zum gewünschten Datenpacketes ausgelesen 
		//werden 
		int recvData(unsigned char* p_data,unsigned int p_maxLength);

		//liest gewünschte Anzahl an Daten aus,
		//tut dies bis Anzahl ausgelesen oder Timeout erreicht
		int recvBuffer(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs);



		//////////////////////////////////////////////////////////////////////	
		//für rfc notwendige Functionen
		/////////////////////////////////////////////////////////////////////


		//aufrufe des Normalen Recv, die empfangenen Daten werden auf 0xFF untersucht
		// zwei aufeinanderfolgende 0xff werden auf eines reduziert 
		int recvBufferRFC(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs);

		//nicht benötigt 
		int recvDataRFC(unsigned char* p_data,unsigned int p_maxLength);

		
	

		//im Datensatz enthaltene 0xff werden verdoppelt um nicht als RFC-Command interpretiert zu werden
		int sendDataRFC(unsigned char* p_data, int p_length);
		//der Wechsel der Baudrate wird als RFC Commando ausgegeben,
		bool setBaudRFC(int p_baud);


		//nicht benötigt 
		bool flush();


		//BitBang SPI Routinen
		void initBBSpi(void);
		unsigned char  sendBBSpi(unsigned char data);
		void  enableSpiDevice(bool enable);

		
		//Setter/Getter
		virtual void setBaud(int P_baud,bool reinit);
		virtual void setDevice(int P_dev);
		virtual void setBits(int p_bits);
		virtual void setPort(int p_port);
		virtual unsigned int getDeviceNumber(void);
		unsigned int a_numDevices;
		bool stopThread;





	protected:

		QLibrary* lib;
		FT_HANDLE handle;
		int testCnt;
		//QTimer * a_timer;
	


public slots:
    void process();


	
 

signals:
    void finished();
    void error(QString err);

 


	private:

		

		char* buffer;
		unsigned int a_recvCnt;
		int a_baud;
		int a_bits;
		int a_portNum;
		int a_tagetDevice;
		//unsigned int a_numDevices;
		unsigned char* txbuffer;//[buffersize]
		unsigned char* rxbuffer;//[buffersize];
		unsigned char* threadBuffer;//[buffersize];
	
		bool bContinue;



	};

	
	inline void FTD::setDevice(int P_dev)
	{
		a_tagetDevice=P_dev;
	}
	inline void FTD::setBits(int p_bits)
	{
		a_bits=p_bits;
	}
	inline void FTD::setPort(int p_port)
	{
		a_portNum=p_port;
	}

   inline unsigned int  FTD::getDeviceNumber(void)
	{
		return a_numDevices;
	}




#endif 