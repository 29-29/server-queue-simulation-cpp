#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <sys/stat.h>

#include "RandomGenExpoMean.h"
#include "Event.h"
#include "Server.h"
#include "Statistics.h"

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

	/* Simulation parameters */
	int maxPackets;
	int servers;
	int bufferLimit;

	/* Simulation state variables */
	double clockTime=0.0; // current time
	double prevEventTime=0.0; // to record the time of the last event
	int lastPacketID=-1; // ID of the last packet
	int serversBusy=0; //
	double lastQueueUpdateTime=0.0;

	/* Simulation logs */
	stringstream eventLogStream;

	/* for statistics */
	int packetsServed=0;
	int packetsArrived=0;
	int packetsDropped=0;
	double waitingTime=0;
	double delayTime=0;
	double weightedQueueLength=0;
	double busyTime=0.0;

	Stats stats;
	double rho; // (traffic intensity) rho = arrival rate / service rate
	double avgWait;
	double avgDelay;
	double avgQueueLength;
	double serverUtilization;
	double throughput;
	double dropRate;

	priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
	queue<int> packetIDQueue;
	vector<double> arrivalTimes;

	double scheduleEvent(const EventType& type, const int& id);
	void scheduleArrival();
	void scheduleDeparture(const int& pid);
	void handleArrival(const int& pid);
	void handleDeparture(const int& pid);

	void computeStatistics();

public:
	Simulation(const double& arrivalMean, const double& serviceMean,
		const int& servers, const int& _bufferLimit, const int& seed,
		const int& packets);

	void run(); // main simulation loop
	string eventLogs() { return eventLogStream.str(); }

	// simulation statistics
	void printStatistics();
	void writeStatisticsToCSV(const string& filename);

	Stats getStatistics() const { return stats; }
};
};

#include "Simulation.cpp"
