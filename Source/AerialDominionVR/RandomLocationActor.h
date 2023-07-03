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

    FVector GetRandomLocation(); // 获取随机位置信息的函数

private:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* CubeMesh; // Cube的StaticMesh组件

};
