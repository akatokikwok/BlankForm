// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "TaskInterface.h"

DECLARE_DELEGATE(FThreadTask);

/** Ïß³Ì */
class BLANK_API ThreadTask : public FRunnable
{
public:
	ThreadTask();
	~ThreadTask();

	FThreadTask ThreadTask_Delegate;
public:
	//
	virtual uint32 Run() override;

	void CreateThread(ITaskInterface* NewTaskInterface);
public:

private:
	FRunnableThread* Task_Thread;

	ITaskInterface* TaskInterface;
};
