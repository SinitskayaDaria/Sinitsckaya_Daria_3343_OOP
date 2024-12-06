#include "../include/double_damage.h" 

DoubleDamageAbility::DoubleDamageAbility(Board& opponent_board) : board(opponent_board) {} 

// метод использования способности двойного урона
void DoubleDamageAbility::use() {
    std::pair<char, int> coordinate = cli.read_coordinate(); // чтение координат от пользователя для выстрела
    board.shoot(coordinate, 2);                              // выполнение выстрела с двойным уроном

}
