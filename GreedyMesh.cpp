// Fill out your copyright notice in the Description page of Project Settings.


#include "GreedyMesh.h"

AGreedyMesh::AGreedyMesh()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	SetRootComponent(Mesh);

	Mesh->CastShadow = false;
	Mesh->bUseAsyncCooking = true;
}

AGreedyMesh::~AGreedyMesh()
{
}

void AGreedyMesh::AddIndices(bool Reverse = false)
{
	if(!Reverse)
	{
		Indices.Add(0 + Vertices.Num());
		Indices.Add(1 + Vertices.Num());
		Indices.Add(3 + Vertices.Num());
		Indices.Add(1 + Vertices.Num());
		Indices.Add(2 + Vertices.Num());
		Indices.Add(3 + Vertices.Num());
	} else
	{	Indices.Add(3 + Vertices.Num());
		Indices.Add(2 + Vertices.Num());
		Indices.Add(1 + Vertices.Num());
		Indices.Add(3 + Vertices.Num());
		Indices.Add(1 + Vertices.Num());
		Indices.Add(0 + Vertices.Num());
	}
}

void AGreedyMesh::AddNormals(const FVector Nor)
{
	for (int i = 0; i < 4; ++i) {
		Normals.Add(Nor);
	}
}

void AGreedyMesh::CreateGreedyChunk(FVector2D ChunkID)
{
	Noise = &NoiseMap->operator[](ChunkID);
	double start = FPlatformTime::Seconds();
	for(int Z = 0; Z < *ChunkZ; ++Z)
	{
		CreateTop(Z);
	}
	for(int X = 0; X < *ChunkX; ++X)
	{
		CreateRight(X);
		CreateLeft(X);
	}
	for(int Y = 0; Y < *ChunkY; ++Y)
	{
		CreateFront(Y);
		CreateBack(Y);
	}

	Mesh->CreateMeshSection_LinearColor(0, Vertices, Indices, Normals, Uvs, VertexColors, Tangents, true);

	double end = FPlatformTime::Seconds();

	//UE_LOG(LogTemp, Warning, TEXT("%f ms"), (end-start) * 1000);
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
					AddIndices();
					AddNormals(FVector(0.0f, 0.0f, 1.0f));

					Vertices.Add(FVector(X * BlockSize, Y * BlockSize, (Z + 1) * BlockSize));
				
					while(!Greed)
					{					
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
									Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, (Z + 1) * BlockSize));
									MaxLength = AddY;
								}
								AddY = Y;
								++AddX;
							} else
							{
								if(AddX == X) Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, (Z + 1) * BlockSize));
								
								Vertices.Add(FVector((AddX + 1) * BlockSize, AddY * BlockSize, (Z + 1) * BlockSize));
								Vertices.Add(FVector((AddX + 1) * BlockSize, Y * BlockSize, (Z + 1) * BlockSize));
								Greed = true;
							}
						}
					}
				}
			}
		}
	}
}

void AGreedyMesh::CreateFront(const int Y)
{
	TArray<bool> CheckedBlock;

	CheckedBlock.Init(false, *ChunkX * *ChunkZ);
	
	for(int Z = 0; Z < *ChunkZ; ++Z)
	{
		for(int X = 0; X < *ChunkX; ++X)
		{
			if(!CheckedBlock[X + (Z * 16)])
			{
				bool Greed = false;
				bool ExpandX = true;

				int AddX = X;
				int AddZ = Z;

				int MaxLength = *ChunkY;
			
				if(Noise->Get(X, Y, Z) > 0 && Noise->Get(X, Y + 1, Z) == 0)
				{
					AddIndices();
					AddNormals(FVector(0.0f, 1.0f, 0.0f));
				
					while(!Greed)
					{				
						if(Noise->Get(AddX, Y, AddZ) > 0 && Noise->Get(AddX, Y + 1, AddZ) == 0 && AddX < MaxLength && !CheckedBlock[AddX + (AddZ * *ChunkY)])
						{
							// Check neighbour if you can expand
							if(Noise->Get(AddX, Y, AddZ + 1) <= 0 || Noise->Get(AddX, Y + 1, AddZ + 1) != 0)
							{
								ExpandX = false;
							}
							
							CheckedBlock[AddX + (AddZ * *ChunkY)] = true;
							++AddX;
						} else
						{
							if(ExpandX)
							{
								if(AddZ == Z)
								{
									Vertices.Add(FVector(AddX * BlockSize, (Y + 1) * BlockSize, Z * BlockSize));
									MaxLength = AddX;
								}
								AddX = X;
								++AddZ;
							} else
							{
								if(AddZ == Z) Vertices.Add(FVector(AddX * BlockSize, (Y + 1) * BlockSize, Z * BlockSize));
								
								Vertices.Add(FVector(AddX * BlockSize, (Y + 1) * BlockSize, (AddZ + 1) * BlockSize));
								Vertices.Add(FVector(X * BlockSize, (Y + 1) * BlockSize, (AddZ + 1) * BlockSize));
								Vertices.Add(FVector(X * BlockSize, (Y + 1) * BlockSize, Z * BlockSize));
								Greed = true;
							}
						}
					}
				}
			}
		}
	}
}

void AGreedyMesh::CreateBack(const int Y)
{
	TArray<bool> CheckedBlock;

	CheckedBlock.Init(false, *ChunkX * *ChunkZ);
	
	for(int Z = 0; Z < *ChunkZ; ++Z)
	{
		for(int X = 0; X < *ChunkX; ++X)
		{
			if(!CheckedBlock[X + (Z * 16)])
			{
				bool Greed = false;
				bool ExpandZ = true;

				int AddX = X;
				int AddZ = Z;

				int MaxLength = *ChunkY;
			
				if(Noise->Get(X, Y, Z) > 0 && Noise->Get(X, Y - 1, Z) == 0)
				{
					AddIndices(true);
					AddNormals(FVector(0.0f, -1.0f, 0.0f));

					Vertices.Add(FVector(X * BlockSize, Y * BlockSize, Z * BlockSize));
				
					while(!Greed)
					{	
						if(Noise->Get(AddX, Y, AddZ) > 0 && Noise->Get(AddX, Y - 1, AddZ) == 0 && AddX < MaxLength && !CheckedBlock[AddX + (AddZ * *ChunkY)])
						{
							// Check neighbour if you can expand
							if(Noise->Get(AddX, Y, AddZ + 1) <= 0 || Noise->Get(AddX, Y - 1, AddZ + 1) != 0)
							{
								ExpandZ = false;
							}
							
							CheckedBlock[AddX + (AddZ * *ChunkY)] = true;
							++AddX;
						} else
						{
							if(ExpandZ)
							{
								if(AddX == X)
								{
									Vertices.Add(FVector(AddX * BlockSize, Y * BlockSize, Z * BlockSize));
									MaxLength = AddX;
								}
								AddX = X;
								++AddZ;
							} else
							{
								if(AddZ == Z) Vertices.Add(FVector(AddX * BlockSize, Y * BlockSize, Z * BlockSize));
								
								Vertices.Add(FVector(AddX * BlockSize, Y * BlockSize, (AddZ + 1) * BlockSize));
								Vertices.Add(FVector(X * BlockSize, Y * BlockSize, (AddZ + 1) * BlockSize));
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
	
	for(int Z = 0; Z < *ChunkZ; ++Z)
	{
		for(int Y = 0; Y < *ChunkX; ++Y)
		{
			if(!CheckedBlock[Y + (Z * 16)])
			{
				bool Greed = false;
				bool ExpandX = true;

				int AddY = Y;
				int AddZ = Z;

				int MaxLength = *ChunkY;
			
				if(Noise->Get(X, Y, Z) > 0 && Noise->Get(X - 1, Y, Z) == 0)
				{
					AddIndices();
					AddNormals(FVector(-1.0f, 0.0f, 0.0f));
				
					while(!Greed)
					{	
						if(Noise->Get(X, AddY, AddZ) > 0 && Noise->Get(X - 1, AddY, AddZ) == 0 && AddY < MaxLength && !CheckedBlock[AddY + (AddZ * *ChunkY)])
						{
							// Check neighbour if you can expand
							if(Noise->Get(X, AddY, AddZ + 1) <= 0 || Noise->Get(X - 1, AddY, AddZ + 1) != 0)
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
								if(AddZ == Z) Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, Z * BlockSize));
								
								Vertices.Add(FVector(X * BlockSize, AddY * BlockSize, (AddZ + 1) * BlockSize));
								Vertices.Add(FVector(X * BlockSize, Y * BlockSize, (AddZ + 1) * BlockSize));
								Vertices.Add(FVector(X * BlockSize, Y * BlockSize, Z * BlockSize));
								Greed = true;
							}
						}
					}
				}
			}
		}
	}
}

void AGreedyMesh::CreateLeft(const int X)
{
	TArray<bool> CheckedBlock;

	CheckedBlock.Init(false, *ChunkY * *ChunkZ);
	
	for(int Z = 0; Z < *ChunkZ; ++Z)
	{
		for(int Y = 0; Y < *ChunkX; ++Y)
		{
			if(!CheckedBlock[Y + (Z * 16)])
			{
				bool Greed = false;
				bool ExpandX = true;

				int AddY = Y;
				int AddZ = Z;

				int MaxLength = *ChunkY;
			
				if(Noise->Get(X, Y, Z) > 0 && Noise->Get(X + 1, Y, Z) == 0)
				{
					AddIndices(true);
					AddNormals(FVector(1.0f, 0.0f, 0.0f));

					Vertices.Add(FVector((X + 1) * BlockSize, Y * BlockSize, Z * BlockSize));
				
					while(!Greed)
					{	
						if(Noise->Get(X, AddY, AddZ) > 0 && Noise->Get(X + 1, AddY, AddZ) == 0 && AddY < MaxLength && !CheckedBlock[AddY + (AddZ * *ChunkY)])
						{
							// Check neighbour if you can expand
							if(Noise->Get(X, AddY, AddZ + 1) <= 0 || Noise->Get(X + 1, AddY, AddZ + 1) != 0)
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
									Vertices.Add(FVector((X + 1) * BlockSize, AddY * BlockSize, Z * BlockSize));
									MaxLength = AddY;
								}
								AddY = Y;
								++AddZ;
							} else
							{
								if(AddZ == Z) Vertices.Add(FVector((X + 1) * BlockSize, AddY * BlockSize, Z * BlockSize));
								
								Vertices.Add(FVector((X + 1) * BlockSize, AddY * BlockSize, (AddZ + 1) * BlockSize));
								Vertices.Add(FVector((X + 1) * BlockSize, Y * BlockSize, (AddZ + 1) * BlockSize));
								Greed = true;
							}
						}
					}
				}
			}
		}
	}
}