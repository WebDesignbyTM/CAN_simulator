#include "CanBus.h"
#include <iostream>
#include <algorithm>

void CanBus::addCandidateMessage(CommunicationFrame* frame)
{
    candidateFrames.push_back(frame);
    std::sort(
        candidateFrames.begin(),
        candidateFrames.end(),
        [](CommunicationFrame* a, CommunicationFrame* b) {
            return *a < *b;
        }
    );
}

void CanBus::transmitFrame()
{
    if (!candidateFrames.size())
        return;

    for (auto device : subscribedDevices)
        device->receiveFrame(candidateFrames[0]);
    framesHistory.push_back(candidateFrames[0]);
    candidateFrames.clear();
}

void CanBus::subscribeDevice(NetworkDevice* newDevice)
{
    subscribedDevices.push_back(newDevice);
}

void CanBus::unsubscribeDevice(NetworkDevice* device)
{
    for (auto it = subscribedDevices.begin(); it != subscribedDevices.end(); ++it)
    {
        if (*it == device)
        {
            subscribedDevices.erase(it);
            break;
        }
    }
}

std::vector<CommunicationFrame*> CanBus::getCandidateFrames()
{
    return candidateFrames;
}
