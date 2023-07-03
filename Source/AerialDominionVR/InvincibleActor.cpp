// Fill out your copyright notice in the Description page of Project Settings.


#include "InvincibleActor.h"

// Sets default values
AInvincibleActor::AInvincibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    RootComponent = SceneComp;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    StaticMeshComp->AttachToComponent(SceneComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AInvincibleActor::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle TimerHandle;
 //   GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
 //       {
 //           if (this)
 //           {
 //               UE_LOG(LogTemp, Display, TEXT("AInvincibleActor::Destroy()"));
 //               Destroy();
 //           }
 //       }, 10, true);
	
}

// Called every frame
void AInvincibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

