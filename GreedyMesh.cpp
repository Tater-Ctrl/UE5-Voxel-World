// Fill out your copyright notice in the Description page of Project Settings.


#include "GreedyMesh.h"

AGreedyMesh::AGreedyMesh()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	this->NoiseMap = NoiseMap;
}



AGreedyMesh::~AGreedyMesh()
{
}

void AGreedyMesh::CreateGreedyChunk(FVector2D ChunkID, FVector Pos)
{
	//bool CheckedBlock[*ChunkZ][*ChunkY][*ChunkX];
	Noise = &NoiseMap->operator[](ChunkID);
	
	for(int Z = 0; Z < *ChunkZ; ++Z)
	{
		CreateTop(Z);
	}
	for(int X = 0; X < *ChunkX; ++X)
	{
		CreateRight(X);
	}

	Mesh->CreateMeshSection_LinearColor(0, Vertices, Indices, Normals, Uvs, VertexColors, Tangents, true);
}

void AGreedyMesh::CreateTop(const int Z)
{
	TArray<bool> CheckedBlock;

	CheckedBlock.Init(false, *ChunkX * *ChunkY);
	
	for(int X = 0; X < *ChunkY; ++X)
	{
		for(int Y = 0; Y < *ChunkX; ++Y)
		{
			if(!CheckedBlock[X + (Y * *ChunkY)])
			{
				bool Greed = false;
				bool ExpandX = true;
				
				int AddX = X;
				int AddY = Y;

				int MaxLength = *ChunkY;
			
				if(Noise->Get(X, Y, Z) > 0 && Noise->Get(X, Y, Z + 1) == 0)
				{
					Indices.Add(0 + Vertices.Num());
					Indices.Add(1 + Vertices.Num());
					Indices.Add(3 + Vertices.Num());
					Indices.Add(1 + Vertices.Num());
					Indices.Add(2 + Vertices.Num());
					Indices.Add(3 + Vertices.Num());

					for (int i = 0; i < 4; ++i) {
						Normals.Add(FVector(0.0f, 0.0f, 1.0f));
					}
				
					Vertices.Add(FVector(X * BlockSize, Y * BlockSize, Z * BlockSize));
				
					while(!Greed)
					{
						if(AddX > *ChunkX || AddY > *ChunkY) Greed = true;
						
						if(Noise->Get(AddX, AddY, Z) > 0 && Noise->Get(AddX, AddY, Z + 1) == 0 && AddY < MaxLength && !CheckedBlock[AddX + (AddY * 16)])
						{
							// Check neighbour if you can expand
							if(Noise->Get(AddX + 1, AddY, Z) <= 0 || Noise->Get(AddX + 1, AddY, Z + 1) != 0)
							{
								ExpandX = false;
							}
							
							CheckedBlock[AddX + (AddY * *ChunkY)] = true;
							++AddY;
						} else
						{
							if(ExpandX)
							{
								if(AddX == X)
								{
									Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, Z * BlockSize));
									MaxLength = AddY;
								}
								AddY = Y;
								++AddX;
							} else
							{
								if(AddX == X) Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, Z * BlockSize));
								
								Vertices.Add(FVector((AddX + 1) * BlockSize, AddY * BlockSize, Z * BlockSize));
								Vertices.Add(FVector((AddX + 1) * BlockSize, Y * BlockSize, Z * BlockSize));
								Greed = true;
							}
						}
					}
				}
			}
		}
	}
}

void AGreedyMesh::CreateRight(const int X)
{
	TArray<bool> CheckedBlock;

	CheckedBlock.Init(false, *ChunkY * *ChunkZ);
	
	for(int Z = 0; Z < *ChunkY; ++Z)
	{
		for(int Y = 0; Y < *ChunkX; ++Y)
		{
			if(!CheckedBlock[X + (Y * 16)])
			{
				bool Greed = false;
				bool ExpandX = true;

				int AddY = Y;
				int AddZ = Z;

				int MaxLength = *ChunkY;
			
				if(Noise->Get(X, Y, Z) > 0 && Noise->Get(X - 1, Y, Z) == 0)
				{
					Indices.Add(0 + Vertices.Num());
					Indices.Add(1 + Vertices.Num());
					Indices.Add(3 + Vertices.Num());
					Indices.Add(1 + Vertices.Num());
					Indices.Add(2 + Vertices.Num());
					Indices.Add(3 + Vertices.Num());

					for (int i = 0; i < 4; ++i) {
						Normals.Add(FVector(-1.0f, 0.0f, 0.0f));
					}
				
					Vertices.Add(FVector(X * BlockSize, Y * BlockSize, Z * BlockSize));
				
					while(!Greed)
					{
						if(AddZ > *ChunkZ || AddY > *ChunkY) Greed = true;
						
						if(Noise->Get(X, AddY, AddZ) > 0 && Noise->Get(X - 1, AddY, AddZ) == 0 && AddY < MaxLength && !CheckedBlock[AddY + (AddZ * *ChunkY)])
						{
							// Check neighbour if you can expand
							if(Noise->Get(AddZ + 1, AddY, Z) <= 0 || Noise->Get(AddZ + 1, AddY, Z + 1) != 0)
							{
								ExpandX = false;
							}
							
							CheckedBlock[AddY + (AddZ * *ChunkY)] = true;
							++AddY;
						} else
						{
							if(ExpandX)
							{
								if(AddZ == X)
								{
									Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, Z * BlockSize));
									MaxLength = AddY;
								}
								AddY = Y;
								++AddZ;
							} else
							{
								if(AddZ == X) Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, Z * BlockSize));
								
								Vertices.Add(FVector((AddZ + 1) * BlockSize, AddY * BlockSize, Z * BlockSize));
								Vertices.Add(FVector((AddZ + 1) * BlockSize, Y * BlockSize, Z * BlockSize));
								Greed = true;
							}
						}
					}
				}
			}
		}
	}
}

