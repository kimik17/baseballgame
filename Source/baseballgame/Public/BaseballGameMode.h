#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseballGameMode.generated.h"

class ABaseballState;

UCLASS()
class BASEBALLGAME_API ABaseballGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void GenerateRandomNumbers();
	bool IsInputValid(FString Input);
	FString CheckAnswer(FString PlayerInput);
	
	void ProcessPlayerGuess(ABaseballState* PlayerState, FString PlayerInput);
	
	void ResetGame();

private:
	int32 SecretNumbers[3];
	int32 RemainingChance = 3;
};
