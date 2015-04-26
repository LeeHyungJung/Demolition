// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "SpawnVolume.h"
#include "UnrealMathUtility.h"
#include "private/ObjectGenerateListener.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WhereToSpawn = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;

	SpawnDelay = GetRandomSpawnDelay();

	EnalbeSpawning();
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick( float DeltaTime )
{
	if (bSpawningEnabled != true)
		return;
	// Always add delta time to our Spawn Time
	SpawnTime += DeltaTime;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);

	if (bShouldSpawn)
	{
		SpawnLinkedNode();

		SpawnTime -= SpawnDelay;

		SpawnDelay = GetRandomSpawnDelay();
	}

}

void ASpawnVolume::EnalbeSpawning()
{
	bSpawningEnabled = true;
}

void ASpawnVolume::DisableSpawing()
{
	bSpawningEnabled = false;
}

float ASpawnVolume::GetRandomSpawnDelay()
{
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

void ASpawnVolume::SpawnLinkedNode()
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetActorLocation();

			FRotator SpawnRotation = FRotator::ZeroRotator;
			
			// 이것도 나중에 빼자 컴퍼넌트로 받아오기
			AActor* const SpawnedLinkedNode = World->SpawnActor<AActor>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			if (Receiver != nullptr)
			{
				Receiver->OnCreatedNode(SpawnedLinkedNode);
			}
		}
	}
}


