#pragma once
#include <queue>
#include <iostream>
#include <vector>

#include "Packet.h"
#include "RandomGenExpoMean.h"
#include "Event.h"

using namespace std;

class Simulation
{
private:
	/* RNGs */
	RandomExpoMean iA; // inter-arrival generator
	RandomExpoMean sD; // service duration generator

	/* Simulation parameters */
	int maxPackets;

	/* Simulation state variables */
	double clockTime; // current time
	int lastPacketID; // ID of the last packet
	bool serverBusy;

	priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
	queue<int> packetIDQueue;
	vector<Packet> packetList;

	void scheduleEvent(EventType type, int id) {
		double time;
		if (type == ARRIVAL) time = clockTime + iA.getValue();
		else time = clockTime + sD.getValue();

		eventQueue.push(Event{ time, type, id });
	}

	void scheduleArrival() {
		scheduleEvent(ARRIVAL, ++lastPacketID);
	}

	void scheduleDeparture(int pid) {
		scheduleEvent(DEPARTURE, pid);
	}

	void handleArrival(int pid) {
		if (serverBusy) packetIDQueue.push(pid);
		else {
			serverBusy = true;
			scheduleDeparture(pid);
		}
		scheduleArrival();
	}

	void handleDeparture(int pid) {
		serverBusy = false;
		if (packetIDQueue.empty()) {
			scheduleArrival();
			return;
		}
		serverBusy = true;
	}

public:
	Simulation(double arrivalMean=1, double serviceMean=1, int maxPackets=20): 
		iA(arrivalMean),
		sD(serviceMean), 
		clockTime(0.0), 
		maxPackets(maxPackets), 
		lastPacketID(-1) {
		// Initialize the event queue with the first arrival event
		scheduleArrival();
	}

	// main simulation loop
	void run() {
		Event currentEvent = eventQueue.top();
		while (lastPacketID < maxPackets) {
			currentEvent = eventQueue.top();
			clockTime = currentEvent.getTime();
			cout << currentEvent.getPacketID() << "\t" << (currentEvent.getType() == ARRIVAL ? "_ARR" : "DEP_") << "\t" << currentEvent.getTime() << "\n";
			if (currentEvent.getType() == ARRIVAL) {
				handleArrival(currentEvent.getPacketID());
			} else {
				handleDeparture(currentEvent.getPacketID());
			}
			eventQueue.pop();
		}
	}

};

