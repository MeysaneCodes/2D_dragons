// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WallBlock.generated.h"

UCLASS()
class TEST01_API AWallBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallBlock();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Box Trigger", meta=(AllowPrivateAccess="true"))
	UBoxComponent* BoxTrigger;
protected:
	// Called when the game starts or when spawned

public:	
	// Called every frame

};
