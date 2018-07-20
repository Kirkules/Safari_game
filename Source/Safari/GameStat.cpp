// Fill out your copyright notice in the Description page of Project Settings.

#include "Safari.h"
#include "GameStat.h"



UGameStat::UGameStat(){
    StatType = GameStatType::SE_Int;
}

FString UGameStat::ValueDisplayString(){
    switch (StatType){
        case GameStatType::SE_Int:
            return FString::FromInt(IntValue);
            break;
        case GameStatType::SE_Float:
            return FString::SanitizeFloat(FloatValue);
            break;
        case GameStatType::SE_String:
            return StringValue;
            break;
        default:
            break;
    }
}
