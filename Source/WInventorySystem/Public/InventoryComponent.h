// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Def.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=("Wrath"), meta=(BlueprintSpawnableComponent))
class WINVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory", Replicated)
	int MaxSlots;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory", Replicated)
	TArray<FInventorySlot> InventorySlots;

	void static InitializeInventory(int SlotCount);

	bool AddItemToInventory(const FInventoryItem& NewItem, int Quantity);

	void SortByCategory();

	void SwapItems(int IndexA, int IndexB);

	// 消耗品：减少数量，当数量为0时移除该物品
	void UseItem(int SlotIndex);

	// 武器：触发装备武器的逻辑
	void EquipWeapon(const FInventoryItem& WeaponItem);
protected:
	virtual void BeginPlay() override;
};
