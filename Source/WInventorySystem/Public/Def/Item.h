#pragma once

#include "InventoryComponent.h"
#include "ItemDef.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	EItemCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	EItemType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	FString Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	AActor* Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	int MaxStackSize;
};
