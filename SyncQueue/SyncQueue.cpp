#include "pch.h"
#include <iostream>
#include "synchronous_queue.h"
#include <thread>
#include <algorithm>

SynchronousQueue<int> q(2);

bool stopping = false;

void producing(int id) {
	for (int i = 0; i < 2; i++) {
		q.produce(id);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}


void consuming(int id) {
	for (int i = 0; i < 2; i++) {
		int val = q.consume(id);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

const int Number_of_consumers = 4;
const int Number_of_producers = 4;



int main()
{
	std::vector<std::thread> producers;
	std::vector<std::thread> consumers;
	producers.reserve(Number_of_producers);
	consumers.reserve(Number_of_consumers);
	for (int i = 0; i < Number_of_producers; i++)
		producers.emplace_back(producing, i + 1);
	for (int i = 0; i < Number_of_consumers; i++)
		consumers.emplace_back(consuming, i + 1);

	std::for_each(producers.begin(), producers.end(), [](auto& th) {th.join(); });
	std::for_each(consumers.begin(), consumers.end(), [](auto& th) {th.join(); });
	
	getchar();
	return 0;
}
