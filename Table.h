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
			bool state, deleted;
		public:
			/* ����������� � ���������� */
			Node(int _value = 0);
			~Node();

			/* ������� � ������� */
			int GetValue() const;
			bool GetState() const;
			bool GetDeleted() const;

			friend class Table;
		};
	private:
		/* ����������� ���� ������ */
		size_t static s_id;
		bool static debug;

		/* ���� ������ */
		size_t id, size, count;
		Node* data;
		double coef;

		/* ������� ����������� */
		size_t HashFunc(int value, size_t probe = 0);
		size_t HashFunc1(int value);
		size_t HashFunc2(int value);

		/* ��������������� ������ */
		bool InsertValueHelper(int value, size_t pos);
	public:
		/* ���������� � ���������� */
		Table(size_t _size = 1);
		~Table();

		/* �������� ������� */
		Table& InsertValue(int value);
		int SearchValue(int value);
		bool DeleteValue(int value);

		/* ���������� ������ ������� */
		friend std::ostream& operator << (std::ostream& out, Table& Base);
	};
};

#endif TABLE_H

