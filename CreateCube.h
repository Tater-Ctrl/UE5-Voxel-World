// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockType.h"

class PROCMAP_API ACreateCube
{

private:
	int cubeSize = 60;
	float uvScale = 1.f / 16.f;
	int Uvx = 1;
	int Uvy = 1;

	int top = 0;
	int side = 0;
	int bottom = 0;

	int offset = 0;

public:	
	// Sets default values for this actor's properties
	ACreateCube();

	TArray<FVector> vertices;
	TArray<FVector> normals;
	TArray<int32> triangles;
	TArray<FVector2D> uvs;

	void Top(int x, int y, int z);
	void Bottom(int , int y, int z);
	void Left(int x, int y, int z);
	void Right(int x, int y, int z);
	void Front(int x, int y, int z);
	void Back(int x, int y, int z);

	void BlockVariations(BlockType blockType);
	void ClearMeshData();
};
