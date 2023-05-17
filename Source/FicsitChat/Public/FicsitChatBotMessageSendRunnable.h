#pragma once

#include "CoreMinimal.h"
#include "FicsitChat_ConfigStruct.h"
#include "HAL/Runnable.h"

// DECLARE_DYNAMIC(FBUIOnCompleteSignature);

// Note that we do not have to mark our class as UCLASS() if we don't want to
class FFicsitChatBotMessageSendRunnable : public FRunnable {
  public:
	// Custom constructor for setting up our thread with its target
	FFicsitChatBotMessageSendRunnable(char *message);
	virtual ~FFicsitChatBotMessageSendRunnable();

	// FRunnable functions
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	// FRunnable

	// FBUIOnCompleteSignature OnCompleteDelegate;

	char *Message;
	bool bBotStarted = false;

  protected:
	FRunnableThread *Thread = nullptr;

	bool bStopThread = false;
};