#ifndef DISPLAY_H 
#define DISPLAY_H 

#include<iostream>

#include "board.h"

class Display {
public:
    void display(Board& player_board, Board& enemy_board); // метод отображения игрового поля
    std::pair<char, int> read_coordinate();                // метод чтения координат

    // шаблонный метод вывода сообщения в консоль
    template<class... Args> 
    void message(Args... text) {
        (std::cout << ... << text); 
    }

private:
    void print_separating_row(int size);                              // метод печати разделительной строки между строками поля
    void print_data_row(Board& board, int rw_counter, bool is_enemy); // метод мечати строки данных поля
    void print_letters_row(int size);                                 // метод печати буквы по верхней части доски
};


#endif 
