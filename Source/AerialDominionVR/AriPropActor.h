// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AriPropActor.generated.h"

UENUM(BlueprintType)
enum class EPropType : uint8
{
    Heal UMETA(DisplayName = "Heal"),          
    Invincible UMETA(DisplayName = "Invincible"),  
    Score UMETA(DisplayName = "Score"),       
};

UCLASS()
class AERIALDOMINIONVR_API AAirPropActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAirPropActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop")
    EPropType PropType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop")
    float PropValue;

    UFUNCTION(BlueprintCallable, Category = "Prop")
    void Use();

private:
    // Billboard component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UBillboardComponent* BillboardComponent;

    void DoHeal();

    void DoInvincible();

    void DoAddScore();

    class UGradesManagerSubsystem* GradesManagerSubsystem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
