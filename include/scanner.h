#ifndef SCANNER_H 
#define SCANNER_H

#include "abilities.h"      
#include "display.h" 

// класс способности сканирования
class ScannerAbility : public Ability {
public:
    ScannerAbility(Board& opponent_board); // конструктор, принимающий ссылку на поле противника
    void use() override;                   // переопределение метода для реализации сканирования

private:
    Display cli;  // объект для вывода сообщений в интерфейс командной строки
    Board& board; // ссылка на поле противника
};

#endif 
