#include <windows.h>
#include <iostream>
using namespace std;
int main()
{
	HANDLE hNamedPipe;
	char pipeName[] = "\\\\.\\pipe\\demo_pipe";
	do
	{
		cerr << "Waiting for connection." << endl;
		Sleep(10000);
		hNamedPipe = CreateFile(
			L"\\\\.\\pipe\\demo_pipe", // имя канала
			GENERIC_WRITE, // записываем в канал
			FILE_SHARE_READ, // разрешаем одновременное чтение из канала
			NULL, // защита по умолчанию
			OPEN_EXISTING, // открываем существующий канал
			0, // атрибуты по умолчанию
			NULL // дополнительных атрибутов нет
		);
	} while (hNamedPipe == INVALID_HANDLE_VALUE);

	// пишем в именованный канал
	for (int i = 0; i < 10; i++)
	{
		DWORD dwBytesWritten;
		if (!WriteFile(
			hNamedPipe, // дескриптор канала
			&i, // данные
			sizeof(i), // размер данных
			&dwBytesWritten, // количество записанных байтов
			NULL // синхронная запись
		))
		{
			// ошибка записи
			cerr << "Writing to the named pipe failed: " << endl
				<< "The last error code: " << GetLastError() << endl;
			CloseHandle(hNamedPipe);
			cout << "Press any key to exit.";
			cin.get();
			return 0;
		}
		// выводим число на консоль
		cout << "The number " << i << " is written to the named pipe."
			<< endl;
		Sleep(1000);
	}
	// закрываем дескриптор канала
	CloseHandle(hNamedPipe);
	// завершаем процесс
	cout << "The data are written by the client." << endl
		<< "Press any key to exit.";
	cin.get();
	return 0;
}