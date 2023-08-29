using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using EpicGames.Core;
using UnrealBuildTool;

public class DPPLibrary : ModuleRules
{
	public DPPLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		var platformName = Target.Platform.ToString();
		var libFolder = Path.Combine(ModuleDirectory, "lib", platformName);

		// Include headers
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

		// Library file
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(libFolder, "dpp.lib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			// TODO: Linux support, need to find a DPP build for Linux
			// PublicAdditionalLibraries.Add(Path.Combine(libFolder, "libdpp.a"));
		}

		// DLLs
		RuntimeDependencies.Add("$(BinaryOutputDir)", Path.Combine(libFolder, "*.dll")); // Windows
//      RuntimeDependencies.Add("$(BinaryOutputDir)", Path.Combine(libFolder, "*.so")); // TODO: Linux
	}
}
