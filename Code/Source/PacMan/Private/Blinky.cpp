#include "Blinky.h"

ABlinky::ABlinky()
{
	// Définir le BT spécifique pour Blinky
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/AI/BT_Blinky.BT_Blinky"));
	if(BT.Succeeded())
		TreeAsset = BT.Object;
}
