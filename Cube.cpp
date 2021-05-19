// Fill out your copyright notice in the Description page of Project Settings.
#include "Cube.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	pm = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	pm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ACube::OnConstruction(const FTransform& Transform)
{
	ClearMeshData();

	//vertices.Add(FVector(0.0f, 0.0f, 0.0f));
	//vertices.Add(FVector(100.0f, 0.0f, 0.0f));
	//vertices.Add(FVector(0.0f, 100.0f, 0.0f));
	//vertices.Add(FVector(100.f, 100.f, 100.f));
	
	uvs.Init(FVector2D(0.0f, 0.0f), 3);
	normals.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	vertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
	tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);

	pm->CreateMeshSection_LinearColor(0, vertices, triangles, normals, uvs, vertexColors, tangents, false);
}

void ACube::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}



