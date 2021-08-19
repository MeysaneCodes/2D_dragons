// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"


AAICharacter::AAICharacter()
{
	
}

void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
   CurrentLocation = GetActorLocation();

	if (CurrentLocation == TeleportLocation)
	{
		
		IsMovingRight = false;
		AddMovementInput(FVector(1,0,0), 1.0f);

	}else if(CurrentLocation == SpawnLoaction ) {
		IsMovingRight = true;
		AddMovementInput(FVector(1,0,0), -1.0f);

	}
	*/
	
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	/*
	SpawnLoaction = GetActorLocation();
	TeleportLocation = FVector(SpawnLoaction.X + TeleportRange, SpawnLoaction.Y, SpawnLoaction.Z);
	*/
}
