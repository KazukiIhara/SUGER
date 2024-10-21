#include "FixFPS.h"

#include <thread>

void FixFPS::Initialize() {
	// 現在時間を記録する
	reference_ = std::chrono::steady_clock::now();
}

void FixFPS::Update() {
	static std::chrono::microseconds accumulatedError(0);
	const std::chrono::microseconds targetFrameTime(uint64_t(1000000.0 / targetFPS_));

	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	std::chrono::microseconds sleepTime = targetFrameTime - elapsed + accumulatedError;

	if (sleepTime.count() > 0) {
		std::this_thread::sleep_for(sleepTime);
	}

	now = std::chrono::steady_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	accumulatedError += targetFrameTime - elapsed;
	reference_ = now;
}
