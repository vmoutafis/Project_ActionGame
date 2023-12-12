// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_ActionGame : ModuleRules
{
	public Project_ActionGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "DerivedDataCache", "AnimGraphRuntime", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Slate", "SlateCore" });
	}
}
