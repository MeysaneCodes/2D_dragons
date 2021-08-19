// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeAnyDamage);
	}


	// ...

	Health = MaxHealth;


	//Get owner who will have this component and recieve damage

	
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UHealthComponent::TakeAnyDamage(AActor* DamagedActor, float Damage,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor == GetOwner())
	{

		
		if (Health != 0 || Damage != 0)
		{
			Health = FMath::Clamp(Health - Damage , 0.0f, MaxHealth);
			UE_LOG(LogTemp, Warning, TEXT("Actor Took Hit , Remaining Health Is = %f"), Health);
		}else if (Health == 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("You are dead"))
		}

	}
	UE_LOG(LogTemp, Warning, TEXT("Hit!"))

	
}

