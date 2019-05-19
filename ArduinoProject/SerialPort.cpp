
#include "SerialPort.h"

std::vector<std::vector<CString>> PortNameAndSerialNumber;
std::vector<CString> PortName;
int numberofPorts;

Serial* SP = new Serial("\\\\.\\COM19");
Serial* SP1 = new Serial("\\\\.\\COM25");


void GetDataFromArduino() {
	
	char incomingData[256] = "";

	int dataLength = 255;
	int readResult = 0;

	

	if (SP->IsConnected())
	{
	//printf("%s\n",incomingData);
		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;
		std::string outoutdata(incomingData);
		OrganizeData(outoutdata);

	}
	

	if (SP1->IsConnected())
	{
	   //printf("%s\n",incomingData);
		readResult = SP1->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;
		std::string outoutdata(incomingData);
		OrganizeData(outoutdata);
	}


}
void OrganizeData(std::string input) {
	std::fstream outPutFileroom;
	std::fstream outPutFileroom1;
	std::fstream outPutFilehall;
	std::fstream outPutFilehall1;
	int linesRoom = 0;
	int linesHall = 0;

	std::string csvItemHall;
	std::string csvItemRoom;

	std::ifstream hallfile("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall.csv");
	std::ifstream roomfile("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room.csv");
	outPutFilehall.open("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall.csv", std::ios::in);

	outPutFilehall1.open("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall1.csv", std::ios::out);
	outPutFileroom.open("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room.csv", std::ios::in);

	outPutFileroom1.open("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room1.csv", std::ios::out);
	if ((input.substr(0, 4)) == "room") {

		while (std::getline(roomfile, csvItemRoom)) {
			linesRoom++;
		}
	
		int roomNumber = std::stoi(input.substr(4, (input.find_first_of("occupancy", 4)) - 4));
		int occupancystrlocation = (input.find_first_of("occupancy", 4)) + 9;
		int numberOfPatients = std::stoi(input.substr(occupancystrlocation, input.find_first_of("patient1", occupancystrlocation) - occupancystrlocation));

		for (int f = 0; f < linesRoom; f++) {
			std::string line;


			if (f < roomNumber) {
				std::getline(outPutFileroom, line);
				outPutFileroom1 << line << std::endl;

			}
			
			else if (f == roomNumber) {
				outPutFileroom1 << roomNumber << ",";
				outPutFileroom1 << numberOfPatients << ",";


				for (uint8_t j = 1; j <= numberOfPatients; j++) {
					
					if ((input.find("patient" + std::to_string(j)) != -1) && ((input.find("patient" + std::to_string(j)) + 8 + std::to_string(j).length()) < input.length())) {
						bool patientok = std::stoi(input.substr((input.find(("patient" + std::to_string(j)), 0)) + (7 + std::to_string(j).length()), (input.find("patient" + std::to_string(j + 1), 0) - (input.find("patient" + std::to_string(j), 0) + 7 + std::to_string(j).length()))));
						if(j == numberOfPatients){
							outPutFileroom1 << patientok;
						}
						else {
							outPutFileroom1 << patientok << ",";
						}
					}
					
				}
				outPutFileroom1 << "\n";
				std::getline(outPutFileroom, line);
			}
			else if (f > roomNumber) {
				std::getline(outPutFileroom, line);
				outPutFileroom1 << line << std::endl;
			}
		}
		outPutFilehall1.close();
		outPutFileroom1.close();
		outPutFilehall.close();
		outPutFileroom.close();
		hallfile.close();
		roomfile.close();
		remove("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room.csv");
		rename("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room1.csv", "C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room.csv");
		remove("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\room1.csv");
		
	}
	else if ((input.substr(0, 4)) == "hall") {

		while (std::getline(hallfile, csvItemHall)) {
			linesHall++;
		}

		
		int hallnumber = std::stoi(input.substr(4, (input.find_first_of("occupancy", 4)) - 4));
		int occupancystrlocation = (input.find_first_of("occupancy", 4)) + 9;
		int numberOfPatients = std::stoi(input.substr(occupancystrlocation));
		for (int f = 0; f < linesHall; f++) {
			std::string line;
			if (f < hallnumber) {
				std::getline(outPutFilehall, line);
				outPutFilehall1 << line << std::endl;

			}
			else if (f > hallnumber) {
				std::getline(outPutFilehall, line);
				outPutFilehall1 << line << std::endl;
			}
			else if (f == hallnumber) {
				std::getline(outPutFilehall, line);
				outPutFilehall1 << hallnumber << ",";
				outPutFilehall1 << numberOfPatients << std::endl;

			}
		}
		outPutFilehall1.close();
		outPutFileroom1.close();
		outPutFilehall.close();
		outPutFileroom.close();
		hallfile.close();
		roomfile.close();
		remove("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall.csv");
		rename("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall1.csv", "C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall.csv");
		remove("C:\\Users\\Eitan\\source\\repos\\ArduinoProject\\ArduinoProject\\hall1.csv");
		
	}
	else {
		outPutFilehall1.close();
		outPutFileroom1.close();
		outPutFilehall.close();
		outPutFileroom.close();
		hallfile.close();
		roomfile.close();
	}
	
	
}
void portNameAndSerialNumber() {
	// device ID of PIC CDC
		// default VID/PID: 04D8/000A
		// for custom VID/PID, modify this string
	int row = 2;
	int column = 0;
	CString deviceID(_T("USB\\VID_2341&PID_0043\\"));
	CString instanceID;
	CString serialNumer;
	CString portName;
	numberofPorts = 0;
	DWORD requiredSize;
	PortName.resize(0);
	// Get Class GUID for PORTS class
	GUID classGuid[1];
	if (!SetupDiClassGuidsFromName(_T("PORTS"), classGuid, 1, &requiredSize)) {
	}
	// List up PORTS class devices in present
	HDEVINFO hDevInfoSet = SetupDiGetClassDevs(classGuid, NULL, NULL, DIGCF_PRESENT);
	if (hDevInfoSet == INVALID_HANDLE_VALUE) {

	}
	// Enumerate devices in the list
	SP_DEVINFO_DATA devInfo;
	devInfo.cbSize = sizeof(SP_DEVINFO_DATA);

	for (DWORD deviceIndex = 0; SetupDiEnumDeviceInfo(hDevInfoSet, deviceIndex, &devInfo); deviceIndex++)
	{

		// Get device instance ID
		SetupDiGetDeviceInstanceId(hDevInfoSet, &devInfo, NULL, 0, &requiredSize);
		SetupDiGetDeviceInstanceId(hDevInfoSet, &devInfo, instanceID.GetBuffer(requiredSize), requiredSize, NULL);
		instanceID.ReleaseBuffer();
		// Check device ID
		if (instanceID.Find(deviceID) != 0)
			continue;
		// Split serial number
		serialNumer = instanceID.Right(instanceID.GetLength() - deviceID.GetLength());
		// Open device parameters reg key
		HKEY hkey = SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL,
			0, DIREG_DEV, KEY_READ);
		if (hkey == INVALID_HANDLE_VALUE) {
			continue;
		}
		// Qurey for portname
		RegQueryValueEx(hkey, _T("PortName"), NULL, NULL, NULL, &requiredSize);
		RegQueryValueEx(hkey, _T("PortName"), NULL, NULL,
			(LPBYTE)portName.GetBuffer(requiredSize), &requiredSize);
		portName.ReleaseBuffer();
		// Close reg key
		RegCloseKey(hkey);
		// Print result
		//_tprintf(_T("Port: %s   Serial number: %s\n"), portName, serialNumer);

		PortNameAndSerialNumber.resize(column + 1, std::vector<CString>(row));
		PortNameAndSerialNumber[column][0] = portName;
		PortNameAndSerialNumber[column][1] = serialNumer;
		PortName.resize(column + 1);
		PortName[column] = PortNameAndSerialNumber[column][0];
		column++;
		numberofPorts++;
	}
	// Destroy device info list
	SetupDiDestroyDeviceInfoList(hDevInfoSet);
}