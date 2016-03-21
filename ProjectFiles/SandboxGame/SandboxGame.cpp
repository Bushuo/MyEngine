#include <Qt\qapplication.h>
#include <QtGui\qwidget.h>
#include "MyGlWindow.h"
#include "Windows.h"
#include "Qt\qdebug.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	// get a window
	MyGlWindow myGlWindow;
	myGlWindow.initialize();
	myGlWindow.show();

	// return error code
	int errorCode = application.exec();
	if (!myGlWindow.shutdown())
		errorCode |= 1;
	return errorCode;
	
}