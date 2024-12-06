#include "../include/player.h" 

Player::Player(int field_size, int ships_count, const std::vector<int>& sizes)
    : AbstractPlayer(field_size, ships_count, sizes) {}

// метод размещения кораблей игрока на поле
bool Player::place_ships() {
    // получение доступа к менеджеру кораблей для игрока
    std::vector<Ship>& ships = ship_manager.get_ships();

    // проход по каждому кораблю для его размещения
    for (auto& ship : ships) {
        bool placed = false; // флаг успешного размещения корабля
        while (!placed) { 
            std::vector<std::pair<char, int>> coords;                                                        // массив координат размещаемого корабля
            cli.message("Enter orientation and coordinates for a ship of length ", ship.get_length(), ": "); // запрос ввода ориентации и координат

            std::string input;                          // ввода пользователя
            std::getline(std::cin >> std::ws, input);
            std::stringstream ss(input);                // строковый поток для обработки ввода
            char orientation;                           // ориентация корабля
            ss >> orientation; 

            // считывание координат для размещения корпуса корабля
            for (int i = 0; i < ship.get_length(); ++i) {
                std::pair<char, int> position; // пара для хранения координат (буква и число)
                std::string coord;             // переменная для считывания координаты
                ss >> coord; 

                // преобразование координаты в нужный формат
                position.first = toupper(coord[0]);           // перевод буквы в верхний регистр
                position.second = std::stoi(coord.substr(1)); // преобразование оставшейся части в число

                coords.push_back(position);                   // добавление координаты в массив
            }

            // размещение корабля на поле
            if (!board.place_ship(ship, coords, toupper(orientation))) {
                std::cout << "Cannot place here.\n"; // вывод сообщения, если размещение невозможно
            } else {
                placed = true; 
            }
        }
    }
    return true; // все корабли успешно размещены
}

// метод выстрела противника
bool Player::make_shot(AbstractPlayer& opponent) {
    std::pair<char, int> coordinate = cli.read_coordinate();  // считывание координат выстрела от игрока
    return opponent.get_board().shoot(coordinate);            // выполенение выстрела противника по указанным координатам и возвращение результата
}
