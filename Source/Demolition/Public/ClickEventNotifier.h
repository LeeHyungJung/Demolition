// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ClickEventNotifier.generated.h"

class UPrimitiveComponent;

UCLASS()
class DEMOLITION_API AClickEventNotifier : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Click)
	class UBoxComponent * BaseClickableComponent;

	UPROPERTY(EditAnywhere, Category = Click)
	TScriptInterface<class IClickEventListener> Receiver;
	
public:	
	// Sets default values for this actor's properties
	AClickEventNotifier();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnClick(UPrimitiveComponent* pComponent);

	UFUNCTION()
	void OnInputTouchBegin(const ETouchIndex::Type FingerIndex,class UPrimitiveComponent * Comp);

	UFUNCTION()
	void OnInputTouchEnd(const ETouchIndex::Type FingerIndex,class UPrimitiveComponent * Comp);
};
