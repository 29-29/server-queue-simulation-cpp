#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

void simulate(double arrivalMean, double serviceMean, int seed, int servers=1, int packets=1000) {
	double runs[3][2] = {
		{arrivalMean,serviceMean},
		{arrivalMean/2,serviceMean},
		{arrivalMean,serviceMean/2},
	};
	string filenames[3] = {
		"IATeST", "IATgST", "IATlST"
	};

	for (int i=0; i<3; i++) {
		Simulation sim(runs[i][0], runs[i][1], servers, seed, packets);
		sim.run();
		sim.printStatistics();
		cout<<'\n';
		// sim.writeStatisticsToCSV("outputs/" + filenames[i] + ".csv");
	}
}


int main() {
	int seed = time(nullptr);
	int n = 100;

	for (int i=0; i<n; i++) {
		simulate(1, 1, seed+i*3);
	}
}
