#include "heron.hpp"
#include "battle_visitor.hpp"

Heron::Heron(const std::string& name, double x, double y)
    : NPC(name, x, y, "Heron") {}

void Heron::accept(Visitor& visitor) {
    visitor.visitHeron(*this);
}