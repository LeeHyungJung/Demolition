
#include "Demolition.h"
#include "DemolitionObjectProperty.h"

UDemolitionObjectProperty::UDemolitionObjectProperty(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

{
	HP = FMath::Abs(FMath::Rand()%5);

	POWER = 1;
}

void UDemolitionObjectProperty::setHP(int input_hp)
{
	HP = input_hp;
}

int32 UDemolitionObjectProperty::getHP()
{
	return HP;
}
