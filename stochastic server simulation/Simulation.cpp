#include "Simulation.h"

Simulation::Simulation(
	const double& arrivalMean=1, 
	const double& serviceMean=1, 
	const int& _servers=1, 
	const int& seed=time(nullptr), 
	const int& packets=20):iA(1/arrivalMean),sD(1/serviceMean) {
	/* generators */

	genA = mt19937(seed+1);
	genS = mt19937(seed-1);

	/* simulation setup */
	maxPackets = packets;
	servers = _servers;
	
	scheduleArrival();

	eventLogStream << fixed << setprecision(2);
	cout << fixed << setprecision(2);
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
	if (!(servers-serversBusy)) {
		packetIDQueue.push(pid);
		// queue length update
		weightedQueueLength += (clockTime - lastQueueUpdateTime) * packetIDQueue.size();
		lastQueueUpdateTime = clockTime;
	}
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
	serverUtilization = busyTime / clockTime * 100 * servers;
	throughput = packetsServed / clockTime;
}

void Simulation::printStatistics() {
	cout
	<< "Simulation time: " << clockTime << "\n"
	<< "Packets arrived: " << lastPacketID << "\n"
	<< "Packets served: " << packetsServed << "\n"
	<< "Average waiting time: " << avgWait << "\n"
	<< "Average delay time: " << avgDelay << "\n"
	<< "Average queue length: " << avgQueueLength << '\n'
	<< "Server Utilization: " << serverUtilization << "%\n"
	<< "Throughput: " << throughput << " packets/time\n"
	;
}

bool fileEmpty(const string& filename) {
	struct stat fileStat;
	if (stat(filename.c_str(), &fileStat) != 0) return true;

	return fileStat.st_size == 0;
}

void Simulation::writeStatisticsToCSV(const string& filename) {
	ofstream file(filename, ios::app);
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return;
	}

	if (fileEmpty(filename)) {
		file
		<< fixed << setprecision(4)
		<< "SimTime" << ','
		<< "ServerBusyTime" << ','
		<< "ArrivalRate" << ','
		<< "ServiceRate" << ','
		<< "ArrivalSeed" << ','
		<< "ServiceSeed" << ','
		<< "PacketsServed" << ','
		<< "PacketsArrived" << ','
		<< "AvgWaitingTime" << ','
		<< "AvgDelay" << ','
		<< "AvgQueueLength" << ','
		<< "ServerUtilization" << ','
		<< "Throughput" << '\n'
		;
	}

	file
	<< fixed << setprecision(4)
	<< clockTime << ','
	<< busyTime << ','
	<< 1. / iA.lambda() << ','
	<< 1. / sD.lambda() << ','
	<< genA.default_seed << ','
	<< genS.default_seed << ','
	<< maxPackets << ','
	<< packetsArrived << ','
	<< avgWait << ','
	<< avgDelay << ','
	<< avgQueueLength << ','
	<< serverUtilization << ','
	<< throughput << '\n'
	;

	file.close();
}