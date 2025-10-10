#include "Inky.h"

AInky::AInky()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/AI/BT_Inky.BT_Inky"));
	if(BT.Succeeded())
		TreeAsset = BT.Object;
}
