// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	noise = nullptr;
	cube = new ACreateCube();

	// Colors for some reason?
	vertexColors.Init(FLinearColor(0.0f,0.0f,0.0f,0.5), 256);

	// Create new procedural mesh
	pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	//WaterMesh = CreateObject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	SetRootComponent(pm);
	//WaterMesh->SetupAttachment(pm);
	
	pm->CastShadow = true;
	pm->bUseAsyncCooking = true;
	//WaterMesh->CastShadow = false;
	//WaterMesh->bUseAsyncCooking = true;
	IsActive = true;
}

int AChunk::CheckNeighbourChunk(int X, int Y, int Z, int IdX, int IdY)
{
	int Value = NoiseMap->operator[](FVector2D(IdX, IdY)).Get(X, Y, Z);
	
	return Value;
}

void AChunk::DrawChunk() 
{
	pm->CreateMeshSection_LinearColor(0, cube->vertices, cube->triangles, cube->normals, cube->uvs, vertexColors, tangents, true);
}

void AChunk::UpdateChunkMesh()
{
	pm->ClearMeshSection(0);
	CreateChunk();
}

void AChunk::CreateChunk()
{	
	cube->ClearMeshData();
	
	noise = &NoiseMap->operator[](chunkID);
	
	for(int x = 0; x < *this->chunkX; ++x)
	{
		for(int y = 0; y < *this->chunkY; ++y)
		{
			for(int z = 0; z < *this->chunkZ; ++z)
			{
				//if(noise->Get(x, y, z) == 0 && z == 88)
				//{
				//	cube->BlockVariations(BlockType::Water);
				//	cube->Top(x, y, z);
				//	continue;
				//}
				
				if(noise->Get(x, y, z) == 0) continue;

				SetBlockType(noise->Get(x, y, z));
				
				//noise->Get(x, y, z + 1 ) == BlockType::Air ? cube->BlockVariations(BlockType::Grass) : cube->BlockVariations(BlockType::Dirt);
				
				// Draw top of block
				if(noise->Get(x, y, z + 1) == BlockType::Air)
				{
					cube->Top(x, y, z );
				}
				if(noise->Get(x, y, z - 1) == BlockType::Air)
				{
					cube->Bottom(x, y, z);
				}
				
				// Draw front of block
				if(noise->Get(x, y + 1, z) == BlockType::Air)
				{
					cube->Front(x, y, z);
				}
				// Check neighbour chunk if it has a block or not
				else if(noise->Get(x, y + 1, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X, chunkID.Y + 1)))
				{
					// if neighbour block is Air, display tile face
					if(CheckNeighbourChunk(x, 0, z, chunkID.X, chunkID.Y + 1) == BlockType::Air)
					{
						cube->Front(x, y, z);
					}
				}

				// Draw back of block
				if(noise->Get(x, y - 1, z) == BlockType::Air)
				{
					cube->Back(x, y, z);
				}
				// Check neighbour chunk if it has a block or not
				else if(noise->Get(x, y - 1, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X, chunkID.Y - 1)))
				{
					// if neighbour chunk block is Air, display tile face
					if(CheckNeighbourChunk(x, *chunkY - 1, z, chunkID.X, chunkID.Y - 1) == BlockType::Air)
						cube->Back(x, y, z);
				}
				
				// Draw left of block
				if(noise->Get(x + 1, y, z) == BlockType::Air)
				{
					cube->Left(x, y, z);
				}
				// Check neighbour chunk if it has a block or not
				else if(noise->Get(x + 1, y, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X + 1, chunkID.Y)))
				{
					// if neighbour chunk block is Air, display tile face
					if(CheckNeighbourChunk(0, y, z, chunkID.X + 1, chunkID.Y) == BlockType::Air)
						cube->Left(x, y, z);
				}
				
				// Draw right of block
				if(noise->Get(x - 1, y, z) == BlockType::Air)
				{
					// if neighbour chunk block is Air, display tile face
					cube->Right(x, y, z);
				}
				// Check neighbour chunk if it has a block or not
				else if(noise->Get(x - 1, y, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X - 1, chunkID.Y)))
				{
					// if neighbour chunk block is Air, display tile face
					if(CheckNeighbourChunk(*chunkX - 1, y, z, chunkID.X - 1, chunkID.Y) == BlockType::Air)
						cube->Right(x, y, z);
				}
			}
		}
	}
	// Create the mesh!
	this->DrawChunk();
}

void AChunk::SetBlockType(int Sum)
{
	if(Sum >= 0) cube->BlockVariations(BlockType::Sand);
	if(Sum > 30) cube->BlockVariations(BlockType::Dirt);
	if(Sum > 50 + 30) cube->BlockVariations(BlockType::Sand);
	if(Sum > 58 + 30) cube->BlockVariations(BlockType::Grass);
	if(Sum > 63 + 30) cube->BlockVariations(BlockType::Dirt);
	if(Sum > 65 + 30) cube->BlockVariations(BlockType::Stone);
	if(Sum > 71 + 30) cube->BlockVariations(BlockType::Dirt);
	if(Sum > 75 + 30) cube->BlockVariations(BlockType::Grass);
}




