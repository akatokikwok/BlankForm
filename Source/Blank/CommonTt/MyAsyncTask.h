#pragma once
#include "CoreMinimal.h"
#include "Async/AsyncWork.h"

/// 供FAsyncTask去使用的 自定义线程任务
class TaskAsyncTask : public FNonAbandonableTask
{
	friend class FAsyncTask<TaskAsyncTask>;
public:
	TaskAsyncTask(int32 _InstanceInt)
		:InstanceInt(_InstanceInt)
	{}

	// Override FAsyncTask.DoWork 
	void DoWork()
	{
		UE_LOG(LogTemp, Log, TEXT("DoWork: %d"), InstanceInt);
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(TaskAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

public:
	int32 InstanceInt;

};