// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomLocationActor.generated.h"

UCLASS()
class AERIALDOMINIONVR_API ARandomLocationActor : public AActor
{
    GENERATED_BODY()

public:
    ARandomLocationActor();

    FVector GetRandomLocation(); // ��ȡ���λ����Ϣ�ĺ���

private:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* CubeMesh; // Cube��StaticMesh���

};
