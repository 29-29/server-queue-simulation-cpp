#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Stats {
public:
	// input
	double arrivalRate;
	double serviceRate;
	int servers;
	int bufferLimit;

	// output
	double simTime=0;
	double packetsArrived=0;
	double packetsServed=0;
	double packetsDropped=0;
	double dropRate=0;
	double avgWait=0;
	double avgDelay=0;
	double avgQueue=0;
	double serverUtilization=0;
	double throughput=0;

	void accumulate(int N);
	Stats& operator+=(const Stats& other);
	void writeToCSV(const string& filename);
	void printStatistics();
};

#include "Statistics.cpp"