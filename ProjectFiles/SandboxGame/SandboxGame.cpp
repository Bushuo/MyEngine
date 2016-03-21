#include <Qt\qapplication.h>

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	// return error code
	return application.exec();
}