#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

void simulate(double arrivalMean, double serviceMean, int seed, int packets=20) {
	Simulation sim(arrivalMean, serviceMean, seed, packets);
	sim.run();
	sim.printStatistics();
	// cout << "------------------\n";
	// cout << sim.eventLogs();
}

int main() {
	int seed = time(nullptr);
	int runs[3][2] = {{1,1}, {2,1}, {1,2}};
	for (auto run : runs) {
		cout << "iA=" << run[0] << " sD=" << run[1] << '\n';
		simulate(run[0], run[1], seed);
		cout << '\n';
	}
}
