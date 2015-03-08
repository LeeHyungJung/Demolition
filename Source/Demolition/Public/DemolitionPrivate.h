// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

// This file is the private precompiled header for your game.
// You must include it first in each .cpp file.
//
// Place any includes here that are needed by the majority of your .cpp files

#include "EngineMinimal.h"
#include "AssertionMacros.h"
/*
#include "Game/Common/ConstID.h"


typedef ConstID DmObjectAttrID;
typedef ConstID DmObjectAttrValueID;
*/
DECLARE_LOG_CATEGORY_EXTERN(TEST, Log, All);

#define    COLLISION_PLAYERMOVEMENT    ECollisionChannel::ECC_GameTraceChannel1
#define    COLLISION_BLOCK			   ECollisionChannel::ECC_GameTraceChannel2