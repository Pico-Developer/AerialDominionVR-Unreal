#include "RandomLocationActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/RandomStream.h"

ARandomLocationActor::ARandomLocationActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // ����������Cube��StaticMesh���
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

    // ��ȡCube�İ�Χ��
    FBox Bounds = CubeMesh->Bounds.GetBox();

    RandomLocation = FMath::RandPointInBox(Bounds);

    // �������λ�ã����ж��Ƿ���Cube�ķ�Χ��
    //bool bInRange = false;
    //while (!bInRange)
    //{
    //    RandomLocation = FVector(RandomStream.FRandRange(Bounds.Min.X, Bounds.Max.X), RandomStream.FRandRange(Bounds.Min.Y, Bounds.Max.Y), RandomStream.FRandRange(Bounds.Min.Z, Bounds.Max.Z));
    //    bInRange = Bounds.IsInside(RandomLocation);
    //}

    return RandomLocation;
}