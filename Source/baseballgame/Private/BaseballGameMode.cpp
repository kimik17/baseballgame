#include "BaseballGameMode.h"
#include "BaseballState.h"

void ABaseballGameMode::GenerateRandomNumbers()
{
	int32 Count = 0;
	while (Count < 3)
	{
		int32 NewNumber = FMath::RandRange(1, 9);
		bool bIsDuplicate = false;
		
		for (int32 i = 0; i < Count; i++)
		{
			if (SecretNumbers[i] == NewNumber)
			{
				bIsDuplicate = true;
				break;
			}
		}
		
		if (!bIsDuplicate)
		{
			SecretNumbers[Count] = NewNumber;
			Count++;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("정답: %d %d %d"), SecretNumbers[0], SecretNumbers[1], SecretNumbers[2]);
}

bool ABaseballGameMode::IsInputValid(FString Input)
{
	// 1. 길이가 3글자인지 확인
	if (Input.Len() != 3) return false;

	// 2. 숫자인지 확인
	if (!Input.IsNumeric()) return false;

	// 3. 중복되는 숫자가 있는지 확인 (예: 112 같은 경우)
	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = i + 1; j < 3; j++)
		{
			if (Input[i] == Input[j]) return false;
		}
	}

	return true; // 모든 검사 통과!
}

FString ABaseballGameMode::CheckAnswer(FString PlayerInput)
{
	int32 Strikes = 0;
	int32 Balls = 0;

	for (int32 i = 0; i < 3; i++)
	{
		int32 InputNum = PlayerInput[i] - '0';

		if (InputNum == SecretNumbers[i])
		{
			Strikes++;
		}
		else
		{
			for (int32 j = 0; j < 3; j++)
			{
				if (i != j && InputNum == SecretNumbers[j])
				{
					Balls++;
					break;
				}
			}
		}
	}
	
	if (Strikes == 0 && Balls == 0)
	{
		return TEXT("OUT");
	}
	
	return FString::Printf(TEXT("%dS %dB"), Strikes, Balls);
}

void ABaseballGameMode::ProcessPlayerGuess(ABaseballState* PlayerState, FString PlayerInput)
{
	// 1. 유효성 검사 실패 시 기회를 깎지 않고 리턴
	if (!IsInputValid(PlayerInput))
	{
		UE_LOG(LogTemp, Warning, TEXT("잘못된 입력입니다. 다시 입력하세요."));
		return;
	}

	// 2. 판정 수행 (예: "3S 0B" 또는 "1S 2B" 등)
	FString Result = CheckAnswer(PlayerInput);
	UE_LOG(LogTemp, Log, TEXT("판정 결과: %s"), *Result);

	// 3. 기회 소진 (유효한 입력을 했으므로 기회 1 감소)
	if (PlayerState)
	{
		PlayerState->DecreaseChance();
	}

	// 4. 승리 판정 (3S를 달성했는가?)
	if (Result == TEXT("3S 0B"))
	{
		UE_LOG(LogTemp, Warning, TEXT("승리! 정답을 맞혔습니다!"));
		ResetGame();
		return;
	}

	// 5. 무승부 판정 (기회를 다 썼는데 정답자가 없다면?)
	// (여기서는 간단히 플레이어의 남은 기회가 0이 되었을 때를 가정합니다)
	if (PlayerState && PlayerState->GetRemainingChance() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("무승부! 기회를 모두 소모했습니다."));
		ResetGame();
	}
}

void ABaseballGameMode::ResetGame()
{
	UE_LOG(LogTemp, Warning, TEXT("게임을 리셋합니다. 새로운 정답을 생성합니다."));
    
	// 정답 새로 생성
	GenerateRandomNumbers();

	// TODO: 필요하다면 플레이어들의 기회도 다시 3회로 복구하는 로직 추가
}