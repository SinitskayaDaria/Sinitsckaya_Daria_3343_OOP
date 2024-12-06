#ifndef ABILITIES_H
#define ABILITIES_H

#include <optional>
#include <random>
#include <memory>

#include "board.h"
#include "ship_manager.h"

// класс способностей
class Ability {
public:
    virtual void use() = 0;                 // метод использования способностей
};

#endif