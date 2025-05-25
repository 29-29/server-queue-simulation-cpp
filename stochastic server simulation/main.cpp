#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

int main() {
	int seed = time(nullptr);
	int n = 100;

	SimulationN sim(n,1,1,1,5,seed,1000);
	sim.run();
	sim.printStatistics();
}