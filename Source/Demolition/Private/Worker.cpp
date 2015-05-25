// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "Worker.h"
#include "Work.h"
#include "Components/PrimitiveComponent.h"
#include "InputCoreTypes.h"
#include "private/DemolitionObjectProperty.h"

// Sets default values
AWorker::AWorker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));

	BaseCollisionComponent->SetCollisionProfileName("BlockAll");

	RootComponent = BaseCollisionComponent;

	DmProperties = CreateOptionalDefaultSubobject<UDemolitionObjectProperty>(TEXT("a"));
}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorker::OnCreatedNode(AActor * node)
{
	AWork * work = Cast<AWork>(node);

	if (work != nullptr)
	{
		OnAddedWork(work);
	}
}

void AWorker::OnClick(UPrimitiveComponent * Comp)
{

}

void AWorker::OnWorkerInputTouchBegin_Implementation(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp)
{

}

void AWorker::OnWorkerInputTouchEnd_Implementation(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp)
{
	UE_LOG(LogTemp, Warning, TEXT("Work Touch End"));

	doWork();

	return;
}

void AWorker::OnAddedWork_Implementation(AWork * node)
{
	QueNodes.push(node);
}

void AWorker::OnStackedWork_Implementation(AWork * node)
{
	UE_LOG(LogTemp, Warning, TEXT("Work Stacked"));
}

void AWorker::removeWorkProc()
{
	if (QueNodes.empty()) return;

	AWork * work = QueNodes.front();

	if (work != nullptr)
	{
		work->Destroy();
		QueNodes.pop();
	}
}

void AWorker::doWork()
{
	if (QueNodes.size() == 0) return;

	AWork * work = QueNodes.front();

	if (work != nullptr && work->GetDmProperties() != nullptr)
	{
		work->OnBeWorked(DmProperties);

		work->GetDmProperties()->HP -= DmProperties->POWER;

		if (work->DmProperties != nullptr && work->GetDmProperties()->HP <= 0)
		{
			removeWorkProc();
		}
	}
}









