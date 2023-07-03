// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GradesManagerSubsystem.h"
#include "EnemyManager.generated.h"

class AEnemyActor;

UCLASS()
class AERIALDOMINIONVR_API AEnemyManager : public AActor
{
    GENERATED_BODY()

public:
    AEnemyManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AEnemyActor> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    int32 WaveCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float EachN;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    int32 PresetCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    float TimeInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    FVector SpawnLocation;

    UPROPERTY(EditAnywhere)
    class ARandomLocationActor* RandomLocationActor; 

    UGradesManagerSubsystem* GradesManagerSubsystem;


protected:
    virtual void BeginPlay() override;

private:
    int32 CurrentWave;
    int32 EnemiesRemaining;
    float TimeSinceLastSpawn;

    bool bIsPause;

    void SpawnWave();
    void SpawnEnemy();

public:
    virtual void Tick(float DeltaTime) override;
    void AerialManagerRestart();

};
