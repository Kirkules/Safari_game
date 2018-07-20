// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "GameStat.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class GameStatType : uint8 {
    SE_Int  UMETA(DisplayName="int"),
    SE_Float UMETA(DisplayName="float"),
    SE_String UMETA(DisplayName="string")
};

UCLASS(Blueprintable)
class SAFARI_API UGameStat : public UObject
{
	GENERATED_BODY()
    
public:
    UGameStat();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameStat")
        UTexture2D* Icon;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameStat")
        FString StatName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameStat")
        GameStatType StatType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameStat")
        int32 IntValue;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameStat")
        float FloatValue;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameStat")
        FString StringValue;
    
	UFUNCTION(BlueprintCallable, Category="GameStat")
        FString ValueDisplayString();
};
