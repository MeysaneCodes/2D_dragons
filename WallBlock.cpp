// Fill out your copyright notice in the Description page of Project Settings.


#include "WallBlock.h"

// Sets default values
AWallBlock::AWallBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	SetRootComponent(BoxTrigger);

}

// Called when the game starts or when spawned

