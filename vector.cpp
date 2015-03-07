#include <iostream>

using namespace std;

#define DEFAULT_CAPACITY 5

template <typename T> class Vector{	
protected:
	int _size;	//��ǰԪ�ظ���
	int _capacity;	//�������
	T* _elem;	//�������Ԫ��
	void copyFrom(T a[], int lo, int hi);	//��a����[lo,hi)���ָ��Ƶ�_elem
	void bubbleSort();	//ð������
public:
	Vector(int c = DEFAULT_CAPACITY)
	{
		_size = 0;
		_capacity = c;
		_elem = new T[c];
	}
	Vector(Vector &s)
	{
		copyFrom(s._elem, 0, s._size);
	}
	void print(void);	//��ӡ
	int size(void);	//���ص�ǰԪ������
	T get(int r);	//������Ϊr��Ԫ��
	bool put(int r, T e);	//��λ��r��Ԫ���滻Ϊe
	bool insert(int r, T e);	//��λ��r������e ����ĺ���
	T remove(int r);	//ɾ����Ϊr��Ԫ�أ�������
	bool disordered();	//�Ƿ�ǽ������У�true���� false����
	void sort();	//���շǽ�����
};




int main()
{
	Vector<int> a(10);
	a.insert(0, 2);
	a.insert(0, 7);
	a.insert(0, 4);
	a.insert(0, 1);
	a.sort();
	a.print();
	return 0;
}

//��a[]��[lo, hi)���Ƶ�����
template <typename T>
void Vector<T>::copyFrom(T a[], int lo, int hi)
{
	_capacity = 2 * (lo - hi);
	_elem = new T[_capacity];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = a[lo++];
	}
}

template <typename T>
void Vector<T>::print(void)
{
	for (int i = 0; i < _size; ++i)
	{
		cout << _elem[i] << " ";
	}
	cout << endl;
}

template <typename T>
bool Vector<T>::insert(int r, T e)
{
	if (r > _size)
		return false;

	int i = _size++;
	while (i > r)
	{
		_elem[i] = _elem[i-1];
		--i;
	}
	_elem[i] = e;
	return true;
}

template <typename T>
int Vector<T>::size(void)
{
	return _size;
}

//������Ϊr��Ԫ��
template <typename T>
T Vector<T>::get(int r)
{
	if (r >= 0 && r < _size)
		return _elem[r];
	else
		return 0;
}

//��λ��r��Ԫ���滻Ϊe
template <typename T>
bool Vector<T>::put(int r, T e)
{
	if (r < 0 || r >= _size)
		return false;
	
	_elem[r] = e;
	return true;
}


//ɾ����Ϊr��Ԫ�أ�������
template <typename T>
T Vector<T>::remove(int r)
{
	if (r < 0 || r >= _size)
		return 0;
	T tmp = _elem[r];
	int i;
	for (i = r; i < _size-1; ++i)
	{
		_elem[i] = _elem[i+1];
	}
	--_size;
	return tmp;
}

//�Ƿ�ǽ������У�true���� false����
template <typename T>
bool Vector<T>::disordered()
{
	for (int i = 0; i < _size-1; ++i)
	{
		if (_elem[i+1] < _elem[i])
			return true;
	}
	return false;
}

//ð������
template <typename T>
void Vector<T>::bubbleSort()
{
	int i, j, temp;
	int flag;
	for (i = _size; i > 0; --i)
	{
		flag = 0;
		for (j = 0; j < i; ++j)
		{
			if (_elem[j] > _elem[j+1])
			{
				temp = _elem[j];
				_elem[j] = _elem[j+1];
				_elem[j+1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}
}


//���շǽ�����
template <typename T>
void Vector<T>::sort()
{
	bubbleSort();
}