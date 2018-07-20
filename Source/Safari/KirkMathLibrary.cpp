// Fill out your copyright notice in the Description page of Project Settings.

#include "Safari.h"
#include "KirkMathLibrary.h"

// 75 multiplication/division operations
bool UKirkMathLibrary::ThreePlaneIntersection( const FPlane& APlane, const FPlane& BPlane, const FPlane& CPlane, FVector& IntersectionPoint){
    // Check if there is a unique point of intersection by checking two matrices
    // First, determinant of matrix of normal vectors of planes; no two should be parallel, i.e. determinant should not be 0.
    const float normals_determinant = (APlane.X*BPlane.Y*CPlane.Z + APlane.Y*BPlane.Z*CPlane.X + APlane.Z*BPlane.X*CPlane.Y
                          - APlane.X*BPlane.Z*CPlane.Y - APlane.Y*BPlane.X*CPlane.Z - APlane.Z*BPlane.Y*CPlane.X);
    // Second, determinant of augmented matrix of normal vectors plus the W terms for the planes. Can throw away any column
    // of this 3x4 matrix to get determinant, so throw away Z column. Also, take negative result, because it doesn't change
    // whether or not the determinant is 0, and will let us use this determinant for calculating the intersection point later.
    const float replace_Z_determinant = -(APlane.X*BPlane.Y*CPlane.W + APlane.Y*BPlane.W*CPlane.X + APlane.W*BPlane.X*CPlane.Y
                          - APlane.X*BPlane.W*CPlane.Y - APlane.Y*BPlane.X*CPlane.W - APlane.W*BPlane.Y*CPlane.X);
    if (normals_determinant == 0 || replace_Z_determinant == 0){
        return false;
    }
    
    // Given that both matrices are rank 3, there is a unique point of intersection and we can compute it with Cramer's Rule.
    // This uses the determinants of the three matrices you get from replacing columns of the normal-matrix with the (negative) W column.
    // (Because this is the solution to the system of equations Ax = b where A is the normals matrix and b = -W)
    const float replace_X_determinant = (APlane.W*BPlane.Y*CPlane.Z + APlane.Y*BPlane.Z*CPlane.W + APlane.Z*BPlane.W*CPlane.Y
                                   - APlane.W*BPlane.Z*CPlane.Y - APlane.Y*BPlane.W*CPlane.Z - APlane.Z*BPlane.Y*CPlane.W);
    const float replace_Y_determinant = (APlane.X*BPlane.W*CPlane.Z + APlane.W*BPlane.Z*CPlane.X + APlane.Z*BPlane.X*CPlane.W
                                   - APlane.X*BPlane.Z*CPlane.W - APlane.W*BPlane.X*CPlane.Z - APlane.Z*BPlane.W*CPlane.X);
    IntersectionPoint.X = replace_X_determinant/normals_determinant;
    IntersectionPoint.Y = replace_Y_determinant/normals_determinant;
    IntersectionPoint.Z = replace_Z_determinant/normals_determinant;
    return true;
}


TArray<FVector> UKirkMathLibrary::CornersOfBoundingBox(const FVector& Origin, const FVector& Extent){
    TArray<FVector> Corners = TArray<FVector>();
    Corners.Add(FVector(Origin.X + Extent.X, Origin.Y + Extent.Y, Origin.Z + Extent.Z));
    Corners.Add(FVector(Origin.X + Extent.X, Origin.Y + Extent.Y, Origin.Z - Extent.Z));
    Corners.Add(FVector(Origin.X + Extent.X, Origin.Y - Extent.Y, Origin.Z + Extent.Z));
    Corners.Add(FVector(Origin.X + Extent.X, Origin.Y - Extent.Y, Origin.Z - Extent.Z));
    
    Corners.Add(FVector(Origin.X - Extent.X, Origin.Y + Extent.Y, Origin.Z + Extent.Z));
    Corners.Add(FVector(Origin.X - Extent.X, Origin.Y - Extent.Y, Origin.Z + Extent.Z));
    Corners.Add(FVector(Origin.X - Extent.X, Origin.Y + Extent.Y, Origin.Z - Extent.Z));
    Corners.Add(FVector(Origin.X - Extent.X, Origin.Y - Extent.Y, Origin.Z - Extent.Z));
    return Corners;
}
