#include <chrono>
#include <engine/interrupt.hpp>
#include <thread>
#include <iostream>

namespace Engine {
Interrupt::Interrupt(const long& time, bool& execute)
  : mExecute(execute)
  , mTime(time) {}

void
Interrupt::execute() {
    while (mExecute) {
        for (auto& func : mFunctions) {
            func();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(mTime));
    }
    std::cout << "Thread " << mTime << std::endl;
}

void
Interrupt::addFunction(std::function<void()> function) {
    mFunctions.push_back(function);
}
}