#ifndef GAMEPROCESS_H 
#define GAMEPROCESS_H

#include "player.h"   
#include "enemy.h"  
#include "abilities_manager.h"
#include "game_setup.h"

// класс игрового процесса
class GameSession {
public:
    GameSession(int field_size, int ships_count, const std::vector<int>& sizes); // конструктор, принимающий параметры настройки игрового процесса
    GameSession(GameSetup& gameSetup);                                           // конструктор, принимающий настройки игры
    void start();                                                                // метод запуска игрового процесса
    bool execute_shot(AbstractPlayer& shooter, AbstractPlayer& target);          // метод выстрела, определяет попадание в цель
    bool use_ability();                                                          // метод использования способностей игра
    void serialize(std::ostream& os);                                            // метод преобразования данных состояния игровой сессии в поток вывода
    void deserialize(std::istream& is);                                          // метод преобразования данных состояния игровой сессии из потока ввода

private:
    Display cli;                                                        // объект для вывода сообщений в интерфейс командной строки
    GameSetup setup;                                                    // объект, представляющий настройки игры
    Player player;                                                      // объект игрока
    Enemy enemy;                                                        // объект противника
    AbilitiesManager abilities_manager;                                 // менеджер управления способностями
};

#endif 
