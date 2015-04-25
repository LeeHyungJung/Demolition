// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "Worker.h"


// Sets default values
AWorker::AWorker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));

	BaseCollisionComponent->SetCollisionProfileName("BlockAll");

	RootComponent = BaseCollisionComponent;
}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorker::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWorker::OnCreatedNode(ALinkedListNode * node)
{
	OnAddedWork(node);
}

void AWorker::OnAddedWork_Implementation(ALinkedListNode * node)
{
	QueNodes.push(node);
}

