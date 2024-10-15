// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventorySystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册需要复制的变量
	DOREPLIFETIME(UInventorySystem, InventorySize);
	DOREPLIFETIME(UInventorySystem, Content);
}
