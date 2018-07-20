// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "PhotoInfo.h"
#include "PhotographedActorInfo.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventPhotoCaptured); // so we can do stuff in blueprints when photo is captured
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventPhotoCaptureFailed); // so we can do stuff in case photo couldn't be taken; RetVal is context

UCLASS()
class SAFARI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
    UTexture2D* EmptyPhotoTexture;
    
    // The LocalPlayer object for getting the view frustum and stuff
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        ULocalPlayer* LocalPlayer;
    
    // Photo Captured Event for Blueprints
    UPROPERTY(BlueprintAssignable, Category="Event Dispatchers")
        FEventPhotoCaptured EventPhotoCaptured;
    
    UPROPERTY(BlueprintAssignable, Category="Event Dispatchers")
        FEventPhotoCaptureFailed EventPhotoCaptureFailed;
    
    // The SceneCapture Object that is acting as the camera
    APlayerCameraManager* CameraManager;
        ASceneCapture2D* SceneCapture;
    
    // The Texture that gets the player's camera shot.
    UPROPERTY(EditDefaultsOnly, Category="PlayerCharacter Properties")
        UCanvasRenderTarget2D* CameraTextureRenderTarget;
    
    // The Dynamic Material Instance that is going to make our textures for us
    UPROPERTY(EditDefaultsOnly, Category="PlayerCharacter Properties")
        UMaterial* CameraMaterial;
    
    // The Character movement Component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        UCharacterMovementComponent* CharacterMovementComponent;
    
    // Player's photos taken
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        TArray<UPhotoInfo*> Photos;
    
    // Slowdown factor of zoomed looking
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        float ZoomedLookSpeedFactor;
    
    // Jumping Speed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        float JumpSpeed;
    
    // Walking Speed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        float WalkSpeed;
    
    // Running Speed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        float RunSpeed;
    
    // Time Since Last Photo (up to 4 seconds)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        FDateTime TimeOfLastPhoto;
    
    // Lag between taking photos
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        FTimespan PhotoTakingLag;
    
    // Walking Disabled? (Zoomed, stunned, etc.)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        bool WalkingDisabled;
    
    // Run button pressed?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        bool RunPressed;
    
    // Is the player camera currently zoomed in?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        bool CameraZoomed;
    
    // How many photos is the player allowed to take?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        int32 MaxNumberOfPhotos;

    // Player's maximum health.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        int32 MaxHealth;
    
    // Player's current health.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        int32 CurrentHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerCharacter")
        float FallDamageRate;
    
    

    
    // Damage taken from falling
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Damage Handling", meta=(Keywords="fall damage fraction health"))
        float FallDamageFraction(const float TimeInAir, const float HarmlessTime, const float DeathTime);
    
    // make the character turn left/right
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="turn input move"))
        void OnTurn(float AxisValue);
    
    // make character look up/down
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="look lookup input move"))
        void OnLookUp(float AxisValue);
    
    // move forward OR backward
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="sprint run jog input move"))
        void OnMoveForward(float AxisValue);
    
    // move left or right
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="sprint run jog input move"))
        void OnMoveRight(float AxisValue);
    
    // toggle running state on
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="sprint run jog input move"))
        void OnRunPressed();
    
    // toggle running state off
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="sprint run jog input move"))
        void OnRunReleased();
    
    // jump!?
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="jump input move"))
        void Jump();
    
    // Primary Action (take photos/pick stuff up)
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter Input Handling", meta=(Keywords="take photo primary action input"))
        void OnPrimaryAction();
    
    // Take a photo and record all PhotographableActors
    void NormalTakePhoto();
    
    // use actor information to build up information about the actor's state at the moment of being photographed
    //UPhotographedActorInfo* BuildActorInfo(const APhotographableActor* Actor, const FConvexVolume Frustum);
    UPhotographedActorInfo* BuildObjectInfo(const AActor* TheObject, const FConvexVolume Frustum);
	
    
    // Has the player taken a photo in the last x seconds?
    UFUNCTION(BlueprintCallable, Category="PlayerCharacter", meta=(Keywords="photo recent recently taken"))
        bool PhotoTakenRecently();

};
