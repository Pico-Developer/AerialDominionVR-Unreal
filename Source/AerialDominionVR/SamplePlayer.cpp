// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePlayer.h"

// Sets default values
ASamplePlayer::ASamplePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASamplePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASamplePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASamplePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

