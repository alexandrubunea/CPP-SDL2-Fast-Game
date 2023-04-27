#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

class Car : public GameObject {
private:

public:
    Car(
        float, 
        float,
        UINT_32, 
        UINT_32
    );
    ~Car();
};