// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "Worker.h"
#include "Components/PrimitiveComponent.h"
#include "InputCoreTypes.h"

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

void AWorker::OnCreatedNode(AActor * node)
{
	ALinkedWork * work = Cast<ALinkedWork>(node);

	if (work != nullptr)
	{
		OnAddedWork(work);
	}
}

void AWorker::OnClick(UPrimitiveComponent * Comp)
{

}

void AWorker::OnInputTouchBeginTest_Implementation(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp)
{
	
}

void AWorker::OnInputTouchEndTest_Implementation(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp)
{
	UE_LOG(LogTemp, Warning, TEXT("Work Touch End"));
	removeWorkProc();
	return;
}

void AWorker::OnAddedWork_Implementation(ALinkedWork * node)
{
	UE_LOG(LogTemp, Warning, TEXT("Add Work"));
	QueNodes.push(node);
}

void AWorker::OnStackedWork_Implementation(ALinkedWork * node)
{
	UE_LOG(LogTemp, Warning, TEXT("Work Stacked"));
}

void AWorker::removeWorkProc()
{
	if (QueNodes.empty()) return;

	ALinkedWork * work = QueNodes.front();

	if (work != nullptr)
	{
		work->Destroy();
		QueNodes.pop();
	}
}









