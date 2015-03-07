// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmBasePawnObject.h"
#include "Game/Object/Attr/DmObjectAttr.h"


ADmBasePawnObject::ADmBasePawnObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Attr = ObjectInitializer.CreateDefaultSubobject<UDmObjectAttr>(this, TEXT("Attr"));
}

void ADmBasePawnObject::OnTargeted_Implementation(const UDmObjectAttr * Attr)
{

}



