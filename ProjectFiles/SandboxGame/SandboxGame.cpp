#include <Qt\qapplication.h>
#include <QtGui\qwidget.h>
#include "MyGlWindow.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	// get a window
	MyGlWindow myGlWindow;
	myGlWindow.show();

	// return error code
	return application.exec();
}