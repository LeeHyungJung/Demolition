// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "LinkedWork.h"
#include "Worker.h"


// Sets default values
ALinkedWork::ALinkedWork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Properies = CreateOptionalDefaultSubobject<UDemolitionObjectProperty>(TEXT("DemolitionProperties"));
	
	setContent(this);

	BaseCollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));

	BaseCollisionComponent->SetCollisionProfileName("BlockAll");
	BaseCollisionComponent->SetSimulatePhysics(true);

	TriggerBox = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	TriggerBox->SetCollisionProfileName("OverlapAllDynamic");
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALinkedWork::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALinkedWork::OnOverlapEnd);

	RootComponent = BaseCollisionComponent;

	TriggerBox->AttachTo(RootComponent);

	ParentNode = nullptr;
	ChildNode = nullptr;

	static int32 index = 0;
	NodeIndex = index;
	++index;
}

// Called when the game starts or when spawned
void ALinkedWork::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALinkedWork::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ALinkedWork::CheckCanBeChild(ALinkedWork * node)
{
	return NodeIndex < node->NodeIndex ? true : false;
}

ALinkedWork * ALinkedWork::GetChildWork()
{
	CLinkedNode<ALinkedWork> * node = GetChildNode();

	if (node != nullptr)
	{
		return node->Content;
	}

	return nullptr;
}


void ALinkedWork::NotiyToRoot(ALinkedWork * node)
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


void ALinkedWork::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ALinkedWork * OtherNode = Cast<ALinkedWork>(OtherActor);

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

void ALinkedWork::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALinkedWork * OtherNode = Cast<ALinkedWork>(OtherActor);

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

void ALinkedWork::Destroyed()
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

int32 ALinkedWork::GetIndex()
{
	return NodeIndex;
}



