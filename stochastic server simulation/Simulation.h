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
	mt19937 genA;
	mt19937 genS;
	exponential_distribution<> iA;
	exponential_distribution<> sD;
	// 
	// normal_distribution<> iA;
	// normal_distribution<> sD;

	/* Simulation parameters */
	int maxPackets;

	/* Simulation state variables */
	double clockTime=0.0; // current time
	double prevEventTime=0.0; // to record the time of the last event
	int lastPacketID=-1; // ID of the last packet
	bool serverBusy=false;
	double lastQueueUpdateTime=0.0;

	/* Simulation logs */
	stringstream eventLogStream;

	/* for statistics */
	int packetsServed=0;
	int packetsArrived=0;
	double waitingTime=0;
	double delayTime=0;
	double weightedQueueLength=0;
	double busyTime=0.0;

	priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
	queue<int> packetIDQueue;
	vector<double> arrivalTimes;

	double scheduleEvent(EventType type, int id);
	void scheduleArrival();
	void scheduleDeparture(int pid);
	void handleArrival(int pid);
	void handleDeparture(int pid);

public:
	Simulation(double arrivalMean, double serviceMean, int seed, int packets);

	void run(); // main simulation loop
	string eventLogs() { return eventLogStream.str(); }
	void printStatistics();
};

#include "Simulation.cpp"
