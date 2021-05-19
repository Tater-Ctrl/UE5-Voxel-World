// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	noise = nullptr;
	cube = new ACreateCube();

	Draw.BindUObject(this, &AChunk::CreateChunk);

	// Colors for some reason?
	vertexColors.Init(FLinearColor(0.0f,0.0f,0.0f,1.0f), 3);

	// Create new procedural mesh
	pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	SetRootComponent(pm);
	pm->CastShadow = false;

    	//// Set material to the loaded one
    	//pm->SetMaterial(0, mat);
}

int AChunk::CheckNeighbour(int X, int Y, int Z)
{
	const int Value = noise->Get(X, Y);

	if(Value < 0) return -1;
	
	if(Z <= Value)
	{
		return 1;
	}
	
	if(Z > Value)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int AChunk::CheckNeighbourChunk(int X, int Y, int Z, int IdX, int IdY)
{
	int Value = NoiseMap->operator[](FVector2D(IdX, IdY)).Get(X, Y);
	
	if(Value < Z)
	{
		return 0;
	}
	
	return -1;
}

void AChunk::DrawChunk() const 
{
	pm->CreateMeshSection_LinearColor(0, cube->vertices, cube->triangles, cube->normals, cube->uvs, vertexColors, tangents, true);
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
				if(this->CheckNeighbour(x, y, z) == 0) continue;

				CheckNeighbour(x, y, z + 1 ) == BlockType::Air ? cube->BlockVariations(BlockType::Grass) : cube->BlockVariations(BlockType::Dirt);
				
				// Draw top of block
				if(this->CheckNeighbour(x, y, z + 1) == 0)
				{
					cube->Top(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}

				// Draw front of block
				if(CheckNeighbour(x, y + 1, z) == BlockType::Air)
				{
					cube->Front(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
				// Check neighbour chunk if it has a block or not
				else if(CheckNeighbour(x, y + 1, z) == -1 && NoiseMap->Find(FVector2D(chunkID.X, chunkID.Y + 1)))
				{
					// if neighbour block is Air, display tile face
					if(CheckNeighbourChunk(x, 0, z, chunkID.X, chunkID.Y + 1) == BlockType::Air)
					{
						cube->Front(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
					}
				}

				// Draw back of block
				if(CheckNeighbour(x, y - 1, z) == BlockType::Air)
				{
					cube->Back(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
				// Check neighbour chunk if it has a block or not
				else if(CheckNeighbour(x, y - 1, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X, chunkID.Y - 1)))
				{
					// if neighbour chunk block is Air, display tile face
					if(CheckNeighbourChunk(x, *chunkY - 1, z, chunkID.X, chunkID.Y - 1) == BlockType::Air)
						cube->Back(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
				
				// Draw left of block
				if(CheckNeighbour(x + 1, y, z) == BlockType::Air)
				{
					cube->Left(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
				// Check neighbour chunk if it has a block or not
				else if(CheckNeighbour(x + 1, y, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X + 1, chunkID.Y)))
				{
					// if neighbour chunk block is Air, display tile face
					if(CheckNeighbourChunk(0, y, z, chunkID.X + 1, chunkID.Y) == BlockType::Air)
						cube->Left(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
				
				// Draw right of block
				if(CheckNeighbour(x - 1, y, z) == BlockType::Air)
				{
					// if neighbour chunk block is Air, display tile face
					cube->Right(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
				// Check neighbour chunk if it has a block or not
				else if(CheckNeighbour(x - 1, y, z) < BlockType::Air && NoiseMap->Find(FVector2D(chunkID.X - 1, chunkID.Y)))
				{
					// if neighbour chunk block is Air, display tile face
					if(CheckNeighbourChunk(*chunkX - 1, y, z, chunkID.X - 1, chunkID.Y) == BlockType::Air)
						cube->Right(x - (*chunkX / 2), y - (*chunkY / 2), z - (*chunkZ / 2));
				}
			}
		}
	}
	// Create the mesh!
	this->DrawChunk();
}



