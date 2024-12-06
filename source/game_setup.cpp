#include "../include/game_setup.h" // Подключаем заголовочный файл GameSetup

// метод считывания начальных данных игры
void GameSetup::read_start_data() {
    std::cout << "Enter field size: ";  // запрос на ввод размера игрового поля
    bool field_size_is_correct = false; // флаг корректности введенного размера поля
    
    // пока пользователь не введет корректный размер поля
    while(!field_size_is_correct) {
        std::cin >> field_size; 
        // проверка нахождения размера в допустимом диапазоне от 1 до 26
        if (field_size > 26 || field_size < 1) {
            std::cout << "Field sizes should be in the range [1, 26]!\nTry again: "; 
        } else {
            field_size_is_correct = true; // размер корректен
        }
    }

    std::cout << "Enter ships count: "; // запрос на ввод количества кораблей
    std::cin >> ships_count; 

    std::cout << "Enter the size of each ship separated by a space: "; // запрос на ввод размеров кораблей
    // считывание размеров кораблей
    for (int i = 0; i < ships_count; ++i) {
        int size; // размер корабля
        std::cin >> size; // 
        sizes.push_back(size); // добавление размера в массив размеров кораблей
    }
}

// Метод для получения количества кораблей
int GameSetup::get_ships_count() {
    return ships_count; // Возвращаем количество кораблей
}

// Метод для получения размеров кораблей
const std::vector<int>& GameSetup::get_sizes() {
    return sizes; // Возвращаем вектор размеров кораблей
}

// Метод для получения размера поля
int GameSetup::get_field_size() {
    return field_size; // Возвращаем размер поля
}

// метод преобразования данных состояния игровой сессии в поток вывода
void GameSetup::serialize(std::ostream& os) {
    os << field_size << " " << ships_count << " "; // размер поля и количество кораблей
    for (auto& size : sizes) {                     // проход по всем размерам кораблей
        os << size << " ";                         // каждый размер корабля
    }
    os << "\n";                                    // завершение записи новой строкой
}

 // метод преобразования данных состояния игровой сессии из потока ввода
void GameSetup::deserialize(std::istream& is){
    is >> field_size >> ships_count;                // считывание размера поля и количества кораблей из потока
    sizes.resize(ships_count);                      // изменение размера массива sizes, чтобы он соответствовал количеству кораблей
    for (int i = 0; i < ships_count; ++i) {         // проход по количеству кораблей
        is >> sizes[i];                             // считывание размера каждого корабля из потока
    }
}
