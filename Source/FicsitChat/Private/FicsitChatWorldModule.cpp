#include "FicsitChatWorldModule.h"
#include "Configuration/ConfigManager.h"
#include "BUIExampleRunnable.h"

// THIRD_PARTY_INCLUDES_START
// #include "dpp/dpp.h"
// THIRD_PARTY_INCLUDES_END

UFicsitChatWorldModule::UFicsitChatWorldModule() {
#if !WITH_EDITOR
	this->bRootModule = true;
#endif
}

// Runs on game world load
void UFicsitChatWorldModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
	// Get mod config
	FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig();

	UE_LOG(LogFicsitChat, Verbose, TEXT("Bot token: %s"), *config.BotToken);

	// TODO: Start Discord bot
	TSharedPtr<FBUIExampleRunnable> SomeRunnable = MakeShared<FBUIExampleRunnable>(10);
}
