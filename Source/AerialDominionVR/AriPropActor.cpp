// Fill out your copyright notice in the Description page of Project Settings.


#include "AriPropActor.h"
#include "GradesManagerSubsystem.h"
#include "AirPlayerState.h"
#include "SamplePlayer.h"
#include "Components/BillboardComponent.h"
#include "Engine/Texture2D.h"
#include <Kismet/GameplayStatics.h>
#include "InvincibleActor.h"

// Sets default values
AAirPropActor::AAirPropActor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create the billboard component
    BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
    RootComponent = BillboardComponent;
    BillboardComponent->SetHiddenInGame(false);
    BillboardComponent->SetWorldScale3D(FVector(0.3f));

}

void AAirPropActor::Use()
{
    switch (PropType)
    {
    case EPropType::Heal:
        DoHeal();
        break;

    case EPropType::Invincible:
        DoInvincible();
        break;

    case EPropType::Score:
        DoAddScore();
        break;

    default:
        break;
    }
    GradesManagerSubsystem->SetPropUseStatus(PropType);
}

void AAirPropActor::DoHeal()
{
    UE_LOG(LogTemp, Display, TEXT("AAriPropActor::DoHeal()"));
    APawn* CurrentPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (CurrentPawn)
    {
        AAirPlayerState* PlayerState = CurrentPawn->GetPlayerState<AAirPlayerState>();
        if (PlayerState)
        {
            UE_LOG(LogTemp, Display, TEXT("Prop add health successed"));
            PlayerState->AddHealth(10.f);
        }
    }
}

void AAirPropActor::DoInvincible()
{
    if (APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn())
    {
        if (ASamplePlayer* SamplePawn = Cast<ASamplePlayer>(Pawn))
        {
            FVector PlaneLocation = SamplePawn->GetAirPlanceLocation();
            UClass* BlueprintVar = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprints/BP_InvincibleActorComp.BP_InvincibleActorComp_C'"));
            if (BlueprintVar != nullptr)
            {
                AActor* Actor = GetWorld()->SpawnActor<AActor>(BlueprintVar);
                if (Actor)
                {
                    AInvincibleActor* InvincibleActor = Cast<AInvincibleActor>(Actor);
                    if (InvincibleActor)
                    {
                        GradesManagerSubsystem->ChangeIninvibleActor(InvincibleActor);
                        InvincibleActor->AttachAndInvincibleTarget();
                    }
                }
            }
        }
    }
}

void AAirPropActor::DoAddScore()
{
    UE_LOG(LogTemp, Display, TEXT("AAriPropActor::DoAddScore()"));
	if (GradesManagerSubsystem)
	{
        UE_LOG(LogTemp, Display, TEXT("AAriPropActor::DoAddScore()"));
		GradesManagerSubsystem->AddScore(10);
	}
}

// Called when the game starts or when spawned
void AAirPropActor::BeginPlay()
{
	Super::BeginPlay();
    UGameInstance* GameInstance = GetWorld()->GetGameInstance();

    GradesManagerSubsystem = GameInstance->GetSubsystem<UGradesManagerSubsystem>();
    GradesManagerSubsystem->AddScore(2);
	PropType = static_cast<EPropType>(FMath::RandRange(0, static_cast<int32>(EPropType::Score)));
    SetLifeSpan(2.f);
    FString TextureAdr;
    switch (PropType)
    {
    case EPropType::Heal:
        TextureAdr = TEXT("/Game/Textures/92.92");
        break;

    case EPropType::Invincible:
        TextureAdr = TEXT("/Game/Textures/91.91");
        break;

    case EPropType::Score:
        TextureAdr = TEXT("/Game/Textures/93.93");
        break;

    default:
        break;
    }
    UTexture2D* Texture = LoadObject<UTexture2D>(this, *TextureAdr);
    if (Texture)
    {
        BillboardComponent->SetSprite(Texture);
    }
    Use();
}

// Called every frame
void AAirPropActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


