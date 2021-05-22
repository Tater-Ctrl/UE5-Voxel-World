// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreateCube.h"
#include "ProceduralMeshComponent.h"
#include "MultiArray.h"
#include "Chunk.generated.h"

UCLASS()
class PROCMAP_API AChunk : public AActor
{
	GENERATED_BODY()

private:
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;
	
	int CheckNeighbourChunk(int X, int Y, int Z, int IdX, int IdY);

public:	
	// Sets default values for this actor's properties
	AChunk();

	//UMaterialInterface* mat;
	UPROPERTY(VisibleAnywhere, Category = "MyProceduralMesh")
	UProceduralMeshComponent* pm;
	ACreateCube* cube;
	
	int* chunkX;
	int* chunkY;
	int* chunkZ;

	UPROPERTY(EditAnywhere, Category="Chunk ID")
	bool IsActive;
	
	UPROPERTY(EditAnywhere, Category="Chunk ID")
	FVector2D chunkID;

	UPROPERTY(EditAnywhere, Category="Distance to Player")
	int ChunkDistance = 0;

	void SetBlockType(int Sum);
	void UpdateChunkMesh();

	FMultiArray* noise;
	
	TMap<FVector2D, FMultiArray>* NoiseMap;

	void DrawChunk();
	void CreateChunk();
};
