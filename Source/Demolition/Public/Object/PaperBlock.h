#pragma once

#include "GameFramework/Actor.h"
#include "PaperBlock.generated.h"

class UPaperFlipbookComponent;
class UBoxComponent;

UCLASS()
class APaperBlock : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnAttacked(float Damage);

	UFUNCTION(BlueprintNativeEvent)
	void OnBeginDemolition();

	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return Sprite; }

	UFUNCTION(BlueprintNativeEvent)
	void UpdateAnimation(float DeltaSeconds);
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdateMovement(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = Attr)
	float getHP();

	UFUNCTION(BlueprintCallable, Category = PaperBlock)
	bool IsBeginDemolition();

private:
	void initBaseCollisionComponent(const FObjectInitializer& ObjectInitializer);
	void initSprite(const FObjectInitializer& ObjectInitializer);
	void FallingByNoPysics(float DeltaSeconds);
protected:
	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PaperBlock)
	class UBoxComponent* BaseCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PaperBlock)
	class UPaperFlipbookComponent* Sprite;

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DemolitionAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attr)
	float HP;

private:
	bool bBeginDemolition;
	float EleapsedTime;
};