// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
    RootComponent = CollisionComponent;

}

void AEnemyBullet::Shoot(FRotator Direction, float Speed)
{
    Velocity = Direction.Vector() * Speed;
}

void AEnemyBullet::OnGameStatusChange(EAerialGameStatus NewStatus)
{
    CurrentGameStatus = NewStatus;
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
    Velocity = GetActorForwardVector() * InitialSpeed;
    //SetLifeSpan(BulletTimeSpan);
    UGameInstance* GameInstance = GetWorld()->GetGameInstance();

    GradesManagerSubsystem = GameInstance->GetSubsystem<UGradesManagerSubsystem>();
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (GradesManagerSubsystem->GetGameStatus() == EAerialGameStatus::GamePause)
    {
        SetLifeSpan(BulletTimeSpan);
        SetActorHiddenInGame(true);
        return;
    }
    if (GradesManagerSubsystem->GetGameStatus() == EAerialGameStatus::GameOver)
    {
        Destroy();
        return;
    }
    SetActorHiddenInGame(false);
    float Distance = DeltaTime * Velocity.Size();

    FVector MoveDirection = Velocity.GetSafeNormal();


    FVector NewLocation = GetActorLocation() + MoveDirection * Distance;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    bool bHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), NewLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(CollisionComponent->GetScaledSphereRadius()), Params);
    if (bHit)
    {
        HitTargetActor(HitResult.GetActor());
    }
    SetActorLocation(NewLocation);
}

void AEnemyBullet::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    //if (GradesManagerSubsystem)
    //{
    //    GradesManagerSubsystem->GameStatusChangeCallback.Remove(Handle);
    //}
}

