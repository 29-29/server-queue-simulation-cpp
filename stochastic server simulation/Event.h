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

	// getters
	double getTime() const { return time; }
	EventType getType() const { return type; }
	int getPacketID() const { return packetID; }

	// setters
	void setTime(double _time) { time = _time; }
	void setType(EventType _type) { type = _type; }
	void setPacketID(int pid) { packetID = pid; }

	bool operator>(Event other) const {
		return time > other.time;
	}
};

