using System.IO;
using UnrealBuildTool;

public class DPPLibrary : ModuleRules
{
	public DPPLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		var thirdPartyFolder = Path.Combine(ModuleDirectory, "./");
		PublicIncludePaths.Add(Path.Combine(thirdPartyFolder, "include"));

		var platformName = Target.Platform.ToString();
		var binaryFolder = Path.Combine(thirdPartyFolder, "Binaries", platformName);
		var libraryFolder = Path.Combine(thirdPartyFolder, platformName);

		PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "dpp.lib"));
		RuntimeDependencies.Add("$(TargetOutputDir)/dpp.dll", Path.Combine(binaryFolder, "dpp.dll"));
		PrivateIncludePaths.Add(binaryFolder);
	}
}
