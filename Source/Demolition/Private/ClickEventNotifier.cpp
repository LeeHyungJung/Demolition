// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "ClickEventNotifier.h"
#include "Private/ClickEventListener.h"

// Sets default values
AClickEventNotifier::AClickEventNotifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseClickableComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));

	BaseClickableComponent->SetCollisionProfileName("BlockAll");
	
	BaseClickableComponent->OnClicked.AddDynamic(this, &AClickEventNotifier::OnClick);

	BaseClickableComponent->OnInputTouchBegin.AddDynamic(this, &AClickEventNotifier::OnInputTouchBegin);

	BaseClickableComponent->OnInputTouchEnd.AddDynamic(this, &AClickEventNotifier::OnInputTouchEnd);

	RootComponent = BaseClickableComponent;
}

// Called when the game starts or when spawned
void AClickEventNotifier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClickEventNotifier::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AClickEventNotifier::OnClick(UPrimitiveComponent* pComponent)
{
	if (Receiver != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("clicked"));
		Receiver->OnClick(pComponent);
	}
}

void AClickEventNotifier::OnInputTouchBegin(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp)
{
	if (Receiver != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("touchBegin"));
		Receiver->OnInputTouchBeginTest(FingerIndex, Comp);
	}
}

void AClickEventNotifier::OnInputTouchEnd(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp)
{
	if (Receiver != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("touchEnd"));
		Receiver->OnInputTouchEndTest(FingerIndex, Comp);
	}
}

