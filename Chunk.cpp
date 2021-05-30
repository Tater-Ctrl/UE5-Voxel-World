// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//noise = nullptr;
	cube = new ACreateCube();

	// Colors for some reason?
	vertexColors.Init(FLinearColor(0.0f,0.0f,0.0f,0.5), 256);

	// Create new procedural mesh
	pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	SetRootComponent(pm);
	
	pm->CastShadow = true;
	pm->bUseAsyncCooking = true;

	IsActive = true;
}

int AChunk::CheckNeighbourChunk(const int X, const int Y, const int Z, const int IdX, const int IdY)
{
	const int Value = NoiseMap->operator[](FVector2D(IdX, IdY)).Get(X, Y, Z);
	
	return Value;
}

void AChunk::DrawChunk() 
{		
	pm->CreateMeshSection_LinearColor(0, cube->vertices, cube->triangles, cube->normals, cube->uvs, vertexColors, tangents, true);
	cube->ClearMeshData();
}

void AChunk::UpdateChunkMesh()
{
	CreateChunk();
}

void AChunk::ChunkInit()
{
	NoiseMiddle = &NoiseMap->operator[](ChunkID);
	NoiseFront = &NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1));
	NoiseBack = &NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1));
	NoiseLeft = &NoiseMap->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y));
	NoiseRight = &NoiseMap->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y));
}

void AChunk::CreateChunk()
{
	double Start = FPlatformTime::Seconds();
	
	for(int X = 0; X < CHUNK_WIDTH; ++X)
	{
		for(int Y = 0; Y < CHUNK_WIDTH; ++Y)
		{
			for(int Z = 0; Z < CHUNK_HEIGHT; ++Z)
			{					
				if(NoiseMap->operator[](ChunkID).Get(X, Y, Z) == 0) continue;

				SetBlockType(NoiseMap->operator[](ChunkID).Get(X, Y, Z));
				
				// Draw top of block
				if(NoiseMap->operator[](ChunkID).Get(X, Y, Z + 1) == BlockType::Air)
				{
					cube->Top(X, Y, Z );
				}

				// Draw bottom of block
				if(NoiseMap->operator[](ChunkID).Get(X, Y, Z - 1) == BlockType::Air)
				{
					cube->Bottom(X, Y, Z);
				}
				
				// Draw front of block and check neighbour chunks
				if(NoiseMap->operator[](ChunkID).Get(X, Y + 1, Z) <= BlockType::Air)
				{
					// Check neighbour chunk if it has a block or not
					if(NoiseMap->operator[](ChunkID).Get(X, Y + 1, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X, ChunkID.Y + 1)))
					{
						// if neighbour block is Air, display tile face
						if(NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1)).Get(X, 0, Z) == BlockType::Air)
						{
							cube->Front(X, Y, Z);
						}
					} else
					{
						cube->Front(X, Y, Z);
					}
				}

				// Draw back of block  and check neighbour chunks
				if(NoiseMap->operator[](ChunkID).Get(X, Y - 1, Z) <= BlockType::Air)
				{
					// Check neighbour chunk if it has a block or not
					if(NoiseMap->operator[](ChunkID).Get(X, Y - 1, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X, ChunkID.Y - 1)))
					{
						// if neighbour chunk block is Air, display tile face
						if(NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1)).Get(X, CHUNK_WIDTH - 1, Z) == BlockType::Air)
							cube->Back(X, Y, Z);
					} else
					{
						cube->Back(X, Y, Z);
					}
				}
				
				// Draw left of block and check neighbour chunks
				if(NoiseMap->operator[](ChunkID).Get(X + 1, Y, Z) <= BlockType::Air)
				{
					// Check neighbour chunk if it has a block or not
					if(NoiseMap->operator[](ChunkID).Get(X + 1, Y, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X + 1, ChunkID.Y)))
					{
						// if neighbour chunk block is Air, display tile face
						if(NoiseMap->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y)).Get(0, Y, Z) == BlockType::Air)
							cube->Left(X, Y, Z);
					} else
					{
						cube->Left(X, Y, Z);
					}
				}
				
				// Draw right of block and check neighbour chunks
				if(NoiseMap->operator[](ChunkID).Get(X - 1, Y, Z) <= BlockType::Air)
				{
					// Check neighbour chunk if it has a block or not
					if(NoiseMap->operator[](ChunkID).Get(X - 1, Y, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X - 1, ChunkID.Y)))
					{
						// if neighbour chunk block is Air, display tile face
						if(NoiseMap->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y)).Get(CHUNK_WIDTH - 1, Y, Z) == BlockType::Air)
							cube->Right(X, Y, Z);
					} else
					{
						// if neighbour chunk block is Air, display tile face
						cube->Right(X, Y, Z);
					}
				}
			}
		}
	}
	
	this->DrawChunk();
}

void AChunk::CreateChunkAsync()
{
	double Start = FPlatformTime::Seconds();

	if(!NoiseMap->Find(ChunkID))
	{
		UE_LOG(LogTemp, Warning, TEXT("MISSING CHUNK ID IN 'CreateChunkAsync'! RETURNING..."));
		return;
	}

	AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [=] ()
	{						
		for(int X = 0; X < CHUNK_WIDTH; ++X)
		{
			for(int Y = 0; Y < CHUNK_WIDTH; ++Y)
			{
				for(int Z = 0; Z < CHUNK_HEIGHT; ++Z)
				{					
					if(NoiseMiddle->Get(X, Y, Z) == 0) continue;
	
					SetBlockType(NoiseMiddle->Get(X, Y, Z));
					
					// Draw top of block
					if(NoiseMiddle->Get(X, Y, Z + 1) == BlockType::Air)
					{
						cube->Top(X, Y, Z );
					}
	
					// Draw bottom of block
					if(NoiseMiddle->Get(X, Y, Z - 1) == BlockType::Air)
					{
						cube->Bottom(X, Y, Z);
					}
					
					// Draw front of block and check neighbour chunks
					if(NoiseMiddle->Get(X, Y + 1, Z) <= BlockType::Air)
					{
						// Check neighbour chunk if it has a block or not
						if(NoiseMiddle->Get(X, Y + 1, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X, ChunkID.Y + 1)))
						{
							// if neighbour block is Air, display tile face
							if(NoiseFront->Get(X, 0, Z) == BlockType::Air)
							{
								cube->Front(X, Y, Z);
							}
						} else
						{
							cube->Front(X, Y, Z);
						}
					}
	
					// Draw back of block  and check neighbour chunks
					if(NoiseMiddle->Get(X, Y - 1, Z) <= BlockType::Air)
					{
						// Check neighbour chunk if it has a block or not
						if(NoiseMiddle->Get(X, Y - 1, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X, ChunkID.Y - 1)))
						{
							// if neighbour chunk block is Air, display tile face
							if(NoiseBack->Get(X, CHUNK_WIDTH - 1, Z) == BlockType::Air)
								cube->Back(X, Y, Z);
						} else
						{
							cube->Back(X, Y, Z);
						}
					}
					
					// Draw left of block and check neighbour chunks
					if(NoiseMiddle->Get(X + 1, Y, Z) <= BlockType::Air)
					{
						// Check neighbour chunk if it has a block or not
						if(NoiseMiddle->Get(X + 1, Y, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X + 1, ChunkID.Y)))
						{
							// if neighbour chunk block is Air, display tile face
							if(NoiseLeft->Get(0, Y, Z) == BlockType::Air)
								cube->Left(X, Y, Z);
						} else
						{
							cube->Left(X, Y, Z);
						}
					}
					
					// Draw right of block and check neighbour chunks
					if(NoiseMiddle->Get(X - 1, Y, Z) <= BlockType::Air)
					{
						// Check neighbour chunk if it has a block or not
						if(NoiseMiddle->Get(X - 1, Y, Z) < BlockType::Air && NoiseMap->Find(FVector2D(ChunkID.X - 1, ChunkID.Y)))
						{
							// if neighbour chunk block is Air, display tile face
							if(NoiseRight->Get(CHUNK_WIDTH - 1, Y, Z) == BlockType::Air)
								cube->Right(X, Y, Z);
						} else
						{
							// if neighbour chunk block is Air, display tile face
							cube->Right(X, Y, Z);
						}
					}
				}
			}
		}
		AsyncTask(ENamedThreads::GameThread, [=] ()
		{		
			this->DrawChunk();
		});
	});

	// Create the mesh!

	double End = FPlatformTime::Seconds();
	
	//UE_LOG(LogTemp, Warning, TEXT("%f ms"), (End-Start) * 1000);
}

void AChunk::SetBlockType(int Sum)
{
	cube->BlockVariations(BlockType::Sand);
}




