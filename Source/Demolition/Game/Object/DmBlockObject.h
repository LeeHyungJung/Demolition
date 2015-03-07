// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DmBasePawnObject.h"
#include "DmBlockObject.generated.h"
/**
 * 
 */
UCLASS()
class DEMOLITION_API ADmBlockObject : public ADmBasePawnObject
{
	GENERATED_UCLASS_BODY()

	/** Name of the Box. */
	static FName BoxComponentName;

	float HP;

	UPROPERTY(Category = Box, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	/** Returns Sprite subobject **/
	FORCEINLINE class UBoxComponent* GetBox() const { return BoxComponent; }

	
	void OnTargeted_Implementation(const UDmObjectAttr * Attr) override;
};
