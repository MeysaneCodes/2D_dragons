// Fill out your copyright notice in the Description page of Project Settings.


#include "RightWallBlock.h"

// Sets default values
ARightWallBlock::ARightWallBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(BoxTrigger);

}

