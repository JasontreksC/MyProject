#pragma once
#include "Headers.h"

template<typename T>
class Node
{
public:
	T Data;
	Node<T>* pPrev;
	Node<T>* pNext;

public:
	Node();
	Node(const T& _Data, Node<T>* _prev_node, Node<T>* _next_node);
	~Node();
};

template<typename T>
class LinkedList
{
protected:
	Node<T>* pHead;
	Node<T>* pTail;
	int iCount;

public:
	LinkedList();
	~LinkedList();

public:
	void PushFront(const T& _Data);
	void PushBack(const T& _Data);
	int  GetCount();

public:
	class iterator;

	typename iterator begin();
	typename iterator end();
	typename iterator find(int _i);
	typename iterator erase(iterator& _otheriter);
	typename iterator insert_front(const iterator& _otheriter, const T& _Data);
	typename iterator insert_back(const iterator& _otheriter, const T& _Data);

public:
	class iterator
	{
		friend class LinkedList;

	protected:
		LinkedList<T>* pList;
		Node<T>* pNode;
		bool valid;

	public:
		iterator();
		iterator(LinkedList<T>* _pList, Node<T>* _pNode);
		~iterator();

// ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼/ 이터레이터 연산자 오버로드 / 포인터, 참거짓비교, 증감 /▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	public:
		T& operator *()
		{
			return pNode->Data;
		}
		bool operator == (const iterator& _otheriter)
		{
			if (pList == _otheriter.pList && pNode == _otheriter.pNode)
				return true;
			else
				return false;
		}
		bool operator != (const iterator & _otheriter)
		{
			return !(*this == _otheriter);
		}
		iterator& operator ++ ()
		{
			if (pNode == nullptr || !valid)
				assert(nullptr);

			pNode = pNode->pNext;
			return *this;
		}
		iterator operator ++ (int)
		{
			if (pNode == nullptr || !valid)
				assert(nullptr);

			iterator copyiter(*this);
			++(*this);
			return copyiter;
		}
		iterator& operator -- ()
		{
			if (pNode == nullptr || !valid)
				assert(nullptr);

			pNode = pNode->prev_node;
			return *this;
		}
		iterator operator -- (int)
		{
			if (pNode == nullptr || !valid)
				assert(nullptr);

			iterator copyiter(*this);
			--(*this);
			return copyiter;
		}
		iterator operator +(int _i)
		{
			if (pNode == nullptr || !valid)
				assert(nullptr);

			iterator temp1(*this);
			iterator temp2;
			for (int i = 0; i < _i; i++)
				++(*this);
			temp2 = *this;
			*this = temp1;
			return temp2;
		}
	};
};

// ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼/ 생성자, 소멸자 정의 / 노드, 리스트, 이터레이터 /▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

template<typename T>
Node<T>::Node()
	: Data()
	, pPrev(nullptr)
	, pNext(nullptr)
{ 
}

template<typename T>
Node<T>::Node(const T& _Data, Node<T>* _pPrev, Node<T>* _pNext)
	: Data(_Data)
	, pPrev(_pPrev)
	, pNext(_pNext)
{
}

template<typename T>
Node<T>::~Node()
{
}

template<typename T>
LinkedList<T>::LinkedList()
	: iCount(0)
	, pHead(nullptr)
	, pTail(nullptr)
{
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* pDelete = pHead;

	while (pDelete) 
	{
		Node<T>* pTemp = pDelete->pNext;
		delete(pDelete);
		pDelete = pTemp;
	}
	iCount = 0;
}

template<typename T>
LinkedList<T>::iterator::iterator()
	: pList(nullptr)
	, pNode(nullptr)
	, valid(false)
{
}

template<typename T>
LinkedList<T>::iterator::iterator(LinkedList<T>* _pList, Node<T>* _pNode)
	: pList(_pList)
	, pNode(_pNode)
	, valid(false)
{
	if (_pList != nullptr && _pNode != nullptr)
		valid = true;
}

template<typename T>
LinkedList<T>::iterator::~iterator()
{
}

// ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼/ 리스트 기본함수 정의 / 푸시 프론트, 푸시 백, 정렬, 갯수반환 /▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
template<typename T>
inline void LinkedList<T>::PushFront(const T& _Data)
{
	Node<T>* pNew = new Node<T>(_Data, nullptr, nullptr);

	if (!iCount)
	{
		pHead = pNew;
		pTail = pNew;
	}
	else
	{
		pHead->pPrev = pNew;
		pNew->pNext = pHead;
		pHead = pNew;
	}

	++iCount;
}

template<typename T>
inline void LinkedList<T>::PushBack(const T& _Data)
{
	Node<T>* pNew = new Node<T>(_Data, nullptr, nullptr);

	if (!iCount)
	{
		pHead = pNew;
		pTail = pNew;
	}
	else
	{
		pTail->pNext = pNew;
		pNew->pPrev = pTail;
		pTail = pNew;
	}

	++iCount;
}

template<typename T>
inline int LinkedList<T>::GetCount()
{
	return iCount;
}

// ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼/ 이터레이터 함수 정의 / 시작과 끝, 찾기와 지우기, 지정 추가 /▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::begin()
{
	return typename LinkedList<T>::iterator(this, pHead);
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::end()
{
	return typename LinkedList<T>::iterator(this, nullptr);
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::find(int _i)
{
	LinkedList<T>::iterator pFind = begin();
	if (_i <= iCount)
	{
		for (int i = 0; i < _i; i++)
			++pFind;
	}
	else
	{
		assert(nullptr);
	}
	return pFind;
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::erase(iterator& _otheriter)
{
	Node<T>* pLeft = _otheriter.pNode->pPrev;
	Node<T>* pRight = _otheriter.pNode->pNext;

	delete(_otheriter.pNode);

	if (pLeft == nullptr && pRight == nullptr)
	{
		pHead = nullptr;
		pTail = nullptr;
	}
	else if (pLeft == nullptr || pRight == nullptr)
	{
		if (pLeft == nullptr)
		{
			pHead = pRight;
			pRight->pPrev = nullptr;
		}

		if (pRight == nullptr)
		{
			pTail = pLeft;
			pLeft->pNext = nullptr;
		}
	}
	else if (pLeft != nullptr && pRight != nullptr)
	{
		pLeft->pNext = pRight;
		pRight->pPrev = pLeft;
	}
	--iCount;

	return typename LinkedList<T>::iterator(this, nullptr);
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::insert_front(const iterator& _otheriter, const T& _Data)
{
	if (end() == _otheriter)
		assert(nullptr);

	if (begin() == _otheriter) {
		PushFront(_Data);
		return typename LinkedList<T>::iterator(this, pHead);
	}

	Node<T>* left = _otheriter.pNode->pPrev;
	Node<T>* right = _otheriter.pNode;
	Node<T>* pNew = new Node<T>(_Data, nullptr, nullptr);

	left->pNext = pNew;
	right->pPrev = pNew;
	pNew->pPrev = left;
	pNew->pNext = right;

	++iCount;
	return typename LinkedList<T>::iterator(this, pNew);
}

template<typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::insert_back(const iterator& _otheriter, const T& _Data)
{
	if (end() == _otheriter)
		assert(nullptr);

	if (begin() == _otheriter) {
		PushBack(_Data);
		return typename LinkedList<T>::iterator(this, pTail);
	}

	Node<T>* left = _otheriter.pNode;
	Node<T>* right = _otheriter.pNode->pNext;
	Node<T>* pNew = new Node<T>(_Data, nullptr, nullptr);

	left->pNext = pNew;
	right->pPrev = pNew;
	pNew->pPrev = left;
	pNew->pNext = right;

	++iCount;

	return typename LinkedList<T>::iterator(this, pNew);
}
