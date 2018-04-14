#include "call_table.hpp"
#include <iostream>
message_result::results cmd_testprogram(std::string)
{
    std:: cout << "I am module!" << std::endl;
    return message_result::results::OK;
}
message_result::results cmd_echomodule(std::string e)
{
    std:: cout << "[MODULE ECHO] " << e << std::endl;
    return message_result::results::OK;
}
extern "C"
{
    void test_module_call_main(CallTable* table);
};
void test_module_call_main(CallTable* table)
{
    std::cout << "Инициализация модуля" << std::endl;
    table->realloc(5);
    table->add(&cmd_testprogram);
    table->add(&cmd_echomodule);
    std::cout << "Инициализация модуля завершена" << std::endl;
}
