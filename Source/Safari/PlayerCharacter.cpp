// Fill out your copyright notice in the Description page of Project Settings.


#include "Safari.h"
#include "PhotographedActorInfo.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // Setup defaults
    ZoomedLookSpeedFactor = 0.4f;
    JumpSpeed = 400.0f;
    WalkSpeed = 350.0f;
    RunSpeed = 750.0f;
    MaxHealth = 100;
    CurrentHealth = MaxHealth;
    FallDamageRate = 2.0f;
    
    WalkingDisabled = false;
    RunPressed = false;
    CameraZoomed = false;
    
    MaxNumberOfPhotos = 64;
    
    PhotoTakingLag = FTimespan(0, 0, 0, 1, 500, 0); // 1.5 seconds until you're allowed to take a photo again!
    TimeOfLastPhoto = FDateTime::MinValue();
    
    // Set starting movement speed to walkspeed
    CharacterMovementComponent = (UCharacterMovementComponent*)GetMovementComponent();
    CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    
    // Get the player camera manager
    for (TActorIterator<APlayerCameraManager> it(GetWorld()); it; ++it){
        CameraManager = *it;
    }
    
    
    // get the scene capture 2d actor and force it to follow this
    for (TActorIterator<ASceneCapture2D> it(GetWorld()); it; ++it){
        if ((*it)->GetName() == "CameraCaptureForPlayer"){
            SceneCapture = *it;
        }
    }
    
    // Find the material for rendering what the camera is looking at. Might get rid of this.
    for (TObjectIterator<UMaterial> it; it; ++it){
        if (UKismetSystemLibrary::GetDisplayName(*it) == "CameraRenderTargetMaterial"){
            CameraMaterial = *it;
        }
    }
    
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    // make photo-taking scene-capture track the player camera
    if (/*CameraZoomed && */ CameraManager && SceneCapture){
        SceneCapture->SetActorTransform(CameraManager->GetActorTransform());
        (SceneCapture->FindComponentByClass<USceneCaptureComponent2D>())->FOVAngle = CameraManager->GetFOVAngle();
    }
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::OnTurn);
    PlayerInputComponent->BindAxis("Look Up", this, &APlayerCharacter::OnLookUp);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::OnRunPressed);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::OnRunReleased);
    PlayerInputComponent->BindAxis("Move Right", this, &APlayerCharacter::OnMoveRight);
    PlayerInputComponent->BindAxis("Move Forward", this, &APlayerCharacter::OnMoveForward);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Primary Action", IE_Pressed, this, &APlayerCharacter::OnPrimaryAction);
}

void APlayerCharacter::OnTurn(float AxisValue){
    // scale look speed when zoomed in
    if (CameraZoomed){
        AxisValue = AxisValue*ZoomedLookSpeedFactor;
    }
    AddControllerYawInput(AxisValue);
}

void APlayerCharacter::OnLookUp(float AxisValue){
    // scale look speed when zoomed in
    if (CameraZoomed){
        AxisValue = AxisValue*ZoomedLookSpeedFactor;
    }
    AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::OnRunPressed(){
    
    CharacterMovementComponent->MaxWalkSpeed = RunSpeed;
}

void APlayerCharacter::OnRunReleased(){
    
    CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::OnMoveForward(float AxisValue){
    if (!WalkingDisabled){
        FVector WorldDirectionYaw = UKismetMathLibrary::GetForwardVector(
                                        FRotator(0, GetControlRotation().Yaw, 0));
        AddMovementInput(WorldDirectionYaw, AxisValue);
    }
}


void APlayerCharacter::OnMoveRight(float AxisValue){
    if (!WalkingDisabled){
        FVector WorldDirectionYaw = UKismetMathLibrary::GetRightVector(
                                        FRotator(0, GetControlRotation().Yaw, 0));
        AddMovementInput(WorldDirectionYaw, AxisValue);
    }
}


void APlayerCharacter::Jump(){
    Super::Jump();
}


void APlayerCharacter::NormalTakePhoto(){
    
    // Deny taking a photo if max number allowed has been reached
    if (Photos.Num() >= MaxNumberOfPhotos){
        EventPhotoCaptureFailed.Broadcast();
        return;
    }
    
    // PAUSE THE GAME, FREEZE EVERYTHING IN PLACE BEFORE CAPTURING
    UGameplayStatics::SetGamePaused(GetWorld(), true);
    
    // Record this as the time the photo was taken
    TimeOfLastPhoto = FDateTime::Now();
    
    if (!SceneCapture){
        UE_LOG(LogTemp,Warning,TEXT("No Scene Capture Actor..."));
    }
    
    // prepare to track all information about the photo
    UPhotoInfo* ThePhotoInfo = NewObject<UPhotoInfo>(this);
    
    
    
    // resize scene capture render target to be the right size
    if (!LocalPlayer){
        LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    }
    // Get Frustum for checking which actors are visible
    FConvexVolume Frustum;
    FSceneView* SceneView = NULL;
    int32 ScreenWidth = 1024;
    int32 ScreenHeight = 1024;
    if (LocalPlayer && LocalPlayer->ViewportClient && LocalPlayer->ViewportClient->Viewport)
    {
        FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
                                                                                LocalPlayer->ViewportClient->Viewport,
                                                                                GetWorld()->Scene,
                                                                                LocalPlayer->ViewportClient->EngineShowFlags)
                                           .SetRealtimeUpdate(true));
        
        FVector ViewLocation;
        FRotator ViewRotation;
        SceneView = LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, LocalPlayer->ViewportClient->Viewport);
        if (SceneView)
        {
            Frustum = SceneView->ViewFrustum;
        } else {
            UE_LOG(LogTemp,Warning,TEXT("Can't Search for Actors in View; SceneView pointer is NULL. Taking Square Photo."));
        }
    }

    // TODO: Figure out how to use ScreenWidth and ScreenHeight to make the textures the right size
    
    // add the visual element of the photo to the list
    UTexture2D* PhotoTexture2D = (SceneCapture->GetCaptureComponent2D()->TextureTarget->
                                  ConstructTexture2D(EmptyPhotoTexture,
                                                     FString(TEXT("New Photo")) + FString::FromInt(Photos.Num() + 1),
                                                     EObjectFlags::RF_NoFlags, 0, NULL ) );
    /*
    UTexture2D* PhotoTexture2D = (SceneCapture->GetCaptureComponent2D()->TextureTarget->
                                  ConstructTexture2D(UTexture2D::CreateTransient(1024, 1024),
                                                     FString(TEXT("New Photo")) + FString::FromInt(Photos.Num() + 1),
                                                     EObjectFlags::RF_NoFlags, 0, NULL ) );
    */
    ThePhotoInfo->Photo = PhotoTexture2D;
    if (!PhotoTexture2D){
        UE_LOG(LogTemp,Warning,TEXT("Didn't make a photo texture..."));
    }
    
    // Setup the Player SceneView for finding actors visible to the camera
    // Borrowed from https://answers.unrealengine.com/questions/65488/perform-frustum-check.html, ue4 user "TooManyCrashes"
    
    
    // Save the frustum and scene view info in the photo info.
    if (SceneView){
        ThePhotoInfo->PhotoViewFrustum = Frustum;
        ThePhotoInfo->ViewProjectionMatrix = SceneView->ProjectionMatrixUnadjustedForRHI;
        int32 SizeX = 0, SizeY = 0;
        GetWorld()->GetFirstPlayerController()->GetViewportSize(SizeX, SizeY);
        ThePhotoInfo->ScreenSize = FVector2D(SizeX, SizeY);
    }
    
    
    // use the player viewport frustum to find visible actors and record them
    ThePhotoInfo->PhotographedActors = ThePhotoInfo->GetActorsInFrustum(this, Frustum);

    ThePhotoInfo->CameraLocation = SceneCapture->GetActorLocation();
    
   

    
    // UNPAUSE GAME NOW THAT EVERYTHING IS CAPTURED
    UGameplayStatics::SetGamePaused(GetWorld(), false);
    
    // Record the photo info in the player's photos.
    Photos.Add(ThePhotoInfo);
    if (Photos.Num() > 0){
        UE_LOG(LogTemp,Warning,TEXT("\n\nGot a Photo\n\n"));
    }
    
    
    // notify blueprints that photo was just captured
    EventPhotoCaptured.Broadcast();
}

bool APlayerCharacter::PhotoTakenRecently(){
    return TimeOfLastPhoto + PhotoTakingLag > FDateTime::Now();
}





void APlayerCharacter::OnPrimaryAction(){
    // If the photo taking lag is longer than the time since the last photo, it was "recent"
    UE_LOG(LogTemp,Warning,TEXT("\n\nPrimary Action Recorded\n\n"));
    // if camera is zoomed, action is "take a photo"
    if (CameraZoomed && !PhotoTakenRecently()){
        NormalTakePhoto();
    }
    
    // for now, if camera is not zoomed, there is no action to take
}


float APlayerCharacter::FallDamageFraction(const float TimeInAir, const float HarmlessTime, const float DeathTime){
    // Before HarmlessTime, return 0
    // After DeathTime, return 1
    // Scale exponentially between
    if (TimeInAir < HarmlessTime){
        return 0;
    } else if (TimeInAir > DeathTime){
        return 1;
    }
    float alpha = FMath::Clamp<float>(TimeInAir/FGenericPlatformMath::Abs(DeathTime - HarmlessTime), 0.0f, 1.0f);
    return FMath::InterpExpoIn<float>(0.0f, 1.0f, alpha);
}
