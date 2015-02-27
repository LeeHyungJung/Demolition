// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Game/Common/ConstID.h"
#include "DmObjectAttrValue.generated.h"

UENUM(BlueprintType)
enum class DM_OBJECT_ATTR : uint8
{
	DM_OBJECT_ATTR_NONE,
	DM_OBJECT_ATTR_HP,
	DM_OBJECT_ATTR_DAMAGE,
	DM_OBJECT_ATTR_DEFENSE,
	DM_OBJECT_ATTR_AGGRO,
	DM_OBJECT_ATTR_MAX,
};

inline uint8 GetTypeHash(const DM_OBJECT_ATTR A)
{
	return (uint8)A;
}

class DEMOLITION_API DmObjectAttrValue
{
	enum DM_OBJECT_ATTR_VAL_OP_TYPE
	{
		DM_OBJECT_ATTR_VAL_OP_TYPE_NONE,
		DM_OBJECT_ATTR_VAL_OP_TYPE_ADD,
		DM_OBJECT_ATTR_VAL_OP_TYPE_PRODUCT,
		DM_OBJECT_ATTR_VAL_OP_TYPE_DIVDE,
	};

public:
	DmObjectAttrValue(const DmObjectAttrValueID _Id
		, DM_OBJECT_ATTR _Attr
		, int _Priority
		, float _Value
		, DM_OBJECT_ATTR_VAL_OP_TYPE Operater
		)
		:Id(_Id)
		, Priority(_Priority)
		, Value(_Value)
		, Attr(_Attr)
	{
	};
	~DmObjectAttrValue(){};

private:
	const DmObjectAttrValueID Id;
	DM_OBJECT_ATTR	Attr;
	DM_OBJECT_ATTR_VAL_OP_TYPE Operater;
	const int Priority;
	const float Value;
};
