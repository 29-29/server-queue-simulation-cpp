#pragma once

class Packet {
	double arrival;
	double departure;
public:
	Packet(double arrival):
	arrival(arrival) {}

	// getter
	double getArrival() const {return arrival;}
	double getDeparture() const {return departure;}
	// setter
	double setDeparture(double time) {
		departure = time;
	}
};