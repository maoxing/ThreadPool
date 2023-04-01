

#include <iostream>
#include <thread>
#include <chrono>
#include <ThreadPool.h>

int main()
{
	ThreadPool pool;

	pool.start();


	pool.dispatchTask([]() {

		std::cout << "Hello  World" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	});

	std::this_thread::sleep_for(std::chrono::seconds(5));

	pool.stop();

	return 0;
}