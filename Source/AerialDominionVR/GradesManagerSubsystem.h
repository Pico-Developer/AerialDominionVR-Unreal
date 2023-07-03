// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Delegates/Delegate.h"
#include "AriPropActor.h"
#include "GradesManagerSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FGameInstanceSubsystemLogChangedNotify, UGradesManagerSubsystem, OnGameInstanceSubsystemLogChangedNotify, int, LogCount);

UENUM(BlueprintType)
enum class EAerialGameStatus : uint8
{
    Unknow,
    GameStart,
    GamePause,
    GamePlaying,
    GameOver
};

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FScoreChangeDelegate, UGradesManagerSubsystem, OnScoreChangeDelegate, float, Score);

DECLARE_MULTICAST_DELEGATE_OneParam(FGameStatusChange, EAerialGameStatus /*GameStatus*/);

UCLASS()
class AERIALDOMINIONVR_API UGradesManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    UGradesManagerSubsystem();

    // Begin USubsytem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End




private:
    float CurrentScore;
    EAerialGameStatus GameStatus = EAerialGameStatus::GameOver;
    int32 KillEnemyCount = 0;

	UPROPERTY()
	FString TotalLog;


public:
    UFUNCTION(BlueprintCallable)
    void AddScore(const float NewScore);

    UFUNCTION(BlueprintCallable)
    void CheckGameArchievementStates();

    UFUNCTION(BlueprintImplementableEvent)
    void UnlockArchievement();


    UFUNCTION(BlueprintCallable)
    void ChangeGameStatus(EAerialGameStatus NewGameStatus);

    UFUNCTION(BlueprintCallable)
    EAerialGameStatus GetGameStatus(){ return GameStatus;}

    UFUNCTION(BlueprintCallable)
    void GamePause(bool bPause);

    UFUNCTION(BlueprintCallable)
    void AeialDominionGameBegin();

    UFUNCTION(BlueprintCallable)
    void AeialDominionGameOver();

	UFUNCTION(BlueprintCallable)
	void SetLogString(const FString& InNewLog);

	UFUNCTION(BlueprintCallable)
	FString GetTotalLog(){return TotalLog;}

    void ReceiveEnemyDeath();

    void SetPropUseStatus(EPropType InPropType);



private:
    FTimerHandle ScoreTimerHandle;  // 计时器句柄
    float ScoreInterval = 60.0f;    // 每隔60秒增加一次分数
    int32 LogInfoCount;
    class AInvincibleActor* InvincibeActor;

    bool bPropAddHealth = false;
    bool bPropAddScore = false;
    bool bPropProtect = false;

public:
    UPROPERTY(BlueprintAssignable, Category = "Score")
    FScoreChangeDelegate OnScoreChangeDelegate;

    UPROPERTY(BlueprintAssignable)
    FGameInstanceSubsystemLogChangedNotify OnGameInstanceSubsystemLogChangedNotify;

    FGameStatusChange GameStatusChangeCallback;

    void ChangeIninvibleActor(AInvincibleActor* NewInvincibeActor);
	
};
