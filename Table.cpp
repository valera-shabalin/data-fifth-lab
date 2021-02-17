#include <iostream>
#include <cmath>

#include "Table.h"

using namespace std;

namespace table
{
	size_t Table::s_id = 0;
	bool Table::debug = false;

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
		size_t new_count = this->count;
		bool status = false;

		if (++new_count > this->size)
		{
			cout << "The table is fuel." << endl;
			return *this;
		}

		size_t h1 = this->HashFunc1(value);
		size_t h2 = this->HashFunc2(value);

		cout << "Insert element '" << value << "'. H1 = " << h1 << " H2 = " << h2 << endl;

		if (this->data[h1] == nullptr)
		{
			this->data[h1] = new Node(value);
			status = true;
		}
		else if (this->data[h2] == nullptr)
		{
			this->data[h2] = new Node(value);
			status = true;
		} 
		else
		{
			size_t probe = 0;
			do
			{
				size_t h3 = (h1 + probe * h2) % this->size;
				cout << "Insert element '" << value << "'. Number of probe: " << probe << ", H1 = " << h1 << ", H2 = " << h2 << ", H3 = " << h3 << endl;

				if (this->data[h3] == nullptr)
				{
					this->data[h3] = new Node(value);
					status = true;
					break;
				}
				probe++;
			} while (probe < this->size);
		}

		if (!status)
		{
			cout << "Insert element '" << value << "'. Failed to insert item into table." << endl;
		}
		else
		{
			this->count++;
			return *this;
		}
	}
	
	/* Функция поиска элемента */
	size_t Table::SearchValue(int value)
	{
		return 0;
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
		size_t res = (this->HashFunc1(value) + probe * HashFunc2(value)) % this->size;
		cout << "Key = " << res << endl;
		return 0;
	}
	size_t Table::HashFunc1(int value)
	{
		return (size_t)(this->size * fmod(value * this->coef, 1));
	}
	size_t Table::HashFunc2(int value)
	{
		return (size_t)((this->size - 2) * fmod(value * this->coef, 1));
	}
}
