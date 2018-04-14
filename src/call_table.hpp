#ifndef CALLTABLE_HPP
#define CALLTABLE_HPP
#include <string>
#include <vector>
#include <variant>
namespace message_result
{
enum class results : unsigned char{
        OK = 0,
        ERROR_FILENOTFOUND = 1,
        ERROR_CMDUNKNOWN = 2
};
};
class CallTable
{
private:
   CallTable( const CallTable& ) = delete;
   void operator=( const CallTable& ) = delete;
public:
    typedef message_result::results CmdResult;
    typedef CmdResult (*CallCell)(std::string);
    CallCell default_cell;
    CallCell* table;
    unsigned int size;
    unsigned int autoincrement;
    CallTable(unsigned int size,CallCell _default);
    unsigned int add(CallCell c);
    bool realloc(unsigned int newsize);
    ~CallTable();
};
#endif
