#pragma once

#include "CoreMinimal.h"
#include "Def.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Consumable UMETA(DisplayName = "消耗品"),
	Weapon UMETA(DisplayName = "武器"),
	Armor UMETA(DisplayName = "防具"),
	Miscellaneous UMETA(DisplayName = "其他")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	HPUP UMETA(DisplayName = "恢复HP"),
	MPUP UMETA(DisplayName = "恢复MP"),
	OneHandedWeapon UMETA(DisplayName = "单手武器"),
	TwoHandedWeapon UMETA(DisplayName = "双手武器"),
	UpperBodyArmor UMETA(DisplayName = "上身防具"),
	LowerBodyArmor UMETA(DisplayName = "下身防具"),
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
	int ID;
	
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

	bool IsValid() const
	{
		return ID > 0 && Name.Len() > 0;
	}
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FInventoryItem Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	int Quantity;

	bool CanAddItem(const FInventoryItem NewItem, int Amount) const
	{
		return Item.IsValid() && Item.ID == NewItem.ID && Quantity + Amount <= Item.MaxStackSize;
	}

	void AddItem(FInventoryItem NewItem, int Amount)
	{
		if (!Item.IsValid())
		{
			Item = NewItem;
			Quantity = Amount;
		}
		else if (Item.ID == NewItem.ID)
		{
			Quantity += Amount;
		}
	}
};
