#include "FicsitChatWorldModule.h"
#include "Configuration/ConfigManager.h"
#include "Containers/UnrealString.h"

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

	// Start Discord bot
	bot = MakeShared<dpp::cluster>(TCHAR_TO_ANSI(*config.BotToken), dpp::i_default_intents | dpp::i_message_content);

	bot->on_message_create([&](const dpp::message_create_t &event) {
		AsyncTask(ENamedThreads::GameThread, [=]() {
			FString messageContent = event.msg.content.c_str();
			FString messageAuthor = event.msg.author.format_username().c_str();

			FChatMessageStruct chatMessageStruct{};
			chatMessageStruct.MessageString = messageContent;
			chatMessageStruct.MessageType = EFGChatMessageType::CMT_PlayerMessage;
			chatMessageStruct.ServerTimeStamp = GetWorld()->TimeSeconds;
			chatMessageStruct.CachedPlayerName = messageAuthor;

			AFGChatManager *chatManager = AFGChatManager::Get(GetWorld());
			chatManager->AddChatMessageToReceived(chatMessageStruct);
		});
	});

	bot->on_slashcommand([](auto event) {
		AsyncThread([=]() {
			if (event.command.get_command_name() == "ping") {
				event.reply("Pong!");
			}
		});
	});

	bot->on_ready([&](auto event) {
		AsyncThread([=]() {
			if (dpp::run_once<struct register_bot_commands>()) {
				bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));
			}
		});
	});

	AsyncThread([=]() { bot->start(false); });
}
