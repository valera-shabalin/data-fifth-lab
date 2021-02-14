#include "Table.h"

using namespace std;

namespace table
{
	size_t Table::static_id = 1;
	bool Table::debug = true;

	/* Функции хеширования */
	size_t Table::HashFunc(int value, size_t probe)
	{
		/*return (this->HashFunc1(value) + probe * this->HashFunc2(value)) % this->buffer_size;*/
	}
	size_t Table::HashFunc1(int value)
	{
		return value % this->buffer_size;
	}
	size_t Table::HashFunc2(int value)
	{
		return 1 + (value % this->buffer_size - 2);
	}
	
	/* Конструктор */
	Table::Table() 
		: id(static_id++), size(0), default_size(8), buffer_size(8), data(nullptr)
	{
		this->data = new Node*[this->buffer_size];
		for (size_t i = 0; i < this->buffer_size; i++)
		{
			this->data[i] = nullptr;
		}
	}

	/* Деструктор */
	Table::~Table()
	{

	}

	/* Функция вставки элемента */
	size_t Table::InsertValue(double value)
	{


		return 0;
	}
	
	/* Функция поиска элемента */
	bool Table::SearchValue(double value)
	{

	}
}
