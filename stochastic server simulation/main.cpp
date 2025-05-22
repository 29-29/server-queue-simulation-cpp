#include <queue>
#include <vector>
#include <iomanip>

#include "Simulation.h"

void simulate(double arrivalMean, double serviceMean, int seed, int packets=200) {
	int runs[3][2] = {
		{arrivalMean,serviceMean},
		{arrivalMean*2,serviceMean},
		{arrivalMean,serviceMean*2},
	};
	string filenames[3] = {
		"iAT=ST", "iAT>ST", "iAT<ST"
	};

	for (int i=0; i<3; i++) {
		Simulation sim(runs[i][0], runs[i][1], seed, packets);
		sim.run();
		sim.printStatistics();
		cout<<'\n';
	}
}


int main() {
	int seed = time(nullptr);

	simulate(1, 1, seed);
}
