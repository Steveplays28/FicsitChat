#include "FicsitChatWorldModule.h"
#include "Configuration/ConfigManager.h"

UFicsitChatWorldModule::UFicsitChatWorldModule() {
#if !WITH_EDITOR
	this->bRootModule = true;
#endif
}

void UFicsitChatWorldModule::BeginDestroy() {
	Super::BeginDestroy();

#if !WITH_EDITOR
	UE_LOG(LogFicsitChat, Verbose, TEXT("BeginDestroy"));
#endif
}

// Runs on game world load
void UFicsitChatWorldModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
	if (Phase != ELifecyclePhase::INITIALIZATION)
		return;

	UE_LOG(LogFicsitChat, Verbose, TEXT("DispatchLifecycleEvent"));

	// Get mod config
	FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig(GetWorld());

	// Start Discord bot
	if (!ValidateBotToken(*config.BotToken)) {
		return;
	}

	UE_LOG(LogFicsitChat, Verbose, TEXT("Starting the Discord bot. If the game crashes due to FicsitChat or DPP, check if you have the right intents set (check on https://discord.com/developers), and check if your bot token is valid."));
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

bool UFicsitChatWorldModule::ValidateBotToken(FString botToken) {
	std::string botTokenString = TCHAR_TO_UTF8(*botToken);

	if (botToken.Len() < 40 || botToken.Len() > 100) {
		UE_LOG(LogFicsitChat, Verbose, TEXT("Failed to validate the Discord bot token. The Discord bot token's length needs to be in between 40 and 100 characters long."));
		return false;
	} else if (botTokenString.find(std::string("BOT_TOKEN_HERE")) != std::string::npos) {
		UE_LOG(LogFicsitChat, Verbose,
			   TEXT("Failed to validate the Discord bot token. The Discord bot token is set to the default value, which is invalid.\nPlease change it in the mod's configuration and reload your save. The Discord bot will not be started "
					"until then."));
		return false;
	}

	return true;
}

void UFicsitChatWorldModule::SendMessageToGame(FString messageContent, FString messageAuthor) {
	FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig(GetWorld());

	FChatMessageStruct chatMessageStruct{};
	chatMessageStruct.MessageString = messageContent;
	chatMessageStruct.MessageType = EFGChatMessageType::CMT_PlayerMessage;
	chatMessageStruct.ServerTimeStamp = GetWorld()->TimeSeconds;
	chatMessageStruct.CachedPlayerName = messageAuthor;
	chatMessageStruct.CachedColor = FLinearColor(config.ChatMessageColor.Red, config.ChatMessageColor.Green, config.ChatMessageColor.Blue);

	AFGChatManager *chatManager = AFGChatManager::Get(GetWorld());
	chatManager->AddChatMessageToReceived(chatMessageStruct);
}
