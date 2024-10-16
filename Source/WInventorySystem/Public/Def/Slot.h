#pragma once
#include "Item.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FInventoryItem* Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	int Quantity;

	bool CanAddItem(const FInventoryItem* NewItem, int Amount) const
	{
		return Item != nullptr && Item == NewItem && Quantity + Amount <= Item->MaxStackSize;
	}

	void AddItem(FInventoryItem* NewItem, int Amount)
	{
		if (Item == nullptr)
		{
			Item = NewItem;
			Quantity = Amount;
		}
		else if (Item == NewItem)
		{
			Quantity += Amount;
		}
	}
};
