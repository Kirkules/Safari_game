// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "PhotoQuest.h"
#include "SafariPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SAFARI_API ASafariPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	
public:
    UPROPERTY(EditAnywhere, Category="PlayerState")
        TArray<UPhotoQuest*> Quests;
	
};
