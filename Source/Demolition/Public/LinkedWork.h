// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "private/LinkedNode.h"
#include "private/DemolitionObjectProperty.h"
#include "LinkedWork.generated.h"

UCLASS()
class DEMOLITION_API ALinkedWork : public AActor, public CLinkedNode<ALinkedWork>
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * BaseCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Demolition)
	class UDemolitionObjectProperty * Properies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LinkedList)
	bool bHead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Work)
	class AWorker * WorkOwner;

public:	
	// Sets default values for this actor's properties
	ALinkedWork();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool CheckCanBeChild(ALinkedWork * node);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	ALinkedWork * GetChildWork();

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	void NotiyToRoot(ALinkedWork * node);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	int32 GetIndex();

	UFUNCTION()
	void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Destroyed() override;
};
