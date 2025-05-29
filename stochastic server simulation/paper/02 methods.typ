#import "@preview/codelst:2.0.2": sourcecode
= Methods

== Simulation Model

The simulation models a single-server or multi-server queueing system using discrete-event simulation. Events are driven by randomly generated inter-arrival and service times, sampled from the `std` exponential distribution. The following comprise the setup:

== Arrival and Service Process

The inter-arrival and service times are sampled from a exponentially distributed random generator. The probability density function of this probability distribution is:
$
	f(x) = lambda e^(-lambda x)
$
where $x$ is the time being measured, $lambda$ is the rate, implying that $1/lambda$ is the mean time.

In practive, the inter-arrival and service times are generated using the standard library's _Mersenne Twister_ engine, `std::mt19937`, which is a pseudorandom generator, being fed into the `std::exponential_distribution`. The declaration for which can be seen in @ia-s-generator below.

#figure(
	caption: "Inter-arrival and service times generators",
	sourcecode(```cpp
// Simulation.h
#include <random>
class Simulation
{
private:
	/* RNGs */
	mt19937 genA;
	mt19937 genS;
	exponential_distribution<> iA;
	exponential_distribution<> sD;

// ...

}
	```)
)<ia-s-generator>

And they are generated as so:
#figure(
	caption: "Inter-arrival and service times generation usage",
	sourcecode(```cpp
// Simulation.cpp
double Simulation::scheduleEvent(const EventType& type, const int& id) {
	double time;

	if (type == ARRIVAL) time = clockTime + iA(genA);
	else time = clockTime + sD(genS);

	eventQueue.push(Event{ time, type, id });
	return time;
}
	```,
	highlighted: (5,6)
	)
)

== Simulation and System Parameters

#lorem(50)

== Event Handling

#lorem(50)

== Data Collection & Metrics

#lorem(50)

== Random Seed

#lorem(50)

== Tools or Libraries

#lorem(50)
