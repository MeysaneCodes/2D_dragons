// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test01Character.h"

//#include <activation.h>
//#include <AudioClient.h>

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Test01/AI_Character.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// ATest01Character

ATest01Character::ATest01Character()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
	

	//For Trigger

	Player = GetOwner();


	//Health Setup

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}


void ATest01Character::DamageHandler()
{
	//LookingLeft
	if (GetCapsuleComponent()->GetComponentRotation().Yaw != 0.0f )
	{
		//Health Function
		FHitResult Hit;
		FVector EndPoint = FVector (GetActorLocation().X - WeaponRange , 0.0f,GetActorLocation().Z);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);


	
		if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params ))

		{
			DrawDebugLine(GetWorld(), GetActorLocation(), EndPoint, FColor::Black, false, 2.0f);

			TSubclassOf<UDamageType>Damage;

		
			//ApplyingDamage
		
			UGameplayStatics::ApplyDamage(Hit.GetActor(), DamageAmount, GetInstigatorController(), this, Damage);
		
		}
	}

	//LookingRight
	if (GetCapsuleComponent()->GetComponentRotation().Yaw == 0.0f )
	{
		//Health Function
		FHitResult Hit;
		FVector EndPoint = FVector (GetActorLocation().X + WeaponRange , 0.0f,GetActorLocation().Z);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		
		if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params ))

		{
			DrawDebugLine(GetWorld(), GetActorLocation(), EndPoint, FColor::Black, false, 2.0f);

			TSubclassOf<UDamageType>Damage;

		
			//ApplyingDamage
		
			UGameplayStatics::ApplyDamage(Hit.GetActor(), DamageAmount, GetInstigatorController(), this, Damage);
		
		}
	}
}

// it will be called when we hit the right mouse button
void ATest01Character::StepUpAttackAnimation()
{
	GetSprite()->SetLooping(false);
	IsAttacking = true;

	DamageHandler();
}


// To be called in UpdateAnimation
void ATest01Character::PlayAttackAnimation()
{
	IsAttacking = GetSprite()->SetFlipbook(Attack);
	
}




//////////////////////////////////////////////////////////////////////////
// Animation

void ATest01Character::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();

	
	if (GetVelocity().X != 0.0f && PlayerVelocity.Z == 0.0f  )
	{
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
		Running =  GetSprite()->SetFlipbook(RunningAnimation);
		
		
	} else if	( GetVelocity().IsZero() && GetSprite()->IsLooping())
	{
		GetSprite()->SetFlipbook(IdleAnimation);
		
		
	}
	
	else if (PlayerVelocity.Z > 0.0f  )
	{
		 GetSprite()->SetLooping(true);
		 GetSprite()->Play();
		 GetSprite()->SetFlipbook(JumpingAnimation);
	} else if (IsAttacking)
	{
		
		PlayAttackAnimation();

		
	}

	//Enable Looping Animation , After disabling it for Attacking animation to be played
	if (GetSprite()->IsPlaying() == false )
	{
		GetSprite()->SetLooping(true);
		GetSprite()->Play();
	}
	
}

void ATest01Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

		UpdateCharacter();
	

	
	
	

	
}



//////////////////////////////////////////////////////////////////////////
// Input

void ATest01Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATest01Character::MoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATest01Character::StepUpAttackAnimation);
	
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATest01Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATest01Character::TouchStopped);
}

void ATest01Character::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ATest01Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Jump();
	
}

void ATest01Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	StopJumping();

}

void ATest01Character::UpdateCharacter()
{
	
		// Update animation to match the motion
		UpdateAnimation();
	

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}






//const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();


// Are we moving or standing still?
/*UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f ) ? RunningAnimation : IdleAnimation;
	
if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
{
GetSprite()->SetFlipbook(DesiredAnimation);
}*/





void ATest01Character::BeginPlay()
{
	Super::BeginPlay();

	

}










//if (GetCapsuleComponent()->GetComponentRotation().Yaw != 0.0f )

	
// When looking at the left
		
//FVector Start = FVector(GetActorLocation().X, 0,GetActorLocation().Z);
//FVector EndPoint = FVector (GetActorLocation().X - WeaponRange , 0.0f,GetActorLocation().Z);
		
//DrawDebugLine(GetWorld(), Start , EndPoint , FColor::Black, false, 1.0);

//if(GetWorld()->LineTraceSingleByChannel(LefttHit, Start, EndPoint, ECollisionChannel::ECC_Pawn, Params))
		

/*if(GetCapsuleComponent()->GetComponentRotation().Yaw == 0.0f ) {

//When Looking at the right 

FVector EndPoint = FVector(GetActorLocation().X + WeaponRange, 0,GetActorLocation().Z) ;
		
FVector Start = FVector(GetActorLocation().X, 0,GetActorLocation().Z);
FCollisionQueryParams Params;

Params.AddIgnoredActor(this);
DrawDebugLine(GetWorld(), Start , EndPoint  , FColor::Red, false, 1.0);




if(GetWorld()->LineTraceSingleByChannel(RightHit, Start, EndPoint, ECollisionChannel::ECC_Pawn, Params))
{
UE_LOG(LogTemp, Warning, TEXT("Block DETECTED"));
UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *RightHit.GetActor()->GetName());
		

if ( RightHit.GetActor()->GetOwner() == Ia->GetOwner())
{
UE_LOG(LogTemp, Warning, TEXT("Health Class Called"));
//PlayerAI->ReceivingDamage();
UE_LOG(LogTemp, Warning, TEXT("Health Class Called"));
				
				
}
*/
		


		
	
/*if (GetWorld()->LineTraceSingleByChannel(Hit, Start, EndPoint, ECollisionChannel::ECC_Pawn, Params ))
{
UE_LOG(LogTemp, Warning, TEXT("Actor hit"));
}
*/
 