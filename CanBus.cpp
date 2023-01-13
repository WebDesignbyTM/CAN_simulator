#include "CanBus.h"
#include <iostream>
#include <algorithm>

void CanBus::addCandidateMessage(CommunicationFrame frame)
{
    candidateFrames.push_back(frame);
}

void CanBus::advanceTransmission()
{
    std::sort(candidateFrames.begin(), candidateFrames.end());

    for (auto frame : candidateFrames)
        std::cout << frame.getIdentifier() << ' ';
//    for (auto device : subscribedDevices)
//        device.receiveFrame(&candidateFrames[0]);
}
