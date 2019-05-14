/*
 * DAGScheduler.h
 *
 *  Created on: May 13, 2019
 *      Author: mirco
 */

#ifndef SIMULATION_DAGSCHEDULER_H_
#define SIMULATION_DAGSCHEDULER_H_
#include <DAG/PlainDAG.h>
#include <Simulation/TaskSet.h>
#include <uavAP/Core/Object/IAggregatableObject.h>
#include <uavAP/Core/Object/ObjectHandle.h>
#include <uavAP/Core/Runner/IRunnableObject.h>

class IScheduler;
class CoreManager;

class DAGScheduler: public IAggregatableObject, public IRunnableObject
{
public:

	using BoolMatrix = PlainDAG::BoolMatrix;

	DAGScheduler(const PlainDAG& dag);

	int
	nextTask();

	void
	taskFinished(unsigned taskId);

	void
	reset();

	void
	notifyAggregationOnUpdate(const Aggregator& agg) override;

	bool
	run(RunStage stage) override;

	const DAG::NodeInfo&
	getNodeInfo() const;

private:

	void
	queueReady();

	void
	scheduleSync();

	void
	syncReady(unsigned syncId);

	PlainDAG dag_;
	BoolMatrix depMatrix_;

	std::multimap<float, int> ready_;
	unsigned numNodes_;

	ObjectHandle<IScheduler> scheduler_;
	ObjectHandle<CoreManager> coreManager_;

};

#endif /* SIMULATION_DAGSCHEDULER_H_ */