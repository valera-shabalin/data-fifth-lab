#include <iostream>

#include "Table.h"

using namespace std;
using namespace table;

int main() 
{
    setlocale(LC_CTYPE, "Rus");

    Table table;

    table.InsertValue(4);

    return 0;
}
