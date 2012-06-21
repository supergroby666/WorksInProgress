#include "MainWindow.h"

unsigned char sBuf[buffersize]={0x80,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
MainWindow::MainWindow(QWidget* parent /* = 0 */, Qt::WindowFlags flags /* = 0 */)
: QMainWindow(parent, flags),
isOpen(false),
useRFC(false),
a_device(0),
a_speed(9600)
{
	// create gui elements defined in the Ui_MainWindow class
	setupUi(this);
	connect(pushButton, SIGNAL(clicked()), this, SLOT(opendevice()));
	connect(pushButton_2, SIGNAL(clicked()), this, SLOT(Header()));
	connect(pushButton_3, SIGNAL(clicked()), this, SLOT(Vars()));
	connect(pushButton_4, SIGNAL(clicked()), this, SLOT(data()));
	connect(pushButton_5, SIGNAL(clicked()), this, SLOT(DataatSpeed()));
	connect(pushButton_6, SIGNAL(clicked()), this, SLOT(closeDevice()));
	connect(comboBox_2, SIGNAL(currentIndexChanged ( int )), this, SLOT(selectDevice(int)));
	connect(comboBox, SIGNAL(currentIndexChanged( int )), this, SLOT(speed(int)));
	connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(RFC(bool)));
	connect(RTSSet, SIGNAL(toggled(bool)), this, SLOT(RTS(bool)));
	connect(actionInfo, SIGNAL(triggered()), this, SLOT(Info()));
	connect(CBus0, SIGNAL(toggled(bool)), this, SLOT(CB0(bool)));
	connect(CBus1, SIGNAL(toggled(bool)), this, SLOT(CB1(bool)));
	connect(CBus2, SIGNAL(toggled(bool)), this, SLOT(CB2(bool)));
	connect(CBus3, SIGNAL(toggled(bool)), this, SLOT(CB3(bool)));
	connect(SPIMode, SIGNAL(toggled(bool)), this, SLOT(SPI(bool)));
	connect(Send, SIGNAL(clicked()), this, SLOT(SendSpi()));
	connect(SPIText, SIGNAL(textChanged()), this, SLOT(CleanSpiText()));



	thread=new QThread;
	master=new FTD();
	master->moveToThread(thread);
	connect(master, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(thread, SIGNAL(started()), master, SLOT(process()));
	connect(master, SIGNAL(finished()), thread, SLOT(quit()));
	connect(master, SIGNAL(finished()), master, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));













	int i=master->getDeviceNumber();
	comboBox_2->clear();
	for(int z=0;z<i;z++)
		comboBox_2->addItem(QString::number(z));
	pushButton_6->setEnabled(false);
	//textEdit->setTextFormat(Qt::LogText);
	
	QFont font("Courir");
	font.setFixedPitch(true);
	font.setBold(true);
	textEdit->setCurrentFont(font);
	
	textEdit->setFontPointSize(8);
	textEdit->setText("Welcome");
	comboBox_2->setEnabled(true);
	pushButton->setEnabled(true);
	pushButton_6->setEnabled(false);
	pushButton_3->setEnabled(false);
	pushButton_4->setEnabled(false);
	pushButton_5->setEnabled(false);
	pushButton_2->setEnabled(false);
	RTSSet->setEnabled(false);
	checkBox->setEnabled(true);
	comboBox->setEnabled(false);

	Cbus->setEnabled(false);
	SPIMode->setEnabled(false);
	SPIGr->setEnabled(false);




}
MainWindow::~MainWindow()
{
	if(isOpen){
		master->stopThread=true;
		master->close();

	}
	//delete thread; unnötig durch den deleteLater slot() der den Thread erst dann löscht wenn der beendet wurde 

	//delete master; wird durch deletelater zerstört 

	// no need to delete child widgets, QT does it all for us
}

void MainWindow::opendevice()
{
	checkBox->setEnabled(false);
	isOpen=true;
	master->setDevice(comboBox_2->currentIndex());
	if(useRFC)
	{		
		master->setBaud(115200,0);
		
	}
	else
	{
		textEdit->setText("Open");
		master->setBaud(9600,0);

	}

	
	master->open();
		master->stopThread=false;
	thread->start();
	master->stopThread=false;


	if(useRFC)
	{
		textEdit->setText("Searching RFC counterpart!!");
		master->setBaud(115200,0);
		QTime t;
		t.start();
		
		while(!master->setBaudRFC(9600))
		{

			if(t.elapsed()>10000) 
			{
				textEdit->setText("TimeOut!!!");
				return;
			}
		}
		textEdit->setText("Open");
	}
	comboBox_2->setEnabled(false);
	pushButton->setEnabled(false);
	pushButton_6->setEnabled(true);


	comboBox_2->setEnabled(false);
	pushButton->setEnabled(false);
	pushButton_6->setEnabled(true);
	pushButton_3->setEnabled(true);
	pushButton_4->setEnabled(true);
	pushButton_5->setEnabled(true);
	pushButton_2->setEnabled(true);
	RTSSet->setEnabled(true);
	
	comboBox->setEnabled(true);
	Cbus->setEnabled(true);
	SPIMode->setEnabled(true);
	textEdit->setText("Open");



	unsigned char mask=0xF0;		
	master->setBit(mask);


}


void MainWindow::closeDevice()
{

	//
	//master->close();
	comboBox_2->setEnabled(true);
	pushButton->setEnabled(true);
	pushButton_6->setEnabled(false);
	pushButton_3->setEnabled(false);
	pushButton_4->setEnabled(false);
	pushButton_5->setEnabled(false);
	pushButton_2->setEnabled(false);
	RTSSet->setEnabled(false);
	checkBox->setEnabled(true);
	comboBox->setEnabled(false);
	Cbus->setEnabled(false);
	SPIMode->setEnabled(false);
	SPIGr->setEnabled(false);
	textEdit->setText("Closed");
	//thread->quit();
}


void MainWindow::RFC(bool val)
{

	if(val)
	{
		master->setBaud(115200,1);
		useRFC=true;
	}
	else
	{
		master->setBaud(9600,1);
		useRFC=false;
	}

}

void MainWindow::selectDevice(int index)
{
	a_device=index;
}

void MainWindow::Header()
{
	int res=0;
	int len=0;
	textEdit->setText("Header: \n");
	if(useRFC)
	{
		

		sBuf[0]=0x80;
		sBuf[1]=0x00;
		len=2;
		res=master->sendDataRFC(sBuf,len);
		Sleep(10);
		res=master->recvBufferRFC(sBuf,buffersize,200);
		//QString text=QString::fromAscii((const char *)sBuf,res);
		////textEdit->setText(text);
		//textEdit->append(text);

		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
			
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}
		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");

	}else
	{
		sBuf[0]=0x80;
		sBuf[1]=0x00;
		len=2;
		res=master->sendData(sBuf,len);
		Sleep(10);
		res=master->recvBuffer(sBuf,buffersize,200);
		//QString text=QString::fromAscii((const char *)sBuf,res);
		////textEdit->setText(text);
		//textEdit->append(text);

		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
			
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}
		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");
	}

}

void MainWindow::Vars()
{	

	int res=0;
	int len=0;
	textEdit->setText("Vars: \n");

	if(useRFC)
	{

		sBuf[0]=0x80;
		sBuf[1]=0x02;
		sBuf[2]=0x52;
		len=3;
		res=master->sendDataRFC(sBuf,len);
		Sleep(50);
		res=master->recvBufferRFC(sBuf,buffersize,200);
		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
		
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}
		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");

	}else
	{
		sBuf[0]=0x80;
		sBuf[1]=0x02;
		sBuf[2]=0x52;
		len=3;
		res=master->sendData(sBuf,len);
		Sleep(50);
		res=master->recvBuffer(sBuf,buffersize,200);
		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
		
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}
		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");
	}
}



void MainWindow::data()
{
	int res=0;
	int len=0;
	textEdit->setText("Data: \n");
	if(useRFC)
	{

		sBuf[0]=0x80;
		sBuf[1]=0x0A;
		sBuf[2]=0x52;
		sBuf[3]=0x00;
		sBuf[4]=0x00;
		sBuf[5]=0x00;
		sBuf[6]=0x00;
		sBuf[7]=0x00;
		sBuf[8]=0x00;
		sBuf[9]=0x00;
		sBuf[10]=0x00;
		sBuf[11]=0x00;
		sBuf[12]=0x00;
		sBuf[13]=0x00;
		sBuf[14]=0x00;
		sBuf[15]=0x0f;
		sBuf[16]=0x0f;
		sBuf[17]=0x0f;
		sBuf[18]=0x0f;
		sBuf[19]=0x0f;
		sBuf[20]=0x0f;
		sBuf[21]=0x0f;
		sBuf[22]=0x0f;
		sBuf[23]=0x0f;
		sBuf[24]=0x0f;
		sBuf[25]=0x0f;
		sBuf[26]=0x0f;
		sBuf[27]=0x00;
		sBuf[28]=0x00;
		sBuf[29]=0x00;
		sBuf[30]=0x00;
		sBuf[31]=0x01;

		len=32;
		res=master->sendDataRFC(sBuf,len);
		Sleep(50);
		res=master->recvBufferRFC(sBuf,buffersize,2000);
		Sleep(100);
		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
		
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}

		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");

	}else
	{


		sBuf[0]=0x80;
		sBuf[1]=0x0A;
		sBuf[2]=0x52;
		sBuf[3]=0x00;
		sBuf[4]=0x00;
		sBuf[5]=0x00;
		sBuf[6]=0x00;
		sBuf[7]=0x00;
		sBuf[8]=0x00;
		sBuf[9]=0x00;
		sBuf[10]=0x00;
		sBuf[11]=0x00;
		sBuf[12]=0x00;
		sBuf[13]=0x00;
		sBuf[14]=0x00;
		sBuf[15]=0x0f;
		sBuf[16]=0x0f;
		sBuf[17]=0x0f;
		sBuf[18]=0x0f;
		sBuf[19]=0x0f;
		sBuf[20]=0x0f;
		sBuf[21]=0x0f;
		sBuf[22]=0x0f;
		sBuf[23]=0x0f;
		sBuf[24]=0x0f;
		sBuf[25]=0x0f;
		sBuf[26]=0x0f;
		sBuf[27]=0x00;
		sBuf[28]=0x00;
		sBuf[29]=0x00;
		sBuf[30]=0x00;
		sBuf[31]=0x01;

		len=32;
		res=master->sendData(sBuf,len);
		Sleep(50);
		res=master->recvBuffer(sBuf,buffersize,2000);
		Sleep(100);
		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
		
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}

		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");

	}
}

void MainWindow::speed(int index)
{
	if(index==0)
		a_speed=9600;
	else if(index==1)
		a_speed=19200;
	else if(index==2)
		a_speed=57600;
	else if(index==3)
		a_speed=115200;

}

void MainWindow::DataatSpeed()
{
	int res=0;
	int len=0;
	textEdit->setText("Data: \n");
	if(useRFC)
	{

		sBuf[0]=0x80;
		sBuf[1]=0x0A;
		sBuf[2]=0x52;
		sBuf[3]=0x00;
		sBuf[4]=0x00;
		sBuf[5]=0x00;
		sBuf[6]=0x00;
		sBuf[7]=0x00;
		sBuf[8]=0x00;
		sBuf[9]=0x00;
		sBuf[10]=0x00;
		sBuf[11]=0x00;
		sBuf[12]=0x00;
		sBuf[13]=0x00;
		sBuf[14]=0x00;
		sBuf[15]=0x0f;
		sBuf[16]=0x0f;
		sBuf[17]=0x0f;
		sBuf[18]=0x0f;
		sBuf[19]=0x0f;
		sBuf[20]=0x0f;
		sBuf[21]=0x0f;
		sBuf[22]=0x0f;
		sBuf[23]=0x0f;
		sBuf[24]=0x0f;
		sBuf[25]=0x0f;
		unsigned int r=a_speed;
		if(r>65535)
		{
			sBuf[26]=0x0f;
			r/=100;
		}
		else
			sBuf[26]=0x07;

		//baudrate shiften
		sBuf[27]=0x00;
		sBuf[27]=(r>>4)&0x0f;
		sBuf[28]=0x00;
		sBuf[28]=r&0x0f;
		sBuf[29]=0x00;
		sBuf[29]=(r>>12)&0x0f;
		sBuf[30]=0x00;
		sBuf[30]=(r>>8)&0x0f;
		len=31;



		Sleep(100);				
		res=master->sendDataRFC(sBuf,len);
		Sleep(100);				
		res=master->recvBufferRFC(sBuf,buffersize,200);


		Sleep(200);				
		while(!master->setBaudRFC(a_speed));
		Sleep(200);
		sBuf[0]=0x01;
		sBuf[1]=0x01;
		sBuf[2]=0x00;			
		len=1;	
		/////////////0x01 senden	
		res=master->sendDataRFC(sBuf,len);
		res=master->recvBufferRFC(sBuf,buffersize,200);

		/////Sende 0x01 0x01 0x00
		sBuf[0]=0x01;
		sBuf[1]=0x01;
		sBuf[2]=0x00;				
		len=3;	


		res=master->sendDataRFC(sBuf,len);

		Sleep(10);			


		res=master->recvBufferRFC(sBuf,buffersize,2000);
		

		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
		
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}
		//textEdit->setAlignment(Qt::AlignCenter);
		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");
		while(!master->setBaudRFC(9600));

	}else
	{
		sBuf[0]=0x80;
		sBuf[1]=0x0A;
		sBuf[2]=0x52;
		sBuf[3]=0x00;
		sBuf[4]=0x00;
		sBuf[5]=0x00;
		sBuf[6]=0x00;
		sBuf[7]=0x00;
		sBuf[8]=0x00;
		sBuf[9]=0x00;
		sBuf[10]=0x00;
		sBuf[11]=0x00;
		sBuf[12]=0x00;
		sBuf[13]=0x00;
		sBuf[14]=0x00;
		sBuf[15]=0x0f;
		sBuf[16]=0x0f;
		sBuf[17]=0x0f;
		sBuf[18]=0x0f;
		sBuf[19]=0x0f;
		sBuf[20]=0x0f;
		sBuf[21]=0x0f;
		sBuf[22]=0x0f;
		sBuf[23]=0x0f;
		sBuf[24]=0x0f;
		sBuf[25]=0x0f;
		unsigned int r=a_speed;
		if(r>65535)
		{
			sBuf[26]=0x0f;
			r/=100;
		}
		else
			sBuf[26]=0x07;

		//baudrate shiften
		sBuf[27]=0x00;
		sBuf[27]=(r>>4)&0x0f;
		sBuf[28]=0x00;
		sBuf[28]=r&0x0f;
		sBuf[29]=0x00;
		sBuf[29]=(r>>12)&0x0f;
		sBuf[30]=0x00;
		sBuf[30]=(r>>8)&0x0f;
		len=31;



		Sleep(100);				
		res=master->sendData(sBuf,len);
		Sleep(100);				
		res=master->recvBuffer(sBuf,buffersize,200);


		Sleep(200);				
		master->setBaud(a_speed ,1);
		Sleep(200);
		sBuf[0]=0x01;
		sBuf[1]=0x01;
		sBuf[2]=0x00;			
		len=1;	
		/////////////0x01 senden	
		res=master->sendData(sBuf,len);
		res=master->recvBuffer(sBuf,buffersize,200);

		/////Sende 0x01 0x01 0x00
		sBuf[0]=0x01;
		sBuf[1]=0x01;
		sBuf[2]=0x00;				
		len=3;	


		res=master->sendData(sBuf,len);

		Sleep(10);			


		res=master->recvBuffer(sBuf,buffersize,2000);
		

		QString text;
		QString str;
		int blocksize=0;
		for(int i=0;i<res;i++)
		{
			str=QString("%1").arg(sBuf[i],0, 16);
			if(str.size()==1)
				text+="0";
			text+=str;
			text+=" ";
			blocksize++;
		
			if(blocksize==16)
			{
				blocksize=0;
				text+="\n";

			}
		}
		//textEdit->setAlignment(Qt::AlignCenter);
		textEdit->append(text);
		textEdit->append("="+QString::number(res)+" Byte");
		master->setBaud(9600 ,1);
	}
}


void MainWindow::RTS(bool val)
{

	master->toggleRTS(val);


}

void MainWindow::CB0(bool val)
{


	unsigned char mask=master->getBit(); //hier auslesen 


	if(val)
		mask|=0x01;
	else
		mask&=~0x01;

	master->setBit(mask);




}

void MainWindow::CB1(bool val)
{

	unsigned char mask=master->getBit(); //hier auslesen 


	if(val)
		mask|=0x02;
	else
		mask&=~0x02;

	master->setBit(mask);;


}

void MainWindow::CB2(bool val)
{

	unsigned char mask=master->getBit(); //hier auslesen 


	if(val)
		mask|=0x04;
	else
		mask&=~0x04;

	master->setBit(mask);


}

void MainWindow::CB3(bool val)
{

	unsigned char mask=master->getBit(); //hier auslesen 


	if(val)
		mask|=0x08;
	else
		mask&=~0x08;

	master->setBit(mask);


}

void MainWindow::SPI(bool val)
{
	if(val)
	{
		SPIGr->setEnabled(true);
		Cbus->setEnabled(false);
		groupBox_2->setEnabled(false);
	}
	else 
	{
		SPIGr->setEnabled(false);
		Cbus->setEnabled(true);
		unsigned char mask=master->getBit(); //hier auslesen 
		master->setBit(mask|0xF0);  //ausgang cb01 als eingang rest als eingang 
		groupBox_2->setEnabled(true);
	}
}


void MainWindow::SendSpi()
{
	unsigned char mask=mask=master->getBit(); //hier auslesen 
	mask|=0x04;		
	master->setBit(mask);
	QString buf=SPIText->toPlainText();


}

void MainWindow::CleanSpiText()
{

	//QRegExp rx("[1-9]\\d{0,3}");
	QRegExp rx("[0-9A-Fa-f]{1,8}"); 
	QRegExpValidator   v(rx, 0);
	int l;
	QString buf=SPIText->toPlainText();
	l=buf.size();

	int pos = 0;
	if(!v.validate(buf,pos))
	{
//buf.resize(l-1);	
//		buf.remove(QRegExp("[f-zF-Z`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]]"));
//		/*if(l>0)
//		{
//		
//		}
//		else 
//		buf.resize(0);*/
//
//		SPIText->setPlainText(buf);
		SPIText->textCursor().deletePreviousChar ();

	}


}

void MainWindow::Info()
{
 QMessageBox msgBox;
 msgBox.setText("TestTool zum direkten Ansprechen eines FTDI-Chips mit D2XX Treibern.\n Zusätzlich Kommunikation mit RFC-Clients möglich.");
 msgBox.exec();

}