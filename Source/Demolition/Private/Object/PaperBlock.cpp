#include "DemolitionPrivate.h"
#include "Engine/CollisionProfile.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperBlock.h"
#include "AssertionMacros.h"
#include "GameFramework/Actor.h"
#include "DemolitionCharacter.h"

APaperBlock::APaperBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bBeginDemolition = false;
	HP = 100.f;
	EleapsedTime = 0.0f;

	PrimaryActorTick.bCanEverTick = true;

	initBaseCollisionComponent(ObjectInitializer);
	initSprite(ObjectInitializer);
}

void APaperBlock::initBaseCollisionComponent(const FObjectInitializer& ObjectInitializer)
{
	BaseCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BaseBoxComponent");
	BaseCollisionComponent->InitBoxExtent(FVector(30.f, 30.f, 30.f));
	BaseCollisionComponent->SetCollisionProfileName("Custom");
	BaseCollisionComponent->SetCollisionObjectType(COLLISION_BLOCK);
	BaseCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BaseCollisionComponent->SetCollisionResponseToChannel(COLLISION_PLAYERMOVEMENT,ECollisionResponse::ECR_Ignore);
	BaseCollisionComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);

	BaseCollisionComponent->CanCharacterStepUpOn = ECB_No;
	BaseCollisionComponent->bCheckAsyncSceneOnMove = false;
	BaseCollisionComponent->bCanEverAffectNavigation = false;
	BaseCollisionComponent->SetLockedAxis(ELockedAxis::Y);
	//BaseCollisionComponent->chanel
	//BaseCollisionComponent->SetSimulatePhysics(true);
	//BaseCollisionComponent->SetEnableGravity(true);
	RootComponent = BaseCollisionComponent;
}

void APaperBlock::initSprite(const FObjectInitializer& ObjectInitializer)
{
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> DemolitionAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		FConstructorStatics()
			: DemolitionAnimationAsset(TEXT("/Game/Sprites/RunningAnimation.RunningAnimation"))
			, IdleAnimationAsset(TEXT("/Game/Sprites/IdleAnimation.IdleAnimation"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;
	IdleAnimation		= ConstructorStatics.IdleAnimationAsset.Get();
	DemolitionAnimation = ConstructorStatics.DemolitionAnimationAsset.Get();
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, "SpriteComponent");
	Sprite->AttachTo(RootComponent);
	GetSprite()->SetFlipbook(IdleAnimation);
}



void APaperBlock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	EleapsedTime += DeltaSeconds;

	UpdateMovement(DeltaSeconds);
	UpdateAnimation(DeltaSeconds);
}

void APaperBlock::OnAttacked_Implementation(float Damage)
{
	HP -= Damage;
	if (HP < 0)
	{
		OnBeginDemolition();
	}
}

void APaperBlock::OnBeginDemolition_Implementation()
{
	bBeginDemolition = true;
}

void APaperBlock::UpdateAnimation_Implementation(float DeltaSeconds)
{
	if (IsBeginDemolition())
	{
		if (GetSprite()->GetFlipbook() == IdleAnimation)
		{
			GetSprite()->SetFlipbook(DemolitionAnimation);
		}
	}
}

void APaperBlock::UpdateMovement_Implementation(float DeltaSeconds)
{
	if (IsBeginDemolition() == false)
	{
		FallingByNoPysics(DeltaSeconds);
	}
	else
	{
		//물리를 넣어야하나
	}
}

void APaperBlock::FallingByNoPysics(float DeltaSeconds)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z += DeltaSeconds * (EleapsedTime * GetWorld()->GetGravityZ());
	FHitResult HitResult;
	if (SetActorLocation(CurrentLocation, true, &HitResult) == false)
	{
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
}

float APaperBlock::getHP()
{
	return HP;
}

bool APaperBlock::IsBeginDemolition()
{
	return bBeginDemolition;
}

