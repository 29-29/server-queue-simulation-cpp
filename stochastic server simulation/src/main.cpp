#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

void simIncArrivalRate(double floor, double ceil, int steps, int seed, int n=100) {
	string filename = "incArrivalRate.csv";
	double stepSize = (ceil - floor) / (steps-1);
	for (int i=0; i < steps; i++) {
		double arrivalRate = floor + i * stepSize;

		SimulationN sim(n, arrivalRate, 1, 1, 5, seed, 100);
		sim.run();
		// sim.printStatistics();
		sim.writeStatsToCSV("../outputs/" + filename);
		cout << "\r" << i+1 << "/" << steps;
	}
	cout << '\n';
}

void simIncServiceRate(double floor, double ceil, int steps, int seed, int n=100) {
	string filename = "incServiceRate.csv";
	double stepSize = (ceil - floor) / (steps - 1);
	for (int i=0; i < steps; i++) {
		double serviceRate = floor + i * stepSize;

		SimulationN sim(n, 1, serviceRate, 1, 5, seed, 1000);
		sim.run();
		// sim.printStatistics();
		sim.writeStatsToCSV("../outputs/" + filename);
		cout << "\r" << i+1 << "/" << steps;
	}
	cout << '\n';
}

void simIncServers(int floor, int ceil, int seed, int n=100) {
	string filename = "incServers.csv";
	for (int i=floor; i <= ceil; i++) {

		SimulationN sim(n, 1, 1, i, 5, seed, 1000);
		sim.run();
		// sim.printStatistics();
		sim.writeStatsToCSV("../outputs/" + filename);
		cout << "\r" << i << "/" << ceil;
	}
	cout << '\n';
}

void simIncBufferLimit(int floor, int ceil, int seed, int n=100) {
	string filename = "incBufferLimit.csv";
	for (int i=floor; i <= ceil; i++) {

		SimulationN sim(n, 1, 1, 1, i, seed, 1000);
		sim.run();
		// sim.printStatistics();
		sim.writeStatsToCSV("../outputs/" + filename);
		cout << "\r" << i << "/" << ceil;
	}
	cout << '\n';
}

void simIncPackets(int floor, int ceil, int seed, int n=100) {
	string filename = "incPackets.csv";
	for (int i=floor; i <= ceil; i+=10) {

		SimulationN sim(n, 1, 1, 1, 5, seed, i);
		sim.run();
		// sim.printStatistics();
		sim.writeStatsToCSV("../outputs/" + filename);
		cout << "\r" << i << "/" << ceil;
	}
	cout << '\n';
}

int main() {
	int seed = time(nullptr);
	int n = 100;
	int res = 250;

	simIncArrivalRate(0.1, 10, res, seed, n);
	simIncServiceRate(0.1, 10, res, seed, n);
	simIncServers(1, 20, seed, n);
	simIncBufferLimit(2, 20, seed, n);
	simIncPackets(200, 2500, seed, n);
}