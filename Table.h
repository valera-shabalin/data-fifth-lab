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
			/* ����������� � ���������� */
			Node(int _value = 0);
			~Node();

			/* ������� � ������� */
			int GetValue() const;
			bool GetState() const;
			Node& SetValue(int value);
			Node& SetState(bool state);
		};
	private:
		/* ����������� ���� ������ */
		size_t static s_id;
		bool static debug;

		/* ���� ������ */
		size_t id, size, count;
		Node** data;
		double coef;

		/* ������� ����������� */
		size_t HashFunc(int value, size_t probe = 0);
		size_t HashFunc1(int value);
		size_t HashFunc2(int value);
	public:
		/* ���������� � ���������� */
		Table(size_t _size = 1);
		~Table();

		/* �������� ������� */
		Table& InsertValue(int value);
		size_t SearchValue(int value);

		/* ���������� ������ ������� */
		friend std::ostream& operator << (std::ostream& out, Table& Base);
	};
};

#endif TABLE_H

