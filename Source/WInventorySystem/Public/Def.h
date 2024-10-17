#pragma once

#include "CoreMinimal.h"
#include "Def.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	None UMETA(DisplayName = "None"),
	Consumable UMETA(DisplayName = "消耗品"),
	Weapon UMETA(DisplayName = "武器"),
	Armor UMETA(DisplayName = "防具"),
	Miscellaneous UMETA(DisplayName = "其他")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None UMETA(DisplayName = "None"),
	HPUP UMETA(DisplayName = "恢复HP"),
	MPUP UMETA(DisplayName = "恢复MP"),
	OneHandedWeapon UMETA(DisplayName = "单手武器"),
	TwoHandedWeapon UMETA(DisplayName = "双手武器"),
	UpperBodyArmor UMETA(DisplayName = "上身防具"),
	LowerBodyArmor UMETA(DisplayName = "下身防具"),
};

USTRUCT(BlueprintType)
struct WINVENTORYSYSTEM_API FInventoryItem
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

	FInventoryItem()
	{
		ID = 0;
		Name = "";
		Category = EItemCategory::None;
		Type = EItemType::None;
		Description = "";
		Icon = nullptr;
		Class = nullptr;
		MaxStackSize = 1;  // 默认不可堆叠
	}

	bool IsValid() const
	{
		return ID > 0 && Name.Len() > 0;
	}

	// 判断是否是相同的物品
	bool IsSameItem(const FInventoryItem& OtherItem) const
	{
		return ID == OtherItem.ID && Name == OtherItem.Name && Category == OtherItem.Category && Type == OtherItem.Type;
	}
};

USTRUCT(BlueprintType)
struct WINVENTORYSYSTEM_API FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FInventoryItem Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Slot")
	int CurrentStackSize;

	FInventorySlot()
	{
		CurrentStackSize = 0;
	}

	bool IsEmpty() const
	{
		return CurrentStackSize == 0 && !Item.IsValid();
	}
	
	bool CanAddItem(const FInventoryItem NewItem) const
	{
		return IsEmpty() || (Item.IsSameItem(NewItem) && CurrentStackSize < Item.MaxStackSize);
	}

	void AddItem(FInventoryItem NewItem, int Amount)
	{
		if (IsEmpty())
		{
			Item = NewItem;
			CurrentStackSize = FMath::Min(Amount, Item.MaxStackSize);
		}
		else if (Item.IsSameItem(NewItem))
		{
			CurrentStackSize += Amount;
			CurrentStackSize = FMath::Min(CurrentStackSize + Amount, Item.MaxStackSize);
		}
	}

	void ClearSlot()
	{
		Item = FInventoryItem();
		CurrentStackSize = 0;
	}
};
