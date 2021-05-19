// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateCube.h"

// Sets default values
ACreateCube::ACreateCube()
{
	
}

void ACreateCube::BlockVariations(BlockType blockType)
{
	switch(blockType)
	{
		case BlockType::Grass:
			top = 2; side = 0; bottom = 1;
		break;
		case BlockType::Dirt:
			top = 1; side = 1; bottom = 1;
		break;
		case BlockType::Bedrock:
			top = 3; side = 3; bottom = 3;
		break;
		default:
			top = 1; side = 1; bottom = 1;
		break;
			
	}
}

void ACreateCube::Top(int x, int y, int z)
{	
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());

	uvs.Add(FVector2D(uvScale * (Uvx + top), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + top), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + top) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + top) - uvScale, uvScale * Uvy));

	for (int i = 0; i < 4; ++i) {
		normals.Add(FVector(0.0f, 0.0f, 1.0f));
	}

	vertices.Add(FVector( 0 + (x * cubeSize) , 0 + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize) , cubeSize + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize) , cubeSize + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize) , 0 + (y * cubeSize), cubeSize + (z * cubeSize)));
}

void ACreateCube::Bottom(int x, int y, int z)
{
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());

	uvs.Add(FVector2D(uvScale * (Uvx + bottom), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + bottom), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + bottom) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + bottom) - uvScale, uvScale * Uvy));

	for (int i = 0; i < 4; ++i) {
		normals.Add(FVector(0.0f, 0.0f, -1.0f));
	}

	vertices.Add(FVector(0 + (x * cubeSize), cubeSize + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize), 0 + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize), 0 + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize), cubeSize + (y * cubeSize), 0 + (z * cubeSize)));
}

void ACreateCube::Front(int x, int y, int z)
{
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());

	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy));

	for (int i = 0; i < 4; ++i) {
		normals.Add(FVector(0.0f, 1.0f, 0.0f));
	}

	vertices.Add(FVector(cubeSize + (x * cubeSize), cubeSize + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize), cubeSize + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize), cubeSize + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize), cubeSize + (y * cubeSize), 0 + (z * cubeSize)));
}

void ACreateCube::Back(int x, int y, int z)
{
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());

	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy));

	for (int i = 0; i < 4; ++i) {
		normals.Add(FVector(0.0f, -1.0f, 0.0f));
	}

	vertices.Add(FVector(0 + (x * (cubeSize)), 0 + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * (cubeSize)), 0 + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * (cubeSize)), 0 + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * (cubeSize)), 0 + (y * cubeSize), 0 + (z * cubeSize)));
}

void ACreateCube::Left(int x, int y, int z)
{
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());

	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy));

	for (int i = 0; i < 4; ++i) {
		normals.Add(FVector(1.0f, 0.0f, 0.0f));
	}

	vertices.Add(FVector(cubeSize + (x * cubeSize), 0 + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize), 0 + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize), cubeSize + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(cubeSize + (x * cubeSize), cubeSize + (y * cubeSize), 0 + (z * cubeSize)));
}

void ACreateCube::Right(int x, int y, int z)
{
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());

	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + side), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + side) - uvScale, uvScale * Uvy));

	for (int i = 0; i < 4; ++i) {
		normals.Add(FVector(-1.0f, 0.0f, 0.0f));
	}

	vertices.Add(FVector(0 + (x * cubeSize), cubeSize + (y * cubeSize), 0 + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize), cubeSize + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize), 0 + (y * cubeSize), cubeSize + (z * cubeSize)));
	vertices.Add(FVector(0 + (x * cubeSize), 0 + (y * cubeSize), 0 + (z * cubeSize)));
}

void ACreateCube::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
}
