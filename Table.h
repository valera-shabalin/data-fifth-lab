#ifndef TABLE_H
#define TABLE_h

namespace table
{
	class Table
	{
		struct Node {
			double value;
			bool state;
			Node(double _value) : value(_value), state(true) {};
		};
	private:
		size_t static static_id;
		bool static debug;

		size_t id, size, buffer_size, default_size;
		Node** data;

		/* Функции хеширования */
		size_t HashFunc(int value, size_t probe = 1);
		size_t HashFunc1(int value);
		size_t HashFunc2(int value);
	public:
		/* Конструтор и деструктор */
		Table();
		~Table();

		/* Основные функции */
		size_t InsertValue(double value);
		bool SearchValue(double value);
	};
};

#endif TABLE_H

