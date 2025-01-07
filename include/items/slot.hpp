#pragma once
#include <items/slots.hpp>
#include <items/item.hpp>

namespace Items{
struct Slot {
    const SlotType Type; // Item type
    Item*          Item; // Pointer to item
    explicit Slot(const SlotType type)
      : Type(type)
      , Item(nullptr) {}
};
}