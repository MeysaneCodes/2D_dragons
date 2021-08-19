// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaperFlipbookComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "FlatLedge.generated.h"

UCLASS()
class TEST01_API AFlatLedge : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* SpriteToPLay;

	
	
	
public:	
	// Sets default values for this actor's properties
	AFlatLedge();

	//UFUNCTION()
	//void UpdateTimeLine (float OutPut);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* CurveFloat;	

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeLine", meta = (AllowPrivateAccess = "true"))
	UTimelineComponent* MovingLedge;

	FOnTimelineFloat UpdateFunctionFloat;
*/

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	int32 SetNewPlayRate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAcess = "true"))
	bool IsEnable;

	private:


	float SpawnLocation;

	

	
};
