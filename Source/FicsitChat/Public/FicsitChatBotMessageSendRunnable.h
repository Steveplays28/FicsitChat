#pragma once

#include "CoreMinimal.h"
#include "FicsitChat_ConfigStruct.h"
#include "HAL/Runnable.h"

class FFicsitChatBotMessageSendRunnable : public FRunnable {
  public:
	FFicsitChatBotMessageSendRunnable(std::string message, std::string userName);
	virtual ~FFicsitChatBotMessageSendRunnable();

	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	std::string Message;
	std::string UserName;
	bool bBotStarted = false;

  protected:
	FRunnableThread *Thread = nullptr;

	bool bStopThread = false;
};
