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

		// �Ӵ��߳��л�����Ϸ���߳�
		FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
			[&]() {
				ThreadTask_Delegate.ExecuteIfBound();// ִ���߳����һ������.�˴�����gamemode�����߳�����˺���PrintF.
			},
			TStatId(), nullptr, ENamedThreads::GameThread 
		);

		// �ȴ����߳��������.
		FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
	}

	return 0;
}

void ThreadTask::CreateThread(ITaskInterface* NewTaskInterface)
{
	TaskInterface = NewTaskInterface;
	Task_Thread = FRunnableThread::Create(this, TEXT("Tt_HelloWorld"), 0, TPri_Normal);
}
