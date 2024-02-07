#include <engine/initializer.hpp>

namespace Engine{
void
InitHandler::addInitializer(std::shared_ptr<Initializer> init) {
    mInitializers.push_back(init);
}

void
InitHandler::startup() {
    for(auto &initializer : mInitializers){
        initializer->startup();
    }
}

void
InitHandler::shutdown() {
    for(auto &initializer : mInitializers){
        initializer->shutdown();
    }
}
}