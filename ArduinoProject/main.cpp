#include "atlstr.h"
#include <wchar.h>
#include "SerialClass.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include "Windows.h"
#include "SetupAPI.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();

}
