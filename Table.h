#ifndef TABLE_H
#define TABLE_h

namespace table
{
	class Table
	{
		class Node
		{
		private:
			int value;
			bool state;
		public:
			/* Конструктор и деструктор */
			Node(int _value = 0);
			~Node();

			/* Геттеры и сеттеры */
			int GetValue() const;
			bool GetState() const;
			Node& SetValue(int value);
			Node& SetState(bool state);
		};
	private:
		/* Статические поля класса */
		size_t static s_id;
		bool static debug;

		/* Поля класса */
		size_t id, size, count;
		Node** data;
		double coef;

		/* Функции хеширования */
		size_t HashFunc(int value, size_t probe = 0);
		size_t HashFunc1(int value);
		size_t HashFunc2(int value);
	public:
		/* Конструтор и деструктор */
		Table(size_t _size = 1);
		~Table();

		/* Основные функции */
		Table& InsertValue(int value);
		size_t SearchValue(int value);

		/* Перегрузка вывода таблицы */
		friend std::ostream& operator << (std::ostream& out, Table& Base);
	};
};

#endif TABLE_H

