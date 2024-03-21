// Листинг 18.13. Выброс структуры типа EXCEPTION_POINTERS как исключения языка программирования С++
#include <windows.h>
#include <iostream>
#include <eh.h>
using namespace std;
void se_trans_func(unsigned code, EXCEPTION_POINTERS * info)
{
	EXCEPTION_RECORD er;
	CONTEXT с;
	EXCEPTION_POINTERS ep = { &er, &с };
	er = *(info->ExceptionRecord);
	с = *(info->ContextRecord);
	throw ep;
}
int main()
{
	int a = 10, b = 0;
	// устанавливаем функцию-транслятор
	_set_se_translator(se_trans_func);
	// перехватываем структурное исключение средствами С++
	try
	{
		a /= b; // ошибка, деление на ноль
	}
	catch (EXCEPTION_POINTERS ep)
	{
		cout << "Exception code = " << hex
			<< ep.ExceptionRecord->ExceptionCode << endl;
	}
	return 0;
}