#include "../include/display.h"

// метод отображения игрового поля игрока и противника
void Display::display(Board& player_board, Board& enemy_board) {
    int size = player_board.get_field_size(); // размер поля
    int rw_counter = 1;                       // счетчик для нумерации строк
    for (int i = 0; i < 2 * size + 1; ++i) {
        if (i % 2 == 0) {
            // четный номер строки, вывод разделительной строки
            print_separating_row(size);
            std::cout << "      ";      // пробелы для выравнивания
            print_separating_row(size); // разделительная строка для вражеского поля
            std::cout << "\n";
        } else {
            // нечетный номер, вывод данных о строках
            print_data_row(player_board, rw_counter, false); // игровое поле игрока
            std::cout << "      ";                           // пробелы для выравнивания
            print_data_row(enemy_board, rw_counter, true);   // игровое поле противника
            std::cout << "\n"; 
            rw_counter++; // увеличение счетчика строк
        }
    }

    print_letters_row(size); // вывод букв для обозначения столбцов
    std::cout << "      ";   // пробелы для выравнивания
    print_letters_row(size); // вывод букв для вражеского поля
    std::cout << "\n\n";   
}

// метод считывания координат, вводимых пользователем
std::pair<char, int> Display::read_coordinate() {
    char letter;                         // переменная для буквы
    int digit;                           // переменная для цифры
    std::cin >> letter >> digit; 
    letter = toupper(letter);            // перевод буквы к верхнему регистру

    std::pair coordinate(letter, digit); // создание пары координат
    return coordinate;
}

// метод печати разделительной строки
void Display::print_separating_row(int size) {
    std::cout << "    ";              // пробелы для выравнивания
    for (int j = 0; j < size; ++j) {
        std::cout << "+ — ";          // разделительные линии
    }
    std::cout << "+";                 // завершение строки
}

// метод печати строки данных из игровой доски
void Display::print_data_row(Board& board, int rw_counter, bool is_enemy) {
    std::cout << std::setw(2) << rw_counter << ". "; // вывод номера строки

    for (int j = 0; j < board.get_field_size(); ++j) {
        std::cout << "| "; // отображение границ клеток
        char cell_display; // переменная для символа, отображаемого в клетке
        
        // получение символа для отображения в зависимости от того, являемся ли мы противником
        if (is_enemy) {
            cell_display = board.get_cell(rw_counter - 1, j).public_display; // данные для противника
        } else {
            cell_display = board.get_cell(rw_counter - 1, j).actual_display; // данные игрока
        }
        
        // выбор отображения в зависимости от содержимого клетки
        switch (cell_display) {
            case '~': // пусто
                std::cout << "  "; 
                break;
            default:
                std::cout << cell_display << " "; // состояние клетки
        }

    }
    std::cout << "|"; // завершение строки
}

// метод печати строки букв по горизонтали для обозначения столбцов
void Display::print_letters_row(int size) {
    // массив заглавных букв
    char letters[] {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                    'V', 'W', 'X', 'Y', 'Z'};
    std::cout << "    ";                        // пробелы для выравнивания
    for (int j = 0; j < size; ++j) {
        std::cout << "  " << letters[j] << " "; // вывод букв столбцов
    }
    std::cout << " "; // завершение строки
}
