// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmPaperTargetObject.h"
#include "Game/ObjectAttr/DmObjectAttr.h"

ADmPaperTargetObject::ADmPaperTargetObject(const class FObjectInitializer& PCIP)
	:Super(PCIP)
{
	bIsActive = true;

	// Create the root SphereComponent to handle the pickup's collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	

	// Set the SphereComponent as the root component
	RootComponent = BaseCollisionComponent;


	Attr = PCIP.CreateDefaultSubobject<UDmObjectAttr>(this, TEXT("DmObjectAttr"));
}


void ADmPaperTargetObject::OnTargeted_Implementation(const UDmObjectAttr * pAttr)
{

}
