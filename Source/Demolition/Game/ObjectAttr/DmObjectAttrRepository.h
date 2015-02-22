// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/Common/ConstID.h"
#include "DmObjectAttr.h"
#include "DmObjectAttrValue.h"

/**
 * 
 */
class DEMOLITION_API DmObjectAttrRepository
{
public:
	DmObjectAttrRepository();
	virtual ~DmObjectAttrRepository();

	void LoadScript(const FString string){};
	void GetObjectAttr(DmObjectAttrID _InId, UDmObjectAttr & _OutAttr){};
/*	void GetAttr(DmObjectAttrValueID _InId, DmObjectAttr & _OutAttr){};*/
private:
 /*	TMap<DmObjectAttrValueID, DmObjectAttrValue> AttrValue;
 */	TMap<DmObjectAttrID, TArray<DmObjectAttrValueID>> AttrMap;
};
