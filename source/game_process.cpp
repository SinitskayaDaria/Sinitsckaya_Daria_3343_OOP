#include "../include/game_process.h"

GameSession::GameSession()
    : player(0, 0, {}),                     // инициализация игрока с нулевыми параметрами
      enemy(0, 0, {}),                      // инициализация противника с нулевыми параметрами
      abilities_manager(player, enemy) {}   // создание менеджера способностей

GameSession::GameSession(GameSetup& gameSetup)
    : setup(gameSetup),                                                            // инициализация параметров игры
      player(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()),  // инициализация игрока 
      enemy(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()),   // инициализация противника 
      abilities_manager(player, enemy) {}                                          // иоздание менеджера способностей

// метод выполнения одного хода в игре
GameSession::step_result GameSession::run_game_step() {
    std::cout << "Your turn -> ";          // сообщение о ходе игрока
    execute_shot(player, enemy);           // игрок атакует противника

    // проверка состояния противника
    if (enemy.update()) {                  
        abilities_manager.add_ability();
    }
    
    // проверка поражения противника
    if (enemy.is_lose()) {
        std::cout << "You win! Next round...\n";                                            // сообщение о победе
        enemy = Enemy(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes());  // инициализация нового противника
        enemy.place_ships();                                                                // размещение кораблей противника
    }

    std::cout << "Enemy turn -> ";          // сообщение о ходе противника
    execute_shot(enemy, player);            // противник атакует игрока
    player.update();                        // обновление состояния игрока

    // проверка поражения игрока
    if (player.is_lose()) {
        std::cout << " Enemy win!\n";               // сообщение о проигрыше игрока
        return GameSession::step_result::GameOver;  // возврат результата "Игра окончена"
    }

    // отображение обновленных игровых полей
    cli.display(player.get_board(), enemy.get_board());

    return GameSession::step_result::PlayerAlive;  // возврат результата "Игрок жив"
}

// метод размещения кораблей
void GameSession::place_ships() {
    cli.display(player.get_board(), enemy.get_board());             // отображение обновленных игровых полей
    player.place_ships();                                           // размещение кораблей игрока

    // размещение кораблей противника
    if (!enemy.place_ships()) {
        std::cout << "The enemy was unable to position the ships!\nTry entering other data.\n";  // сообщение об ошибке
        return;
    }
    std::cout << std::endl;
}

// метод выстрела
bool GameSession::execute_shot(AbstractPlayer& shooter, AbstractPlayer& target) {
    return shooter.make_shot(target); // выполнение выстрела от одного игрока по другому и возвращение результата
}

// метод использования способностей игрока
bool GameSession::use_ability() {
    try {
        abilities_manager.use_ability();    // попытка использовать способность
        return true;                        // успешно
    } catch (GameException& exception) {    
        std::cout << exception.what();      
        return false;                       
    }
}

// метод преобразования данных состояния объекта GameSession в поток вывода
void GameSession::serialize(std::ostream& os) {
    setup.serialize(os);               // настройки игры
    player.serialize(os);              // данные игрока
    enemy.serialize(os);               // данные врага
    abilities_manager.serialize(os);   // данные способностей
}

// метод преобразования данных состояния объекта GameSession из потока ввода
void GameSession::deserialize(std::istream& is) {
    setup.deserialize(is);              // настройки игры
    player.deserialize(is);             // данные игрока
    enemy.deserialize(is);              // данные врага
    abilities_manager.deserialize(is);  // данные способностей
}

