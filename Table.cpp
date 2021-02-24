#include <iostream>
#include <cmath>

#include "Table.h"

using namespace std;

namespace table
{
	size_t Table::s_id = 0;
	bool Table::debug = true;

	/* Конструктор и деструктор NODE */
	Table::Node::Node(int _value) : value(_value), state(false), deleted(false) {}
	Table::Node::~Node() {}
	int Table::Node::GetValue() const
	{
		return this->value;
	}
	bool Table::Node::GetState() const
	{
		return this->state;
	}
	bool Table::Node::GetDeleted() const
	{
		return this->deleted;
	}

	/* Вспомогательные методы */
	bool Table::InsertValueHelper(int value, size_t pos)
	{
		if (this->data[pos].state)
		{
			if (this->data[pos].deleted)
			{
				this->data[pos].value = value;
				this->data[pos].deleted = false;
				this->count++;
				return true;
			}
		}
		else
		{
			this->data[pos].value = value;
			this->data[pos].state = true;
			this->count++;
			return true;
		}
		
		return false;
	}
	
	/* Конструктор */
	Table::Table(size_t _size) : id(++s_id), count(0), size(_size), coef(0.618033)
	{
		this->data = new Node[size];

		if (debug)
		{
			cout << "Constructor 'Table' with ID: " << this->id << endl;
		}
	}

	/* Деструктор */
	Table::~Table()
	{
		if (this->data != nullptr)
		{
			delete[] this->data;
			this->data = nullptr;
		}

		if (debug)
		{
			cout << "Destructor 'Table' with ID: " << this->id << endl;
		}
	}

	/* Функция вставки элемента */
	Table& Table::InsertValue(int value)
	{
		if (this->count == this->size)
		{
			cout << "The table is fuel." << endl;
			return *this;
		}

		size_t h1 = this->HashFunc1(value);
		size_t h2 = this->HashFunc2(value);
		bool status = false;

		if (debug)
		{
			cout << "Insert element '" << value << "'. H1 = " << h1 << " H2 = " << h2 << endl;
		}

		if (this->InsertValueHelper(value, h1))
		{
			return *this;
		} 

		if (this->InsertValueHelper(value, h2))
		{
			return *this;
		}

		size_t probe = 0;
		do
		{
			size_t h3 = this->HashFunc(value, probe);

			if (this->InsertValueHelper(value, h3))
			{
				status = true;
				break;
			}
			probe++;
		} while (probe < this->size);

		cout << "Count of probe insert '" << value << "': " << probe << " " << endl;

		if (!status)
		{
			cout << "Insert element '" << value << "'. Failed to insert item into table." << endl;
		}

		return *this;
	}
	
	/* Функция поиска элемента */
	int Table::SearchValue(int value)
	{
		size_t h1 = this->HashFunc1(value);
		size_t h2 = this->HashFunc2(value);
		int result = -1;

		if (this->data[h1].state && this->data[h1].value == value)
		{
			return h1;
		}

		if (this->data[h2].state && this->data[h2].value == value)
		{
			return h2;
		}

		size_t probe = 0;
		do
		{
			size_t h3 = this->HashFunc(value, probe);

			if (this->data[h3].state && this->data[h3].value == value && !this->data[h3].deleted)
			{
				result = h3;
				break;
			}
			probe++;
		} while (probe < this->size);

		cout << "Count of probe search '" << value << "': " << probe << endl;

		return result;
	}

	/* Функция удаления элемента */
	bool Table::DeleteValue(int value)
	{
		size_t pos = this->SearchValue(value);

		if (pos < 0)
		{
			return false;
		}

		this->data[pos].deleted = true;
		this->count--;

		return true;
	}

	/* Перегрузка вывода таблицы */
	ostream& operator << (std::ostream& out, Table& table)
	{
		if (table.count == 0)
		{
			cout << "Table is empty.";
			return out;
		}

		for (size_t i = 0; i < table.size; i++)
		{
			if (table.data[i].GetState() && !table.data[i].GetDeleted())
			{
				cout << table.data[i].GetValue() << " ";
			}
			else {
				cout << "_" << " ";
			}
		}

		return out;
	}

	/* Функции хеширования */
	size_t Table::HashFunc(int value, size_t probe)
	{
		return (this->HashFunc1(value) + probe * HashFunc2(value)) % this->size;
	}
	size_t Table::HashFunc1(int value)
	{
		return this->size * fmod(value * this->coef, 1);
	}
	size_t Table::HashFunc2(int value)
	{
		return (this->size - 1) * fmod(value * this->coef, 1);
	}
}
