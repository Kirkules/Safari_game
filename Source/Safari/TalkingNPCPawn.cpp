// Fill out your copyright notice in the Description page of Project Settings.

#include "Safari.h"
#include "TalkingNPCPawn.h"


// Sets default values
ATalkingNPCPawn::ATalkingNPCPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATalkingNPCPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATalkingNPCPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATalkingNPCPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

