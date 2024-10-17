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
	int MaxSlotsNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory", Replicated)
	TArray<FInventorySlot> Slots;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	void InitializeInventory(int SlotCount);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	bool AddItemToInventory(const FInventoryItem& NewItem, int Quantity);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	void SortInventory();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	void SwapItems(int IndexA, int IndexB);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	void DragItem(int FromSlotIndex, int ToSlotIndex);

	// 消耗品：减少数量，当数量为0时移除该物品
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	void UseItem(int SlotIndex);

	// 武器：触发装备武器的逻辑
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	void EquipWeapon(const FInventoryItem& WeaponItem);
protected:
	virtual void BeginPlay() override;
};
