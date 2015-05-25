// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class DEMOLITION_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	class UBoxComponent * WhereToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class AActor> WhatToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelayRangeHigh;
	
	UPROPERTY(EditAnywhere, Category = Spawning)
	TScriptInterface<class IObjectGenerateListener> Receiver;

private:

	bool bSpawningEnabled;

	float SpawnDelay;

	float SpawnTime;

public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void EnalbeSpawning();

	void DisableSpawing();

private:
	float GetRandomSpawnDelay();
	
	void SpawnActor();
};
