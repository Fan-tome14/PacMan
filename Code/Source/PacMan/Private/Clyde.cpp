#include "Clyde.h"

AClyde::AClyde()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/AI/BT_Clyde.BT_Clyde"));
	if(BT.Succeeded())
		TreeAsset = BT.Object;
}
