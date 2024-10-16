#pragma once

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
