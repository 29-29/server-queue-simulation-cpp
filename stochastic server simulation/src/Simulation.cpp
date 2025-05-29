#include "Simulation.h"

Simulation::Simulation(
	const double& arrivalRate=1, 
	const double& serviceRate=1, 
	const int& _servers=1, 
	const int& _bufferLimit=5, 
	const int& seed=time(nullptr), 
	const int& packets=20):iA(arrivalRate),sD(serviceRate) {
	/* generators */

	genA = mt19937(seed+1);
	genS = mt19937(seed-1);
	rho = arrivalRate / (serviceRate * _servers);

	/* simulation setup */
	maxPackets = packets;
	servers = _servers;
	bufferLimit = _bufferLimit;
	
	// stats initialize
	stats.arrivalRate = arrivalRate;
	stats.serviceRate = serviceRate;
	stats.servers = _servers;
	stats.bufferLimit = _bufferLimit;
	
	scheduleArrival();

	eventLogStream << fixed << setprecision(2);
	cout << fixed << setprecision(2);
}

Simulation::~Simulation() {
	while (!eventQueue.empty()) eventQueue.pop();
	queue<int>().swap(packetIDQueue);
	vector<double>().swap(arrivalTimes);
}

double Simulation::scheduleEvent(const EventType& type, const int& id) {
	double time;

	if (type == ARRIVAL) time = clockTime + iA(genA);
	else time = clockTime + sD(genS);

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
void Simulation::scheduleDeparture(const int& pid) {
	scheduleEvent(DEPARTURE, pid);
	waitingTime += clockTime - arrivalTimes[pid];
}

void Simulation::handleArrival(const int& pid) {
	packetsArrived++;

	// if all the servers are busy
	if (serversBusy >= servers) {
		// push to queue only if buffer limit hasn't been reached
		if (packetIDQueue.size() < bufferLimit) {
			packetIDQueue.push(pid);
			// queue length update
			weightedQueueLength += (clockTime - lastQueueUpdateTime) * packetIDQueue.size();
			lastQueueUpdateTime = clockTime;
		} else packetsDropped++;
	}
	// else one or more servers are free
	// then serve that packet
	else {
		serversBusy++;
		scheduleDeparture(pid);
	}
	scheduleArrival();
}

void Simulation::handleDeparture(const int& pid) {
	// updating statistics
	packetsServed++;
	delayTime += clockTime - arrivalTimes[pid];

	// release server
	serversBusy--;
	if (packetIDQueue.empty()) return;

	// serve next packet in queue
	serversBusy++;
	int nextPacket = packetIDQueue.front();
	packetIDQueue.pop();
	scheduleDeparture(nextPacket);

	// queue length update
	weightedQueueLength += (clockTime - lastQueueUpdateTime) * packetIDQueue.size();
	lastQueueUpdateTime = clockTime;
}

void Simulation::run() {
	Event currentEvent = eventQueue.top();
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
		busyTime += (clockTime - prevEventTime) * serversBusy;
		// server utilization has to be rethought

	}

	computeStatistics();
}

void Simulation::computeStatistics() {
	avgWait = waitingTime / packetsServed;
	avgDelay = delayTime / packetsServed;
	avgQueueLength = weightedQueueLength / clockTime;
	serverUtilization = busyTime / (servers * clockTime);
	throughput = packetsServed / clockTime;
	dropRate = double(packetsDropped) / double(packetsArrived);

	stats.simTime = clockTime;
	stats.packetsArrived = packetsArrived;
	stats.packetsServed = packetsServed;
	stats.packetsDropped = packetsDropped;
	stats.dropRate = dropRate;
	stats.avgWait = avgWait;
	stats.avgDelay = avgDelay;
	stats.avgQueue = avgQueueLength;
	stats.serverUtilization = serverUtilization;
	stats.throughput = throughput;
}

void Simulation::printStatistics() {
	stats.printStatistics();
}

void Simulation::writeStatisticsToCSV(const string& filename) {
	stats.writeToCSV(filename);
}

// SIMULATION N

SimulationN::SimulationN(const int& _N, const double& _arrivalMean, const double& _serviceMean, const int& _servers, const int& _bufferLimit, const int& _seed, const int& _packets):
N(_N),
arrivalMean(_arrivalMean),
serviceMean(_serviceMean),
servers(_servers),
bufferLimit(_bufferLimit),
originalSeed(_seed),
maxPackets(_packets)
{
	rho = serviceMean*_servers / arrivalMean;

	// simulation parameters in statistics
	stats.arrivalRate = _arrivalMean;
	stats.serviceRate = _serviceMean;
	stats.servers = _servers;
	stats.bufferLimit = _bufferLimit;
}

void SimulationN::run() {
	for (int i=0; i<N; i++) {
		Simulation sim(arrivalMean, serviceMean, servers, bufferLimit,
			(originalSeed+(3*N)*i), maxPackets);
		sim.run();
		getStatistics(&sim);
	}
	// printStatistics();
	accumulate();
}

void SimulationN::printStatistics() {
	stats.printStatistics();
}

void SimulationN::getStatistics(Simulation* sim) {
	stats += sim->getStatistics();
}

void SimulationN::accumulate() {
	stats.accumulate(N);
}

void SimulationN::writeStatsToCSV(const string& filename) {
	stats.writeToCSV(filename);
}

Stats SimulationN::thisStats() {
	return stats;
}