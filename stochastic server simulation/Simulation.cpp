#include "Simulation.h"

Simulation::Simulation(double arrivalMean=1, double serviceMean=1, int seed=time(nullptr), int packets=20):iA(arrivalMean),sD(serviceMean) {
	/* generators */

	generator = mt19937(seed);
	iA = exponential_distribution<>(arrivalMean);
	sD = exponential_distribution<>(serviceMean);
	// 
	// iA = RandomExpoMean(arrivalMean);
	// sD = RandomExpoMean(serviceMean);

	/* simulation setup */
	maxPackets = packets;
	
	scheduleArrival();

	eventLogStream << fixed << setprecision(2);
	cout << fixed << setprecision(2);
}

void Simulation::scheduleEvent(EventType type, int id) {
	double time;

	// if (type == ARRIVAL) time = clockTime + iA.getValue();
	// else time = clockTime + sD.getValue();
	// 
	if (type == ARRIVAL) time = clockTime + iA(generator);
	else time = clockTime + sD(generator);

	eventQueue.push(Event{ time, type, id });
}

void Simulation::handleDeparture(int pid) {
	// updating statistics
	packetsServed++;
	waitingTime += clockTime - arrivalTimes[pid];

	// release server
	serverBusy = false;
	if (packetIDQueue.empty()) return;

	// serve next packet in queue
	serverBusy = true;
	int nextPacket = packetIDQueue.front();
	packetIDQueue.pop();
	scheduleDeparture(nextPacket);
}

void Simulation::handleArrival(int pid) {
	arrivalTimes.push_back(clockTime);

	if (serverBusy) packetIDQueue.push(pid);
	else {
		serverBusy = true;
		scheduleDeparture(pid);
	}
	scheduleArrival();
}

void Simulation::run() {
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

void Simulation::printStatistics() {
	double avgWaitTime = waitingTime / packetsServed;

	cout
	<< "Simulation time: " << clockTime << "\n"
	<< "Packets arrived: " << lastPacketID << "\n"
	<< "Packets served: " << packetsServed << "\n"
	<< "Average waiting time: " << avgWaitTime << "\n"
	;
}