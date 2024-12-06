#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

#include "abilities.h"         
#include "display.h"  

// класс способности двойного урона
class DoubleDamageAbility : public Ability {
public:
    DoubleDamageAbility(AbstractPlayer& player_ref);    // конструктор, принимающий ссылку на объект игрока
    void use() override;                                // переопределение метода для использования способности двойного урона
    std::string get_name() override;                    // переопределение метода для получения имени способности
    ~DoubleDamageAbility() = default;                   // деструктор класса, по умолчанию

private:
    Display cli;  // объект для взаимодействия с интерфейсом командной строки
    AbstractPlayer& player; // ссылка на поле противника
    Board& board; // ссылка на поле противника
};

#endif



