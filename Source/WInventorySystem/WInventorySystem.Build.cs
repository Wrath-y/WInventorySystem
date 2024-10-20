// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WInventorySystem : ModuleRules
{
	public WInventorySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
