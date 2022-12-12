#include <iostream>
#include<windows.h>
#include<string>

using namespace std;

void reader() {
	string fileMap; // проецируемый файл
	HANDLE handleMap;
	LPVOID addressMap;

	cout << "Enter name of mapped file: ";
	cin >> fileMap;

	handleMap = OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, fileMap.c_str());

	//проецирование фрагмента файла в память
	addressMap = MapViewOfFile(handleMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (addressMap)
	{
		cout << "Data file: " << (char*)addressMap << endl << endl;
		system("pause");
		UnmapViewOfFile(addressMap); // завершение проецирования файла
	}
	else
	{
		cout << "Error";
	}
}

int main() {
	reader();
	return 0;
}
