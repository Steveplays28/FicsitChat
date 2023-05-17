#include "BUIExampleRunnable.h"
#include "Configuration/ConfigManager.h"

#include "Windows/WindowsHWrapper.h"

THIRD_PARTY_INCLUDES_START
#include "dpp/dpp.h"
THIRD_PARTY_INCLUDES_END

FBUIExampleRunnable::FBUIExampleRunnable(int32 InTargetCount) {
	TargetCount = InTargetCount;
	FoundCount = 0;
	Thread = FRunnableThread::Create(this, TEXT("FICSIT.chat Discord bot thread"));
}

FBUIExampleRunnable::~FBUIExampleRunnable() {
	if (Thread != nullptr) {
		Thread->Kill(true);
		delete Thread;
	}
}

uint32 FBUIExampleRunnable::Run() {
	bStopThread = false;

	if (!bBotStarted) {
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

		bBotStarted = true;
		bot.start(dpp::st_wait);
	}

	// Keep processing until we're cancelled through Stop() or we're done,
	// although this thread will suspended for other stuff to happen at the same time
	// while (!bStopThread && FoundCount < TargetCount) {
		// This is where we would do our expensive threaded processing

		// Instead we're going to make a really busy while loop to slow down processing
		// You can change INT_MAX to something smaller if you want it to run faster
		// int32 x = 0;
		// while (x < INT_MAX) {
		// 	x++;
		// }
		// ProcessedNumbers.Add(FMath::RandRange(0, 999));
		// FoundCount += 1;
	// }

	// OnCompleteDelegate.ExecuteIfBound();

	// Return success
	return 0;
}

void FBUIExampleRunnable::Exit() {
	// Here's where we can do any cleanup we want to
}

void FBUIExampleRunnable::Stop() {
	// Force our thread to stop early
	bStopThread = true;
}
