#include "Pinky.h"

APinky::APinky()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/AI/BT_Pinky.BT_Pinky"));
	if(BT.Succeeded())
		TreeAsset = BT.Object;
}
