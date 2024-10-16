// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::InitializeInventory(int SlotCount)
{
	
}

bool UInventoryComponent::AddItemToInventory(FInventoryItem* NewItem, int Quantity)
{
	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.CanAddItem(NewItem, Quantity))
		{
			Slot.AddItem(NewItem, Quantity);
			return true;
		}
	}

	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Item == nullptr)
		{
			Slot.AddItem(NewItem, Quantity);
			return true;
		}
	}

	return false;
}

void UInventoryComponent::SortByCategory()
{
	InventorySlots.Sort([](const FInventorySlot& A, const FInventorySlot& B)
	{
		if (A.Item && B.Item)
		{
			return A.Item->Category < B.Item->Category && A.Item->Type < B.Item->Type; // 直接比较FName
		}
		return false;
	});
}

void UInventoryComponent::SwapItems(int IndexA, int IndexB)
{
	if (InventorySlots.IsValidIndex(IndexA) && InventorySlots.IsValidIndex(IndexB))
	{
		FInventorySlot Temp = InventorySlots[IndexA];
		InventorySlots[IndexA] = InventorySlots[IndexB];
		InventorySlots[IndexB] = Temp;
	}
}

void UInventoryComponent::UseItem(int SlotIndex)
{
	if (InventorySlots.IsValidIndex(SlotIndex))
	{
		FInventorySlot& Slot = InventorySlots[SlotIndex];

		if (Slot.Item != nullptr)
		{
			switch (Slot.Item->Category)
			{
			case EItemCategory::Consumable:
				// 使用消耗品逻辑
					Slot.Quantity--;
				if (Slot.Quantity <= 0)
				{
					Slot.Item = nullptr;
					Slot.Quantity = 0;
				}
				break;

			case EItemCategory::Weapon:
				// 装备武器逻辑
					EquipWeapon(*Slot.Item);
				break;

				// 其他类型处理
			default:
				break;
			}
		}
	}
}

void UInventoryComponent::EquipWeapon(const FInventoryItem& WeaponItem)
{
	// TODO
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册需要复制的变量
	DOREPLIFETIME(UInventoryComponent, MaxSlots);
	DOREPLIFETIME(UInventoryComponent, InventorySlots);
}
