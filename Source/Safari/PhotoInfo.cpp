// Fill out your copyright notice in the Description page of Project Settings.


#include "Safari.h"
#include "PhotoInfo.h"




int32 UPhotoInfo::CountActors(const UClass* Type){
    int32 total = 0;
    for (auto ActorInfo : PhotographedActors){
        if (ActorInfo->ActorClass == Type){
            total += 1;
        }
    }
    return total;
}


TArray<UPhotographedActorInfo*> UPhotoInfo::GetActorsInFrustum(const AActor* ContextActor, const FConvexVolume Frustum){
    TArray<UPhotographedActorInfo*> ResultArray;
    
    // how recently were things rendered? give a 2-frame window
    float RenderRecentness = 2*ContextActor->GetWorld()->DeltaTimeSeconds;
    
    FVector VisibilityOrigin;
    FVector VisibilityExtent;
    float VisibilityRadius;
    AActor* Actor;

    for ( TObjectIterator<UPhotoInfoRecordComponent> it; it; ++it ){
        Actor = (*it)->GetOwner();
        if (Actor){
            Actor->GetActorBounds(true /* use only collision components */, VisibilityOrigin, VisibilityExtent);
            VisibilityRadius = FMath::Max3<float>(VisibilityExtent.X, VisibilityExtent.Y, VisibilityExtent.Z);
            
            // check a "visibility radius" around the actor's location and see if it is in the camera's frustum.
            if (Frustum.IntersectSphere(VisibilityOrigin, VisibilityRadius)){
                // Check that the actor was actually rendered recently. Same idea as doing collision checking, but UE4 already
                // did the work!
                if (Actor->WasRecentlyRendered(RenderRecentness)){
                    // build PhotographedActorInfo for this actor
                    UPhotographedActorInfo* ActorInfo = (*it)->GetPhotographedActorInfo(ScreenSize);
                    ResultArray.Add(ActorInfo);
                }
            }
        }
    }
    return ResultArray;
}


UPhotographedActorInfo* UPhotoInfo::BuildObjectInfo(const AActor* TheObject, const FConvexVolume Frustum){
    UPhotographedActorInfo* ActorInfo = NewObject<UPhotographedActorInfo>();
    
    ActorInfo->ActorName = Cast<UObject>(TheObject)->GetName();
    ActorInfo->ActorClass = Cast<UObject>(TheObject)->GetClass();
    
    return ActorInfo;
}


