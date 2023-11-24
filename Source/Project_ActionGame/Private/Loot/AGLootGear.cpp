// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot\AGLootGear.h"

#include "AGHelperFunctions.h"

void AAGLootGear::BeginPlay()
{
	Super::BeginPlay();

	const FLinearColor RarityColour = UAGHelperFunctions::GetRarityColour(Rarity);
	
	for (auto i = 0; i < Mesh->GetMaterials().Num(); i++)
	{
		UMaterialInstanceDynamic* DynMat = Mesh->CreateDynamicMaterialInstance(i, Mesh->GetMaterials()[i]);

		DynMat->SetVectorParameterValue(FName("Emissive Colour Tint"), RarityColour);
	}
}
