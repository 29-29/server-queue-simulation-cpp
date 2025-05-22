#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>

#include "RandomGenExpoMean.h"
#include "Event.h"

using namespace std;

class Simulation
{
private:
	/* RNGs */
	// RandomExpoMean iA; // inter-arrival generator
	// RandomExpoMean sD; // service duration generator
	// 
	mt19937 generator;
	exponential_distribution<> iA;
	exponential_distribution<> sD;

	/* Simulation parameters */
	int maxPackets;

	/* Simulation state variables */
	double clockTime=0.0; // current time
	int lastPacketID=-1; // ID of the last packet
	bool serverBusy=false;

	/* Simulation logs */
	stringstream eventLogStream;

	/* for statistics */
	int packetsServed=0;
	int packetsArrived=0;
	double waitingTime=0;

	priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
	queue<int> packetIDQueue;
	vector<double> arrivalTimes;

	void scheduleEvent(EventType type, int id) {
		double time;

		// if (type == ARRIVAL) time = clockTime + iA.getValue();
		// else time = clockTime + sD.getValue();
		// 
		if (type == ARRIVAL) time = clockTime + iA(generator);
		else time = clockTime + sD(generator);

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
		packetsServed++;
		serverBusy = false;
		if (packetIDQueue.empty()) return;
		serverBusy = true;
		int nextPacket = packetIDQueue.front();
		packetIDQueue.pop();
		scheduleDeparture(nextPacket);
	}

public:

	Simulation(double arrivalMean=1, double serviceMean=1, int packets=20):iA(arrivalMean),sD(serviceMean) {
		/* generators */

		generator = mt19937(time(nullptr));
		iA = exponential_distribution<>(arrivalMean);
		sD = exponential_distribution<>(serviceMean);
		// 
		// iA = RandomExpoMean(arrivalMean);
		// sD = RandomExpoMean(serviceMean);

		/* simulation setup */
		maxPackets = packets;
		
		scheduleArrival();

		eventLogStream << fixed << setprecision(2);
	}

	// main simulation loop
	void run() {
		Event currentEvent = eventQueue.top();
		// while (lastPacketID < maxPackets) {
		while (packetsServed < maxPackets) {

			currentEvent = eventQueue.top();
			clockTime = currentEvent.getTime();
			eventLogStream << currentEvent.getPacketID() << "\t" << (currentEvent.getType() == ARRIVAL ? "_ARR" : "DEP_") << "\t" << currentEvent.getTime() << "\n";
			if (currentEvent.getType() == ARRIVAL) {
				handleArrival(currentEvent.getPacketID());
			} else {
				handleDeparture(currentEvent.getPacketID());
			}
			eventQueue.pop();

		}
	}

	string eventLogs() {
		return eventLogStream.str();
	}

	void printStatistics() {
		cout
		<< "Simulation time: " << clockTime << "\n"
		<< "Packets arrived: " << lastPacketID << "\n"
		<< "Packets served: " << packetsServed << "\n"
		;
	}
};

