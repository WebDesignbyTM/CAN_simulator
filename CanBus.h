#ifndef CANBUS_H
#define CANBUS_H

#include <vector>
#include "CommunicationFrame.h"
#include "NetworkDevice.h"

class CanBus
{
private:
    std::vector<CommunicationFrame*> candidateFrames;
    // needed for clearing out all allocated frames
    // on application shutdown
    std::vector<CommunicationFrame*> framesHistory;
    std::vector<NetworkDevice*> subscribedDevices;
    int messageIndex;
public:
    void addCandidateMessage(CommunicationFrame* frame);
    void transmitFrame();
    void subscribeDevice(NetworkDevice* newDevice);
    void unsubscribeDevice(NetworkDevice* device);
    std::vector<CommunicationFrame*> getCandidateFrames();
};

#endif // CANBUS_H
