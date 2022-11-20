#ifndef HIGHWAY_HPP_
#define HIGHWAY_HPP_

#include <iostream>
#include "Node.hpp"

class Highway {
    public:
        //Highway(int aLength, int aCapacity, const Node& aStart, const Node& aDestination);
        Highway(int aLength, int aCapacity, int aStart, int aDestination);
        virtual ~Highway();

        int getLength();
        int getCapacity();
        int getStart();
        int getDestination();

    private:
        int length;
        int capacity;
        int start;
        int destination;
        //Node start;
        //Node destination;
};

#endif 