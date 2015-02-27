// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmBaseObject.h"
#include "Game/Object/Attr/DmObjectAttr.h"

ADmBaseObject::ADmBaseObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Attr = ObjectInitializer.CreateDefaultSubobject<UDmObjectAttr>(this, TEXT("Attr"));
}


