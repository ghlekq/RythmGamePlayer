#pragma once


template <class T> class Node;
template <class T> class DLinkedList;
template <class T> class DLinkedListIterator;


template <class T>
class Node
{
public:
	T _data;

public:
	Node* Next;
	Node* Prev;

	// Insert
public:
	void InsertAfter(T data)
	{
		Node* newNode = new Node();
		newNode->_data = data;

		newNode->Next = Next;
		newNode->Prev = this;

		if (0 != Next)
		{
			Next->Prev = newNode;
		}

		Next = newNode;
	}

	void InsertBefore(T data)
	{
		Node* newNode = new Node();
		newNode->_data = data;

		newNode->Next = this;
		newNode->Prev = Prev;

		if (0 != Prev)
		{
			Prev->Next = newNode;
		}
		Prev = newNode;
	}

	void Delink()
	{
		if (0 != Prev)
			Prev->Next = Next;

		if (0 != Next)
			Next->Prev = Prev;
	}
};


template <class T>
class DLinkedList
{
public:
	Node<T>* _head;
	Node<T>* _tail;
	int _count;

public:
	DLinkedList()
	{
		_head = 0;
		_tail = 0;
		_count = 0;
	}

	~DLinkedList()
	{
		Node<T>* node = _head;
		Node<T>* next;
		while (0 != node)
		{
			next = node->Next;

			delete node;
			node = next;
		}
	}


	// Info
public:
	int Count()
	{
		return _count;
	}


	// Interface
public:
	// �� ��������, ���ο� ��� ����
	void Append(T data)
	{
		if (0 == _head)
		{
			// �ƹ��� ��尡 ������, ù�� ° ��带 �����Ѵ�.
			_head = _tail = new Node<T>();
			_head->_data = data;
			_head->Next = 0;
			_head->Prev = 0;
		}
		else
		{
			// �� �������� �� ��带 �����Ѵ�.
			_tail->InsertAfter(data);
			_tail = _tail->Next;	// �� ������ ������ �缳�� �Ѵ�.
		}
		_count++;
	}

	// �� �տ� ���ο� ��� ����
	void Prepend(T data)
	{
		// �ƹ��͵� ������ ���� �����.
		if (0 == _head)
		{
			_head = _tail = new Node<T>();
			_head->_data = data;
			_head->Next = 0;
			_head->Prev = 0;
		}
		else
		{
			_head->InsertBefore(data);
			_head = _head->Prev;	// ��� ��� �缳��
		}
		_count++;
	}

	// ��� ����
	void RemoveHead()
	{
		if (0 != _head)
		{
			Node<T>* node = _head->Next;
			delete _head;
			_head = node;

			// ����� ��� üũ
			if (0 == _head)
				_tail = 0;
			else
				_head->Prev = 0;
		}
		_count--;
	}

	// ���� ����
	void RemoveTail()
	{
		if (0 != _tail)
		{
			Node<T>* node = _tail->Prev;
			delete _tail;
			_tail = node;

			// ����� ��� ó��
			if (0 == _tail)
				_head = 0;
			else
				_tail->Next = 0;
		}
		_count--;
	}


	// Iterator
public:
	DLinkedListIterator<T> GetIterator()
	{
		return DLinkedListIterator<T>(this, _head);;
	}

	void Remove(DLinkedListIterator<T>& itr)
	{
		if (0 == itr._node)
			return;

		Node<T>* node = itr._node;
		if (node == _head)
			_head = _head->Next;
		else if (node == _tail)
			_tail = _tail->Prev;

		itr.Forth();

		node->Delink();
		delete node;

		if (0 == _head)
			_tail = 0;

		_count--;
	}

	void InsertAfter(DLinkedListIterator<T>& itr, int data)
	{
		if (0 != itr._node)
		{
			itr._node->InsertAfter(data);

			// ���� ��尡 ���� �� ��� ó��
			if (itr._node == _tail)
				_tail = itr._node->Next;

			_count++;
		}
		else
		{
			Append(data);
		}
	}

	void InsertBefore(DLinkedListIterator<T>& itr, int data)
	{
		if (0 != itr._node)
		{
			itr._node->InsertBefore(data);

			// head �� �� cjfl
			if (itr._node == _head)
				_head = itr._node->Prev;

			_count++;
		}
		else
		{
			Prepend(data);
		}
	}


	// Save/Load
public:
	void SaveData(const char* fileName)
	{
		FILE* fp = fopen(fileName, "wb");
		if (0 != fp)
		{
			fwrite(&_count, sizeof(int), 1, fp);

			Node<T>* node = _head;
			while (0 != node)
			{
				fwrite(&node->_data, sizeof(T), 1, fp);
				node = node->Next;
			}

			fclose(fp);
		}
	}

	void LoadData(const char* fileName)
	{
		FILE* fp = fopen(fileName, "rb");
		if (0 != fp)
		{
			int count = 0;
			fread(&count, sizeof(int), 1, fp);

			int buffer;
			while (0 != count)
			{
				fread(&buffer, sizeof(T), 1, fp);
				Append(buffer);
				count--;
			}

			fclose(fp);
		}
	}
};


template <class T>
class DLinkedListIterator
{
public:
	DLinkedList<T>* _linkedList;
	Node<T>* _node;

public:
	DLinkedListIterator<T>(DLinkedList<T>* linkedList, Node<T>* node)
	{
		_linkedList = linkedList;
		_node = node;
	}


	// operator overload
public:
	bool operator == (DLinkedListIterator<T>& itr)
	{
		if (_node == itr._node && _linkedList == itr._linkedList)
			return true;
		return false;
	}


	// Iterator
public:
	// �� ó������ ����
	void Start()
	{
		if (0 != _linkedList)
			_node = _linkedList->_head;
	}

	// �� �ڷ� ����
	void End()
	{
		if (0 != _linkedList)
			_node = _linkedList->_tail;
	}

	// ����
	void Forth()
	{
		if (0 != _node)
			_node = _node->Next;
	}

	// ����
	void Back()
	{
		if (0 != _node)
			_node = _node->Prev;
	}

	bool Valid()
	{
		return (0 != _node);
	}

	T Item()
	{
		return _node->_data;
	}
};

