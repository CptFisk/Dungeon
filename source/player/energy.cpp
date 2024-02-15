#include <player/energy.hpp>

namespace Player{
    EnergyMeter::EnergyMeter(const Engine::Scale& scale) :mEnergy(100.0) {}
    EnergyMeter::~EnergyMeter() {}
}