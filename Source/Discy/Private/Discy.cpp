#include "Discy.h"
#include "Patching/NativeHookManager.h"

#define LOCTEXT_NAMESPACE "FDiscyModule"

DEFINE_LOG_CATEGORY(LogDiscy);

void FDiscyModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// TODO: Start Discord bot
}

void FDiscyModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void registerHooks() {
#if !WITH_EDITOR
	// TODO: Register chat hook
	SUBSCRIBE_METHOD(FGChatManager::Multicast_BroadcastChatMessage, [](auto &scope, FGChatManager *self, const FChatMessageStruct &newMessage)
					 {
		// do some nice stuff there
		UE_LOG(LogDiscy, Verbose, TEXT("Chat message sent to all clients")); });
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDiscyModule, Discy)
