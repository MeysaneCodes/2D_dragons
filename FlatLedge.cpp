// Fill out your copyright notice in the Description page of Project Settings.


#include "FlatLedge.h"

#include "Curves/CurveVector.h"


// Sets default values
AFlatLedge::AFlatLedge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);

	SpriteToPLay = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite "));
	SpriteToPLay->SetupAttachment(SceneComponent);
	
	
}


// Called when the game starts or when spawned
void AFlatLedge::BeginPlay()
{
	Super::BeginPlay();

/*	
	UpdateFunctionFloat.BindDynamic(this, &AFlatLedge::UpdateTimeLine);
	
	if (CurveFloat)
	{
		if (MovingLedge)
		{
			MovingLedge->AddInterpFloat(CurveFloat, UpdateFunctionFloat);

		}
	
		
	}
	
	*/

}

// Called every frame
void AFlatLedge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
	


}

int32 AFlatLedge::SetNewPlayRate()
{
	UE_LOG(LogTemp, Warning, TEXT("Testing"))
	return 25;
}

/*
void AFlatLedge::UpdateTimeLine(float OutPut)
{

	//This is output that will be used for the track
	
	UE_LOG(LogTemp, Warning, TEXT("Executed") );

	FVector Location = FVector(OutPut, GetActorLocation().Y, GetActorLocation().Z);
	UE_LOG(LogTemp, Warning, TEXT("Output is %s"), *Location.ToString() );

	SetActorLocation(Location);	
}
*/
