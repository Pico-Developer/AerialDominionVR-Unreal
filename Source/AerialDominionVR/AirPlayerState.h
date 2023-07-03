// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Delegates/Delegate.h"
#include "AirPlayerState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FHealthChangeDelegate, AAirPlayerState, OnHealthChangeDelegate, float, CurrentHealth);

UCLASS()
class AERIALDOMINIONVR_API AAirPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	float Health = 100.f;

public:
	void AddHealth(float InputValue);

	void AirGameStart();

	UFUNCTION(BlueprintCallable)
	void ApplyCustomDamage(float InputValue);

public:
    UPROPERTY(BlueprintAssignable, Category = "Health")
    FHealthChangeDelegate OnHealthChangeDelegate;
	
};
