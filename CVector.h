#pragma once

#include <iostream>
#include <cassert>
#include <initializer_list>

#define SAFE_DELETE(a) {if(a) {delete[] a; a = nullptr;}}// if(a) == a가 있을 때 라는 의미다.

class CVector
{
public:
	class CVectorBaseIterator // 인터페이스 : 순수 가상 함수가 포함된 클래스. 양식서 같은 것
	{
	public:
		CVectorBaseIterator(int* At) : m_At{ At } {};
		virtual ~CVectorBaseIterator() {};

		// 순수 가상 함수. 공란 같은 것.
		// 상속받은 클래스에서 채워넣어야 함
		virtual CVectorBaseIterator& operator++() = 0;

		virtual bool operator!=(const CVectorBaseIterator& B)
		{
			return (m_At != B.m_At) ? true : false;
		}

		virtual int& operator*()
		{
			assert(m_At);
			return *m_At;
		}

	protected:
		int* m_At{};
	};

	class CVectorIterator : public CVectorBaseIterator
	{
	public:
		CVectorIterator(int* At) : CVectorBaseIterator(At) {};
		~CVectorIterator() {};

		CVectorIterator& operator++() override
		{
			++m_At;
			return *this;
		}
	};

	class CVectorReverseIterator : public CVectorBaseIterator
	{
	public:
		CVectorReverseIterator(int* At) : CVectorBaseIterator(At) {};
		~CVectorReverseIterator() {};

		CVectorReverseIterator& operator++() override
		{
			--m_At;
			return *this;
		}
	};

public:
	CVector()
	{
		//std::cout << "기본 생성자가 호출되었습니다.\n";
	};

	CVector(const std::initializer_list<int>& i_list)
	{
		//std::cout << "initializer_list를 이용한 생성자가 호출되었습니다.\n";

		const int* first{ i_list.begin() };

		for (int i = 0; i < i_list.size(); ++i)
		{
			PushBack(*first);

			++first;
		}
	};

	~CVector()
	{
		//std::cout << "소멸자가 호출되었습니다.\n";

		SAFE_DELETE(m_Data);
	};

public: // 자료 출력 함수
	void Display()
	{
		using std::cout;

		for (int i = 0; i < m_Capacity; ++i)
		{
			cout << "[" << m_Data[i] << "]";
		}
	}

public: // 공간 할당 함수들
	void Reserve(int NewCapacity)
	{
		if (NewCapacity <= m_Capacity) { return; }

		int* temp = new int[m_Size] {};
		memcpy(temp, m_Data, sizeof(int) * m_Size);

		SAFE_DELETE(m_Data);

		m_Capacity = NewCapacity;

		m_Data = new int[m_Capacity] {};
		memcpy(m_Data, temp, sizeof(int) * m_Size);

		SAFE_DELETE(temp);
	}

	void Resize(int NewSize)
	{
		if (NewSize <= m_Capacity)
		{
			m_Capacity = 0;

			Reserve(NewSize);
		}
		else
		{
			Reserve(NewSize);
		}

		m_Size = m_Capacity;
	}

public: // 자료 삽입/제거 함수들
	void PushBack(int Value)
	{
		if (m_Data == nullptr)
		{
			Reserve(1);
		}

		if (m_Size == m_Capacity)
		{
			Reserve(m_Capacity * 2);
		}

		m_Data[m_Size] = Value;
		++m_Size;
	}

	int PopBack()
	{
		if (m_Size == 0) { return 0; }

		--m_Size;

		int result{ m_Data[m_Size] };

		m_Data[m_Size] = 0;

		return result;
	}

	void Clear()
	{
		while (!IsEmpty())
		{
			PopBack();
		}
	}

public: // iterator 함수들
	CVectorIterator begin()
	{
		return CVectorIterator(&m_Data[0]);
	}

	CVectorIterator end()
	{
		return CVectorIterator(&m_Data[m_Size]);
	}

	CVectorReverseIterator rbegin()
	{
		return CVectorReverseIterator(&m_Data[m_Size - 1]);
	}
	
	CVectorReverseIterator rend()
	{
		return CVectorReverseIterator(&m_Data[-1]);
	}

public: // 기타 함수들
	bool IsEmpty() { return ((m_Size == 0) ? true : false); }

	int Size() { return m_Size; }

	int Capacity() { return m_Capacity; }

	int Front() { if (m_Data) { return m_Data[0]; } return 0; }

	int Back() { if (m_Data) { return m_Data[m_Size - 1]; } return 0; }

	int At(int Index) { if (m_Data) { return m_Data[Index]; } return 0; }

private:
	int* m_Data{};
	int m_Size{};
	int m_Capacity{};
};
