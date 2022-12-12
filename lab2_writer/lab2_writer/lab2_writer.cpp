#include <iostream>
#include<windows.h>
#include<string>

using namespace std;

void writer() {
	string file, // файл
		   fileMap; // проецируемый файл
	HANDLE handleFile, handleMap;
	LPVOID addressMap;
	char* data = new char[10000]; // строка с данными для записи

	cout << "Enter file path: ";
	cin >> file;
	cout << "Enter name of mapped file: ";
	cin >> fileMap;

	handleFile = CreateFileA(file.c_str(), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	handleMap = CreateFileMappingA(handleFile, NULL, PAGE_READWRITE, 
		0, 1024, fileMap.c_str());

	//проецирование фрагмента файла в память
	addressMap = MapViewOfFile(handleMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (addressMap)
	{
		cout << "\nEnter data without spaces: ";
		cin >> data;
		memcpy(addressMap, data, strlen(data) * sizeof(char));
		cout << "\nStart reader program to read data from input data\n";
		system("pause");
		UnmapViewOfFile(addressMap); // завершаем проецирование файла
	}
	else
	{
		cout << "Error";
	}
}

int main() {
	writer();
	return 0;
}