#ifndef BFSNAMESPACE_H
#define BFSNAMESPACE_H

#include <algorithm>

namespace generalContainer
{
    struct node
    {
        int end; // id of ending team
        int weight; //weight from vertex to ending team
        node():end(0),weight(0){};
    };
}

#endif // BFSNAMESPACE_H
