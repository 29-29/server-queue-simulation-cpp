#include "RandomGenExpoMean.h"

RandomExpoMean::RandomExpoMean(double mean) {
    RandomExpoMean::Globalmean = mean;
    RandomExpoMean::count = 0;
    RandomExpoMean::average = 0;
}
