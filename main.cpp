//6. Дан текстовый файл и ключевое слово для поиска. Выдать на экран 5 строк файла начиная с первой строки, 
// включающей заданное слово. Выделить ключевое слово курсором или подсветкой 
#include <fstream> 
#include <iostream> 
#include <windows.h>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

bool IsWordFound(const string &str, const string &searchStr, int & searchedStrPos)
{
	bool wordFound = false;
	string word; 
	for (int i = 0; i < str.length(); ++i)
	{
		if (isalnum(str[i]))
        {
            word = word + str[i];
        	transform(word.begin(), word.end(), word.begin(), (int (*)(int))toupper);    
        }
        else if (word == searchStr)
        {
    		wordFound = true;
    		searchedStrPos = i - searchStr.length();
    		break;
		}
		else
		{
			word = "";
		}
	}
	return wordFound;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

    if (argc != 3)
    {
        cout << "Использование программы: " << argv[0] << " <input file> <search word>\n";
        return 1;
    }

    ifstream in(argv[1]);
    bool keyWordFound = false;
    int keyWordPos, numberOfStrings = 0, k = 0;
    string buffer, word = "0";
    string keyWord = argv[2];
	transform(keyWord.begin(), keyWord.end(), keyWord.begin(), (int (*)(int))toupper);
    SetConsoleTextAttribute(console, 15);

    if (!in.is_open())
    {
        cout << "Файл не может быть открыт. Проверьте правильность ввода\n";
        return 1;
    }
    while (getline(in, buffer))
    {
        if (IsWordFound(buffer, keyWord, keyWordPos))
        {
        	for (int i = 0; i < keyWordPos; ++i)
        	{
        		cout << buffer[i];
			}
			
			SetConsoleTextAttribute(console, 12);
			for (int i = keyWordPos; i < keyWordPos + keyWord.length(); ++i)
        	{
        		cout << buffer[i];
			}
			keyWordFound = true;
			SetConsoleTextAttribute(console, 15);
			
			for (int i = keyWordPos + keyWord.length(); i < buffer.length(); ++i)
			{
        		cout << buffer[i];
			}
			cout << endl;
			break;
		}
    }
	while (keyWordFound && getline(in, buffer) && (numberOfStrings < 4))
	{
		cout << buffer << endl;
		++numberOfStrings;
	}
    in.close();
    return 0;
}
