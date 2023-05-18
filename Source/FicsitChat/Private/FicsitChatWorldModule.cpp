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

	UE_LOG(LogFicsitChat, Verbose, TEXT("Bot token: %s"), *config.BotToken);

	bot = MakeShared<dpp::cluster>(TCHAR_TO_ANSI(*config.BotToken));

	AsyncThread([=]() {
		bot->on_slashcommand([](auto event) {
			if (event.command.get_command_name() == "ping") {
				event.reply("Pong!");
			}
		});

		bot->on_ready([&](auto event) {
			if (dpp::run_once<struct register_bot_commands>()) {
				bot->global_command_create(dpp::slashcommand("ping", "Ping pong!", bot->me.id));
			}
		});

		bot->start(false);
	});
}
