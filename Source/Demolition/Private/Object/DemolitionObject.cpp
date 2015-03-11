#include "DemolitionPrivate.h"
#include "Components/BoxComponent.h"

#include "DemolitionCharacter.h"
#include "DemolitionObject.h"

ADemolitionObject::ADemolitionObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bBeginDemolition = false;
	bApplyFallingAttr = false;

	FallingTime = 0.0f;
	PrimaryActorTick.bCanEverTick = true;

	initBaseCollisionComponent(ObjectInitializer);
}

void ADemolitionObject::initBaseCollisionComponent(const FObjectInitializer& ObjectInitializer)
{
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BaseBoxComponent");
	BaseCollisionComponent->CanCharacterStepUpOn = ECB_No;
	BaseCollisionComponent->bCheckAsyncSceneOnMove = false;
	BaseCollisionComponent->bCanEverAffectNavigation = false;
	BaseCollisionComponent->SetLockedAxis(ELockedAxis::Y);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Y = DEMOLITION_POS_Y;

	RootComponent = BaseCollisionComponent;
}


void ADemolitionObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	OnUpdateMovement(DeltaSeconds);
}

void ADemolitionObject::OnUpdateMovement_Implementation(float DeltaSeconds)
{
	if (IsApplyFallingAttr() == true)
	{
		applyFalling(DeltaSeconds);
	}
}

bool ADemolitionObject::IsApplyFallingAttr()
{
	return bApplyFallingAttr;
}

bool ADemolitionObject::IsFalling()
{
	return FallingTime > 0.f ? true : false;
}

void ADemolitionObject::setApplyFallingAttr(bool bFallingAttr)
{
	bApplyFallingAttr = bFallingAttr;
}

void ADemolitionObject::applyFalling(float DeltaSeconds)
{
	bool bApply = true;

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z += DeltaSeconds * (FallingTime * GetWorld()->GetGravityZ());
	FHitResult HitResult;

	if (SetActorLocation(CurrentLocation, true, &HitResult) == false)
	{
		bApply = false;
		//OnBeginDemolition();
		// If the set function returned false something is blocking at that location. We can interrogate this result to determine details of this  
		// @See FHitResult for more information  
		if (HitResult.GetActor() != nullptr)
		{
			ADemolitionCharacter * const HitActor = Cast<ADemolitionCharacter>(HitResult.GetActor());

			if (HitActor)
			{
				SetActorLocation(CurrentLocation, false, &HitResult);
			}
		}
	}

	if (bApply)
	{
		FallingTime += DeltaSeconds;
	}
}

void ADemolitionObject::OnAttacked_Implementation(float Damage)
{
	HP -= Damage;
	if (HP < 0)
	{
		OnBeginDemolition();
	}
}

void ADemolitionObject::OnBeginDemolition_Implementation()
{
	bBeginDemolition = true;
}

float ADemolitionObject::getEleapsedTime()
{
	return FallingTime;
}

bool ADemolitionObject::IsBeingDemolition()
{
	return bBeginDemolition;
}

float ADemolitionObject::getHP()
{
	return HP;
}







