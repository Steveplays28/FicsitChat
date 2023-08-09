#include "FicsitChatWorldModule.h"
#include "Configuration/ConfigManager.h"

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

	// Start Discord bot
	bot = MakeShared<dpp::cluster>(TCHAR_TO_UTF8(*config.BotToken), dpp::i_default_intents | dpp::i_message_content);

	bot->on_ready([&](auto event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));
		}

		botUsername = bot->me.username.c_str();
		botDiscriminator = bot->me.discriminator;
	});

	bot->on_message_create([&](const dpp::message_create_t &event) {
		FString messageContent = event.msg.content.c_str();
		FString messageAuthor = event.msg.author.username.c_str();
		uint16_t messageAuthorDiscriminator = event.msg.author.discriminator;

		if (messageAuthor == botUsername && messageAuthorDiscriminator == botDiscriminator)
			return;

		AsyncTask(ENamedThreads::GameThread, [=]() { SendMessageToGame(messageContent, messageAuthor); });
	});

	bot->on_slashcommand([](auto event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
	});

	bot->start(true);
}

void UFicsitChatWorldModule::SendMessageToGame(FString messageContent, FString messageAuthor) {
	FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig();

	FChatMessageStruct chatMessageStruct{};
	chatMessageStruct.MessageString = messageContent;
	chatMessageStruct.MessageType = EFGChatMessageType::CMT_PlayerMessage;
	chatMessageStruct.ServerTimeStamp = GetWorld()->TimeSeconds;
	chatMessageStruct.CachedPlayerName = messageAuthor;
	chatMessageStruct.CachedColor = FLinearColor(config.ChatMessageColor.Red, config.ChatMessageColor.Green, config.ChatMessageColor.Blue);

	AFGChatManager *chatManager = AFGChatManager::Get(GetWorld());
	chatManager->AddChatMessageToReceived(chatMessageStruct);
}
