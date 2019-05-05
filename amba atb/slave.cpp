#include "slave.h"
#include "master.h"
using namespace std;

Slave::Slave(bitset<7> ID, Master *m)
{
    ATID = ID;
    this->master = m;
}

bitset<7> Slave::getID()
{
    return ATID;
}

void Slave::receiveData()
{                      // This function receives all the data on the bus and clears it
    Data.push(ATDATA); // Add data to the Buffer
    ATDATA.reset();    // Clears the Bus
    ATBYTES = 0;       // Clears the Bus
}

void Slave::flushData()
{
    master->flushData(ATID); // Ask for all the data to be sent
}

queue<bitset<32>> Slave::getData(bool clear)
{ // Get the data on the buffer and clear if true
    queue<bitset<32>> ret = Data;
    if (clear)
    {
        while (!Data.empty())
            Data.pop();
        return ret;
    }
}
