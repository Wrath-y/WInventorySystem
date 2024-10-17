// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Def.h"
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
	MaxSlotsNum = SlotCount;
	Slots.SetNum(SlotCount);
}

bool UInventoryComponent::AddItemToInventory(const FInventoryItem& NewItem, int Quantity)
{
	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.CanAddItem(NewItem))
		{
			Slot.AddItem(NewItem, Quantity);
			return true;
		}
	}

	return false;
}

void UInventoryComponent::SortInventory()
{
	Slots.Sort([](const FInventorySlot& A, const FInventorySlot& B)
	   {
		   if (A.Item.Category != B.Item.Category)
		   {
			   return A.Item.Category < B.Item.Category;  // 先按大类排序
		   }
		   return A.Item.Type < B.Item.Type;  // 再按小类排序
	   });
}

void UInventoryComponent::SwapItems(int IndexA, int IndexB)
{
	if (Slots.IsValidIndex(IndexA) && Slots.IsValidIndex(IndexB))
	{
		FInventorySlot Temp = Slots[IndexA];
		Slots[IndexA] = Slots[IndexB];
		Slots[IndexB] = Temp;
	}
}

// 拖动物品并交换两个格子的物品
void UInventoryComponent::DragItem(int FromSlotIndex, int ToSlotIndex)
{
	if (Slots.IsValidIndex(FromSlotIndex) && Slots.IsValidIndex(ToSlotIndex))
	{
		SwapItems(FromSlotIndex, ToSlotIndex);
	}
}

void UInventoryComponent::UseItem(int SlotIndex)
{
	if (Slots.IsValidIndex(SlotIndex))
	{
		FInventorySlot& Slot = Slots[SlotIndex];

		if (!Slot.IsEmpty() && Slot.Item.IsValid())
		{
			switch (Slot.Item.Category)
			{
			case EItemCategory::Consumable:
				// 使用消耗品逻辑
					Slot.CurrentStackSize--;
				if (Slot.CurrentStackSize <= 0)
				{
					Slot.Item = FInventoryItem();
					Slot.CurrentStackSize = 0;
				}
				break;

			case EItemCategory::Weapon:
				// 装备武器逻辑
					EquipWeapon(Slot.Item);
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
	DOREPLIFETIME(UInventoryComponent, MaxSlotsNum);
	DOREPLIFETIME(UInventoryComponent, Slots);
}
