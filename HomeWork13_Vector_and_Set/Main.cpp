# include <iostream>
# include<string>
# include<fstream>
# include<vector>
# include<set>
# include<algorithm> 

/// <summary>
/// Прототип функции для "очистки" считанного из файла слова от мусора (знаки препинания, спец.символы, цифры и пр.) и перевода 
/// всех символов слова в нижний регистр для последующей обработки
/// </summary>
/// <param name="word"></param>
void Cleaning(std::string &word);

int main() {		
	// ==================== Блок общих для обоих вариантов переменных =============================

	std::string path = "J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt"; // Относительный путь к файлу
	std::ifstream in; // Создаём объект для считывания слов из файла
	std::ofstream out; // Создаём объект для записи в файл
	std::string word; // Переменная для пословного считывания информации из файла
	char my_choice; // Переменная для хранения выбора пользователя
	std::string path_vector = "Vector_unique_words.txt"; // Относительный путь к словарю, сформированному вектором
	std::string path_set = "Set_unique_words.txt"; // Относительный путь к словарю, сформированному сэтом
	double time_start; // Переменная для хранения времени начала работы куска кода
	double time_end; // Переменная для хранения времени завершения работы куска кода

	// ======================== Вариант 1 - Словарь уникальных слов в виде вектора строк ===========================
	
	std::cout << "\033[91mTask 1. First option:\033[0m Dictionary of unique words, specified as a vector of strings.\n\n";
	time_start = clock(); // Точка начала отсчёта времени
	std::vector<std::string> dictionary;
	in.open(path); // Открываем файл для чтения
	if (in.is_open())  // Если файл открыт для чтения, то
		std::cout << "File \033[93m" << path << "\033[0m is open for reading." << std::endl;
	else { // Если файл не получилось открыть
		std::cout << "\033[94mError opening file!\033[0m\n";
		system("pause");
		throw - 1; // Кидаем исключение
	}			
	while (!in.eof()) { // Пословное считывание инф-ии из объекта
		in >> word;
		Cleaning(word); // Чистим считанное слово от мусора переводим его в нижний регистр 		
		// Заполняем vector через костр. if...else для "очистки" слов от сокращений форм глагола to be, have, would, сокращений частичек "not"
		if (word == "i'm") {
			dictionary.push_back("i");
			dictionary.push_back("am");
		}
		else
			if (word.find("'d") != std::string::npos) {
				dictionary.push_back("would");
				dictionary.push_back(word.substr(0,word.find("'d")));
			}
			else
				if (word.find("'ll") != std::string::npos) {
					dictionary.push_back("will");
					dictionary.push_back(word.substr(0,word.find("'ll")));
				}
				else
					if (word.find("'ve") != std::string::npos) {
						dictionary.push_back("have");
						dictionary.push_back(word.substr(0, word.find("'ve")));
					}
					else
						if (word.find("'re") != std::string::npos) {
							dictionary.push_back("are");
							dictionary.push_back(word.substr(0, word.find("'re")));
						}
						else
							if (word.find("'s") != std::string::npos) {
								dictionary.push_back("is");
								dictionary.push_back(word.substr(0, word.find("'s")));
							}
							else
								if (word == "isn't") {
									dictionary.push_back("is");
									dictionary.push_back("not");
								}
								else
									if (word == "aren't") {
										dictionary.push_back("are");
										dictionary.push_back("not");
									}								
									else
										if (word != "")
											dictionary.push_back(word);				
	}	
	in.close(); // После считывания из файла информации закрываем его
	std::cout << "Data was successfully read from the file.\nFile \033[93m" << path << "\033[0m is closed.\n\n";
	std::cout << "There are \033[92m" << dictionary.size() << " words\033[0m in the vector (in the book 'Harry Potter and the Philosopher's Stone')\n\n";
	// Сортируем данные в векторе
	std::sort(dictionary.begin(), dictionary.end());
	// Удаляем дубликаты слов, оставляя только уникальные слова:
	auto last = std::unique(dictionary.begin(), dictionary.end());
	dictionary.erase(last, dictionary.end());
	std::cout << "The sorted dictionary of unique words contains \033[92m" << dictionary.size() << " words.\033[0m" << std::endl << std::endl;
	// Запись словаря-вектора в файл		
	out.open(path_vector, std::ios::out); // Открывем файл для записи (создаём файл, если его ещё нет)
	if (out.is_open())
		std::cout << "File \033[93m" << path_vector << "\033[0m is open for rewriting.";
	else { // Если файл для записи открыть не удалось
		std::cout << "\n\033[94mError opening file!\033[0m\n";
		system("pause");
		throw - 1; // Кидаем исключение
	}
	for (std::string el : dictionary) { // Цикл пословной записи в файл
		out << el << std::endl;
	}
	std::cout << "\nThe unique words has been successfully added into file \033[92m" << path_vector << "\033[0m\n";
	out.close(); // Закрываем перезаписанный файл
	time_end = clock(); // Точка завершения отсчёта времени
	std::cout << "File \033[93m" << path_vector << "\033[0m is closed\n\nThe vector code worked in \033[92m"\
		<< (time_end - time_start) / CLOCKS_PER_SEC << " seconds.\033[0m\n(From opening a book file for reading to closing a file with a dictionary of unique words)" << std::endl << std::endl;	
	std::cout<<"Do you want to output the dictionary to the console ? " << std::endl << \
		"Press \033[91m1\033[0m for yes \033[4mor\033[0m press \033[91many other key\033[0m for no\nYour choice -> ";	
	std::cin >> my_choice;
	if (my_choice == '1')
		for (std::string el : dictionary) // Цикл пословного вывода в консоль
			std::cout << el << '\n';

	// ======================== Вариант 2 - Словарь уникальных слов в виде set-множества строк ===========================

	std::cout << std::endl << "\033[91mTask 1. Second option:\033[0m Dictionary of unique words in the form of many (set) strings.\n\n";
	time_start = clock(); // Точка начала отсчёта времени
	std::set<std::string> unique_dictionary;
	in.open(path); // Открываем файл для чтения
	if (in.is_open())  // Если файл открыт для чтения, то
		std::cout << "File \033[93m" << path << "\033[0m is open for reading." << std::endl;
	else { // Если файл не получилось открыть
		std::cout << "\033[94mError opening file!\033[0m\n";
		system("pause");
		throw - 1; // Кидаем исключение
	}
	while (!in.eof()) { // Пословное считывание инф-ии из объекта
		in >> word;
		Cleaning(word); // Чистим считанное слово от мусора переводим его в нижний регистр 		
		// Заполняем set через костр. if...else для "очистки" слов от сокращений форм глагола to be, have, would, сокращений частичек "not"
		if (word == "i'm") {
			unique_dictionary.insert("i");
			unique_dictionary.insert("am");
		}
		else
			if (word.find("'d") != std::string::npos) {
				unique_dictionary.insert("would");
				unique_dictionary.insert(word.substr(0, word.find("'d")));
			}
			else
				if (word.find("'ll") != std::string::npos) {
					unique_dictionary.insert("will");
					unique_dictionary.insert(word.substr(0, word.find("'ll")));
				}
				else
					if (word.find("'ve") != std::string::npos) {
						unique_dictionary.insert("have");
						unique_dictionary.insert(word.substr(0, word.find("'ve")));
					}
					else
						if (word.find("'re") != std::string::npos) {
							unique_dictionary.insert("are");
							unique_dictionary.insert(word.substr(0, word.find("'re")));
						}
						else
							if (word.find("'s") != std::string::npos) {
								unique_dictionary.insert("is");
								unique_dictionary.insert(word.substr(0, word.find("'s")));
							}
							else
								if (word == "isn't") {
									unique_dictionary.insert("is");
									unique_dictionary.insert("not");
								}
								else
									if (word == "aren't") {
										unique_dictionary.insert("are");
										unique_dictionary.insert("not");
									}
									else
										if (word != "")
											unique_dictionary.insert(word);										
	}
	in.close(); // После считывания из файла информации закрываем его
	std::cout << "Data was successfully read from the file.\nFile \033[93m" << path << "\033[0m is closed.\n\n";
	std::cout << "There are \033[92m" << unique_dictionary.size() << " unique words \033[0min the set (in the book 'Harry Potter and the Philosopher's Stone')\n\n";
	// Запись словаря-сэта в файл		
	out.open(path_set, std::ios::out); // Открывем файл для записи (создаём файл, если его ещё нет)
	if (out.is_open())
		std::cout << "File \033[93m" << path_set << "\033[0m is open for rewriting.";
	else { // Если файл для записи открыть не удалось
		std::cout << "\n\033[94mError opening file!\033[0m\n";
		system("pause");
		throw - 1; // Кидаем исключение
	}
	for (std::string el : unique_dictionary) { // Цикл пословной записи в файл
		out << el << std::endl;
	}
	std::cout << "\nThe unique words has been successfully added into file \033[92m" << path_set << "\033[0m\n";
	out.close(); // Закрываем перезаписанный файл
	time_end = clock(); // Точка завершения отсчёта времени
	std::cout << "File \033[93m" << path_set << "\033[0m is closed\n\nThe set code worked in \033[92m"\
		<< (time_end - time_start) / CLOCKS_PER_SEC << " seconds.\033[0m\n(From opening a book file for reading to closing a file with a dictionary of unique words)" << std::endl << std::endl;
	std::cout<<"Do you want to output the dictionary to the console ? " \
		<< std::endl << "Press \033[91m1\033[0m for yes \033[4mor\033[0m press \033[91many other key\033[0m for no\nYour choice -> ";
	std::cin >> my_choice;
	if (my_choice == '1')
		for (std::string el : unique_dictionary) // Цикл пословного вывода в консоль
			std::cout << el << '\n';

	return 0;
}

void Cleaning(std::string& word) {
	// Цикл "очистки" слов от "прилипшего" мусора (знаки препинания, спец.символы, цифры и пр.)
	for (int i = 0; i < word.length(); ++i) {
		if ((word.at(i) == '\'' && i == 0) || (word.at(i) == '\'' && i == word.length() - 1) || word.at(i) == '(' || word.at(i) == ')' \
			|| word.at(i) == '.' || word.at(i) == ',' || word.at(i) == '!' || word.at(i) == '?' || word.at(i) == '"' || word.at(i) == '-' \
			|| word.at(i) == '\\' || (word.at(i) >= 48 && word.at(i) <= 57) || word.at(i) == ';' || word.at(i) == ':') {
			word.erase(i, 1);
			--i; // Сдвигаем итератор в соответствии с удалённым символом
		}
	}
	// Переводим в нижний регистр каждое слово
	std::transform(word.begin(), word.end(), word.begin(), tolower);
}
