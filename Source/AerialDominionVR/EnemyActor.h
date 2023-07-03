// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GradesManagerSubsystem.h"
#include "EnemyActor.generated.h"

UCLASS()
class AERIALDOMINIONVR_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called when the actor is being destroyed
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(VisibleAnywhere, Category = "Enemy")
    class USphereComponent* CollisionComponent;


private:
    FVector TargetLocation;
    float MoveSpeed;
    bool bIsLarge;
    UGradesManagerSubsystem* GradesManagerSubsystem;
    FDelegateHandle Handle;
    bool bFirstSpawn = true;
    //FTimerHandle TimerHandle;
public:
	UFUNCTION(BlueprintCallable)
	void SetTargetLocationAndSpeed(FVector NewTargetLocation, float NewMoveSpeed);

    UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
    void HitTargetActor(AActor* TargetActor);

    void SpawnEnemyBullet(); // 生成EnemyBullet类的函数

    UFUNCTION(BlueprintCallable)
    void OnDamageReveived(int32 InputDamage);

    UFUNCTION(BlueprintCallable)
    bool GetIsLarge() {return bIsLarge;}

    void OnGameStatusChange(EAerialGameStatus NewStatus);

    UFUNCTION(BlueprintImplementableEvent)
    void ChangeActorMaterial(int32 InputHealth);

    UFUNCTION(BlueprintImplementableEvent)
    void EnemyDie();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BulletSpawnTime = 1.2f; // 生成EnemyBullet类的时间间隔



    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Health;

    float LastSpawnTime = 0.5f; // 上一次生成EnemyBullet类的时间

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<class AEnemyBullet> EnemyClass;


    EAerialGameStatus CurrentGameStatus = EAerialGameStatus::GamePlaying;





};
