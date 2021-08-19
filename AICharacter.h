// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Test01Character.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"

#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEST01_API AAICharacter : public ATest01Character
{
	GENERATED_BODY()
	AAICharacter();

	public:
	virtual void Tick(float DeltaSeconds) override;
	
	
	private:

	FVector SpawnLoaction;
	FVector TeleportLocation;
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere)
	float TeleportRange;
	float MoveDirection;
	bool IsMovingRight;

	//
	


	//void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void BeginPlay() override;
	
};
