#include "FicsitChatModule.h"
#include "FGChatManager.h"
#include "FGPlayerState.h"
#include "FicsitChatWorldModule.h"
#include "Module/GameInstanceModule.h"
#include "Module/WorldModuleManager.h"
#include "Patching/NativeHookManager.h"
#include "Reflection/BlueprintReflectionLibrary.h"

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
	SUBSCRIBE_METHOD_AFTER(AFGChatManager::AddChatMessageToReceived, [](AFGChatManager *self, const FChatMessageStruct &newMessage) {
		UE_LOG(LogFicsitChat, Verbose, TEXT("Chat message by %s sent to all clients: %s"), *newMessage.MessageSender.ToString(), *newMessage.MessageText.ToString());

		FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig((UFicsitChatWorldModule *)self->GetWorld());
		UFicsitChatWorldModule *worldModule = (UFicsitChatWorldModule *)self->GetWorld()->GetSubsystem<UWorldModuleManager>()->FindModule(TEXT("FicsitChat"));

		FString messageText = newMessage.MessageText.ToString().Replace(TEXT("<PlayerName/>"), *newMessage.MessageSender.ToString());
		if (messageText.EndsWith(TEXT("has joined the game!")) && !config.HasJoinedMessage) {
			return;
		}
		if (messageText.EndsWith(TEXT("has left the game!")) && !config.HasLeftMessage) {
			return;
		}

		std::string userName = TCHAR_TO_UTF8(*newMessage.MessageSender.ToString());
		std::string message = TCHAR_TO_UTF8(*messageText);

		dpp::embed embed =
			dpp::embed().set_color(dpp::colors::orange).set_title(userName).set_description(message).set_footer(dpp::embed_footer().set_text("If you're tired, just remember you can buy a FICSIT™ Coffee Cup at the AWESOME Shop!"));

		worldModule->bot->message_create(dpp::message(dpp::snowflake::snowflake(TCHAR_TO_UTF8(*config.ChannelId)), embed));
	});
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FFicsitChatModule, FicsitChat)
