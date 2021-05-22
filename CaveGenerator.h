// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplexNoise.h"

/**
 * 
 */
struct CaveGenerator
{
public:
	CaveGenerator();
	
	SimplexNoise* Simplex;

	float GenerateCaveNoise(FVector Pos);
	
	~CaveGenerator();
};
