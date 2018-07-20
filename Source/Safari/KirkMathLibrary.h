// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "KirkMathLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SAFARI_API UKirkMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    
public:
    /* Returns true iff there is a unique point of intersection. 75 mult/divide operations. */
	UFUNCTION(BlueprintPure, Category="Math|3DGeometry|Intersection")
        static bool ThreePlaneIntersection( const FPlane& APlane, const FPlane& BPlane, const FPlane& CPlane, /* out */ FVector& IntersectionPoint);
	
    //ConvexHull2D::ComputeConvexHull
    UFUNCTION(BlueprintPure, Category="Math|3DGeometry|BoundingBox")
        static TArray<FVector> CornersOfBoundingBox(const FVector& Origin, const FVector& Extent);
};
