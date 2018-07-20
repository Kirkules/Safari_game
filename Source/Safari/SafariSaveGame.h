// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "PhotoInfo.h"
#include "SaveableActorComponent.h"
#include "SafariSaveGame.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAFARI_API USafariSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	
public:
    // Name of the current level to be reloaded
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        FString LevelName;
    
    // Photos that the player has taken and saved so far.
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        TArray<UPhotoInfo*> SavedPhotos;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        FDateTime SaveTime;
    
    // Name of this save-game.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        FString SaveSlotName;
    
    // Player's position and orientation in the world at the time of saving.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        FTransform PlayerTransform;
    
    // Player's current health
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        int PlayerCurrentHealth;
    
    // Player's current health
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        int PlayerMaxHealth;
    
    // List of where to spawn actors;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        TArray<FString> SavedActorNames;
    
    // List of types of actors to spawn; index is important!
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        TArray<UClass*> SavedActorClasses;
    
    // List of where to spawn actors
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Save Game")
        TArray<FTransform> SavedActorTransforms;
    
    UFUNCTION(BlueprintCallable, Category="Save Game")
        TArray<UClass*> GetSavedActorClasses();
    
    UFUNCTION(BlueprintCallable, Category="Save Game")
    TArray<FTransform> GetSavedActorTransforms();
    
    UFUNCTION(BlueprintCallable, Category="Save Game")
        TArray<UPhotoInfo*> GetSavedPhotos();
    
    UFUNCTION(BlueprintCallable, Category="Save Game")
    static TArray<AActor*> GetSaveableActors();
    
    USafariSaveGame();
};
