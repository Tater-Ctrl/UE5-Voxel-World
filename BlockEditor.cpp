// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockEditor.h"

ABlockEditor::ABlockEditor(TMap<FVector2D, FMultiArray>* NoiseMap, TMap<FVector2D, AChunk*>* Chunks,  int* ChunkX, int* ChunkY, int* ChunkZ)
{
	this->NoiseMap = NoiseMap;
	this->Chunks = Chunks;

	this->ChunkX = ChunkX;
	this->ChunkY = ChunkY;
	this->ChunkZ = ChunkZ;
}

void ABlockEditor::BreakBlock(FVector Position, FVector2D ChunkID)
{
	if(NoiseMap->Find(ChunkID))
	{
		if(Position.Z == 0) return;
		if(NoiseMap->operator[](ChunkID).Get(Position) >= 0)
		{
			NoiseMap->operator[](ChunkID).Set(Position.X, Position.Y, Position.Z, 0);

			UpdateSurroundingChunkBlocks(ChunkID, Position);
		
			Chunks->operator[](ChunkID)->UpdateChunkMesh();
		} else
		{
			if(Position.X >= *ChunkX)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y)).Set(0, Position.Y, Position.Z, 0);
				UpdateSurroundingChunkBlocks(ChunkID, Position);
				Chunks->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
			if(Position.X < 0)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y)).Set(*ChunkX - 1, Position.Y, Position.Z, 0);
				UpdateSurroundingChunkBlocks(ChunkID, Position);
				Chunks->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
			if(Position.Y >= *ChunkY)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1)).Set(Position.X, 0, Position.Z, 0);
				UpdateSurroundingChunkBlocks(ChunkID, Position);
				Chunks->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
			if(Position.Y < 0)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1)).Set(Position.X, *ChunkY - 1, Position.Z, 0);
				UpdateSurroundingChunkBlocks(ChunkID, Position);
				Chunks->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
		}
	}
}

void ABlockEditor::PlaceBlock(FVector Position, FVector2D ChunkID)
{
	if(NoiseMap->Find(ChunkID))
	{
		if(NoiseMap->operator[](ChunkID).Get(Position) >= 0)
		{
			NoiseMap->operator[](ChunkID).Set(Position.X, Position.Y, Position.Z, 1);
			UpdateSurroundingChunkBlocks(ChunkID, Position);
			Chunks->operator[](ChunkID)->UpdateChunkMesh();
		} else
		{
			if(Position.X >= *ChunkX)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y)).Set(0, Position.Y, Position.Z, 1);
				Chunks->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
			if(Position.X < 0)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y)).Set(*ChunkX - 1, Position.Y, Position.Z, 1);
				Chunks->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
			if(Position.Y >= *ChunkY)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1)).Set(Position.X, 0, Position.Z, 1);
				Chunks->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
			if(Position.Y < 0)
			{
				NoiseMap->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1)).Set(Position.X, *ChunkY - 1, Position.Z, 1);
				Chunks->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1))->UpdateChunkMesh();
				Chunks->operator[](ChunkID)->UpdateChunkMesh();
			}
		}
	}
}

void ABlockEditor::UpdateSurroundingChunkBlocks(FVector2D ChunkID, FVector Position)
{
	if(NoiseMap->operator[](ChunkID).Get(Position.X + 1, Position.Y, Position.Z) == -1) Chunks->operator[](FVector2D(ChunkID.X + 1, ChunkID.Y))->UpdateChunkMesh();
	if(NoiseMap->operator[](ChunkID).Get(Position.X - 1, Position.Y, Position.Z) == -1) Chunks->operator[](FVector2D(ChunkID.X - 1, ChunkID.Y))->UpdateChunkMesh();
	if(NoiseMap->operator[](ChunkID).Get(Position.X, Position.Y + 1, Position.Z) == -1) Chunks->operator[](FVector2D(ChunkID.X, ChunkID.Y + 1))->UpdateChunkMesh();
	if(NoiseMap->operator[](ChunkID).Get(Position.X, Position.Y - 1, Position.Z) == -1) Chunks->operator[](FVector2D(ChunkID.X, ChunkID.Y - 1))->UpdateChunkMesh();
}

ABlockEditor::~ABlockEditor()
{
}
