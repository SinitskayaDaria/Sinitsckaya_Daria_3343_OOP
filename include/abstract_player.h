#ifndef ABSTRACTPLAYER_H 
#define ABSTRACTPLAYER_H

#include "ship_manager.h"    
#include "display.h"  
#include "board.h"        

// абстрактный класс представления игрока в игре
class AbstractPlayer {
public:
    AbstractPlayer(int field_size, int ships_count, const std::vector<int>& sizes); // конструктор класса, инициализирующий игровое поле и менеджер кораблей
    virtual bool place_ships() = 0;                                                 // виртуальная функция размещения кораблей
    virtual bool make_shot(AbstractPlayer& opponent) = 0;                           // виртуальная функция выстрела по противнику
    virtual bool update();                                                          // виртуальная функция обновления состояния игрока
    virtual Board& get_board();                                                     // виртуальный метод получения ссылки на игровое поле
    virtual ShipManager& get_ship_manager();                                        // виртуальный метод получения ссылки на менеджер кораблей игрока
    virtual bool is_lose();                                                         // виртуальная функция проверки проигрыша игрока
    void serialize(std::ostream& os);                                               // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);                                             // метод преобразования данных состояния игровой сессии из потока ввода

protected:
    Board board;                 // игровое поле игрока
    ShipManager ship_manager;    // менеджер кораблей игрока
};

#endif
