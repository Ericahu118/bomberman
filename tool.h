#ifndef TOOL_H
#define TOOL_H
#include <component.h>
#include <gameobject.h>
class Tools : public Component{
    public:
        Tools(int type);
        int getType();
    private:
        int type;


};

#endif // TOOL_H
