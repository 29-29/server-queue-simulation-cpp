#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

int main() {
	cout << fixed << setprecision(2);
	Simulation sim;
	sim.run();

	sim.printStatistics();
	cout << "--------------------\n";
	cout << sim.eventLogs();
}
