// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"
#include "RandomLocationActor.h"

AEnemyManager::AEnemyManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyManager::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARandomLocationActor::StaticClass(), FoundActors);
    if (FoundActors.Num() > 0)
    {
        RandomLocationActor = Cast<ARandomLocationActor>(FoundActors[0]);
    }
    CurrentWave = 0;
    EnemiesRemaining = 0;
    TimeSinceLastSpawn = TimeInterval;
    UGameInstance* GameInstance = GetWorld()->GetGameInstance();
    GradesManagerSubsystem = GameInstance->GetSubsystem<UGradesManagerSubsystem>();


}

void AEnemyManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GradesManagerSubsystem->GetGameStatus() == EAerialGameStatus::GamePause)
    {
        return;
    }
    if (GradesManagerSubsystem->GetGameStatus() == EAerialGameStatus::GameOver)
    {
        TimeSinceLastSpawn = TimeInterval - 0.2f;
        CurrentWave = 0;
        return;
    }
    TimeSinceLastSpawn += DeltaTime;

    if(TimeSinceLastSpawn >= TimeInterval)
    {
        SpawnWave();
    }


    //if (EnemiesRemaining <= 0 && TimeSinceLastSpawn >= TimeInterval)
    //{

    //}
    //else if (EnemiesRemaining > 0 && TimeSinceLastSpawn >= TimeInterval)
    //{
    //    SpawnEnemy();
    //}
}

void AEnemyManager::AerialManagerRestart()
{
    
}

void AEnemyManager::SpawnWave()
{
    CurrentWave++;
    EnemiesRemaining = EachN * CurrentWave + PresetCount;
    TimeSinceLastSpawn = 0.f;

    for(int i = 0; i < EnemiesRemaining; i++)
    {
        SpawnEnemy();
    }
    UE_LOG(LogTemp, Warning, TEXT("Spawning wave %d with %d enemies"), CurrentWave, EnemiesRemaining);
}

void AEnemyManager::SpawnEnemy()
{
    if (EnemyClass)
    {
        if (RandomLocationActor)
        {
            SpawnLocation = RandomLocationActor->GetRandomLocation();
        }
        AEnemyActor* EnemyActor = GetWorld()->SpawnActor<AEnemyActor>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
    }
}
