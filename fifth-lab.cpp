#include <iostream>
#include <fstream>

#include "Table.h"

using namespace std;
using namespace table;

int main() 
{
    setlocale(LC_CTYPE, "Rus");

    ifstream file("input.txt");
    Table table(15);
    int tmp = 0, search_result = 0;

    while (file >> tmp)
    {
        table.InsertValue(tmp);
    }

    table.DeleteValue(92);

    cout << table << endl;

    do
    {
        cout << "Введите число для поиска. Для остановки программы введите '-1': ";
        cin >> tmp;
        search_result = table.SearchValue(tmp);

        if (search_result >= 0)
        {
            cout << "Число '" << tmp << "' найдено. Позиция: " << search_result << endl;
        }
        else
        {
            cout << "Число не найдено." << endl;
        }
    } while (tmp != -1);

    return 0;
}
