#ifndef SHARED_DOUBLE_BUFFER_HPP
#define SHARED_DOUBLE_BUFFER_HPP

#include <mutex>
#include <condition_variable>
#include <deque>
#include <iostream>

using namespace std;

class SharedDoubleBuffer
{
public:
	SharedDoubleBuffer(int buffersize);
	~SharedDoubleBuffer();
	void write(double value);
	double read();
	int writeBufferSize();
	int bufferSize();
	void reset();

private:
	deque<double> *writeBuffer;
	deque<double> *readBuffer;
	int bufsize;
	mutex the_mutex;
	condition_variable the_condition;
};
#endif

