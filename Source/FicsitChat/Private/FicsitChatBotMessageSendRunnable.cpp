#include "FicsitChatBotMessageSendRunnable.h"
#include "Configuration/ConfigManager.h"

#include "Windows/WindowsHWrapper.h"

THIRD_PARTY_INCLUDES_START
#include "dpp/dpp.h"
THIRD_PARTY_INCLUDES_END

FFicsitChatBotMessageSendRunnable::FFicsitChatBotMessageSendRunnable(std::string message, std::string userName) {
	Message = message;
	UserName = userName;
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

		if (Message == std::string("has joined the game!") && !config.HasJoinedMessage) {
			bBotStarted = true;
			return 0;
		}

		if (Message == std::string("has left the game!") && !config.HasLeftMessage) {
			bBotStarted = true;
			return 0;
		}

		bBotStarted = true;

		dpp::embed embed = dpp::embed()
							   .set_color(dpp::colors::orange)
							   .set_title(UserName)
							   .set_description(Message)
							   .set_footer(dpp::embed_footer().set_text("If you're tired, just remember you can buy a FICSIT™ Coffee Cup at the AWESOME Shop!"));

		bot.message_create(dpp::message(1107400352384426104, embed));
	}

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
