#include "FicsitChatWorldModule.h"
#include "BUIExampleRunnable.h"
#include "Configuration/ConfigManager.h"

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
	if (Phase != ELifecyclePhase::INITIALIZATION)
		return;

	// Get mod config
	FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig();

	UE_LOG(LogFicsitChat, Verbose, TEXT("Bot token: %s"), *config.BotToken);

	// TODO: Start Discord bot
	FBUIExampleRunnable *SomeRunnable = new FBUIExampleRunnable();
}
