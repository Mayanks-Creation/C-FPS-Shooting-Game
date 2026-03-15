// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CyrusFPSAssignment : ModuleRules
{
	public CyrusFPSAssignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
            "HTTP",
			"Json",
			"JsonUtilities",
            "AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CyrusFPSAssignment",
			"CyrusFPSAssignment/Variant_Horror",
			"CyrusFPSAssignment/Variant_Horror/UI",
			"CyrusFPSAssignment/Variant_Shooter",
			"CyrusFPSAssignment/Variant_Shooter/AI",
			"CyrusFPSAssignment/Variant_Shooter/UI",
			"CyrusFPSAssignment/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
