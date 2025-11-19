#include <iostream>
#include <string>
#include <array>

#include <wchar.h>
#include <stdio.h>

#include "PhoneInput.h"
#include "tests.h"

using namespace std;

bool test(int argc, char** input, wstring expected)
{
	wstring test_subject = handle_numpad(argc, input);
	wstring exp = expected;
	size_t length = exp.size() > test_subject.size() ? exp.size() : test_subject.size();
	bool isEqual = true;
	wchar_t comparison_result[2000] = { L"\0" };
	wchar_t* comparison_ptr = comparison_result;

	for (int i = 0; i < length; i++)
	{
		if (i >= test_subject.size() || i >= exp.size()) {
			isEqual = false;

			if (i < test_subject.size())
			{
				*comparison_ptr = test_subject[i];
				comparison_ptr++;
			}
			continue;
		}
		wchar_t expected_letter = exp[i];
		wchar_t letter = test_subject[i];
		if (letter == expected_letter)
		{
			*comparison_ptr = letter;
			comparison_ptr++;
		}
		else {
			isEqual = false;
			swprintf(comparison_ptr, 10, L"[%lc][%lc]", letter, expected_letter);
			comparison_ptr+=6;
		}
	}
	wcout << L"Последовательность: " << **input << endl;
	wcout << L"Ожидаемый результат: " << expected << endl;
	wcout << L"Результат выполнения: " << comparison_result << endl;
	wcout << L"Результат теста: " << (isEqual ? L"ПРОЙДЕН" : L"НЕ ПРОЙДЕН") << endl;
	wcout << comparison_result << endl;
	return isEqual;
}

int init_tests() {
	char* t[] = {
		(char*)"\0\0",
		(char*)"55556422233666\0\0"
	};
	test(2, t, wstring(L"ПРИВЕТТ"));
	return 0;
}