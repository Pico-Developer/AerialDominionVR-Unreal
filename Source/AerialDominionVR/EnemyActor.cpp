// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBullet.h"
#include "SamplePlayer.h"
#include "GradesManagerSubsystem.h"
#include "AriPropActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
    RootComponent = CollisionComponent;
    TargetLocation = FVector::ZeroVector;
    MoveSpeed = 100.f;

    float RandomValue = FMath::FRand();

    if (RandomValue <= 0.33f)
    {
        bIsLarge = false;
        Health = 1;
    }
    else
    {
        bIsLarge = true;
        Health = 3;
    }
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
    UGameInstance* GameInstance = GetWorld()->GetGameInstance();
    float DiffSpawn = UKismetMathLibrary::RandomFloatInRange(-0.5f, 0.5f);
    BulletSpawnTime += DiffSpawn;
    GradesManagerSubsystem = GameInstance->GetSubsystem<UGradesManagerSubsystem>();
    if (bIsLarge)
    {
        SetActorScale3D(FVector(2.f));
    }

	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GradesManagerSubsystem->GetGameStatus() == EAerialGameStatus::GamePause)
    {
        SetActorHiddenInGame(true);
        return;
    }
    if (GradesManagerSubsystem->GetGameStatus() == EAerialGameStatus::GameOver)
    {
        UE_LOG(LogTemp, Display, TEXT("GameOver::Destroy()"));
        Destroy();
        return;
    }
    SetActorHiddenInGame(false);
    float CurrentTime = GetWorld()->GetTimeSeconds();
    float TimeDiff = CurrentTime - LastSpawnTime;

    if (TimeDiff >= BulletSpawnTime)
    {
        SpawnEnemyBullet();
        LastSpawnTime = CurrentTime;
    }

    APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (MyPawn != nullptr)
    {
        ASamplePlayer* Pawn = Cast<ASamplePlayer>(MyPawn);
        TargetLocation = MyPawn->GetActorLocation();
        if(Pawn)
        {
            TargetLocation = Pawn->GetAirPlanceLocation();
        }
        // Do something with PawnLocation
    }

    // If the target location is a zero vector, do not move
    if (TargetLocation == FVector::ZeroVector)
    {
        return;
    }

    // Calculate the direction vector towards the target location
    FVector Direction = TargetLocation - GetActorLocation();
    Direction.Normalize();

    // Calculate the distance to move
    float Distance = MoveSpeed * DeltaTime;

    // Calculate the next location
    FVector NextLocation = GetActorLocation() + Direction * Distance;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    bool bHit = GetWorld()->SweepSingleByChannel(HitResult, GetActorLocation(), NextLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(CollisionComponent->GetScaledSphereRadius()), Params);
    if (bHit)
    {
        HitTargetActor(HitResult.GetActor());
    }

    // Move the Actor to the next location
    SetActorLocation(NextLocation);
    SetActorRotation((TargetLocation - GetActorLocation()).Rotation());


}

void AEnemyActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    //if (GradesManagerSubsystem)
    //{
    //    GradesManagerSubsystem->GameStatusChangeCallback.Remove(Handle);
    //}
}

void AEnemyActor::SetTargetLocationAndSpeed(FVector NewTargetLocation, float NewMoveSpeed)
{
    TargetLocation = NewTargetLocation;
    MoveSpeed = NewMoveSpeed;
}

void AEnemyActor::SpawnEnemyBullet()
{
    if (bFirstSpawn)
    {
        bFirstSpawn = false;
        return;
    }
    if (EnemyClass)
    {
        AEnemyBullet* EnemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(EnemyClass, GetActorLocation(), GetActorRotation());
        EnemyBullet->Shoot(GetActorRotation(), 600.f);

        //GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {

        //    }, 0.3f, false);
    }
}

void AEnemyActor::OnDamageReveived(int32 InputDamage)
{
    Health -= InputDamage;
    ChangeActorMaterial(Health);
    if (Health < 1)
    {
        if (bIsLarge)
        {
            GradesManagerSubsystem->AddScore(3);
        }
        else
        {
            GradesManagerSubsystem->AddScore(1);
        }
        float RandomNumber = FMath::FRandRange(0.f, 1.f);
        if (RandomNumber <= 0.2f)
        {
            UWorld* World = GetWorld();
            if (World)
            {
                AAirPropActor* PropActor = World->SpawnActor<AAirPropActor>(AAirPropActor::StaticClass(), GetActorLocation(), GetActorRotation());
            }
           
        }
        UE_LOG(LogTemp, Display, TEXT("OnDamageReveived::Destroy()"));
        EnemyDie();
    }
}

void AEnemyActor::OnGameStatusChange(EAerialGameStatus NewStatus)
{
    CurrentGameStatus = NewStatus;
}

