// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <queue>
#include "Private/ObjectGenerateListener.h"
#include "private/ClickEventListener.h"
#include "LinkedWork.h"
#include "Worker.generated.h"

UCLASS()
class DEMOLITION_API AWorker : public AActor, public IObjectGenerateListener, public IClickEventListener
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * BaseCollisionComponent;
	
public:	
	// Sets default values for this actor's properties
	AWorker();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnCreatedNode(AActor * node) override;

	virtual void OnClick(class UPrimitiveComponent * Comp) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnWorkerInputTouchBegin(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp);

	void OnWorkerInputTouchBegin_Implementation(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp);

	UFUNCTION(BlueprintNativeEvent)
	void OnWorkerInputTouchEnd(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp);

	void OnWorkerInputTouchEnd_Implementation(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp);

	UFUNCTION(BlueprintNativeEvent)
	void OnAddedWork(ALinkedWork * node);

	void OnAddedWork_Implementation(ALinkedWork * node);

	UFUNCTION(BlueprintNativeEvent)
	void OnStackedWork(ALinkedWork * node);

	void OnStackedWork_Implementation(ALinkedWork * node);

private:
	void removeWorkProc();

private:
	std::queue<ALinkedWork *> QueNodes;
};
