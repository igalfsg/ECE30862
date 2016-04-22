#ifndef _EXCEPTIONS_H
#define	_EXCEPTIONS_H
#include <string>

using std::string;

#include <stdexcept>
using std::invalid_argument;
using std::runtime_error;

class MissingItem : public invalid_argument
{
 public:
 MissingItem() : invalid_argument("That item is not here.")
    {
    }
};

#endif
