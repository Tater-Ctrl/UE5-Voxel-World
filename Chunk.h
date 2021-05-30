// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreateCube.h"
#include "ProceduralMeshComponent.h"
#include "MultiArray.h"
#include "MapVariables.h"
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

	UPROPERTY(VisibleAnywhere, Category = "MyProceduralMesh")
	UProceduralMeshComponent* pm;
	ACreateCube* cube;

	UPROPERTY(EditAnywhere, Category="Chunk ID")
	bool IsActive;
	
	UPROPERTY(EditAnywhere, Category="Chunk ID")
	FVector2D ChunkID;
	
	void SetBlockType(int Sum);
	void UpdateChunkMesh();

	TMap<FVector2D, FMultiArray>* NoiseMap;

	FMultiArray* NoiseMiddle;
	FMultiArray* NoiseFront;
	FMultiArray* NoiseBack;
	FMultiArray* NoiseLeft;
	FMultiArray* NoiseRight;

	UFUNCTION()
	void DrawChunk();
	UFUNCTION()
	void CreateChunk();
	UFUNCTION()
	void CreateChunkAsync();
	UFUNCTION()
	void ChunkInit();
};
