#ifndef NETWORKDEVICE_H
#define NETWORKDEVICE_H

#include <vector>
#include <string>
#include "CommunicationFrame.h"

class NetworkDevice
{
private:
    unsigned deviceId;
    std::string deviceName;
    std::vector<CommunicationFrame*> receivedFrames;
public:
    NetworkDevice(unsigned id, std::string name);
    void receiveFrame(CommunicationFrame* frame);
    std::string getName();
    void setName(std::string newName);
    unsigned getId();
    std::vector<CommunicationFrame*> getReceivedFrames();
};

#endif // NETWORKDEVICE_H
