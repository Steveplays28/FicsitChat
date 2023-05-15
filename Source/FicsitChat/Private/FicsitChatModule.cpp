#include "FicsitChatModule.h"
#include "FGChatManager.h"
#include "FGPlayerState.h"
#include "Patching/NativeHookManager.h"

#define LOCTEXT_NAMESPACE "FFicsitChatModule"

DEFINE_LOG_CATEGORY(LogFicsitChat);

void FFicsitChatModule::StartupModule() {
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// TODO: Start Discord bot

	// Register hooks
	RegisterHooks();
}

void FFicsitChatModule::ShutdownModule() {
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FFicsitChatModule::RegisterHooks() {
#if !WITH_EDITOR
	AFGChatManager *afgChatManager = GetMutableDefault<AFGChatManager>();
	SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGChatManager::Multicast_BroadcastChatMessage, afgChatManager, [](AFGChatManager *self, const FChatMessageStruct &newMessage) {
		// do some nice stuff there
		// FString logMessage = FString::Format(*"Chat message by {0} sent to all clients: {1}", {newMessage.Sender->GetUserName(), newMessage.MessageString});
		UE_LOG(LogFicsitChat, Verbose, TEXT("Chat message by %s sent to all clients: %s"), *newMessage.Sender->GetUserName(), *newMessage.MessageString);
	});
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FFicsitChatModule, FicsitChat)
