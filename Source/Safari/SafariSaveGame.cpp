// Fill out your copyright notice in the Description page of Project Settings.

#include "Safari.h"
#include "SafariSaveGame.h"




USafariSaveGame::USafariSaveGame(){
    SaveSlotName = "<Save Slot Name Not Set>";
    LevelName = "<Save Slot Level Not Set>";
}

TArray<AActor*> USafariSaveGame::GetSaveableActors(){
    TArray<AActor*> SaveableActors;
    for ( TObjectIterator<UPhotoInfoRecordComponent> it; it; ++it ){
        SaveableActors.Add((*it)->GetOwner());
    }
    return SaveableActors;
}



TArray<UClass*> USafariSaveGame::GetSavedActorClasses(){
    return SavedActorClasses;
}


TArray<FTransform> USafariSaveGame::GetSavedActorTransforms(){
    return SavedActorTransforms;
}


TArray<UPhotoInfo*> USafariSaveGame::GetSavedPhotos(){
    return SavedPhotos;
}
