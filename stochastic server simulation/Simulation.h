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

	void scheduleEvent(EventType type, int id);
	void scheduleArrival() { scheduleEvent(ARRIVAL, ++lastPacketID); }
	void scheduleDeparture(int pid) { scheduleEvent(DEPARTURE, pid); }
	void handleArrival(int pid);
	void handleDeparture(int pid);

public:
	Simulation(double arrivalMean=1, double serviceMean=1, int packets=20);

	void Simulation::run(); // main simulation loop
	string eventLogs() { return eventLogStream.str(); }
	void printStatistics();
};

#include "Simulation.cpp"
