// PhoneInput.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include <string>
#include "PhoneInput.h"
#include "tests.h"


using namespace std;

#define CHARS_PER_NUMPAD 4

static const wstring numpad_str = L"@@@@АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ    ";





static wchar_t get_numpad_char(int* taps, char * numpad_btn)
{
	int a = (int) *numpad_btn;
	int numpad_char_idx = ((*taps - 1) % CHARS_PER_NUMPAD);
	int numpad_idx = a - (int) 48;
	numpad_idx = numpad_idx == 0 ? 9 : numpad_idx - 1;
	int idx = numpad_idx * CHARS_PER_NUMPAD + numpad_char_idx;
	wchar_t result = numpad_str.at(idx);
	return result;
}

wstring handle_numpad(int argc, char* argv[])
{
	/* Результирующий буфер */
	wchar_t res[1000] = { L"\0" };

	/* Указатель на результирующий буфер */
	wchar_t* pointer = &res[0];

	/* Счетчик нажатий на одну кнопку */
	int current_taps = 0;

	/* Текущая буква к вставке */
	wchar_t letter;

	/* Предыдущий символ аргумента */
	char prev_char[4] = { 0 };

	for (int i = 1; i < argc; i++)
	{
		// Готовимся обрабатывать новый аргумент
		current_taps = 0;
		string arg = string(argv[i]);
		*prev_char = (char)arg[0];

		for (int i = 0; i < arg.size(); i++) {
			if (*prev_char == (char)arg[i])
			{
				// Пользователь нажимает одну и ту же кнопку несколько раз
				current_taps++;
			}
			else {
				// Пользователь нажимает другую кнопку. Отправляем накопившиеся данные и сбрасываем счетчик
				letter = get_numpad_char(&current_taps, prev_char);
				*pointer = letter;
				pointer++;
				*prev_char = (char)arg[i];
				current_taps = 1;
			}
		}
		// Отправляем полученный результат
		if (current_taps > 0) {
			letter = get_numpad_char(&current_taps, prev_char);
			*pointer = letter;
			pointer++;
		}
	}

	return wstring(res);
}

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	init_tests();
	wstring result = handle_numpad(argc, argv);
	return 0;
}




