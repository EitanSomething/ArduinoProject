#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <qlistwidget.h>
#include <qtimer.h>
#include "SerialClass.h"
#include "SerialPort.h"
extern int numberofSelectedPorts;
extern std::vector<CString> SelectedPorts;
class QPushButton;
class MainWindow : public QWidget
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	void paintEvent(QPaintEvent *event);
signals:
	void counterReached();
	
private slots:
private:
	QTimer* m_timer;
	
};

#endif // MAINWINDOW_H