using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using EpicGames.Core;
using UnrealBuildTool;

public class FicsitChat : ModuleRules
{
	public FicsitChat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// FactoryGame transitive dependencies
		// Not all of these are required, but including the extra ones saves you from having to add them later.
		PublicDependencyModuleNames.AddRange(new[] {
			"Core", "CoreUObject",
			"Engine",
			"DeveloperSettings",
			"PhysicsCore",
			"InputCore",
			"OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils",
			"SignificanceManager",
			"GeometryCollectionEngine",
			"ChaosVehiclesCore", "ChaosVehicles", "ChaosSolverEngine",
			"AnimGraphRuntime",
			"AkAudio",
			"AssetRegistry",
			"NavigationSystem",
			"ReplicationGraph",
			"AIModule",
			"GameplayTasks",
			"SlateCore", "Slate", "UMG",
			"InstancedSplines",
			"RenderCore",
			"CinematicCamera",
			"Foliage",
			"Niagara",
			"EnhancedInput",
			"GameplayCameras",
			"TemplateSequence",
			"NetCore",
			"GameplayTags",
		});

		// FactoryGame plugins
		PublicDependencyModuleNames.AddRange(new[] {
			"AbstractInstance",
			"InstancedSplinesComponent",
			"SignificanceISPC"
		});

		// Header stubs
		PublicDependencyModuleNames.AddRange(new[] {
			"DummyHeaders",
		});

		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "OnlineBlueprintSupport", "AnimGraph" });
		}
		PublicDependencyModuleNames.AddRange(new string[] { "FactoryGame", "SML", "DPPLibrary" });

		var platformName = Target.Platform.ToString();
		var binaryFolder = Path.Combine(ModuleDirectory, "../../Binaries", platformName);

		RuntimeDependencies.Add(Path.Combine(binaryFolder, "dpp.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libcrypto-1_1-x64.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libsodium.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libssl-1_1-x64.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "opus.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "zlib1.dll"));
	}
}
