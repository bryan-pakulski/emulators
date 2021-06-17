#ifndef __taskScheduler_HPP__
#define __taskScheduler_HPP__

#include <thread>
#include <chrono>

typedef std::chrono::duration<double, std::milli> td_milliseconds;

template <class TYPE, class DTYPE>
class taskScheduler {

	private:
		int clk;
		td_milliseconds targetDT;

		void waitOnDT(std::chrono::milliseconds executionTime);
	public:
		taskScheduler(int clockSpeed);
		double executeCommand(TYPE func, DTYPE data);
};

/**
 * Initialises target delta time between execution cycles
 *
 * @param clockSpeed expected clock speed (instructions per 1000.0 m/s)
 */
template <class TYPE, class DTYPE>
taskScheduler<TYPE, DTYPE>::taskScheduler(int clockSpeed) {
	clk = clockSpeed;
	targetDT = td_milliseconds(1000.0 / clk);
}

/**
 * Compares the execution time of a command to the expected delta time, if the time is less the thread waits until dt is reached before continuing execution
 *
 * @param executionTime 
 */
template <class TYPE, class DTYPE> void
taskScheduler<TYPE, DTYPE>::waitOnDT(std::chrono::milliseconds executionTime) {
	if (executionTime.count() >= targetDT.count()) {
		return;
	} else {
		td_milliseconds waitTime = td_milliseconds(targetDT.count() - executionTime.count());
		std::this_thread::sleep_for(waitTime);
	}
}

/**
 * Executes a passed command and measures the execution time, waits after execution if DT has not been reached
 * 
 * This function can be extended / overloaded to support a variety of function calls with multi data variables
 *
 * @param func function pointer to call
 * @param data data to pass through 
 */
template <class TYPE, class DTYPE> double
taskScheduler<TYPE, DTYPE>::executeCommand(TYPE func, DTYPE data) {

	auto beg_t = std::chrono::system_clock::now();
	func(data);
	auto end_t = std::chrono::system_clock::now();

	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - beg_t);
	waitOnDT(diff);
	return diff.count();
}

#endif