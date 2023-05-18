#include "BUIExampleRunnable.h"
#include "Configuration/ConfigManager.h"

#include "Windows/WindowsHWrapper.h"

THIRD_PARTY_INCLUDES_START
#include "dpp/dpp.h"
THIRD_PARTY_INCLUDES_END

FBUIExampleRunnable::FBUIExampleRunnable() { Thread = FRunnableThread::Create(this, TEXT("FICSIT.chat Discord bot thread")); }

FBUIExampleRunnable::~FBUIExampleRunnable() {
	if (Thread != nullptr) {
		Thread->Kill(true);
		delete Thread;
	}
}

bool FBUIExampleRunnable::Init() { return true; }

uint32 FBUIExampleRunnable::Run() {
	FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig();
	dpp::cluster bot(TCHAR_TO_ANSI(*config.BotToken));

	bot.on_slashcommand([](auto event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
	});

	bot.on_ready([&bot](auto event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
		}
	});

	bot.start(false);

	FBUIExampleRunnable::Stop();

	// Return success
	return 0;
}

void FBUIExampleRunnable::Stop() {}
