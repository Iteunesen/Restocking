#include "Highway.hpp"

// Highway::Highway(int aLength, int aCapacity, const Node& aStart, const Node& aDestination) 
// :length(aLength), capacity(aCapacity), start(aStart), destination(aDestination)
// {
// }

Highway::Highway(int aLength, int aCapacity, int aStart, int aDestination) 
:length(aLength), capacity(aCapacity), start(aStart), destination(aDestination)
{
}

Highway::~Highway()
{
}

int Highway::getLength() {
    return length;
}
        
int Highway::getCapacity() {
    return capacity;
}
        
int Highway::getStart() {
    return start;
}
        
int Highway::getDestination() {
    return destination;
}