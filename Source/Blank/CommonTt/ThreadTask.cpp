// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadTask.h"
#include "Async/TaskGraphInterfaces.h"

ThreadTask::ThreadTask()
{
	TaskInterface = nullptr;
}

ThreadTask::~ThreadTask()
{}

uint32 ThreadTask::Run()
{
	UE_LOG(LogTemp, Log, TEXT("Run"));

	if (TaskInterface != nullptr) {
		TaskInterface->DoWork();

		// 从此线程切换至游戏主线程
		FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
			[&]() {
				ThreadTask_Delegate.ExecuteIfBound();// 执行线程里的一个代理.此代理在gamemode的主线程里绑了函数PrintF.
			},
			TStatId(), nullptr, ENamedThreads::GameThread 
		);

		// 等待此线程任务完成.
		FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
	}

	return 0;
}

void ThreadTask::CreateThread(ITaskInterface* NewTaskInterface)
{
	TaskInterface = NewTaskInterface;
	Task_Thread = FRunnableThread::Create(this, TEXT("Tt_HelloWorld"), 0, TPri_Normal);
}
