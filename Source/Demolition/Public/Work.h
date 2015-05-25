// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "private/LinkedNode.h"
#include "private/DemolitionObjectProperty.h"
#include "Work.generated.h"

class UDemolitionObjectProperty;

UCLASS()
class DEMOLITION_API AWork : public AActor, public CLinkedNode<AWork>
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LinkedList)
	class UBoxComponent * BaseCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Demolition)
	UDemolitionObjectProperty * DmProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LinkedList)
	bool bHead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Work)
	class AWorker * WorkOwner;

public:	
	// Sets default values for this actor's properties
	AWork();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool CheckCanBeChild(AWork * node);

	UFUNCTION(BlueprintNativeEvent, Category = "Work")
	void OnBeWorked(UDemolitionObjectProperty * Properties);

	virtual void OnBeWorked_Implementation(UDemolitionObjectProperty * Properties);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	AWork * GetChildWork();

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	void NotiyToRoot(AWork * node);

	UFUNCTION(BlueprintCallable, Category = LinkedList)
	int32 GetIndex();

	UFUNCTION(BlueprintCallable, Category = Work)
	UDemolitionObjectProperty * GetDmProperties();

	UFUNCTION()
	void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Destroyed() override;
};
