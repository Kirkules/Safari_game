// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "PhotoInfo.h"
#include "PhotoQuest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAFARI_API UPhotoQuest : public UObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PhotoQuest")
        FString QuestName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PhotoQuest")
    FString QuestDescription;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PhotoQuest")
        UStaticMesh* StaticMeshToDisplay;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PhotoQuest")
        USkeletalMesh* SkeletalMeshToDisplay;
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="PhotoQuest")
    bool QuestIsComplete(APlayerCharacter* PlayerCharacter);
    
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="PhotoQuest")
    bool UpdateProgress(APlayerCharacter* PlayerCharacter);
    
    TArray<UPhotoInfo*> QuestPhotos;
};
