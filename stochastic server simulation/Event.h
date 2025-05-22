#pragma once

enum EventType {
	ARRIVAL, DEPARTURE
};

class Event
{
private:
	double time;
	EventType type;
	int packetID;

public:
	Event(double _time, EventType _type, int pid): time(_time), type(_type), packetID(pid) {}

	bool operator>(Event other) const {
		return time > other.time;
	}
};

