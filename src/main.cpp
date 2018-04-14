#include "call_table.hpp" 
#include <iostream>
#include <dlfcn.h>
CallTable* table;
bool isContinue = true;
message_result::results cmd_unknown(std::string)
{
    return message_result::results::ERROR_CMDUNKNOWN;
}
message_result::results cmd_stop(std::string)
{
    isContinue = false;
    std:: cout << "[COMMAND STOP] Stopping" << std::endl;
    return message_result::results::OK;
}
message_result::results cmd_echo(std::string e)
{
    std:: cout << "[COMMAND ECHO] " << e << std::endl;
    return message_result::results::OK;
}
message_result::results cmd_loadmodule(std::string file)
{
    void* fd = dlopen(file.c_str(), RTLD_LAZY);
    if(fd == NULL) {
        return message_result::results::ERROR_FILENOTFOUND;
    }
    void (*test_module_main)(CallTable*);
    test_module_main = (void (*)(CallTable*))dlsym(fd,"test_module_call_main");
    test_module_main(table);
    return message_result::results::OK;
};
int main()
{
    std::cout << "Инициализация CallTable  ";
    table = new CallTable(4,&cmd_unknown);
    std::cout << "OK" << std::endl;
    
    
    std::cout << "Запись комманд  ";
    table->add(&cmd_echo);
    table->add(&cmd_loadmodule);
    table->add(&cmd_stop);
    std::cout << "OK" << std::endl;
    while(isContinue)
    {
        unsigned int cmdnumber = 0;
        std::string param;
        std::cin >> cmdnumber >> param;
        if(cmdnumber >= table->size) {
                std::cerr << "Комманда не существует" << std::endl;
                continue;
        }
        message_result::results r = table->table[cmdnumber](param);
        using message_result::results;
        if(r == results::OK) {}
        else if(r == results::ERROR_FILENOTFOUND)
        {
            std::cout << "Файл не найден" << std::endl;
        }
        else if(r == results::ERROR_CMDUNKNOWN)
        {
            std::cout << "Вызвана default комманда" << std::endl;
        }
    }
}
