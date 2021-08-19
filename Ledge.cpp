// Fill out your copyright notice in the Description page of Project Settings.


#include "Ledge.h"

#include "PaperFlipbookComponent.h"

ALedge::ALedge()
{
	Scene =  CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(Paper);

	Paper =  CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper"));
	SetRootComponent(Paper);

	
}

void ALedge::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetOwner()->GetActorLocation().X;
	UE_LOG(LogTemp, Warning, TEXT("Position is %f "), SpawnLocation);
	
	
}

void ALedge::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	

	const float NextLocation = SpawnLocation + 470.0f;
	const  float CurrentLocation = 	GetOwner()->GetActorLocation().X;


	FMath::FInterpTo(SpawnLocation, NextLocation, DeltaSeconds, 1.0f);
	if (CurrentLocation == NextLocation)
	{
		FMath::FInterpTo(CurrentLocation, SpawnLocation, DeltaSeconds, 1.0f);
	}

}

