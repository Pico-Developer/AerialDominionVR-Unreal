// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlanePlayer.h"

// Sets default values
AAirPlanePlayer::AAirPlanePlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirPlanePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAirPlanePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

