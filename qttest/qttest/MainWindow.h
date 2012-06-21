#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include "Ui_MainWindow.h"
#include "FTD.h"
#include <Qt/Qstring.h>
#include <Qt/Qtextstream.h>
#include <Qt/QThread.h>
#include <Qt/qregexp.h>
 #include <Qt/QTimer.h>
 #include <Qt/QMessageBox.h>

/**
* Sample MainWindow Class
* The class is a simple implementation of a QDesigner created form file
* defining a simple QMainWindow application
* The class inherits from QMainWindow and Ui_MainWindow. The Ui_MainWindow
* provides the QDesigner part of the implementation, while the QMainWindow
* provides the main functions of a QT Application
*/
class MainWindow : public QMainWindow, protected Ui_MainWindow
{
	Q_OBJECT
public:
	/**
	* Constructor of the MainWindow class
	* @param parent this optional parameter defines a parent widget the
	created instance will be child of
	* @param flags optional parameter defining extra widget options
	(see also the QT documentation)
	*/
	MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	/**
	Destructor of the MainWindow class, defined virtual to guarantee that
	the destructor will be called even if the instance of this class is
	saved in a variable of a parent class type
	*/

	virtual ~MainWindow();
private:
	FTD* master;
	QThread* thread;
	bool isOpen;
	bool useRFC;
	int a_speed;
	int a_device;

	protected slots:
		void opendevice();
		void RFC(bool val);
		void selectDevice(int index);
		void Header();
		void Vars();
		void data();
		void speed(int index);
		void DataatSpeed();
		void closeDevice();
		void RTS(bool val);
		void Info();
		void CB0(bool val);
		void CB1(bool val);
		void CB2(bool val);
		void CB3(bool val);

		void SPI(bool val);
		void SendSpi();
		void CleanSpiText();





};
#endif // end of #ifndef MAINWINDOW_H_