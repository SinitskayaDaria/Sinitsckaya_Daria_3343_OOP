#ifndef PLAYER_H 
#define PLAYER_H

#include "abstract_player.h"

// класс представления игрока в игре
class Player : public AbstractPlayer {
public:
    Player(int field_size, int ships_count, const std::vector<int>& sizes); // конструктор, принимающий размер поля, количество кораблей и их размеры
    bool place_ships() override;                                            // метод размещения кораблей
    bool make_shot(AbstractPlayer& opponent) override;                      // метод выстрела по противнику

private:
    Display cli; // объект для взаимодействия с интерфейсом командной строки
};

#endif 
