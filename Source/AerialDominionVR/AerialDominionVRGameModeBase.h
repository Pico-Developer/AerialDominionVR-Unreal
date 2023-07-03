// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AerialDominionVRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AERIALDOMINIONVR_API AAerialDominionVRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent)
	void WriteLeaderboardEntry(float InTotalScore);

	UFUNCTION(BlueprintImplementableEvent)
	void AddCountAchievements();

	UFUNCTION(BlueprintImplementableEvent)
	void UnLockTargetAchievements(const FString& InAchName);

	UFUNCTION(BlueprintImplementableEvent)
	void CallGameEnd();
	
};
