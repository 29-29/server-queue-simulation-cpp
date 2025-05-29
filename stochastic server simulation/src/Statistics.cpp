#include "Statistics.h"

bool fileEmpty(const string& filename) {
	struct stat fileStat;
	if (stat(filename.c_str(), &fileStat) != 0) return true;

	return fileStat.st_size == 0;
}

void Stats::accumulate(int N) {
	simTime /= N;
	packetsArrived /= N;
	packetsServed /= N;
	packetsDropped /= N;
	dropRate /= N;
	avgWait /= N;
	avgDelay /= N;
	avgQueue /= N;
	serverUtilization /= N;
	throughput /= N;
}

Stats& Stats::operator+=(const Stats& other) {
	simTime += other.simTime;
	packetsArrived += other.packetsArrived;
	packetsServed += other.packetsServed;
	packetsDropped += other.packetsDropped;
	dropRate += other.dropRate;
	avgWait += other.avgWait;
	avgDelay += other.avgDelay;
	avgQueue += other.avgQueue;
	serverUtilization += other.serverUtilization;
	throughput += other.throughput;
	return *this;
}

void Stats::writeToCSV(const string& filename) {
	ofstream file(filename, ios::app);
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return;
	}

	if (fileEmpty(filename)) {
		file
		<< fixed << setprecision(4)
		<< "TrafficIntensity(rho)" << ','
		<< "Servers" << ','
		<< "BufferLimit" << ','
		<< "SimTime" << ','
		<< "ArrivalRate" << ','
		<< "ServiceRate" << ','
		<< "PacketsArrived" << ','
		<< "PacketsServed" << ','
		<< "PacketsDropped" << ','
		<< "DropRate" << ','
		<< "AvgWaitingTime" << ','
		<< "AvgDelay" << ','
		<< "AvgQueueLength" << ','
		<< "ServerUtilization" << ','
		<< "Throughput" << '\n'
		;
	}

	file
	<< fixed << setprecision(4)
	<< arrivalRate / serviceRate * servers << ','
	<< servers << ','
	<< bufferLimit << ','
	<< simTime << ','
	<< arrivalRate << ','
	<< serviceRate << ','
	<< packetsArrived << ','
	<< packetsServed << ','
	<< packetsDropped << ','
	<< dropRate << ','
	<< avgWait << ','
	<< avgDelay << ','
	<< avgQueue << ','
	<< serverUtilization << ','
	<< throughput << '\n'
	;

	file.close();
}

void Stats::printStatistics() {
cout
<< "Traffic intensity (rho): " << arrivalRate / serviceRate * servers << "\n"
<< "Average simulation time: " << simTime << "\n"
<< "Average packets arrived: " << packetsArrived << "\n"
<< "Average packets served: " << packetsServed << "\n"
<< "Average packets dropped: " << packetsDropped << "\n"
<< "Average drop rate: " << dropRate * 100 << "%\n"
<< "Average waiting time: " << avgWait << "\n"
<< "Average delay time: " << avgDelay << "\n"
<< "Average queue length: " << avgQueue << '\n'
<< "Average server Utilization: " << serverUtilization << "%\n"
<< "Average throughput: " << throughput << " packets/time\n"
;
}