#include <QApplication>
#include <QMainWindow>

#include "window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
	Window widg;
	widg.show();

	return app.exec();
}

