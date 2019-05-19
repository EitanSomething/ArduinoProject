
#include "SerialClass.h"
#include "atlstr.h"
#include "MainWindow.h"
#include <iostream>
#include "Windows.h"
#include "SetupAPI.h"
#include <fstream>
#include <string.h>

#include <tchar.h>
#include <vector>
#include <wchar.h>
#include <SerialClass.h>
extern std::vector<std::vector<CString>> PortNameAndSerialNumber;
extern std::vector<CString> PortName;
extern int numberofPorts;
	void GetDataFromArduino();
	void OrganizeData(std::string input);
	void portNameAndSerialNumber();
