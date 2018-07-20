// Fill out your copyright notice in the Description page of Project Settings.

#include "Safari.h"
#include "SaveableActorComponent.h"


// Sets default values for this component's properties
USaveableActorComponent::USaveableActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USaveableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USaveableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


AActor* USaveableActorComponent::Owner(){
    return GetOwner();
}
