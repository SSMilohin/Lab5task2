// Лабораторная работа №5 Задача 2 Вариант 9
//
// Задачу 2 можно решить как через массив char, так и через std::string.
// 
// Дан файл, содержащий русский текст, размер текста не превышает 10 К байт. 
// Найти в тексте N (N ≤ 100) самых длинных слов, содержащих одинаковое количество гласных и согласных. 
// Записать найденные слова в текстовый файл в порядке не возрастания длины. Все найденные слова должны быть разными. 
// Число N вводить из файла.

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

#define WORDS_COUNT 10000

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);

	std::ifstream in("../input.txt");
	std::ofstream out("../output.txt");

	std::string
		word,
		words[WORDS_COUNT],
		vowels = "аеёиоуыэюя",
		consonants = "бвгджзйклмнпрстфхцчшщъь",
		symbols = "!?():;.,<>";
	int elements = 0,
		lengths[WORDS_COUNT];

	for (int i = 0; i < WORDS_COUNT; i++) {
		words[i] = "";
		lengths[i] = 0;
	}

	while (!in.eof()) {
		int vowelsCount = 0, 
			consonantsCount = 0;

		in >> word;

		for (int i = 0; i < word.length(); i++) {
			word.replace(i, 1, 1, tolower(word[i]));
			for (int j = 0; j < symbols.length(); j++) {
				if (word[i] == symbols[j]) {
					word.erase(i);
				}
			}
			for (int j = 0; j < vowels.length(); j++) {
				if (word[i] == vowels[j]) {
					vowelsCount++;
				}
			}
			for (int j = 0; j < consonants.length(); j++) {
				if (word[i] == consonants[j]) {
					consonantsCount++;
				}
			}
		}

		if (vowelsCount == consonantsCount && vowelsCount!=0) {
			bool isUnique = true;
			for (int i = 0; i < elements; i++) {
				if (word == words[i]) {
					isUnique = false;
					break;
				}
			}
			if (isUnique) {
				words[elements] = word;
				lengths[elements] = word.length();
				elements++;
			}
		}
	}

	for (int i = 0; i < elements - 1; i++) {
		for (int j = i + 1; j < elements; j++) {
			if (lengths[i] < lengths[j]) {
				std::swap(words[i],words[j]);
				std::swap(lengths[i],lengths[j]);
			}
		}
	}

	int n; // количество слов, необходимых для вывода
	std::cin >> n;

	for (int i = 0; i < n; i++) {
		out << words[i] + "\n";
	}
}