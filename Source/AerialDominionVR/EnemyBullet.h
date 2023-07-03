// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GradesManagerSubsystem.h"
#include "EnemyBullet.generated.h"

UCLASS()
class AERIALDOMINIONVR_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:    
    AEnemyBullet();
    
    UFUNCTION(BlueprintCallable, Category = "Bullet")
    void Shoot(FRotator Direction, float Speed);

    void OnGameStatusChange(EAerialGameStatus NewStatus);
    
protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    // Called when the actor is being destroyed
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintImplementableEvent, Category = "Bullet")
    void HitTargetActor(AActor* TargetActor);

    UPROPERTY(EditAnywhere, Category = "Bullet")
    float InitialSpeed = 1000.f;

    UPROPERTY(VisibleAnywhere, Category = "Bullet")
    FVector Velocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
    class USphereComponent* CollisionComponent;

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float BulletTimeSpan;

    EAerialGameStatus CurrentGameStatus = EAerialGameStatus::GamePlaying;

private:
    UGradesManagerSubsystem* GradesManagerSubsystem;

    FDelegateHandle Handle;
    


};
