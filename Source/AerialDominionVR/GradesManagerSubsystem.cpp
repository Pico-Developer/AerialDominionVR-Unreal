// Fill out your copyright notice in the Description page of Project Settings.


#include "GradesManagerSubsystem.h"
#include "AerialDominionVRGameModeBase.h"
#include "AirPlayerState.h"
#include "InvincibleActor.h"

UGradesManagerSubsystem::UGradesManagerSubsystem()
    : UGameInstanceSubsystem()
{

}

void UGradesManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UGradesManagerSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UGradesManagerSubsystem::AeialDominionGameBegin()
{
    ChangeGameStatus(EAerialGameStatus::GamePlaying);
    SetLogString(TEXT("Aeial Dominion Game Begin!"));
    KillEnemyCount = 0;
    CurrentScore = 0;
    // 获取PlayerState
    APlayerState* PlayerState = GetWorld()->GetFirstPlayerController()->GetPawn()->GetPlayerState();

    // 将PlayerState转换为AAirPlayerState类
    AAirPlayerState* AirPlayerState = Cast<AAirPlayerState>(PlayerState);

    // 如果转换成功，调用AirGameStart()函数
    if (AirPlayerState)
    {
        AirPlayerState->AirGameStart();
    }
    OnScoreChangeDelegate.Broadcast(CurrentScore);
    if (GetWorld()->GetTimerManager().IsTimerActive(ScoreTimerHandle))
    {
        GetWorld()->GetTimerManager().ClearTimer(ScoreTimerHandle);
    }
    GetWorld()->GetTimerManager().SetTimer(ScoreTimerHandle, [this]()
        {
            if (GameStatus == EAerialGameStatus::GamePlaying)
            {
                //
                SetLogString(TEXT("Add score per 60 seconds!"));
                AddScore(20);
            }
        }, ScoreInterval, true);
}



void UGradesManagerSubsystem::AddScore(const float NewScore)
{
    UE_LOG(LogTemp, Display, TEXT("Call add score: %f"), NewScore);
    CurrentScore += NewScore;
    UE_LOG(LogTemp, Display, TEXT("Current score: %f"), CurrentScore);
    OnScoreChangeDelegate.Broadcast(CurrentScore);
}

void UGradesManagerSubsystem::AeialDominionGameOver()
{
    ChangeGameStatus(EAerialGameStatus::GameOver);
    SetLogString(TEXT("Aeial Dominion Game Over!"));
    GetWorld()->GetTimerManager().ClearTimer(ScoreTimerHandle);
    AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

    // 将GameMode对象转换为AAerialDominionVRGameModeBase对象
    AAerialDominionVRGameModeBase* AerialDominionVRGameMode = Cast<AAerialDominionVRGameModeBase>(GameMode);

    // 调用WriteLeaderboardEntry()函数
    if (AerialDominionVRGameMode != nullptr)
    {
        AerialDominionVRGameMode->WriteLeaderboardEntry(CurrentScore);
        AerialDominionVRGameMode->AddCountAchievements();
        AerialDominionVRGameMode->CallGameEnd();
        if (CurrentScore >= 50)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("PicoWorld"));
        }
        if (CurrentScore >= 300)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("WildAviator"));
        }
        if (CurrentScore >= 1000)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("FlightGod"));
        }
    }
}

void UGradesManagerSubsystem::SetLogString(const FString& InNewLog)
{
    LogInfoCount++;
    if (LogInfoCount >= 40)
    {
        LogInfoCount = 0;
        TotalLog = FString();
    }
    TotalLog = InNewLog + TEXT("/n") + TotalLog;
    OnGameInstanceSubsystemLogChangedNotify.Broadcast(LogInfoCount);
}

void UGradesManagerSubsystem::ReceiveEnemyDeath()
{
    KillEnemyCount ++;
    if (KillEnemyCount >= 999)
    {
        AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
        AAerialDominionVRGameModeBase* AerialDominionVRGameMode = Cast<AAerialDominionVRGameModeBase>(GameMode);
        if (AerialDominionVRGameMode != nullptr)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("UltimateVictor"));
        }
    }
}

void UGradesManagerSubsystem::SetPropUseStatus(EPropType InPropType)
{
    switch (InPropType)
    {
    case EPropType::Heal:
        bPropAddHealth = true;
        break;

    case EPropType::Invincible:
        bPropProtect = true;
        break;

    case EPropType::Score:
        break;
        bPropAddScore = true;
    default:
        break;
    }
    CheckGameArchievementStates();
}

void UGradesManagerSubsystem::ChangeIninvibleActor(AInvincibleActor* NewInvincibeActor)
{
    if (InvincibeActor)
    {
        InvincibeActor->Destroy();
        InvincibeActor = NewInvincibeActor;
        InvincibeActor->SetLifeSpan(10.f);
    }
    else
    {
        InvincibeActor = NewInvincibeActor;
        InvincibeActor->SetLifeSpan(10.f);
    }
}

void UGradesManagerSubsystem::ChangeGameStatus(EAerialGameStatus NewGameStatus)
{
    GameStatus = NewGameStatus;
    GameStatusChangeCallback.Broadcast(GameStatus);
}

void UGradesManagerSubsystem::GamePause(bool bPause)
{
    if (GameStatus == EAerialGameStatus::GamePlaying)
    {
        if (bPause)
        {
            ChangeGameStatus(EAerialGameStatus::GamePause);
            return;
        }
    }
    if (GameStatus == EAerialGameStatus::GamePause)
    {
        if (!bPause)
        {
            ChangeGameStatus(EAerialGameStatus::GamePlaying);
            return;
        }
    }

}

void UGradesManagerSubsystem::CheckGameArchievementStates
()
{
    if (bPropAddHealth || bPropAddScore || bPropProtect)
    {
        AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
        AAerialDominionVRGameModeBase* AerialDominionVRGameMode = Cast<AAerialDominionVRGameModeBase>(GameMode);
        if (AerialDominionVRGameMode != nullptr)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("AirborneSpecialist"));
        }
    }
    if ((bPropAddHealth && bPropAddScore) || (bPropAddHealth && bPropProtect) || (bPropAddScore && bPropProtect))
    {
        AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
        AAerialDominionVRGameModeBase* AerialDominionVRGameMode = Cast<AAerialDominionVRGameModeBase>(GameMode);
        if (AerialDominionVRGameMode != nullptr)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("AerialAce"));
        }
    }
    if (bPropAddHealth && bPropAddScore && bPropProtect)
    {
        AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
        AAerialDominionVRGameModeBase* AerialDominionVRGameMode = Cast<AAerialDominionVRGameModeBase>(GameMode);
        if (AerialDominionVRGameMode != nullptr)
        {
            AerialDominionVRGameMode->UnLockTargetAchievements(FString("SkyHunter"));
        }
    }
}



