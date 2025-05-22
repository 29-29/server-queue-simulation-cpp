#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

void simulate(double arrivalMean, double serviceMean, int seed, int packets=200) {
	Simulation sim(arrivalMean, serviceMean, seed, packets);
	sim.run();
	sim.printStatistics();
	// cout << "------------------\n";
	// cout << sim.eventLogs();
}

int main() {
	int seed = time(nullptr);
	cout << "iA=5 = sD=5\n";
	simulate(5,5,seed);

	cout << "\niA=3 < sD=7\n";
	simulate(3,7,seed);

	cout << "\niA=7 > sD=3\n";
	simulate(7,3,seed);
}
