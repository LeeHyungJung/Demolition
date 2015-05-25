#pragma once


#include "Components/SceneComponent.h"
#include "DemolitionObjectProperty.generated.h"

UCLASS()
class DEMOLITION_API UDemolitionObjectProperty : public USceneComponent
{
	GENERATED_BODY()
public:
	UDemolitionObjectProperty(const FObjectInitializer& ObjectInitializer);

	int32 HP;

	int32 POWER;

	UFUNCTION(BlueprintCallable, Category = Property)
		void setHP(int32 input_hp);

	UFUNCTION(BlueprintCallable, Category = Property)
		int32 getHP();
};