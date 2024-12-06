#include "../include/game_process.h"

GameSession::GameSession(int field_size, int ships_count, const std::vector<int>& sizes)
    : player(field_size, ships_count, sizes), // инициализация игрока с заданным размером поля, количеством кораблей и их размерами
      enemy(field_size, ships_count, sizes),  // инициализация противника с теми же параметрами
      abilities_manager(player, enemy) {}     // инициализация менеджера способностей 


GameSession::GameSession(GameSetup& gameSetup)
    : setup(gameSetup),                                                           // инициализация переменной setup с помощью переданных настроек
      player(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()), // инициализация игрока с указанным размером поля и количеством кораблей
      enemy(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()),  // инициализация врага с указанным размером поля и количеством кораблей
      abilities_manager(player, enemy) {}                                         // инициализация менеджера способностей

// метод выполнения игрового процесса
void GameSession::start() {
    // отображение игровых полей игрока и противника
    cli.display(player.get_board(), enemy.get_board());
    
    // размещение кораблей игроком
    player.place_ships();
    
    // размещение кораблей противником, проверка на успех
    if (!enemy.place_ships()) {
        std::cout << "The enemy was unable to position the ships!\nTry entering other data.\n";
        return;  // завершение процесса, если противник не смог разместить корабли
    }

    std::cout << "\n";
    bool player_turn = true; // отслеживание чей сейчас ход

    // пока ни один из игроков не проиграл
    while (!player.is_lose() && !enemy.is_lose()) {
        if (player_turn) {                       // ход игрока
            cli.message("Your turn -> ");
            execute_shot(player, enemy);         // игрок атакует противника
            if (enemy.update()) {                // проверка обновления состояния противника
                abilities_manager.add_ability(); // добавление новой способности
            }
        } else {                                 // ход противника
            std::cout << "Enemy turn -> ";
            execute_shot(enemy, player);         // противник атакует игрока
            player.update();                     // обновление состояния игрока
        }

        // отображение обновленных игровых полей
        cli.display(player.get_board(), enemy.get_board());
        player_turn = !player_turn; // смена хода
    }

    // провекрка победителя
    if (player.is_lose()) {
        std::cout << "Enemy win!\n"; // победа противника
        return;                                     
    } else {
        std::cout << "You win!\n";   // победа игрока
        return;                                         
    }
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

