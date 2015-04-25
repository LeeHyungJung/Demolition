// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LinkedListNode.h"

class ALinkedListNode;
/**
 * 
 */
class INodeGenerateListener
{
public:
	INodeGenerateListener();
	~INodeGenerateListener();

	virtual void OnCreatedNode(ALinkedListNode * node) = 0;
};
