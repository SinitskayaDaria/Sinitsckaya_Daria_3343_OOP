#include "../include/game_process.h" 
#include "../include/game_setup.h"  
#include "../include/game_state.h" 
#include "../include/enemy.h"   

#include <sstream>                  
   

int main() {

    GameSetup setup;                                                                          // объект для конфигурации игры
    setup.read_start_data();                                                                         // чтение данных о конфигурации игры
    GameSession session(setup.get_field_size(), setup.get_ships_count(), setup.get_sizes()); // инициализация игрового процесса
    session.start();                                                                   // запуск игрового процесса
    
    // Запрос пользователя, хотите ли вы сохранить игру
    char save_choice;
    std::cout << "Do you want to save the game state? (y/n): ";
    std::cin >> save_choice;

    if (save_choice == 'y' || save_choice == 'Y') {
        GameState game_state(session);  // создаем объект для сохранения состояния
        const char* filename = "game_state.txt";  // указываем имя файла

        // Попытка сохранить состояние игры в файл
        if (game_state.save(filename)) {
            std::cout << "Game state has been successfully saved to " << filename << ".\n";
        } else {
            std::cout << "Failed to save the game state.\n";
        }
    }

    //session.start();             

    return 0;
}
