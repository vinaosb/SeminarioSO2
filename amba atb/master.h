#ifndef _MASTER_ATB_
#define _MASTER_ATB_
#include "atb.h"

using namespace std;

class Slave;

class Master
{
public:
    void AddSlave(Slave *toAdd);
    void AddSlave(bitset<7> toAdd);

    void AddData(list<bitset<32>> DataAdd, bitset<7> ID);
    void AddData(bitset<32> DataAdd, bitset<7> ID);

    list<Slave> getListOfSlaves();

    void transferData();

    void flushData(bitset<7> ID);

    void reset()
    {
        for (list<pair<bitset<7>, bitset<32>>>::iterator it = Data.begin(); it != Data.end(); ++it)
            it->second.reset();
        Data.clear();
    }

private:
    map<bitset<7>, Slave *> listSlaves;
    list<pair<bitset<7>, bitset<32>>> Data;
};

#endif