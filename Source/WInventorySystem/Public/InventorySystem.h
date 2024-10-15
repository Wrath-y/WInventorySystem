// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"

// 创建一个struct来存储物品信息
USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	FString ItemID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	int ItemCount;
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	FString Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	AActor* ItemClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	int StackSize;
};

UCLASS(Blueprintable, ClassGroup=("Wrath"), meta=(BlueprintSpawnableComponent))
class WINVENTORYSYSTEM_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventorySystem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory", Replicated)
	int InventorySize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory", Replicated)
	TArray<FInventorySlot> Content;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
