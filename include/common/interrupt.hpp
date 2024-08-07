#pragma once
#include <functional>
#include <memory>
#include <vector>

namespace Common {
class Interrupt {
  public:
    Interrupt(const long int& time, bool& execute);
    void execute();
    void addFunction(const std::function<void()>& function);

  protected:
  private:
    bool&                                             mExecute;
    long int                                          mTime;
    std::vector<std::function<void()>> mFunctions;
};
}