#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BaseballState.generated.h"

UCLASS()
class BASEBALLGAME_API ABaseballState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void DecreaseChance();
	
	int32 GetRemainingChance() const { return RemainingChance; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Baseball")
	int32 RemainingChance = 3;
};
