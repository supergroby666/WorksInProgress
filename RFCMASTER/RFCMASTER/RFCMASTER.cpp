// RFCMASTER.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "FTD.h"

#define testRFC (1)

using namespace USB;

unsigned int rates[4]={9600,19200,57600,115200};


#define USB_direct //Auswahl flag, wenn nicht definiert wird über COM (virtuelle Schnittstelle) ausgelesen



//Test-Applikation um korrekte Ansteuerung der Wlan schnittstelle zu testen
//der PC-Seitige Master läuft dabei mit einer festen, möglichst hohen Baudrate (ideal 115200 Baud)
//per RFC Commando wird dann bei bedarf die Baudrate auf der Slave seite eingestellt, so dass im Idealfall 
//in der PWB-Software nur der Baudratenbefehl gegen einen RFC-Befehl getauscht werden muss



int _tmain(int argc, _TCHAR* argv[])
{

	int len=2;
	int res=0;
	std::cout<<"************************"<<std::endl;
	std::cout<<"*RFC-Software Test-Tool*"<<std::endl;
	std::cout<<"************************"<<std::endl;





	unsigned char buf[buffersize]={0x80,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
#ifdef USB_direct
	FTD* master= new FTD();
#else 

	RS232* master =new RS232();
#endif 


	char c[2];
	unsigned int dev=0;
	std::cout<<std::endl<<"Anzahl angeschlossener Geraete "<<master->getDeviceNumber()<<std::endl;
	std::cout<<std::endl<<"Welches Geraet oeffnen?  (1 bis "<<master->getDeviceNumber()<<")"<<std::endl;
	while(1)
	{
		c[0]=getch();
		dev=(unsigned int)c[0]-48-1;
		if(dev<master->getDeviceNumber())
		{
				master->setDevice(dev);
					break;
		}
		else
			std::cout<<std::endl<<"Falsche Eingabe! 1-"<<master->getDeviceNumber()<<" erwartet"<<std::endl;

	}


	master->setPort(15);
	master->setBaud(rates[3],0);//nur die BR zwischen PC und WLAN modul. die Baudraten "am" logger werden per rfc geswitched
	master->open();
	int Size=0;


	
	int i=0;

	if(testRFC)
	{
		int ct=0;
		std::cout<<std::endl<<"Warte auf Logger  ";
		while(!master->setBaudRFC(rates[i]))
		{

			//kann je nach sleep-zyklus des Slaves einige sekunden dauern (max 6.Sekunden für aufwachen + einige sekunden für automatisches verbinden des Sockets
			if(ct==0)
				std::cout<<"\b\b \\";
			else if(ct==1)
				std::cout<<"\b\b |";
			else if(ct==2)
			{
				std::cout<<"\b\b /";
				ct=0;
				continue;

			}
			ct++;
			Sleep(500);
		}
		std::cout<<std::endl<<"Geoeffnet! "<<std::endl;		
		Sleep(50);
	}
	else
	{
		master->setBaud(rates[0],1);
		
	}

	while(1)
	{


		if(testRFC)
			while(!master->setBaudRFC(rates[0]));
			//std::cout<<std::endl<<" Fehler beim setzen der Baudrate (RFC)"<<std::endl;
		else
			master->setBaud(rates[0],1);





		std::cout<<"Befehl:(1) Header; (2)Variablen; (3)Daten; (4)Daten mit gewaehlter BR; (ESC)Ende "<<std::endl;
		c[0]=getch();
		i=atoi(c);
		if((i>0)&(i<5))
		{
			if(i==1)
			{

				buf[0]=0x80;
				buf[1]=0x00;
				len=2;
				std::cout<<"Sende: ";
				for(int a =0; a<len;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}
				std::cout<<std::endl;

				if(testRFC)
					res=master->sendDataRFC(buf,len);
				else
					res=master->sendData(buf,len);

				Sleep(10);
				Size=0;
				std::cout<<"Empfange: ";
				std::cout<<std::endl;	


				if(testRFC)
					res=master->recvBufferRFC(buf,buffersize,200);
				else
					res=master->recvBuffer(buf,buffersize,200);

				//res=master->recvData(buf,buffersize);
				for(int a =0; a<res;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}
				std::cout<<std::endl;

				std::cout<<std::endl;
				std::cout<<" = "<<std::dec<<res<<" Byte";
				std::cout<<std::endl;
			}
			else if(i==2)
			{


				buf[0]=0x80;
				buf[1]=0x02;
				buf[2]=0x52;
				len=3;
				std::cout<<"Sende: ";
				for(int a =0; a<len;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}

				std::cout<<std::endl;

				if(testRFC)
					res=master->sendDataRFC(buf,len);
				else
					res=master->sendData(buf,len);
				Sleep(50);	

				Size=0;
				std::cout<<"Empfange: ";
				std::cout<<std::endl;			

				if(testRFC)
					res=master->recvBufferRFC(buf,buffersize,600);
				else
					res=master->recvBuffer(buf,buffersize,600);


				for(int a =0; a<res;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}
				std::cout<<std::endl;

				std::cout<<std::endl;
				std::cout<<" = "<<std::dec<<res<<" Byte";
				std::cout<<std::endl;
			}
			else if(i==3)
			{


				buf[0]=0x80;
				buf[1]=0x0A;
				buf[2]=0x52;
				buf[3]=0x00;
				buf[4]=0x00;
				buf[5]=0x00;
				buf[6]=0x00;
				buf[7]=0x00;
				buf[8]=0x00;
				buf[9]=0x00;
				buf[10]=0x00;
				buf[11]=0x00;
				buf[12]=0x00;
				buf[13]=0x00;
				buf[14]=0x00;
				buf[15]=0x0f;
				buf[16]=0x0f;
				buf[17]=0x0f;
				buf[18]=0x0f;
				buf[19]=0x0f;
				buf[20]=0x0f;
				buf[21]=0x0f;
				buf[22]=0x0f;
				buf[23]=0x0f;
				buf[24]=0x0f;
				buf[25]=0x0f;
				buf[26]=0x0f;
				buf[27]=0x00;
				buf[28]=0x00;
				buf[29]=0x00;
				buf[30]=0x00;
				buf[31]=0x01;

				len=32;
				std::cout<<"Sende: ";
				for(int a =0; a<len;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}
				std::cout<<std::endl;

				if(testRFC)
					res=master->sendDataRFC(buf,len);
				else	
					res=master->sendData(buf,len);
				Sleep(10);

				Size=0;
				std::cout<<"Empfange: ";
				std::cout<<std::endl;			

				if(testRFC)
					res=master->recvBufferRFC(buf,buffersize,2000);
				else
					res=master->recvBuffer(buf,buffersize,2000);
		
				for(int a =0; a<res;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}
				std::cout<<std::endl;

				std::cout<<std::endl;
				std::cout<<" = "<<std::dec<<res<<" Byte";
				std::cout<<std::endl;

			}
			else if(i==4)
			{
				std::cout<<"Datenrate waehlen (1)9600; (2)19200; (3)57600; (4)115200 "<<std::endl;
				c[0]=getch();
				i=atoi(c);
				if((i>0)&(i<5))
				{
					i--;
					std::cout<<"Datenrate: "<<std::dec<<rates[i]<<" Baud"<<std::endl;
				}		
				else
				{
					std::cout<<"Falsche Eingabe!!"<<std::endl;
					continue;
				}
				buf[0]=0x80;
				buf[1]=0x0A;
				buf[2]=0x52;
				buf[3]=0x00;
				buf[4]=0x00;
				buf[5]=0x00;
				buf[6]=0x00;
				buf[7]=0x00;
				buf[8]=0x00;
				buf[9]=0x00;
				buf[10]=0x00;
				buf[11]=0x00;
				buf[12]=0x00;
				buf[13]=0x00;
				buf[14]=0x00;
				buf[15]=0x0f;
				buf[16]=0x0f;
				buf[17]=0x0f;
				buf[18]=0x0f;
				buf[19]=0x0f;
				buf[20]=0x0f;
				buf[21]=0x0f;
				buf[22]=0x0f;
				buf[23]=0x0f;
				buf[24]=0x0f;
				buf[25]=0x0f;
				unsigned int r=rates[i];
				if(r>65535)
				{
					buf[26]=0x0f;
					r/=100;
				}
				else
					buf[26]=0x07;				

				//baudrate shiften
				buf[27]=0x00;
				buf[27]=(r>>4)&0x0f;
				buf[28]=0x00;
				buf[28]=r&0x0f;
				buf[29]=0x00;
				buf[29]=(r>>12)&0x0f;
				buf[30]=0x00;
				buf[30]=(r>>8)&0x0f;
				len=31;

				///////////Befehl senden			

				Sleep(100);
				if(testRFC)
					res=master->sendDataRFC(buf,len);
				else
					res=master->sendData(buf,len);
				Sleep(100);
				if(testRFC)
					res=master->recvBufferRFC(buf,buffersize,200);
				else
					res=master->recvBuffer(buf,buffersize,200);
				//res=master->recvDataRFC(buf,readLength);



				/////////////Baudrate ändern


				Sleep(200);
				if(testRFC)
					while(!master->setBaudRFC(rates[i]));
				else
					master->setBaud(rates[i] ,1);
				//std::cout<<std::endl<<" Fehler beim setzen der Baudrate (RFC)"<<std::endl;

				Sleep(200);

				buf[0]=0x01;
				buf[1]=0x01;
				buf[2]=0x00;			
				len=1;	
				/////////////0x01 senden		

				if(testRFC)
					res=master->sendDataRFC(buf,len);
				else
					res=master->sendData(buf,len);



				if(testRFC)
					res=master->recvBufferRFC(buf,buffersize,200);
				else	
					res=master->recvBuffer(buf,buffersize,200);
					
			


				/////Sende 0x01 0x01 0x00
				buf[0]=0x01;
				buf[1]=0x01;
				buf[2]=0x00;				
				len=3;		

				if(testRFC)
					res=master->sendDataRFC(buf,len);
				else
					res=master->sendData(buf,len);

				Sleep(10);			

				if(testRFC)
					res=master->recvBufferRFC(buf,buffersize,2000);
				else
					res=master->recvBuffer(buf,buffersize,2000);




				Size=0;
				std::cout<<"Empfange: ";
				std::cout<<std::endl;		
				for(int a =0; a<res;a++)
				{
					std::cout<<std::hex<<(int)buf[a]<<" ";
				}
				std::cout<<std::endl;

				std::cout<<std::endl;
				std::cout<<" = "<<std::dec<<res<<" Byte";
				std::cout<<std::endl;



				if(testRFC)
					while(!master->setBaudRFC(rates[i]));
				else
					master->setBaud(rates[i],1);
				//std::cout<<std::endl<<" Fehler beim setzen der Baudrate (RFC)"<<std::endl;
			}



		}
		else if(c[0]==0x1B)
			break;
		else
		{
			std::cout<<"Falsche Eingabe!!"<<std::endl;
			continue;
		}








	}









	
		master->close();

#ifndef USB_direct
		delete master;
#endif 





	return 0;
}

