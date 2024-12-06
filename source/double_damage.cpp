#include "../include/double_damage.h" 

DoubleDamageAbility::DoubleDamageAbility(AbstractPlayer& player_ref): player(player_ref), board(player.get_board()) {}

// метод использования способности двойного урона
void DoubleDamageAbility::use() {
    std::pair<char, int> coordinate = cli.read_coordinate(); // чтение координат от пользователя для выстрела
    board.shoot(coordinate, 2);                              // выполнение выстрела с двойным уроном

}

std::string DoubleDamageAbility::get_name() {return "Double-damage";} // возвращает имя способности