#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

#include "abilities.h"         
#include "display.h"  

// класс способности двойного урона
class DoubleDamageAbility : public Ability {
public:
    DoubleDamageAbility(Board& opponent_board); // конструктор, принимающий ссылку на игровое поле противника
    void use() override;                        // переопределение метода для использования способности двойного урона

private:
    Display cli;  // объект для взаимодействия с интерфейсом командной строки
    Board& board; // ссылка на поле противника
};

#endif
