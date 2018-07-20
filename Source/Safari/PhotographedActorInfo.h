// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "PhotographedActorInfo.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAFARI_API UPhotographedActorInfo : public UObject
{
	GENERATED_BODY()
	
public:
    
    // The UE4 Unique Identifier of the actor in question
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FString ActorName;
    
    // Bounding box origin of the appearance of the actor in the image
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector BoundingBoxOrigin;
    
    // Bounding box extent of the appearance of the actor in the image
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector BoundingBoxExtent;
    
    // Kind of actor that was recorded
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        UClass* ActorClass;
    
    // Position on the screen of the actor when it was recorded
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector2D ScreenPosition;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector2D ScreenBoundingBoxTopLeft;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector2D ScreenBoundingBoxBottomRight;
    
    // World position of actor at time of photo, for context.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector WorldPosition;
    
    // Direction the actor was facing at the time of the photo, for context.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photographed Actor Info")
        FVector ForwardVector;
    
    float OnScreenRadius(AActor* TheActor);
};
