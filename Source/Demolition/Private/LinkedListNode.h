// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LinkedListNode.generated.h"

UCLASS()
class ALinkedListNode : public AActor
{
	GENERATED_BODY()

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * BaseCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LinkedList)
	bool bIsHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	uint8 NodeIndex;

	
private:
	ALinkedListNode * ChildNode;
	
	ALinkedListNode * ParentNode;
	
public:	
	// Sets default values for this actor's properties
	ALinkedListNode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	ALinkedListNode * GetChildNode();
	
	UFUNCTION(BlueprintCallable, Category = LinkedList)
	ALinkedListNode * GetParentNode();

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	void GetChildList(TArray<ALinkedListNode *> & list);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	void SetChildNode(ALinkedListNode * node);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	void SetParentNode(ALinkedListNode * node);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	void AddLast(ALinkedListNode * node);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	bool CheckCanBeChild(ALinkedListNode * node);

	UFUNCTION()
	void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Destroyed() override;
};
