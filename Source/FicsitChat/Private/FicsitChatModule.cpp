#include "FicsitChatModule.h"
#include "FGChatManager.h"
#include "FGPlayerState.h"
#include "FicsitChatWorldModule.h"
#include "Module/GameInstanceModule.h"
#include "Module/WorldModuleManager.h"
#include "Patching/NativeHookManager.h"

#define LOCTEXT_NAMESPACE "FFicsitChatModule"

DEFINE_LOG_CATEGORY(LogFicsitChat);

void FFicsitChatModule::StartupModule() {
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

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
		UE_LOG(LogFicsitChat, Verbose, TEXT("Chat message by %s sent to all clients: %s"), *newMessage.Sender->GetUserName(), *newMessage.MessageString);

		FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig();
		UFicsitChatWorldModule *worldModule = (UFicsitChatWorldModule *)self->GetWorld()->GetSubsystem<UWorldModuleManager>()->FindModule(TEXT("FicsitChat"));

		AsyncThread([=]() {
			if (TCHAR_TO_UTF8(*newMessage.MessageString) == std::string("has joined the game!") && !config.HasJoinedMessage) {
				return;
			}

			if (TCHAR_TO_UTF8(*newMessage.MessageString) == std::string("has left the game!") && !config.HasLeftMessage) {
				return;
			}

			dpp::embed embed = dpp::embed()
								   .set_color(dpp::colors::orange)
								   .set_title(TCHAR_TO_UTF8(*newMessage.Sender->GetUserName()))
								   .set_description(TCHAR_TO_UTF8(*newMessage.MessageString))
								   .set_footer(dpp::embed_footer().set_text("If you're tired, just remember you can buy a FICSIT™ Coffee Cup at the AWESOME Shop!"));

			worldModule->bot->message_create(dpp::message(1107400352384426104, embed));
		});
	});
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FFicsitChatModule, FicsitChat)
