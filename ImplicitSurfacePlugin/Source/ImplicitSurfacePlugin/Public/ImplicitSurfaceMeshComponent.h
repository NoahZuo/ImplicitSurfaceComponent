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
#include "UObject/ObjectMacros.h"
#include "DynamicMeshBuilder.h"
#include "Components/MeshComponent.h"
#include "ImplicitSurfaceMeshComponent.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent))
class IMPLICITSURFACEPLUGIN_API UImplicitSurfaceMeshComponent : public UMeshComponent
{
	GENERATED_BODY()
	
public:
	UImplicitSurfaceMeshComponent();
	static int edgeTable[256];
	static int triTable[256][16];

	// Begin Component Interface
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void OnRegister() override;
	virtual void SendRenderDynamicData_Concurrent() override;
	virtual void CreateRenderState_Concurrent() override;
	// End Component Interface

	// Begin Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		float z_Top = 10.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		float z_Buttom = -10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		float x_Left = -10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		float x_Right = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		float y_Front = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		float y_Back = -10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
		int subdivision = 10;

	virtual void ImplicitSurfaceFunction(float x, float y, float z, float& result);

	// End Property


	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	//~ End UPrimitiveComponent Interface.


	//~ Begin UMeshComponent Interface.
	virtual int32 GetNumMaterials() const override;
	//~ End UMeshComponent Interface.

	FCriticalSection m_mutex;

	TArray<FVector> TriangleVertices;
	TArray<FIntVector> TriangleIndex;
	TArray<FVector> TriangleNormals;


#if WITH_EDITOR
	// Begin Debug Interface
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
		bool DebugDrawSurface;
private:
	void DebugDrawVertices();
	void DebugDrawTriangles();
	// End Debug Interface
#endif



	void GenerateMesh();
	void CalculateVerticesFromAGrid(TArray<FVector> Grid, TArray<FVector>& Verts, TArray<FIntVector>& Triangles, TArray<FVector>& Normals);
	FVector VertexInterp(FVector p1, FVector p2, float densityP1, float densityP2);

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	friend class FImplicitSurfaceSceneProxy;
	
	
};
