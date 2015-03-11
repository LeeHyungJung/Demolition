#pragma once

#include "GameFramework/Actor.h"
#include "DemolitionObject.generated.h"


#define DEMOLITION_POS_Y -10

class UBoxComponent;

UCLASS()
class ADemolitionObject : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, Category = DemolitionObject)
	void OnUpdateMovement(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = DemolitionObject)
	bool IsApplyFallingAttr();

	UFUNCTION(BlueprintCallable, Category = DemolitionObject)
	bool IsFalling();

	UFUNCTION(BlueprintCallable, Category = DemolitionObject)
	void setApplyFallingAttr(bool bFallingAttr);

	UFUNCTION(BlueprintCallable, Category = Attr)
	float getHP();

	UFUNCTION(BlueprintCallable, Category = DemolitionObject)
	bool IsBeingDemolition();

	UFUNCTION(BlueprintNativeEvent, Category = DemolitionObject)
	void OnAttacked(float Damage);

	UFUNCTION(BlueprintNativeEvent, Category = DemolitionObject)
	void OnBeginDemolition();

	FORCEINLINE class UBoxComponent* GetBaseColisionBox() const{ return BaseCollisionComponent; }

protected:
	virtual void initBaseCollisionComponent(const FObjectInitializer& ObjectInitializer);
	virtual void applyFalling(float DeltaSeconds);
	float getEleapsedTime();

protected:
	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = DemolitionObject)
	class UBoxComponent* BaseCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attr)
	float HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DemolitionObject)
	bool bApplyFallingAttr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DemolitionObject)
	bool bBeginDemolition;

	float FallingTime;
};

