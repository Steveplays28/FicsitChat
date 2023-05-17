#include "FicsitChatBotMessageSendRunnable.h"
#include "Configuration/ConfigManager.h"

#include "Windows/WindowsHWrapper.h"

THIRD_PARTY_INCLUDES_START
#include "dpp/dpp.h"
THIRD_PARTY_INCLUDES_END

FFicsitChatBotMessageSendRunnable::FFicsitChatBotMessageSendRunnable(char *message) {
	Message = message;
	Thread = FRunnableThread::Create(this, TEXT("FICSIT.chat Discord bot thread"));
}

FFicsitChatBotMessageSendRunnable::~FFicsitChatBotMessageSendRunnable() {
	if (Thread != nullptr) {
		Thread->Kill(true);
		delete Thread;
	}
}

uint32 FFicsitChatBotMessageSendRunnable::Run() {
	bStopThread = false;

	if (!bBotStarted) {
		FFicsitChat_ConfigStruct config = FFicsitChat_ConfigStruct::GetActiveConfig();
		dpp::cluster bot(TCHAR_TO_ANSI(*config.BotToken));

		bBotStarted = true;

		dpp::embed embed = dpp::embed()
							   .set_color(dpp::colors::sti_blue)
							   .set_title("Some name")
							   .set_url("https://dpp.dev/")
							   .set_author("Some name", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png")
							   .set_description("Some description here")
							   .set_thumbnail("https://dpp.dev/DPP-Logo.png")
							   .add_field("Regular field title", "Some value here")
							   .add_field("Inline field title", "Some value here", true)
							   .add_field("Inline field title", "Some value here", true)
							   .set_image("https://dpp.dev/DPP-Logo.png")
							   .set_footer(dpp::embed_footer().set_text("Some footer text here").set_icon("https://dpp.dev/DPP-Logo.png"))
							   .set_timestamp(time(0));

		bot.message_create(dpp::message(1107400352384426104, embed));
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

void FFicsitChatBotMessageSendRunnable::Exit() {
	// Here's where we can do any cleanup we want to
}

void FFicsitChatBotMessageSendRunnable::Stop() {
	// Force our thread to stop early
	bStopThread = true;
}
