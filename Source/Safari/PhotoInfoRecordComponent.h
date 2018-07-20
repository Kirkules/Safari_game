// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhotographedActorInfo.h"
#include "PhotoInfoRecordComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAFARI_API UPhotoInfoRecordComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhotoInfoRecordComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category="PhotoInfoRecord Component")
    UPhotographedActorInfo* GetPhotographedActorInfo(FVector2D ScreenSize);
	
    UPROPERTY(EditAnywhere, Category="PhotoInfoRecord Component")
    UBoxComponent* BoundsComponent;
    
};
