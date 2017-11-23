////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Noah Zuo (noahzuo1994@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
#pragma once

#include "CoreMinimal.h"
#include "ImplicitSurfaceMeshComponent.h"
#include "MetaballMeshComponent.generated.h"

USTRUCT(BlueprintType)
struct FControlPoint
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Metaball")
		FVector position;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Metaball")
		float scaleFactor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Metaball")
		float threshold;


	FControlPoint()
		: position(0, 0, 0)
		, scaleFactor(1.0f)
		, threshold(1.0f)
	{ }
};

/**
 * 
 */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent))
class IMPLICITSURFACEPLUGIN_API UMetaballMeshComponent : public UImplicitSurfaceMeshComponent
{
	GENERATED_BODY()
public:
	UMetaballMeshComponent();
	virtual void ImplicitSurfaceFunction(float x, float y, float z, float& result) override;

	float getEquipotentialValue(FControlPoint& controlPoint, FVector p);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Metaball")
		TArray<FControlPoint> controlPoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Metaball")
		float equipotentialValue;
};
