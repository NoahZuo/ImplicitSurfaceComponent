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
#include "MetaballMeshComponent.h"

UMetaballMeshComponent::UMetaballMeshComponent()
{
}

void UMetaballMeshComponent::ImplicitSurfaceFunction(float x, float y, float z, float& result)
{
	float r = 0.0f;


	for (int i = 0; i < controlPoints.Num(); i++)
	{
		r += getEquipotentialValue(controlPoints[i], FVector(x, y, z));
	}

	r -= equipotentialValue;
	result = r;
}

float UMetaballMeshComponent::getEquipotentialValue(FControlPoint& controlPoint, FVector p)
{
	float sqr = (p - controlPoint.position).SizeSquared();
	float sqrThreshold = controlPoint.threshold*controlPoint.threshold;
	if (sqr >= sqrThreshold)
		return 0.0f;
	else
	{
		return (controlPoint.scaleFactor * ((sqr / sqrThreshold - 1) * (sqr / sqrThreshold - 1) * (sqr / sqrThreshold - 1) * (sqr / sqrThreshold - 1)));
	}
}