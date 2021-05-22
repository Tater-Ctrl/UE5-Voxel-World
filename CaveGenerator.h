// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiArray.h"
#include "SimplexNoise.h"

/**
 * 
 */
class PROCMAP_API CaveGenerator
{
public:
	CaveGenerator();

	TArray<FVector2D, FMultiArray> CaveNoise;
	SimplexNoise* Simplex;
	int* ChunkX;
	int* ChunkY;
	int* ChunkZ;

	void GenerateCaveNoise();
	
	~CaveGenerator();
};
