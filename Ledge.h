// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaperFlipbookComponent.h"
#include "PaperSpriteActor.h"
#include "Ledge.generated.h"

/**
 * 
 */
UCLASS()
class TEST01_API ALedge : public APaperSpriteActor
{
	GENERATED_BODY()
	
	public:
	ALedge();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* Paper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Scene;


		

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaSeconds) override;
	private:

	 float SpawnLocation;
	
};
