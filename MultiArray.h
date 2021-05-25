// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FMultiArray
{
private:
	int Rows = 0;
	int Columns = 0;
	int Pillars = 0;
	TArray<int> Array;
public:
	FMultiArray(const int X, const int Y, const int Z)
	{
		this->Array.Init(0, X * Y * Z);
		this->Rows = X;
		this->Columns = Y;
		this->Pillars = Z;
	}

	FMultiArray(const int X, const int Y)
	{
		this->Array.Init(0, X * Y);
		this->Rows = X;
		this->Columns = Y;
	}

	int operator[](const int& Index)
	{
		return Array[Index];
	}

	int Get(const int X, const int Y, const int Z)
	{
		// Check if array is out of bounds and return if it is
		if(X >= Rows || Y >= Columns || Z >= Pillars || X < 0 || Y < 0 || Z < 0) return -1;
		
		const int Val = X + (Y * Rows) + (Rows * Columns * Z);
		
		if(Val >= Array.Num() || Val < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Array out of bounds!"));
			return -1; 
		}
		
		return this->Array[Val];
	}

	int Get(const FVector Pos)
	{
		if(Pos.X >= Rows || Pos.Y >= Columns || Pos.Z >= Pillars || Pos.X < 0 || Pos.Y < 0 || Pos.Z < 0) return -1;

		const int Val = Pos.X + (Pos.Y * Rows) + (Rows * Columns * Pos.Z);
		
		if(Val >= Array.Num() || Val < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Array out of bounds!"));
			return -1; 
		}
		
		return this->Array[Val];
	}

	int Get(const int X, const int Y)
	{
		if(X >= Rows || Y >= Columns || X < 0 || Y < 0) return -1;

		const int Val = X + (Y * Rows);

		if(Val >= Array.Num() || Val < 0)
		{
			return 0;
		}

		return this->Array[Val];
	}

	int Get(const int index)
	{
		return this->Array[index];
	}

	void Set (const int X, const int Y, const int Z, const int Value)
	{
		if(X >= Rows || Y >= Columns || Z >= Pillars || X < 0 || Y < 0 || Z < 0) return;
		
		const int Val = X + (Y * Rows) + (Rows * Columns * Z);

		this->Array[Val] = Value;
	}

	void Set (const int X, const int Y, const int Value)
	{
		const int Val = X + (Y * Rows);

		this->Array[Val] = Value;
		
	}

	int Length() const
	{
		return this->Array.Num();
	}
};
