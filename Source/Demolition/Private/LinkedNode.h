#pragma once

#include "Demolition.h"

template <class T>
class DEMOLITION_API CLinkedNode
{
public:
	T * Content;

	uint32 NodeIndex;

	CLinkedNode<T> * ChildNode;

	CLinkedNode<T> * ParentNode;

public:
	CLinkedNode<T>()
	{
		ChildNode = nullptr;

		ParentNode = nullptr;

		NodeIndex = -1;
		
		Content = nullptr;
	}

	virtual ~CLinkedNode<T>()
	{

	}

	void setContent(T * Content)
	{
		this->Content = Content;
	}

	CLinkedNode<T> * GetChildNode()
	{
		return ChildNode;
	}

	CLinkedNode<T> * GetParentNode()
	{
		return ParentNode;
	}

	void GetChildList(TArray<CLinkedNode<T> *> & list)
	{
		CLinkedNode<T> * tempChild = GetChildNode();
		while (tempChild != nullptr)
		{
			list.Add(tempChild);
			tempChild = tempChild->GetChildNode();
		}
	}

	void SetChildNode(CLinkedNode<T> * node)
	{
		ChildNode = node;
	}

	void SetParentNode(CLinkedNode<T> * node)
	{
		ParentNode = node;
	}

	void AddLast(CLinkedNode<T> * node)
	{
		if (ChildNode != nullptr)
		{
			ChildNode->AddLast(node);
		}
		else
		{
			ChildNode = node;
			ChildNode->ParentNode = this;
		}
	}

};
