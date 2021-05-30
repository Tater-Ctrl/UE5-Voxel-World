// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapVariables.h"
#include "BlockType.h"

class PROCMAP_API ACreateCube
{

private:
	// UV Scale divided by number of images in texture atlas!
	float uvScale = 1.f / TEXTURE_ATLAS_SIZE;
	short int Uvx = 1;
	short int Uvy = 1;

	unsigned short int top = 0;
	unsigned short int side = 0;
	unsigned short int bottom = 0;

	int offset = 0;

	int VerticesCount = 0;

public:	
	// Sets default values for this actor's properties
	ACreateCube();

	TArray<FVector> vertices;
	TArray<FVector> normals;
	TArray<int32> triangles;
	TArray<FVector2D> uvs;

	void Top(int X, int Y, int Z);
	void Bottom(int , int Y, int Z);
	void Left(int X, int Y, int Z);
	void Right(int X, int Y, int Z);
	void Front(int X, int Y, int Z);
	void Back(int X, int Y, int Z);

	void AddTriangles();
	void AddUV(const int Value);
	void AddNormals(FVector Nor);
	void BlockVariations(BlockType blockType);
	void ClearMeshData();
};
