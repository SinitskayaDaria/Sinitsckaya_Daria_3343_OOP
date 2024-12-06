#include "../include/abilities_manager.h"

AbilitiesManager::AbilitiesManager(AbstractPlayer& enemy_ref) : enemy(enemy_ref) {
    add_ability();  // при создании экземпляра класса добавляется новая способность
}

// метод добавления новой способности
void AbilitiesManager::add_ability() {
    std::random_device rd;                        // генератор случайных чисел
    std::mt19937 gen(rd());                       // инициализация генератора Mersenne Twister
    std::uniform_int_distribution<> range(0, 2);  // определение равномерного распределение от 0 до 2

    int result = range(gen);                      // генерация случайного числа

    // добавление одной из трех возможных способностей
    switch (result) {
        case 0:
            abilities.emplace(std::make_unique<DoubleDamageAbility>(enemy.get_board()));  // добавление спосбности двойного урона
            break;
        case 1:
            abilities.emplace(std::make_unique<ScannerAbility>(enemy.get_board()));       // добавление спосоности сканирования
            break;
        case 2:
            abilities.emplace(std::make_unique<ShellingAbility>(enemy.get_board()));      // добавление спосбности обстрела
            break;
    }
}

// метод использования доступной способности
void AbilitiesManager::use_ability() {
    try {
        // проверка на доступные способности
        if (!abilities.empty()) {
            abilities.front()->use();            // использование способности
            abilities.pop();                     // удаление способности из очереди
        } else {
            throw AbilityUnavailableException(); // способности отсутствуют
        }
    } catch (GameException& exception) {
        cli.message(exception.what());           // обработка исключения и вывод сообщения об ошибке
    }
}
