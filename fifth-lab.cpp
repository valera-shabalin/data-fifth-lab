#include <iostream>

#include "Table.h"

using namespace std;
using namespace table;

int main() 
{
    setlocale(LC_CTYPE, "Rus");

    Table table(4);
    table.InsertValue(2).InsertValue(2).InsertValue(12).InsertValue(54);

    cout << table << endl;

    return 0;
}
