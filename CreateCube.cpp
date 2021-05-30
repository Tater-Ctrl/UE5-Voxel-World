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
			top = 0; side = 0; bottom = 0;
		break;
		case BlockType::Dirt:
			top = 1; side = 1; bottom = 1;
		break;
		case BlockType::Stone:
			top = 3; side = 3; bottom = 3;
		break;
		case BlockType::Bedrock:
			top = 4; side = 4; bottom = 4;
		break;
		case BlockType::Water:
			top = 5; side = 5; bottom = 5;
		break;
		case BlockType::Sand:
			top = 6; side = 6; bottom = 6;
		break;
		default:
			top = 1; side = 1; bottom = 1;
		break;
	}
}

void ACreateCube::AddNormals(FVector Nor)
{
	normals.Add(Nor);
	normals.Add(Nor);
	normals.Add(Nor);
	normals.Add(Nor);
}

void ACreateCube::AddTriangles()
{
	triangles.Add(0 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(3 + vertices.Num());
	triangles.Add(1 + vertices.Num());
	triangles.Add(2 + vertices.Num());
	triangles.Add(3 + vertices.Num());
}

void ACreateCube::AddUV(const int Value)
{
	uvs.Add(FVector2D(uvScale * (Uvx + Value), uvScale * Uvy));
	uvs.Add(FVector2D(uvScale * (Uvx + Value), uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + Value) - uvScale, uvScale * Uvy - uvScale));
	uvs.Add(FVector2D(uvScale * (Uvx + Value) - uvScale, uvScale * Uvy));
}

void ACreateCube::Top(const int X, const int Y, const int Z)
{	
	AddTriangles();
	AddUV(top);
	AddNormals(FVector(0.0f, 0.0f, 1.0f));

	vertices.Add(FVector( X * BLOCK_SIZE, Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));

	VerticesCount += 4;
}

void ACreateCube::Bottom(const int X, const int Y, const int Z)
{
	AddTriangles();
	AddUV(bottom);
	AddNormals(FVector(0.0f, 0.0f, -1.0f));

	vertices.Add(FVector(X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, Z * BLOCK_SIZE));
	vertices.Add(FVector(X * BLOCK_SIZE, Y * BLOCK_SIZE, Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, Y * BLOCK_SIZE, Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, Z * BLOCK_SIZE));

	VerticesCount += 4;
}

void ACreateCube::Front(const int X, const int Y, const int Z)
{
	AddTriangles();
	AddUV(side);
	AddNormals(FVector(0.0f, 1.0f, 0.0f));
	
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(X * BLOCK_SIZE, BLOCK_SIZE + Y * BLOCK_SIZE, Z * BLOCK_SIZE));

	VerticesCount += 4;
}

void ACreateCube::Back(const int X, const int Y, const int Z)
{
	AddTriangles();
	AddUV(side);
	AddNormals(FVector(0.0f, -1.0f, 0.0f));
	
	vertices.Add(FVector(0 + X * BLOCK_SIZE, Y * BLOCK_SIZE, Z * BLOCK_SIZE));
	vertices.Add(FVector(0 + X * BLOCK_SIZE, Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, Y * BLOCK_SIZE, BLOCK_SIZE + (Z * BLOCK_SIZE)));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, Y * BLOCK_SIZE, Z * BLOCK_SIZE));

	VerticesCount += 4;
}

void ACreateCube::Left(const int X, const int Y, const int Z)
{
	AddTriangles();
	AddUV(side);
	AddNormals(FVector(1.0f, 0.0f, 0.0f));

	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, Y * BLOCK_SIZE, Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, Y * BLOCK_SIZE, BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, BLOCK_SIZE + (Y * BLOCK_SIZE), BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(BLOCK_SIZE + X * BLOCK_SIZE, BLOCK_SIZE + (Y * BLOCK_SIZE), Z * BLOCK_SIZE));

	VerticesCount += 4;
}

void ACreateCube::Right(const int X, const int Y, const int Z)
{
	AddTriangles();
	AddUV(side);
	AddNormals(FVector(-1.0f, 0.0f, 0.0f));

	vertices.Add(FVector(X * BLOCK_SIZE, BLOCK_SIZE + (Y * BLOCK_SIZE), Z * BLOCK_SIZE));
	vertices.Add(FVector(X * BLOCK_SIZE, BLOCK_SIZE + (Y * BLOCK_SIZE), BLOCK_SIZE + Z * BLOCK_SIZE));
	vertices.Add(FVector(X * BLOCK_SIZE, Y * BLOCK_SIZE, BLOCK_SIZE + (Z * BLOCK_SIZE)));
	vertices.Add(FVector(X * BLOCK_SIZE, Y * BLOCK_SIZE, Z * BLOCK_SIZE));

	VerticesCount += 4;
}

void ACreateCube::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
}
