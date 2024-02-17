#pragma once
#include <vector>
#include <memory>

namespace Common {

class Initializer {
  public:
    virtual void startup()  = 0;
    virtual void shutdown() = 0;

  protected:
    bool isStarted();

  private:
};

class InitHandler {
  public:
    void addInitializer(std::shared_ptr<Initializer> init);
    void startup();
    void shutdown();

  private:
  protected:
    std::vector<std::shared_ptr<Initializer>> mInitializers;
};

}