// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MythsAndLegends : ModuleRules
{
	public MythsAndLegends(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "HeadMountedDisplay", 
	        "NavigationSystem", 
	        "AIModule",
	        "GameplayTasks",
	        "UMG",
	        "Slate",
	        "SlateCore"
        });
    }
}
