#ifndef __CLOCKTIMER8_HPP__
#define __CLOCKTIMER8_HPP__

#include <thread>
#include <chrono>

template <class TYPE, class DTYPE>
class clockTimer {

	private:
		int clk;
		double targetDT;

		void waitOnDT(double executionTime);
	public:
		clockTimer(int clockSpeed);

		double executeCommand(TYPE func, DTYPE data);
};

template <class TYPE, class DTYPE>
clockTimer<TYPE, DTYPE>::clockTimer(int clockSpeed) {
	clk = clockSpeed;
	targetDT = 1.0 / clk;
}

template <class TYPE, class DTYPE> void
clockTimer<TYPE, DTYPE>::waitOnDT(double executionTime) {
	if (executionTime >= targetDT) {
		return;
	} else {
		// TODO: wait till DT is reached
	}
}

template <class TYPE, class DTYPE> double
clockTimer<TYPE, DTYPE>::executeCommand(TYPE func, DTYPE data) {

	auto beg_t = std::chrono::system_clock::now();
	func(data);
	auto end_t = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end_t - beg_t;

	waitOnDT(diff.count());
	return diff.count();
}

#endif