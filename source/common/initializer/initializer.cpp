#include <common/initializer/initializer.hpp>

namespace Common {

InitHandler::InitHandler(std::vector<std::shared_ptr<Initializer>> initializers)
  : mInitializers(initializers) {
    for (auto& initializer : mInitializers) {
        initializer->startup();
    }
}

void
InitHandler::addInitializer(std::shared_ptr<Initializer> init) {
    mInitializers.push_back(init);
}

void
InitHandler::startup() {
    for (auto& initializer : mInitializers) {
        initializer->startup();
    }
}

void
InitHandler::shutdown() {
    for (auto& initializer : mInitializers) {
        initializer->shutdown();
    }
}
}