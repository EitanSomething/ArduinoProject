#include "MainWindow.h"
#include "SerialClass.h"
#include "SerialPort.h"
#include "atlstr.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <qpainter.h>
#include <QPushButton>
#include <QApplication>
#include <QListWidget>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPainter>
std::vector<CString> SelectedPorts;
int numberofSelectedPorts;
MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent)
{
	// Set size of the window
	
	setMinimumSize(160, 160);
	resize(480, 320);
	// Create and position the button
	// Set the counter to 0

	// Convert a TCHAR string to a LPCSTR
	
	m_timer = new QTimer(this);

	m_timer->start(1000); // for a 1 second interval

	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	connect(this, SIGNAL(counterReached()), QApplication::instance(), SLOT(quit()));

}

void MainWindow::paintEvent(QPaintEvent *event)
{
	GetDataFromArduino();
	std::cout << "exit";
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::black);
	std::ifstream fileRoom("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room.csv");
	std::string csvItemRoom;
	std::ifstream fileHall("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall.csv");
	std::string csvItemHall;
	int lines = 0;
	while (std::getline(fileRoom, csvItemRoom)) {
		if (lines == 0) {
			painter.drawText(0, 0, 75, 25, Qt::AlignCenter, "Rooms");
		}
		else if (lines > 0) {
			for (int i = 0; i < std::stoi(csvItemRoom.substr(2, 1))+2; i++) {
				if ((i > 1) && (std::stoi(csvItemRoom.substr(i * 2, 1).c_str()) == 1)) {
					painter.setBrush(QBrush("#027f19"));
					painter.drawRect(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25);

					painter.drawText(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25, Qt::AlignCenter, std::to_string(i-1).c_str());

				}
				else if ((i > 1) && (std::stoi(csvItemRoom.substr(i * 2, 1).c_str()) == 0)) {
					painter.setBrush(QBrush("#c90808"));
					painter.drawRect(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25);

					painter.drawText(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25, Qt::AlignCenter, std::to_string(i - 1).c_str());

				}
				else if (i == 1) {
					painter.setBrush(QBrush("#6842f4"));
					painter.drawRect(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25);

					painter.drawText(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25, Qt::AlignCenter, csvItemRoom.substr(i * 2, 1).c_str());

				}
				else {
					painter.setBrush(QBrush("#f4eb41"));
					painter.drawRect(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25);

					painter.drawText(0 + (75 * i), 25 + (25 * (lines - 1)), 75, 25, Qt::AlignCenter, csvItemRoom.substr(i * 2, 1).c_str());

				}

				
			}
		}
		lines++;
	}
	int offset = lines;
	lines = 0;
	while (std::getline(fileHall, csvItemHall)) {
		if (lines == 0) {
			painter.drawText(0, (25 * offset), 75, 25, Qt::AlignCenter, "Hallway");
		}
		else if (lines > 0) {
			for (int i = 0; i < 2; i++) {
				if ((i==1)&&(std::stoi(csvItemHall.substr(i * 2, 1).c_str())==1)) {
					painter.setBrush(QBrush("#c90808"));

				}
				else if((i == 1) && (std::stoi(csvItemHall.substr(i * 2, 1).c_str()) == 0)) {
					painter.setBrush(QBrush("#027f19"));
				}
				else {
					painter.setBrush(QBrush("#f4eb41"));

				}
				painter.drawRect(0 + (75 * i), (25* offset) + (25 * (lines)), 75, 25);
				painter.drawText(0 + (75 * i), (25 * offset) + (25 * (lines)), 75, 25, Qt::AlignCenter, csvItemHall.substr(i * 2, 1).c_str());


			}
		}
		lines++;
	}
	fileRoom.close();
	fileHall.close();
}
