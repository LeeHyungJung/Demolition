#pragma once
#include "Game/Common/ConstID.h"
#include "DmObjectAttrValue.h"
#include "DmObjectAttr.generated.h"
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, notplaceable,hidecategories = (Movement, Collision, Rendering, "Utilities|Transformation"))
class DEMOLITION_API UDmObjectAttr : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void MakeAttr(){};

	void Clear(){};

	float operator[](DM_OBJECT_ATTR idx)  {
		return CachedATTR[idx];
	};

	float operator[](DM_OBJECT_ATTR idx) const {
		return CachedATTR[idx];
	};

private:
	TMap<DM_OBJECT_ATTR, TArray<DmObjectAttrValueID>> ATTR;
	TMap<DM_OBJECT_ATTR, float> CachedATTR;
	bool Dirty;
};
