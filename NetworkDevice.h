#ifndef NETWORKDEVICE_H
#define NETWORKDEVICE_H

#include <vector>
#include <string>
#include "CommunicationFrame.h"

class NetworkDevice
{
private:
    int deviceId;
    std::string deviceName;
    std::vector<CommunicationFrame*> receivedFrames;
public:
    NetworkDevice(int id, std::string name);
    void receiveFrame(CommunicationFrame* frame);
    std::string getName();
    void setName(std::string newName);
};

#endif // NETWORKDEVICE_H
