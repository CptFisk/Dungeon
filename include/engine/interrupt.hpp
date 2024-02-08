#pragma once
#include <functional>
#include <memory>
#include <vector>

namespace Engine {
class Interrupt {
  public:
    Interrupt(const long int& time, bool& execute);
    void execute();
    void addFunction(std::function<void()> function);

  protected:
  private:
    bool&                                             mExecute;
    long int                                          mTime;
    std::vector<std::function<void()>> mFunctions;
};
}