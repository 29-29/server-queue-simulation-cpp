/*
 * File:   RandomGenExpoMean.h
 * Author: jojo
 *
 * Created on July 22, 2012, 2:30 PM
 */

#ifndef RANDOMGENEXPOMEAN_H
#define    RANDOMGENEXPOMEAN_H
#include <cmath>
#include <cstdlib>

using namespace std;

class RandomExpoMean {
public:
    RandomExpoMean(double mean);
    void setMean(double mean);
    double getValue();
    double getAverageMean() const {return average/count;}

private:
    double randomExpoMean;
    double Globalmean;
    double average = 0;
    int count = 0;
    void generate();
};

void RandomExpoMean::generate() {
    //double uniform = rand() % int (60*Globalmean-1) + 1;
    //randomExpoMean = -1*log(1-(uniform/60));
   
    double uniform = rand() % int (60*Globalmean-1) + 1;
    randomExpoMean = -1*log(1-(uniform/(60.0*Globalmean)))*Globalmean*60;
}

// this member function resets everything
void RandomExpoMean::setMean(double mean) {
    Globalmean = mean;
}

double RandomExpoMean::getValue() {
    count++;
    generate();
    average += randomExpoMean;
    return randomExpoMean;
}

#endif    /* RANDOMGENEXPOMEAN_H */

