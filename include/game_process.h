#ifndef GAMEPROCESS_H 
#define GAMEPROCESS_H

#include "player.h"   
#include "enemy.h"  
#include "abilities_manager.h"
#include "game_setup.h"

// класс игрового процесса
class GameSession {
public:
    enum class step_result {GameOver, PlayerAlive};                              // перечисление для результатов шага игры
    GameSession();                                                               // конструктор по умолчанию
    GameSession(GameSetup& gameSetup);                                           // конструктор, принимающий настройки игры
    GameSession::step_result run_game_step();                                    // метод выполнения одного шага игры
    void place_ships();                                                          // метод размещения кораблей на поле
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
