// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Anekra : ModuleRules
{
	public Anekra(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "UMG", "SlateCore",
			"OnlineSubsystem", "Steamworks", "OnlineSubsystemSteam", "OnlineSubsystemUtils",
			"Niagara",
			"GameplayAbilities", "GameplayTags", "GameplayTasks"
		});
	}
}