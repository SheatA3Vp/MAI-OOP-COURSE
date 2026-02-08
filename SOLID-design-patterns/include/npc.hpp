#pragma once
#include <string>
#include <stdexcept>

class Visitor;

class NPC {
public:
    NPC(const std::string& name, double x, double y, const std::string& type);
    virtual ~NPC() = default;

    virtual void accept(Visitor& visitor) = 0;

    const std::string& getName() const;
    double getX() const;
    double getY() const;
    const std::string& getType() const;

    double distanceTo(const NPC& other) const;

private:
    std::string name_;
    double x_, y_;
    std::string type_;
    
    void validateCoordinates(double x, double y) const;
};