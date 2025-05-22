#include "Simulation.h"

Simulation::Simulation(double arrivalMean=1, double serviceMean=1, int seed=time(nullptr), int packets=20):iA(1/arrivalMean),sD(1/serviceMean) {
	/* generators */

	generator = mt19937(seed);
	// iA = normal_distribution<>(arrivalMean);
	// sD = normal_distribution<>(serviceMean);
	// 
	// iA = exponential_distribution<>(arrivalMean);
	// sD = exponential_distribution<>(serviceMean);
	// 
	// iA = RandomExpoMean(arrivalMean);
	// sD = RandomExpoMean(serviceMean);

	/* simulation setup */
	maxPackets = packets;
	
	scheduleArrival();

	eventLogStream << fixed << setprecision(2);
	cout << fixed << setprecision(2);
}

double Simulation::scheduleEvent(EventType type, int id) {
	double time;

	// if (type == ARRIVAL) time = clockTime + iA.getValue();
	// else time = clockTime + sD.getValue();
	// 
	if (type == ARRIVAL) time = clockTime + iA(generator);
	else time = clockTime + sD(generator);

	eventQueue.push(Event{ time, type, id });
	return time;
}

void Simulation::scheduleArrival() {
	double time = scheduleEvent(ARRIVAL, ++lastPacketID);
	arrivalTimes.push_back(time);
}

// this is called only in these circumstances:
// - a packet arrives and the queue is empty
// - a packet has been served and the queue isn't empty
void Simulation::scheduleDeparture(int pid) {
	scheduleEvent(DEPARTURE, pid);
	waitingTime += clockTime - arrivalTimes[pid];
}

void Simulation::handleArrival(int pid) {
	arrivalTimes.push_back(clockTime);

	if (serverBusy) {
		packetIDQueue.push(pid);
		// queue length update
		weightedQueueLength += (clockTime - lastQueueUpdateTime) * packetIDQueue.size();
		lastQueueUpdateTime = clockTime;
	}
	else {
		serverBusy = true;
		scheduleDeparture(pid);
	}
	scheduleArrival();
}

void Simulation::handleDeparture(int pid) {
	// updating statistics
	packetsServed++;
	delayTime += clockTime - arrivalTimes[pid];

	// release server
	serverBusy = false;
	if (packetIDQueue.empty()) return;

	// serve next packet in queue
	serverBusy = true;
	int nextPacket = packetIDQueue.front();
	packetIDQueue.pop();
	scheduleDeparture(nextPacket);

	// queue length update
	weightedQueueLength += (clockTime - lastQueueUpdateTime) * packetIDQueue.size();
	lastQueueUpdateTime = clockTime;
}

void Simulation::run() {
	Event currentEvent = eventQueue.top();
	// while (lastPacketID < maxPackets) {
	while (packetsServed < maxPackets) {

		currentEvent = eventQueue.top();
		prevEventTime = clockTime;
		clockTime = currentEvent.getTime();

		// handle event
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
	double avgWait = waitingTime / packetsServed;
	double avgDelay = delayTime / packetsServed;
	double avgQueueLength = weightedQueueLength / clockTime;

	cout
	<< "Simulation time: " << clockTime << "\n"
	<< "Packets arrived: " << lastPacketID << "\n"
	<< "Packets served: " << packetsServed << "\n"
	<< "Average waiting time: " << avgWait << "\n"
	<< "Average delay time: " << avgDelay << "\n"
	<< "Average queue length: " << avgQueueLength << '\n'
	;
}