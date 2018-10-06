#include "message_queue.hpp"

void message_queue::addMessage(const std::string message)
{
	std::unique_lock<std::mutex> locker(the_mutex);
	messageQueue.push(message);
	locker.unlock();
	the_condition.notify_one();
}

bool  message_queue::empty() const
{
	std::lock_guard<std::mutex> locker(the_mutex);
	return messageQueue.empty();
}

std::string  message_queue::removeMessage()
{
	std::unique_lock<std::mutex> locker(the_mutex);
	while (messageQueue.empty())
	{
		the_condition.wait(locker);
	}
	std::string popped_value = messageQueue.front();
	messageQueue.pop();
	return popped_value;
}