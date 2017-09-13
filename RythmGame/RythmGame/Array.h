#pragma once

template<class T>
class Array
{
private:
	T* _array;
	int _size;

	// operator overloading
public:
	T& operator[] (int index);	// 연산자 오버로딩
	operator T* ();	// 변환 연산자
	
public:
	Array(int size);
	~Array();

	int Size();

	bool Resize(int newSizse);
	
	void Set(int index, T newItem)
	{
		_array[index] = newItem;
	}

	T Get(int index)
	{
		return _array[index];
	}

	void Insert(T newItem, int insertIndex);
	void Remove(int removeIndex);

	bool SaveData(const char* fileName);
	bool LoadData(const char* fileName);
};

template<class T>
Array<T>::Array(int size)
{
	_array = new T[size];
	_size = size;
}

template<class T>
Array<T>::~Array()
{
	if (NULL != _array)
	{
		delete[] _array;
	}
	_array = NULL;
	_size = 0;
}

template<class T>
T& Array<T>::operator[] (int index)
{
	return _array[index];
}

template<class T>
Array<T>::operator T* ()
{
	return _array;
}

template<class T>
int Array<T>::Size()
{
	return _size;
}

template<class T>
bool Array<T>::Resize(int newSize)
{
	T* newArray = new T[newSize];
	if (NULL == newArray)
		return false;

	int minSize = 0;
	if (newSize < _size)
		minSize = newSize;
	else
		minSize = _size;

	for (int i = 0; i < minSize; i++)
	{
		newArray[i] = _array[i];
	}
	_size = newSize;

	if (NULL != _array)
		delete[] _array;

	_array = newArray;

	return true;
}

template<class T>
void Array<T>::Insert(T newItem, int insertIndex)
{
	for (int i = _size - 1; insertIndex < i; i--)
	{
		_array[i] = _array[i - 1];
	}
	_array[insertIndex] = newItem;
}

template<class T>
void Array<T>::Remove(int removeIndex)
{
	for (int i = removeIndex + 1; i < _size; i++)
	{
		_array[i - 1] = _array[i];
	}
}

template<class T>
bool Array<T>::SaveData(const char* fileName)
{
	FILE* fp = fopen(fileName, "wb");
	if (NULL == fp)
		return false;

	int writtenSize = fwrite(_array, sizeof(int), _size, fp);

	fclose(fp);

	if (writtenSize != _size)
		return false;

	return true;
}

template<class T>
bool Array<T>::LoadData(const char* fileName)
{
	FILE* fp = fopen(fileName, "rb");
	if (NULL == fp)
		return false;

	int readSize = fread(_array, sizeof(int), _size, fp);

	fclose(fp);

	if (readSize != _size)
		return false;
	return true;
}