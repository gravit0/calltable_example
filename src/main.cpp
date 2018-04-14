#include "call_table.hpp" 
#include <iostream>
CallTable* table;
bool isContinue = true;
message_result::results cmd_unknown(unsigned int, std::string)
{
    return message_result::results::ERROR_CMDUNKNOWN;
}
message_result::results cmd_stop(unsigned int, std::string)
{
    isContinue = false;
    std:: cout << "[COMMAND STOP] Stopping" << std::endl;
    return message_result::results::OK;
}
message_result::results cmd_echo(unsigned int, std::string)
{
    std:: cout << "[COMMAND ECHO] Hello World!" << std::endl;
    return message_result::results::OK;
}
int main()
{
    std::cout << "Инициализация CallTable  ";
    table = new CallTable(4,&cmd_unknown);
    std::cout << "OK" << std::endl;
    
    
    std::cout << "Запись комманд  ";
    table->add(&cmd_echo);
    table->add(&cmd_echo);
    table->add(&cmd_stop);
    std::cout << "OK" << std::endl;
    while(isContinue)
    {
        unsigned int cmdnumber = 0;
        std::cin >> cmdnumber;
        if(cmdnumber >= table->size) {
                std::cerr << "Комманда не существует" << std::endl;
                continue;
        }
        message_result::results r = table->table[cmdnumber](0,"");
        using message_result::results;
        if(r == results::OK) continue;
        else if(r == results::ERROR_FILENOTFOUND)
        {
            std::cout << "Файл не найден" << std::endl;
        }
        else if(r == results::ERROR_CMDUNKNOWN)
        {
            std::cout << "Вызвана default комманда" << std::endl;
        }
        continue;
    }
}
