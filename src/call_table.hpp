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
    typedef CmdResult (*CallCell)(unsigned int, std::string);
    CallCell default_cell;
    CallCell* table;
    unsigned int size;
    unsigned int autoincrement;
    CallTable(unsigned int size,CallCell _default);
    unsigned int add(CallCell c);
    inline CmdResult call(unsigned int index,unsigned int arg1, std::string arg2)
    {
        return table[index](arg1,arg2);
    }
    bool realloc(unsigned int newsize);
    ~CallTable();
};
#endif
