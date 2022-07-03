#include "tool.h"

Tools::Tools(int type):Component(){
    this->type = type;
}

int Tools:: getType(){
    return this->type;
}
