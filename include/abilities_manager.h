#ifndef ABILITIESMANAGER_H 
#define ABILITIESMANAGER_H

#include <queue>        
#include <random>      
#include <memory>      

#include "abilities.h" 
#include "double_damage.h" 
#include "scanner.h"   
#include "shelling.h"  
#include "abstract_player.h" 
#include "exception.h" 
#include "display.h"  

// класс управления способностями игрока
class AbilitiesManager {
public:
    AbilitiesManager(AbstractPlayer& enemy_ref);  // конструктор, принимающий ссылку на противника
    void add_ability();                           // метод добавления новой способности в список доступных способностей
    void use_ability();                           // метод использования доступной способности

private:
    std::queue<std::unique_ptr<Ability>> abilities; // очередь для хранения указателей на способности
    AbstractPlayer& enemy;                          // ссылка на пртивника, к которому применяются спобности
    Display cli;                              // объект для вывода ссобщений в интерфейс командной строки
};

#endif 

