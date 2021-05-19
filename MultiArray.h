// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "utility"

/**
 * 
 */
struct FMultiArray
{
private:
	int Rows = 0;
	int Columns = 0;
	TArray<int> Array;
public:
	FMultiArray(int X, int Y, int Z)
	{
		this->Array.Init(0, X * Y * Z);
		this->Rows = X;
		this->Columns = Y;
	}

	FMultiArray(int X, int Y)
	{
		this->Array.Init(0, X * Y);
		this->Rows = X;
		this->Columns = Y;
	}

	int Get(const int X, const int Y, const int Z)
	{
		// Check if array is out of bounds and return if it is
		if(X >= Rows || Y >= Columns || X < 0 || Y < 0) return -1;
		
		const int Val = X + (Y * Rows) + (Rows * Columns * Z);
		
		if(Val >= Array.Num() || Val < 0)
		{
			return 0; 
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

	void Set (const int X, const int Y, int Value)
	{
		const int Val = X + (Y * Rows);

		this->Array[Val] = Value;
		
	}

	int Length() const
	{
		return this->Array.Num();
	}
};
