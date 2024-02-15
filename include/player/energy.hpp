#pragma once
#include <engine/structures.hpp>

namespace Player{
    class EnergyMeter{
      public:
        EnergyMeter(const Engine::Scale& scale);
        ~EnergyMeter();
      protected:
      private:
        float mEnergy;

    };
}