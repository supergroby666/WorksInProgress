// Header file to get a new instance of QApplication
#include <Qt/qapplication.h>
// Header file for MainWindow class
#include "MainWindow.h"
int main(int argc, char* argv[])
{
	// create a new instance of QApplication with params argc and argv
	QApplication app( argc, argv );
	// create a new instance of MainWindow with no parent widget
	MainWindow mainWindow(0, Qt::Window);

	// Shows the widget and its child widgets.
	mainWindow.show();
	// Enters the main event loop and waits until exit() is called
	// or the main widget is destroyed or by default the last window closed,
	// and returns the value that was set via to exit()
	
	return app.exec(); 
}