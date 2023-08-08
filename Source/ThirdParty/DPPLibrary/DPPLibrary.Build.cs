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
		var libraryFolder = Path.Combine(ModuleDirectory, platformName);
		var binaryFolder = Path.Combine(ModuleDirectory, "../../../Binaries", platformName);

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
		PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "dpp.lib"));
		PrivateIncludePaths.Add(binaryFolder);
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "dpp.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libcrypto-1_1-x64.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libsodium.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "libssl-1_1-x64.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "opus.dll"));
		RuntimeDependencies.Add(Path.Combine(binaryFolder, "zlib1.dll"));
	}
}
