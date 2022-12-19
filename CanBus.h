#ifndef CANBUS_H
#define CANBUS_H

#include <vector>
#include "CommunicationFrame.h"
#include "NetworkDevice.h"

class CanBus
{
private:
    std::vector<CommunicationFrame> candidateFrames;
    std::vector<CommunicationFrame> currentFrames;
    std::vector<NetworkDevice> subscribedDevices;
    int messageIndex;
public:
    void addCandidateMessage();
    void advanceTransmission();
    void subscribeDevice(NetworkDevice device);
};

#endif // CANBUS_H
