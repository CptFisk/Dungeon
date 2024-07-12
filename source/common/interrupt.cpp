#include <chrono>
#include <common/interrupt.hpp>
#include <thread>

namespace Common {
Interrupt::Interrupt(const long& time, bool& execute)
  : mExecute(execute)
  , mTime(time) {}

void
Interrupt::execute() {
    while (mExecute) {
        for (auto& function : mFunctions) {
            function();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(mTime));
    }
}

void
Interrupt::addFunction(const std::function<void()>& function) {
    mFunctions.push_back(function);
}
}