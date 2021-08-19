// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AI_Testing.generated.h"

/**
 * 
 */
UCLASS()
class TEST01_API AAI_Testing : public APaperCharacter
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere)
	AActor* Test;
	
	
};
