#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

class ElemL2
{
	char inf;
	int key;
	ElemL2* next;
	ElemL2* prev;

public:

	ElemL2(char Inf, int Key)
	{
		next = nullptr;
		prev = nullptr;
		inf = Inf;
		key = Key;
	}

	friend class List;
	friend class Sifer;

	~ElemL2()
	{
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
	}
};

class List
{
	ElemL2* head;
	ElemL2* last;
	size_t size;

public:

	List(List* Copy = nullptr)
	{
		head = nullptr;
		last = nullptr;
		size = 0;
		if (Copy)
		{
			ElemL2* Cur = Copy->head;
			while (Cur)
			{
				push_back(Cur->inf, Cur->key);
				Cur = Cur->next;
			}
		}
	}

	bool isEmpty()
	{
		return size == 0;
	}

	size_t get_size() { return size; }

	void BubbleSort()
	{
		ElemL2* E1, * E2;
		int temp_key;
		char temp_inf;
		bool is_swapped = 0;
		for (int i = 0; i < (size - 1); i++)
		{
			for (int j = 0; j < (size - 1) - i; j++)
			{
				E1 = at(j);
				E2 = at(j + 1);
				if (E1->key < E2->key)
				{
					is_swapped = true;
					temp_key = E1->key;
					temp_inf = E1->inf;
					set(E2->inf, E2->key, j);
					set(temp_inf, temp_key, j + 1);
				}
			}
			if (!is_swapped)
				break;
			is_swapped = false;
		}
	}

	void push_back(char inf, int key)
	{
		if (!isEmpty())
		{
			last->next = new ElemL2(inf, key);
			last->next->prev = last;
			last = last->next;
		}
		else
		{
			head = new ElemL2(inf, key);
			last = head;
		}
		size += 1;
	}

	void push_front(char inf, int key)
	{
		if (!isEmpty())
		{
			head->prev = new ElemL2(inf, key);
			head->prev->next = head;
			head = head->prev;
		}
		else
		{
			head = new ElemL2(inf, key);
			last = head;
		}
		size += 1;
	}

	void pop_back()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		ElemL2* newLast = last->prev;
		delete last;
		last = newLast;
		if (!newLast)
			head = nullptr;
		size -= 1;
	}

	void pop_front()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		ElemL2* newHead = head->next;
		delete head;
		head = newHead;
		if (!newHead)
			last = nullptr;
		size -= 1;
	}

	ElemL2* at(size_t index)
	{
		if (index >= size)
			throw out_of_range("Index is out of range\n");
		if (index == 0)
			return head;
		if (index == (size - 1))
			return last;
		int count;
		ElemL2* Cur;
		if ((size / 2) > index)
		{
			Cur = head;
			count = 0;
			while (count != index)
			{
				Cur = Cur->next;
				count++;
			}
		}
		else
		{
			Cur = last;
			count = size - 1;
			while (count != index)
			{
				Cur = Cur->prev;
				count--;
			}
		}
		return Cur;
	}

	ElemL2* find_by_inf(char inf)
	{
		ElemL2* Cur = head;
		while (Cur)
		{
			if (Cur->inf == inf)
				return Cur;
			Cur = Cur->next;
		}
		return nullptr;
	}

	void insert(char inf, int key, size_t index)
	{
		if (index == 0)
			push_front(inf, key);
		else
		{
			try
			{
				ElemL2* Next = at(index);
				ElemL2* Prev = Next->prev;
				ElemL2* Include = new ElemL2(inf, key);
				Prev->next = Include;
				Include->prev = Prev;
				Next->prev = Include;
				Include->next = Next;
				size += 1;
			}
			catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
		}
	}

	void remove(size_t index)
	{
		try
		{
			if (index == 0)
				pop_front();
			else if (index == (size - 1))
				pop_back();
			else
			{
				ElemL2* Exclude = at(index);
				delete Exclude;
				size -= 1;
			}
		}
		catch (runtime_error& exception) { throw runtime_error("List is empty\n"); }
		catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
	}

	void set(char inf, int key, size_t index)
	{
		ElemL2* cur;
		try
		{
			cur = at(index);
			cur->inf = inf;
			cur->key = key;
		}
		catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
	}

	void print_to_console()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		ElemL2* Cur = head;
		while (Cur)
		{
			cout << Cur->inf << ' ' << Cur->key << endl;
			Cur = Cur->next;
		}
	}

	void clear()
	{
		while (!isEmpty())
			pop_front();
	}

	~List()
	{
		clear();
	}
};

#endif
