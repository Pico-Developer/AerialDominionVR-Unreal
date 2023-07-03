// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlayerState.h"
#include "GradesManagerSubsystem.h"

void AAirPlayerState::AddHealth(float InputValue)
{
    Health += InputValue;
    if (Health >= 100)
    {
        Health = 100;
    }
    OnHealthChangeDelegate.Broadcast(Health);
}

void AAirPlayerState::AirGameStart()
{
    Health = 100.f;
    OnHealthChangeDelegate.Broadcast(Health);
}

void AAirPlayerState::ApplyCustomDamage(float InputValue)
{
    Health -= InputValue;
    if (Health <= 0)
    {
        Health = 0;
        UGameInstance* GameInstance = GetWorld()->GetGameInstance();
        UGradesManagerSubsystem* GradesManagerSubsystem = GameInstance->GetSubsystem<UGradesManagerSubsystem>();
        GradesManagerSubsystem->AeialDominionGameOver();
    }
    OnHealthChangeDelegate.Broadcast(Health);
}
