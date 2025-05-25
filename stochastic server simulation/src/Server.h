#pragma once
enum ServerStatus {
	IDLE, BUSY
};

struct Server {
	ServerStatus status=IDLE;
	double busyTime=0.0;
};

