// Fill out your copyright notice in the Description page of Project Settings.


#include "CaveGenerator.h"

CaveGenerator::CaveGenerator()
{
	Simplex = new SimplexNoise();
}

float CaveGenerator::GenerateCaveNoise(FVector Pos)
{
	float Height = (Simplex->fractal3D(1, 0.0001f, Pos.X, Pos.Y, Pos.Z));

	return Height;
}

CaveGenerator::~CaveGenerator()
{
	
}
