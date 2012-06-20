

#ifndef RS232_H_
#define RS232_H_

#using <System.dll>
#include <iostream>
#include "globals.h"
//#include "stdafx.h"
#include <windows.h> 
#include <sstream>
using namespace System;
using namespace System::IO::Ports;


class RS232
{

public:
	RS232();
	~RS232();

	virtual int sendData(unsigned char* data, int length);
	virtual void setBaud(int P_baud);	
	virtual void setBits(int p_bits);
	virtual void setPort(int p_port);
	void init(void);
	virtual void reinit(void);
	

	//für rfc notwendige Functionen
	virtual int recvBufferRFC(unsigned char* p_data,unsigned int p_maxLength,unsigned int p_timeOutMs);
    virtual int recvDataRFC(unsigned char* p_data,unsigned int p_maxLength);
	virtual int sendDataRFC(unsigned char* p_data, int p_length);
	virtual bool setBaudRFC(int P_baud);
	virtual bool flush();
	int recvData(unsigned char* data,unsigned int maxLength);
	int recvBuffer(unsigned char* data,unsigned int maxLength,unsigned int timeOutMs);

protected: 
	char* buffer;
	int a_baud;
	int a_bits;
	int a_portNum;
	static unsigned char txbuffer[buffersize];
    static unsigned char rxbuffer[buffersize];

private:
	
	HANDLE hSerial;


};

inline void RS232::setBaud(int P_baud)
{
	a_baud=P_baud;
};
inline void RS232::setBits(int p_bits)
{
	a_bits=p_bits;
};
inline void RS232::setPort(int p_port)
{
	a_portNum=p_port;
};

#endif
