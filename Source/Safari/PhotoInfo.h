// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineUtils.h"
#include "UObject/NoExportTypes.h"
#include "PhotoInfoRecordComponent.h"
#include "PhotographedActorInfo.h"
#include "PhotoInfo.generated.h"


UCLASS(Blueprintable)
class SAFARI_API UPhotoInfo : public UObject
{
	GENERATED_BODY()

public:
    
    // The visual image of the photo
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photo Info")
        UTexture2D* Photo;
    
    // The thing that was centered in the frame (first raycast hit from crosshair center)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photo Info")
        class UPhotographedActorInfo* CenteredActor;
    
    // List of actors that appeared in the photograph, with info. about how they appeared
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photo Info")
        TArray<UPhotographedActorInfo*> PhotographedActors;
    
    
    // The view projection matrix when the photo was taken.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Photo Info")
        FMatrix ViewProjectionMatrix;
    
    // The view projection matrix when the photo was taken.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Photo Info")
        FText PhotoName;
    
    // The location of the camera when the photo was taken, for context.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Photo Info")
        FVector CameraLocation;
    
    // The view rectangle when the photo was taken.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Photo Info")
        FVector2D ScreenSize;
    
    // The frustum that the image was taken from/with
    FConvexVolume PhotoViewFrustum;
    
    // Count actors of a given type in the photo
    UFUNCTION(BlueprintCallable, Category="Photo Info")
        int32 CountActors(const UClass* Type);
    
    TArray<UPhotographedActorInfo*> GetActorsInFrustum(const AActor* ContextActor, const FConvexVolume Frustum);
    static UPhotographedActorInfo* BuildObjectInfo(const AActor* TheObject, const FConvexVolume Frustum);
    
    /*
     *  
     */
};
