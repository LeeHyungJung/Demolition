// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Game/ObjectAttr/DmObjectAttr.h"
#include "DmPaperTargetObject.generated.h"

class UDmObjectAttr;
/**
 * 
 */
UCLASS()
class DEMOLITION_API ADmPaperTargetObject : public AActor
{
	GENERATED_UCLASS_BODY()
private:
	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* Sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attr, meta = (AllowPrivateAccess = "true"))
	class UDmObjectAttr* Attr;

public:
	/** Returns Sprite subobject **/
	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return Sprite; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TargetObject)
	bool bIsActive;
	
	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = TargetObject)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;


	/** Function to call when the Pickup is collected */
	UFUNCTION(BlueprintNativeEvent)
	void OnTargeted(const UDmObjectAttr * pAttr);


};
