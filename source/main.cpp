#include "../include/game_process.h" 
#include "../include/game_setup.h"  
#include "../include/game_state.h" 
#include "../include/enemy.h"   

#include <sstream>      
#include <iostream>
#include <utility>            
   

int main() {

    GameSetup setup;                                                                          // объект для конфигурации игры
    setup.read_start_data();                                                                  // чтение данных о конфигурации игры
    std::unique_ptr<GameSession> session = std::make_unique<GameSession>(setup);              // инициализация игрового процесса
    session->place_ships();                                                                   // размещение кораблей
    
    // Управление игровой сессией
    while (true) {
        std::cout << "\n=== Game Menu ===\n";
        std::cout << "1. Make a move\n";
        std::cout << "2. Save game\n";
        std::cout << "3. Load game\n";
        std::cout << "4. Use ability\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                auto step_result = session->run_game_step();
                if (step_result == GameSession::step_result::GameOver) {
                    std::cout << "Game over. Starting a new game...\n";

                    // Уничтожаем старую сессию и создаем новую
                    session = std::make_unique<GameSession>(setup);
                    session->place_ships();
                }
                break;
            }
            case 2: {
                GameState state(*session);
                if (state.save("game_save.txt")) {
                    std::cout << "Game saved successfully.\n";
                } else {
                    std::cout << "Failed to save the game.\n";
                }
                break;
            }
            case 3: {
                GameState state(*session);
                if (state.load("game_save.txt")) {
                    std::cout << "Game loaded successfully.\n";
                } else {
                    std::cout << "Failed to load the game.\n";
                }
                // отображение обновленных игровых полей
                break;
            }
            case 4:
                session->use_ability();
                // отображение обновленных игровых полей
                break;
            case 5:
                std::cout << "Exiting the game. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }


    return 0;
}
