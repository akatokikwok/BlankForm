#pragma once
#include "CoreMinimal.h"
#include "Async/TaskGraphInterfaces.h"

/// 自定义的线程任务.
class FTaskGraph
{
public:
	FTaskGraph(float f)
	: m_f(f)
	{}

public:
	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	/** 任务组 */
	FORCEINLINE TStatId GetStatId() { RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskGraph, STATGROUP_TaskGraphTasks); }

	/**  具体任务*/
	void DoTask(ENamedThreads::Type CurrentThread, FGraphEventRef Subsequents) 
	{ 
		UE_LOG(LogTemp, Log, TEXT("HelloWorld: %f"),m_f); 
	}

	static ENamedThreads::Type GetDesiredThread() { return ENamedThreads::AnyThread; }

private:
	float m_f;


};