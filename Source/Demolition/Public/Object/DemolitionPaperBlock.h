#pragma once

#include "Object/DemolitionObject.h"
#include "DemolitionPaperBlock.generated.h"

UCLASS()
class ADemolitionPaperBlock : public ADemolitionObject
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UPaperFlipbookComponent* GetSprite() const { return Sprite; }

	UFUNCTION(BlueprintNativeEvent)
	void UpdateAnimation(float DeltaSeconds);

private:
	void initSprite(const FObjectInitializer& ObjectInitializer);
	void CollisionSetup();

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DemolitionAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PaperBlock)
	class UPaperFlipbookComponent* Sprite;

};