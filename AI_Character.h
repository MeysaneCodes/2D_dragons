// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "RightWallBlock.h"
#include "Test01Character.h"
#include "WallBlock.h"
#include "Components/BoxComponent.h"
#include "HealthSystem/HealthComponent.h"

#include "AI_Character.generated.h"

/**
 * 
 */
UCLASS()
class TEST01_API AAI_Character : public APaperCharacter
{
	GENERATED_BODY()
	AAI_Character();
	
	void StartGuarding();

public:

	virtual void Tick(float DeltaSeconds) override;
	void DamageHandler();


	AActor* Owner;
	AController* Controller;
	


	// Wall Block



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wall Block Trigger", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AWallBlock> LeftWallClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wall Block Trigger", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ARightWallBlock> RightWallClass;

	AActor* LeftWallTrigger;

	AActor* RightWallTrigger;
	
	

	private:

	//Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Flipbook",  meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Running;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Flipbook",  meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Flipbook",  meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Flipbook",  meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Hurt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Flipbook",  meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* Dead;


	//Overlap Trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Box Trigger", meta=(AllowPrivateAccess="true"))
	UBoxComponent* LeftBoxTrigger;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Box Trigger", meta=(AllowPrivateAccess="true"))
	UBoxComponent* RightBoxTrigger;

	

	

	




	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health",  meta = (AllowPrivateAccess = "true"))
	UHealthComponent* Health;

	float GetCurrentHealth;

	float GetHealth();
	


	//Overlap Functions
	
	UFUNCTION()
	void OverLapRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	// Wall Overlap

	UFUNCTION()
	void LeftWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	UFUNCTION()
	void FinishOverlapWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	//RightWall

	



	

	
	UFUNCTION()
	void OverLapLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void FinishOverLapRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void FinishOverLapLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);




	//Animation Hurt
	UFUNCTION()
	void OnTakeDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	//References 
	ATest01Character* Player;




	
	protected:

	virtual void BeginPlay() override;
	void Guard();


	//Vectors References for Guard Movement 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guarding Positions",  meta = (AllowPrivateAccess = "true"))
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guarding Positions",  meta = (AllowPrivateAccess = "true"))
	FVector CurrentLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guarding Positions",  meta = (AllowPrivateAccess = "true"))
	FVector TeleportTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guarding Positions",  meta = (AllowPrivateAccess = "true"))
	float Range = 400.0;

	//Weapon Range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon",  meta = (AllowPrivateAccess = "true"))
	float WeaponRange = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon",  meta = (AllowPrivateAccess = "true"))
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon",  meta = (AllowPrivateAccess = "true"))
	float WeaponDamage = 20.0f;
	

	bool BackAttack;

	bool TriggerBackAttack();


	bool IsMovingRight;

	bool IsAttacking;
	
	bool IsBeingDamaged;
};
