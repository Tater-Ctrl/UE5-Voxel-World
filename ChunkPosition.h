// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct ChunkPosition
{
private:
	int X = 0, Y = 0;
public:
	ChunkPosition();

	void CalculatePosition(FVector Pos)
	{
		this->X = floor(Pos.X / 960);
		this->X = floor(Pos.Y / 960);
	}
};
