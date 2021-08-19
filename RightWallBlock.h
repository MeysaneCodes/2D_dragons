// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RightWallBlock.generated.h"

UCLASS()
class TEST01_API ARightWallBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARightWallBlock();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Box Trigger", meta=(AllowPrivateAccess="true"))
	UBoxComponent* BoxTrigger;

protected:

public:	
	

};
