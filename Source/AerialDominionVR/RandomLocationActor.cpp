#include "RandomLocationActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/RandomStream.h"

ARandomLocationActor::ARandomLocationActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // 创建并设置Cube的StaticMesh组件
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
    }
    RootComponent = CubeMesh;
}

FVector ARandomLocationActor::GetRandomLocation()
{
    FVector RandomLocation;
    FRandomStream RandomStream;

    // 获取Cube的包围盒
    FBox Bounds = CubeMesh->Bounds.GetBox();

    RandomLocation = FMath::RandPointInBox(Bounds);

    // 生成随机位置，并判断是否在Cube的范围内
    //bool bInRange = false;
    //while (!bInRange)
    //{
    //    RandomLocation = FVector(RandomStream.FRandRange(Bounds.Min.X, Bounds.Max.X), RandomStream.FRandRange(Bounds.Min.Y, Bounds.Max.Y), RandomStream.FRandRange(Bounds.Min.Z, Bounds.Max.Z));
    //    bInRange = Bounds.IsInside(RandomLocation);
    //}

    return RandomLocation;
}