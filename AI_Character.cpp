// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AAI_Character::AAI_Character()
{
	LeftBoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBoxTrigger"));
	LeftBoxTrigger->SetupAttachment(RootComponent);
	LeftBoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAI_Character::OverLapLeft);
	LeftBoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AAI_Character::FinishOverLapLeft );

	RightBoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RighttBoxTrigger"));
	RightBoxTrigger->SetupAttachment(RootComponent);
	RightBoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAI_Character::OverLapRight );
	RightBoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AAI_Character::FinishOverLapRight);



	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAI_Character::LeftWall);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAI_Character::FinishOverlapWall);


	Owner = GetCapsuleComponent()->GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &AAI_Character::OnTakeDamage);

	}

	
}



void AAI_Character::BeginPlay()
{
	Super::BeginPlay();

	IsBeingDamaged = false;

	// For Guarding
	IsMovingRight = FMath::RandBool();

	IsAttacking = false;

	//References
	SpawnLocation = GetActorLocation();

	
	Player = Cast<ATest01Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	//Reference for Wall Block
	if (!LeftWallTrigger && !LeftWallClass ){return;}
	LeftWallTrigger = Cast<AActor>(LeftWallClass->GetDefaultObject());

	if(!RightWallTrigger && !RightWallClass){return;}
	RightWallTrigger = Cast<AActor>(RightWallClass->GetDefaultObject());

	if (Health == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Health System is not working!"));
	}
}

void AAI_Character::Guard()
{
	
		if (IsMovingRight)
		{
			AddMovementInput(FVector(1.0f,0.0f,0.0f), 1.0);
			GetSprite()->SetRelativeScale3D(FVector(0.5f, 1.0f, 0.5f));
			GetSprite()->SetFlipbook(Running);
			GetSprite()->SetLooping(true);
			return;
		}

		if (!IsMovingRight)
		{
			AddMovementInput(FVector(1.0f,0.0f,0.0f), -1.0);
			GetSprite()->SetRelativeScale3D(FVector(-0.5f, 1.0f, 0.5f));
			GetSprite()->SetFlipbook(Running);
			GetSprite()->SetLooping(true);

		}
	
		
}


void AAI_Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(!IsAttacking && IsBeingDamaged == false && Health->Health > 0.0f)
	{
		Guard();
	}

	
	
	if(Health->Health == 0.0f)
	{
		GetSprite()->SetLooping(false);
		GetSprite()->SetFlipbook(Dead);
		
		//Destroy();
	
	}

	if(IsBeingDamaged == true && !GetSprite()->IsPlaying())
	{
		IsBeingDamaged = false;

		// Sync When the attack is finished to play the routine animation

		GetSprite()->SetLooping(true);
		GetSprite()->SetFlipbook(Attack);
		GetSprite()->Play();
		
	}
	
}

void AAI_Character::DamageHandler()
{
	// Damage Handler
	FHitResult Hit;
	FVector EndPointForward = FVector(GetActorLocation().X + WeaponRange, 0.0f, GetActorLocation().Z);

	FVector EndPointReverse = FVector(GetActorLocation().X - WeaponRange, 0.0f, GetActorLocation().Z);

	FVector EndPoint;


	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	float PlayerLocation = Player->GetActorLocation().X;
	float AILOcation = GetActorLocation().X;
	
	
	if (PlayerLocation >= AILOcation)
	{
		EndPoint = EndPointForward;
	}else if (PlayerLocation < AILOcation)
	{
		EndPoint = EndPointReverse;
	}

	
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params ))

	{
		DrawDebugLine(GetWorld(), GetActorLocation(), EndPoint, FColor::Black, false, 2.0f);

		TSubclassOf<UDamageType>Damage;

		
		//ApplyingDamage
		if (Hit.GetActor() == Player)
		{
			//FTimerHandle TimerHandle;
			//GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &AAI_Character::StartGuarding, 1.0f, true, false );
				UE_LOG(LogTemp, Warning, TEXT("Hit Registered"));
				UGameplayStatics::ApplyDamage(Hit.GetActor(), WeaponDamage, GetInstigatorController(), this, Damage);
				

		}
			
	}
}

void AAI_Character::OverLapRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		if (OtherActor && OtherActor != this && OtherActor == Player )
		{
			IsAttacking = true;
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Black ,TEXT("Overlaping Right Side now"));
			GetSprite()->Stop();


			if (TriggerBackAttack())
			{
				GetSprite()->SetRelativeScale3D(FVector(0.5f, 1.0f, 0.5f));
			}else if (!TriggerBackAttack())
			{
				GetSprite()->SetRelativeScale3D(FVector(-0.5f, 1.0f, 0.5f));
			}
		
			GetSprite()->SetFlipbook(Attack);
			GetSprite()->Play();



			FTimerHandle TimerHandle;
		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &AAI_Character::DamageHandler, FireRate, true, false );
		
		}
	
}

void AAI_Character::LeftWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	
	

	
	//Left Wall

	
	if ( OtherActor && OtherActor != this && OtherActor->GetOwner() == LeftWallTrigger->GetOwner() && IsMovingRight == false )
		{
			IsMovingRight = true;
			return;
	}
	
	

	// Right Wall
	if (OtherActor && OtherActor != this && OtherActor->GetOwner() == RightWallTrigger->GetOwner() && IsMovingRight == true)
	{
		IsMovingRight = false;
	}

}

void AAI_Character::FinishOverlapWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


	if (  true)
	{




	//UE_LOG(LogTemp, Warning, TEXT("Wall Finished"));

	}

	
}


void AAI_Character::OverLapLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && OtherActor != this && OtherActor == Player )
	{
		IsAttacking = true;
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Black ,TEXT("Overlaping Left Side now"));


		GetSprite()->Stop();



		// Check Whether the attack is in front or from back
		if (TriggerBackAttack())
		{
			GetSprite()->SetRelativeScale3D(FVector(0.5f, 1.0f, 0.5f));
		}else if (!TriggerBackAttack())
		{
			GetSprite()->SetRelativeScale3D(FVector(-0.5f, 1.0f, 0.5f));
		}
		
			GetSprite()->SetFlipbook(Attack);
			GetSprite()->Play();

			FTimerHandle TimerHandle;
		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &AAI_Character::DamageHandler, FireRate, true, false );
		

	}
}

void AAI_Character::FinishOverLapRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && OtherActor == Player )
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Black ,TEXT("Overlaping just Stopped"));
		IsAttacking = false;
	}
}

void AAI_Character::FinishOverLapLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && OtherActor == Player )
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Black ,TEXT("Overlaping just Stopped"));
		IsAttacking = false;

	}
}








bool AAI_Character::TriggerBackAttack()
{

	float PlayerLocation = Player->GetActorLocation().X;
	float AILOcation = GetActorLocation().X;
	
	if (PlayerLocation >= AILOcation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Back Attack trigger"))
		return BackAttack = true;	
	}if (PlayerLocation <= AILOcation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Back Attack trigger"))
		return BackAttack = false;
	}

	return  BackAttack;
}



float AAI_Character::GetHealth()
{
	if (Health)
	{
		GetCurrentHealth = Health->Health;
		UE_LOG(LogTemp, Warning, TEXT("Current AI Health is %f"), GetCurrentHealth);
	}

	return  GetCurrentHealth;
	
}

void AAI_Character::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor == this)
	{
		IsBeingDamaged = true;
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red ,TEXT("Called"));
		GetSprite()->Stop();

		GetSprite()->SetFlipbook(Hurt);
		GetSprite()->SetLooping(false);
		GetSprite()->Play();

		float Playback = GetSprite()->GetPlaybackPosition();
		float length =  GetSprite()->GetFlipbookLength();
		
		if(GetSprite()->IsPlaying())
		{
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red ,TEXT("Playing"));
		}
		

		

		/*
		while (IsBeingDamaged)
		{
			
			GetSprite()->Stop();
			
			GetSprite()->SetFlipbook(Hurt);
			GetSprite()->SetLooping(false);
			GetSprite()->Play();
			

			while (IsBeingDamaged  )
			{
				
				UE_LOG(LogTemp, Warning, TEXT("Playing"));

			}

			*/
		
		

		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red ,TEXT("Broke"));


	}


	
}