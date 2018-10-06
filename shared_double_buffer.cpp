#include "shared_double_buffer.hpp"

SharedDoubleBuffer::SharedDoubleBuffer(int buffersize)
{
	writeBuffer = new deque<double>;
	readBuffer = new deque<double>;
	bufsize = buffersize;
}

SharedDoubleBuffer::~SharedDoubleBuffer()
{
	delete writeBuffer;
	delete readBuffer;
}

void SharedDoubleBuffer::write(double value)
{
	unique_lock<mutex> locker(the_mutex);
	writeBuffer->push_back(value);
	locker.unlock();
	the_condition.notify_one();
}

double SharedDoubleBuffer::read()
{
	while ((writeBuffer->empty() && readBuffer->empty()))
	{
		//the_condition.wait(locker);
	}
	if (readBuffer->empty())
	{
		std::swap(writeBuffer, readBuffer);
	}
	double front = readBuffer->front();
	readBuffer->pop_front();
	return front;
}

void SharedDoubleBuffer::reset()
{
	unique_lock<mutex> locker(the_mutex);
	readBuffer->clear();
	writeBuffer->clear();
	locker.unlock();
}

int SharedDoubleBuffer::writeBufferSize()
{
	unique_lock<mutex> locker(the_mutex);
	return writeBuffer->size();
	locker.unlock();
}

int SharedDoubleBuffer::bufferSize()
{
	unique_lock<mutex> locker(the_mutex);
	return bufsize;
	locker.unlock();
}