// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiArray.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "GreedyMesh.generated.h"

/**
 * 
 */
UCLASS()

class PROCMAP_API AGreedyMesh : public AActor
{
	GENERATED_BODY()
	
public:
	AGreedyMesh();
	~AGreedyMesh();

	int* ChunkX;
	int* ChunkY;
	int* ChunkZ;

	int BlockSize = 60;

	TMap<FVector2D, FMultiArray>* NoiseMap;
	void CreateGreedyChunk(FVector2D ChunkID, FVector Pos);

private:
	TArray<FVector> Vertices;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FVector2D> Uvs;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	UProceduralMeshComponent* Mesh;
	FMultiArray* Noise;
	
	void CreateTop(int Z);
	void CreateRight(int X);
};
