// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiArray.h"
#include "Chunk.h"

/**
 * 
 */
class PROCMAP_API ABlockEditor
{
public:
	ABlockEditor(TMap<FVector2D, FMultiArray>* NoiseMap, TMap<FVector2D, AChunk*>* Chunks, int* ChunkX, int* ChunkY, int* ChunkZ);

	TMap<FVector2D, FMultiArray>* NoiseMap;
	TMap<FVector2D, AChunk*>* Chunks;

	int* ChunkX;	
	int* ChunkY;
	int* ChunkZ;

	void BreakBlock(FVector Position, FVector2D ChunkID);
	void PlaceBlock(FVector Position, FVector2D ChunkID);

	void UpdateSurroundingChunkBlocks(FVector2D ChunkID, FVector Pos);
	
	~ABlockEditor();
};
