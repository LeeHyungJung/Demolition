// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "LinkedListNode.h"
#include "Components/BoxComponent.h"


// Sets default values
ALinkedListNode::ALinkedListNode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCollisionComponent = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("BaseBoxComponent"));

	BaseCollisionComponent->SetCollisionProfileName("BlockAll");
	BaseCollisionComponent->SetSimulatePhysics(true);

	TriggerBox = CreateOptionalDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	TriggerBox->SetCollisionProfileName("OverlapAllDynamic");
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALinkedListNode::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALinkedListNode::OnOverlapEnd);

	RootComponent = BaseCollisionComponent;

	TriggerBox->AttachTo(RootComponent);

	ParentNode = nullptr;
	ChildNode = nullptr;

	NodeIndex = -1;
}
// Called when the game starts or when spawned
void ALinkedListNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALinkedListNode::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

ALinkedListNode * ALinkedListNode::GetChildNode()
{
	return ChildNode;
}

ALinkedListNode * ALinkedListNode::GetParentNode()
{
	return ParentNode;
}

void ALinkedListNode::GetChildList(TArray<ALinkedListNode *> & list)
{
	ALinkedListNode * tempChild = GetChildNode();
	while (tempChild != nullptr)
	{
		list.Add(tempChild);
	   tempChild = tempChild->GetChildNode();
	}
}

void ALinkedListNode::SetChildNode(ALinkedListNode * node)
{
	ChildNode = node;
}

void ALinkedListNode::SetParentNode(ALinkedListNode * node)
{
	ParentNode = node;
}

void ALinkedListNode::AddLast(ALinkedListNode * node)
{
	if (ChildNode != nullptr)
	{
		ChildNode->AddLast(node);
	}
	else
	{
		ChildNode = node;
		ChildNode->ParentNode = this;
		ChildNode->BaseCollisionComponent->SetSimulatePhysics(false);
	}
}

void ALinkedListNode::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ALinkedListNode * OtherNode = Cast<ALinkedListNode>(OtherActor);

	if (OtherNode != nullptr && (OtherNode != this) )
	{
		//충돌된 노드가 부모노드이다.
		if (ParentNode == OtherNode)
		{
			BaseCollisionComponent->SetSimulatePhysics(false);
			return;
		}

		//충돌된 노드가 자식노드이다.
		if (ChildNode == OtherNode) return;

		// 충돌된 노드가 헤드이거나 부모를 가지고 있으면 리턴한다.
		if (OtherNode->GetParentNode() != nullptr || OtherNode->bIsHead) return;

		if (CheckCanBeChild(OtherNode))
		{
			AddLast(OtherNode);

			
		}
	}
}

void ALinkedListNode::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALinkedListNode * OtherNode = Cast<ALinkedListNode>(OtherActor);

	if (OtherNode != nullptr && (OtherNode != this) && OtherNode->GetParentNode() == nullptr)
	{
		if (ParentNode == OtherNode)
		{
			ParentNode = nullptr;
			BaseCollisionComponent->SetSimulatePhysics(true);
		}
		else if (ChildNode == OtherNode)
		{
			ChildNode = nullptr;
		}
	}
}

bool ALinkedListNode::CheckCanBeChild(ALinkedListNode * node)
{
	return NodeIndex < node->NodeIndex ? true : false;
}

void ALinkedListNode::Destroyed()
{
	if (ParentNode != nullptr)
	{
		ParentNode->SetChildNode(nullptr);
	}

	if (ChildNode != nullptr)
	{
		ChildNode->SetParentNode(nullptr);
		ChildNode->BaseCollisionComponent->SetSimulatePhysics(true);
	}
}





