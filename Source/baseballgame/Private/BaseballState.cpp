#include "BaseballState.h"

void ABaseballState::DecreaseChance()
{
	if (RemainingChance > 0)
	{
		RemainingChance--;
	}
}