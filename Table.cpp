#include <iostream>
#include <cmath>

#include "Table.h"

using namespace std;

namespace table
{
	size_t Table::s_id = 0;
	bool Table::debug = true;

	/* Конструктор и деструктор NODE */
	Table::Node::Node(int _value) : value(_value), state(true) {}
	Table::Node::~Node() {}
	int Table::Node::GetValue() const
	{
		return this->value;
	}
	bool Table::Node::GetState() const
	{
		return this->state;
	}
	Table::Node& Table::Node::SetValue(int value)
	{
		this->value = value;
		return *this;
	}
	Table::Node& Table::Node::SetState(bool state)
	{
		this->state = state;
		return *this;
	}

	/* Вспомогательные методы */
	bool Table::InsertValueHelper(int value, size_t pos)
	{
		bool status = false;

		if (this->data[pos] == nullptr)
		{
			this->data[pos] = new Node(value);
			this->count++;
			status = true;
		}
		else if (this->data[pos]->value == value)
		{
			cout << "Element '" << value << "' is already inserted." << endl;
			status = true;
		}
		
		return status;
	}
	
	/* Конструктор */
	Table::Table(size_t _size) : id(++s_id), count(0), size(_size), coef(0.618033)
	{
		this->data = new Node*[size];

		for (size_t i = 0; i < this->size; i++)
		{
			this->data[i] = nullptr;
		}

		if (debug)
		{
			cout << "Constructor 'Table' with ID: " << this->id << endl;
		}
	}

	/* Деструктор */
	Table::~Table()
	{
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

		for (size_t probe = 0; probe < this->size; probe++)
		{
			size_t h3 = this->HashFunc(value, probe);

			if (debug)
			{
				cout << "Insert element '" << value << "'. Number of probe: " << probe << ", H1 = " << h1 << ", H2 = " << h2 << ", H3 = " << h3 << endl;
			}

			if (this->InsertValueHelper(value, h3))
			{
				return *this;
			}
		}

		cout << "Insert element '" << value << "'. Failed to insert item into table." << endl;
		return *this;
	}
	
	/* Функция поиска элемента */
	int Table::SearchValue(int value)
	{
		size_t h1 = this->HashFunc1(value);
		size_t h2 = this->HashFunc2(value);

		if (this->data[h1] != nullptr && this->data[h1]->value == value)
		{
			return h1;
		}

		if (this->data[h2] != nullptr && this->data[h2]->value == value)
		{
			return h2;
		}

		for (size_t probe = 0; probe < this->size; probe++)
		{
			size_t h3 = this->HashFunc(value, probe);
				
			if (debug)
			{
				cout << "Search element '" << value << "'. Number of probe: " << probe << ", H1 = " << h1 << ", H2 = " << h2 << ", H3 = " << h3 << endl;
			}

			if (this->data[h3] != nullptr && this->data[h3]->value == value)
			{
				return h3;
			}
		}

		return -1;
	}

	/* Перегрузка вывода таблицы */
	ostream& operator << (std::ostream& out, Table& table)
	{
		if (table.size == 0)
		{
			cout << "Table is empty.";
			return out;
		}

		for (size_t i = 0; i < table.size; i++)
		{
			if (table.data[i] != nullptr)
			{
				cout << table.data[i]->GetValue() << " ";
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
