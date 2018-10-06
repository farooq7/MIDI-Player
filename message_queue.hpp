#ifndef MESSAGE_QUEUE_HPP
#define MESSAGE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class message_queue
{
public:

	void addMessage(const std::string message);

	bool empty() const;

	std::string removeMessage();

private:
	std::queue<std::string> messageQueue;
	mutable std::mutex the_mutex;
	std::condition_variable the_condition;

};
#endif