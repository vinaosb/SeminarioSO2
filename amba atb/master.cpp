#include "master.h"
#include "slave.h"
using namespace std;

void Master::AddSlave(Slave *toAdd)
{                                              // Add a slave to this master
    if (listSlaves[toAdd->getID()] == nullptr) // Check if the slave belongs to this master
        listSlaves[toAdd->getID()] = toAdd;
}
void Master::AddSlave(bitset<7> toAdd)
{                                     // Create a new slave to this master
    if (listSlaves[toAdd] == nullptr) // Check if the slave belongs to this master
        listSlaves[toAdd] = new Slave(toAdd, this);
}

void Master::AddData(list<bitset<32>> DataAdd, bitset<7> ID)
{ // Add data to the buffer to be sent
    for (list<bitset<32>>::iterator it = DataAdd.begin(); it != DataAdd.end(); ++it)
        Data.push_back(pair(ID, *it));
}
void Master::AddData(bitset<32> DataAdd, bitset<7> ID)
{ // Add data to the buffer to be sent
    Data.push_back(pair(ID, DataAdd));
}

list<Slave> Master::getListOfSlaves()
{
    list<Slave> ret;
    for (map<bitset<7>, Slave *>::iterator it = listSlaves.begin(); it != listSlaves.end(); ++it)
        ret.push_back(*it->second);
    return ret;
}

void Master::transferData()
{ // Send the 1st position data on the buffer
    bitset<7> ID = Data.front().first;
    while (Data.front().first == ID)
    { // Continues to send the data if the id doesnt change
        listSlaves.at(ID)->receiveData();
        Data.pop_front();
    }
}

void Master::flushData(bitset<7> ID)
{                                  // Send all the data for the slave that is requesting
    if (listSlaves[ID] != nullptr) // Check if the slave belongs to this master
        for (list<pair<bitset<7>, bitset<32>>>::iterator it = Data.begin(); it != Data.end(); ++it)
            if (it->first == ID)
            { // If the data belongs to this address send
                ATDATA = Data.front().second;
                ATBYTES = 3;
                listSlaves.at(ID)->receiveData();
            }
}