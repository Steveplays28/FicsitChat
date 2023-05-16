// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class FicsitChat : ModuleRules
{
	public FicsitChat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject",
			"Engine",
			"InputCore",
			"OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNULL",
			"SignificanceManager",
			"PhysX", "APEX", "PhysXVehicles", "ApexDestruction",
			"AkAudio",
			"ReplicationGraph",
			"UMG",
			"AIModule",
			"NavigationSystem",
			"AssetRegistry",
			"GameplayTasks",
			"AnimGraphRuntime",
			"Slate", "SlateCore",
			"Json",
			"AbstractInstance",
			"Niagara",
			"LevelSequence",
		});


		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "OnlineBlueprintSupport", "AnimGraph" });
		}
		PublicDependencyModuleNames.AddRange(new string[] { "FactoryGame", "SML", "DPPLibrary" });

		var thirdPartyFolder = Path.Combine(ModuleDirectory, "../../ThirdParty");
		var platformName = Target.Platform.ToString();
		var binaryFolder = Path.Combine(thirdPartyFolder, "Binaries", platformName);

		RuntimeDependencies.Add(Path.Combine(binaryFolder, "dpp.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libcrypto-1_1-x64.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libsodium.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libssl-1_1-x64.dll.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "opus.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "zlib1.dll"));
	}
}
