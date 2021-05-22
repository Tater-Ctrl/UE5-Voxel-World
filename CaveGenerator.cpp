// Fill out your copyright notice in the Description page of Project Settings.


#include "CaveGenerator.h"

CaveGenerator::CaveGenerator()
{
}

void CaveGenerator::GenerateCaveNoise()
{
	for(int X = 0; X < *ChunkX; ++X)
	{
		for(int Y = 0; Y < *ChunkY; ++Y)
		{
			for(int Z = 0; Z < *ChunkZ; ++Z)
			{
				const int Height = Simplex->fractal3D(1, 0.05f, X, Y, Z);
			}
		}
	}
}

CaveGenerator::~CaveGenerator()
{
	
}
