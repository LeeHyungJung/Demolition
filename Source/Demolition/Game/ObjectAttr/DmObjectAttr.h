// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Game/Common/ConstID.h"
#include "DmObjectAttrValue.h"
/**
 * 
 */

class DEMOLITION_API DmObjectAttr
{
public:
	DmObjectAttr(){};
	~DmObjectAttr(){};

public:
	void MakeAttr(){};
	void Clear(){};
	
	float operator[](DM_OBJECT_ATTR idx) {
		return CachedATTR[idx];
	};

private:
	TMap<DM_OBJECT_ATTR, TArray<DmObjectAttrValueID>> ATTR;
	TMap<DM_OBJECT_ATTR, float> CachedATTR;
	bool Dirty;
};
