#pragma once
#include <vector>
#include <memory>

namespace Common {

class Initializer {
  public:
    virtual void startup()  = 0;
    virtual void shutdown() = 0;

  protected:
  private:
};

class InitHandler {
  public:
    explicit InitHandler(std::vector<std::shared_ptr<Initializer>> initializers);
    void shutdown();

  private:
  protected:
    std::vector<std::shared_ptr<Initializer>> mInitializers;
};

}