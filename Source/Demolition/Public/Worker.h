// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Private/INodeGenerateListener.h"
#include <queue>
#include "Worker.generated.h"

UCLASS()
class DEMOLITION_API AWorker : public AActor, public INodeGenerateListener
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

	virtual void OnCreatedNode(ALinkedListNode * node) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnAddedWork(ALinkedListNode * node);

private:
	std::queue<ALinkedListNode *> QueNodes;
};
