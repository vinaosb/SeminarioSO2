#ifndef _SLAVE_ATB_
#define _SLAVE_ATB_
#include "atb.h"
using namespace std;

class Master;

class Slave
{
private:
    Master *master;         // Address of the Master
    bitset<7> ATID;         // ID of the slave
    queue<bitset<32>> Data; // Buffer using FIFO for data alignment

public:
    Slave(bitset<7> ID, Master *m);

    bitset<7> getID();

    void receiveData(); // This function receives all the data on the bus and clears it

    void flushData(); // Ask for all the data to be sent

    queue<bitset<32>> getData(bool clear); // Get the data on the buffer and clear if true

    void reset()
    {
        int size = Data.size(), i;
        for (i = 0; i < size; i++)
            Data.pop();
    }
};

#endif