#pragma once
#include <queue>
#include "RandomGenExpoMean.h"
#include "Event.h"

using namespace std;

class Simulation
{
private:
	RandomExpoMean iA; // inter-arrival generator
	RandomExpoMean sD; // service duration generator
	double clockTime;

	priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
	queue<int> packetQueue;
public:
	Simulation(double arrivalMean, double serviceMean): iA(arrivalMean), sD(serviceMean), clockTime(.0) {
	}

	void scheduleEvent(EventType type, int id) {
		double time;
		if (type == ARRIVAL) time = iA.getValue();
		else time = sD.getValue();

		eventQueue.push(Event{ time, type, id });
	}
};

