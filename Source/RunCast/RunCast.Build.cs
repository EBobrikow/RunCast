// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RunCast : ModuleRules
{
	public RunCast(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[] 
			{ 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"WebSockets",
                "Json",
                "JsonUtilities",
                "ALSV4_CPP",
                "NavigationSystem",
				"AIModule", 
				"GameplayTasks",
                "Niagara",
				"GameplayAbilities",
				"GameplayTags"
            });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
