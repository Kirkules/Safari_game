// Fill out your copyright notice in the Description page of Project Settings.

#include "Safari.h"
#include "KirkMathLibrary.h"
#include "PhotoInfoRecordComponent.h"


// Sets default values for this component's properties
UPhotoInfoRecordComponent::UPhotoInfoRecordComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPhotoInfoRecordComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find a BoxComponent in the actor in case it has one for collision -- to use for finding the actor in the photo.
    BoundsComponent = GetOwner()->FindComponentByClass<UBoxComponent>();
	
}


// Called every frame
void UPhotoInfoRecordComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


UPhotographedActorInfo* UPhotoInfoRecordComponent::GetPhotographedActorInfo(FVector2D ScreenSize){
    UPhotographedActorInfo* ResultInfo = NewObject<UPhotographedActorInfo>();
    AActor* Owner = GetOwner();
    
    // Get the owning actor's object name
    ResultInfo->ActorName = Owner->GetName();
    
    // Get the world bounding box of the actor in the image
    
    FVector2D nextScreenPoint;
    float XMin = -1, XMax = -1, YMin = -1, YMax = -1;
    bool XMinSet = false, XMaxSet = false, YMinSet = false, YMaxSet = false;
    // if "BoundsComponent" is set, use that to get location in photo of the actor instead of the "GetActorBounds" function
    TArray<FVector> BBoxPoints;
    if (BoundsComponent){
//        ResultInfo->BoundingBoxOrigin = BoundsComponent->GetComponentLocation();
//        ResultInfo->BoundingBoxExtent = BoundsComponent->GetScaledBoxExtent();
        ResultInfo->BoundingBoxOrigin = BoundsComponent->CalcBounds(BoundsComponent->ComponentToWorld).Origin;
        ResultInfo->BoundingBoxExtent = BoundsComponent->CalcBounds(BoundsComponent->ComponentToWorld).BoxExtent;
        
        UE_LOG(LogTemp,Warning,TEXT("USING BOUNDING BOX COMPONENT:"));
    } else {
        Owner->GetActorBounds(true, ResultInfo->BoundingBoxOrigin, ResultInfo->BoundingBoxExtent);
        UE_LOG(LogTemp,Warning,TEXT("USING GET-ACTOR-BOUNDS FUNCTION:"));
    }
    BBoxPoints = UKirkMathLibrary::CornersOfBoundingBox(ResultInfo->BoundingBoxOrigin, ResultInfo->BoundingBoxExtent);
    
    UE_LOG(LogTemp,Warning,TEXT("Screen points:"));
    for (int i = 0; i < BBoxPoints.Num(); ++i){
        UGameplayStatics::ProjectWorldToScreen(Owner->GetWorld()->GetFirstPlayerController(),
                                               BBoxPoints[i],
                                               nextScreenPoint);
        
        if (!XMinSet){
            XMin = nextScreenPoint.X;
            XMinSet = true;
        }
        if (!XMaxSet){
            XMax = nextScreenPoint.X;
            XMaxSet = true;
        }
        if (!YMinSet){
            YMin = nextScreenPoint.Y;
            YMinSet = true;
        }
        if (!YMaxSet){
            YMax = nextScreenPoint.Y;
            YMaxSet = true;
        }
        XMin = FGenericPlatformMath::Min(XMin, nextScreenPoint.X);
        XMax = FGenericPlatformMath::Max(XMax, nextScreenPoint.X);
        YMin = FGenericPlatformMath::Min(YMin, nextScreenPoint.Y);
        YMax = FGenericPlatformMath::Max(YMax, nextScreenPoint.Y);
        
        UE_LOG(LogTemp,Warning,TEXT("%s"), *(nextScreenPoint.ToString()) );
    }
    ResultInfo->ScreenBoundingBoxTopLeft = FVector2D(FMath::Clamp<float>(XMin, 0, ScreenSize.X), FMath::Clamp<float>(YMin, 0, ScreenSize.Y));
    ResultInfo->ScreenBoundingBoxBottomRight = FVector2D(FMath::Clamp<float>(XMax, 0, ScreenSize.X), FMath::Clamp<float>(YMax, 0, ScreenSize.Y));
    // Clamp to screen size, in case bounding box is not all on screen...
    UE_LOG(LogTemp,Warning,TEXT("SCREEN SIZE IS::::: %s"), *(ScreenSize.ToString()) );
    UE_LOG(LogTemp,Warning,TEXT("Got Bounding Box Points:"));
    UE_LOG(LogTemp,Warning,TEXT("Top Left: %s"), *(ResultInfo->ScreenBoundingBoxTopLeft.ToString()) );
    UE_LOG(LogTemp,Warning,TEXT("Bottom Right: %s"), *(ResultInfo->ScreenBoundingBoxBottomRight.ToString()) );
    
    
    // Get the world position and facing-direction of the actor
    ResultInfo->WorldPosition = Owner->GetActorLocation();
    ResultInfo->ForwardVector = Owner->GetActorForwardVector();
    
    
    // Get the type of the owning actor
    ResultInfo->ActorClass = Owner->GetClass();
    
    // Get the (center of the) actor's position on the screen
    UGameplayStatics::ProjectWorldToScreen(Owner->GetWorld()->GetFirstPlayerController(),
                                           Owner->GetActorLocation(),
                                           ResultInfo->ScreenPosition);
    
    return ResultInfo;
}
