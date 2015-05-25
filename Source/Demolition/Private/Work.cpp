// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "Work.h"
#include "Worker.h"
#include "DemolitionObjectProperty.h"


// Sets default values
AWork::AWork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	setContent(this);

	DmProperties = CreateOptionalDefaultSubobject<UDemolitionObjectProperty>(TEXT("DmProperties"), true);

	DmProperties->AttachTo(RootComponent);

	BaseCollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));

	BaseCollisionComponent->SetCollisionProfileName("BlockAll");

	BaseCollisionComponent->SetSimulatePhysics(true);

	TriggerBox = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	TriggerBox->SetCollisionProfileName("OverlapAllDynamic");

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWork::OnBeginOverlap);

	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AWork::OnOverlapEnd);

	RootComponent = BaseCollisionComponent;

	TriggerBox->AttachTo(RootComponent);

	ParentNode = nullptr;

	ChildNode = nullptr;

	

	static int32 index = 0;

	NodeIndex = index;

	++index;

}

// Called when the game starts or when spawned
void AWork::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AWork::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AWork::CheckCanBeChild(AWork * node)
{
	return NodeIndex < node->NodeIndex ? true : false;
}

AWork * AWork::GetChildWork()
{
	CLinkedNode<AWork> * node = GetChildNode();

	if (node != nullptr)
	{
		return node->Content;
	}

	return nullptr;
}


void AWork::NotiyToRoot(AWork * node)
{
	if (bHead && WorkOwner != nullptr)
	{
		WorkOwner->OnStackedWork(node);
	}
	else if (ParentNode != nullptr)
	{
		ParentNode->Content->NotiyToRoot(node);
	}
}


void AWork::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AWork * OtherNode = Cast<AWork>(OtherActor);

	if (OtherNode != nullptr && (OtherNode != this))
	{
		//�浹�� ��尡 �θ����̴�.
		if (ParentNode == OtherNode)
		{
			//BaseCollisionComponent->SetSimulatePhysics(false);
			return;
		}

		if (bHead)
		{
			NotiyToRoot(OtherNode);
		}

		//�浹�� ��尡 �ڽĳ���̴�.
		if (ChildNode == OtherNode) return;

		// �浹�� ��尡 ����̰ų� �θ� ������ ������ �����Ѵ�.
		if (OtherNode->GetParentNode() != nullptr || OtherNode->bHead) return;

		if (CheckCanBeChild(OtherNode))
		{
			AddLast(OtherNode);
			NotiyToRoot(OtherNode);
		}
	}
}

void AWork::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWork * OtherNode = Cast<AWork>(OtherActor);

	if (OtherNode != nullptr && (OtherNode != this) && OtherNode->GetParentNode() == nullptr)
	{
		if (ParentNode == OtherNode)
		{
			ParentNode = nullptr;
			//BaseCollisionComponent->SetSimulatePhysics(true);
		}
		else if (ChildNode == OtherNode)
		{
			ChildNode = nullptr;
		}
	}
}

void AWork::Destroyed()
{
	if (ParentNode != nullptr)
	{
		ParentNode->SetChildNode(nullptr);
	}

	if (ChildNode != nullptr)
	{
		ChildNode->SetParentNode(nullptr);
		ChildNode->Content->BaseCollisionComponent->SetSimulatePhysics(true);
	}
}

int32 AWork::GetIndex()
{
	return NodeIndex;
}

void AWork::OnBeWorked_Implementation(UDemolitionObjectProperty * Properties)
{
	if (this->DmProperties == nullptr) return;

	this->DmProperties->HP -= Properties->POWER;
}

UDemolitionObjectProperty * AWork::GetDmProperties()
{
	return DmProperties;
}

