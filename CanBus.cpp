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

//    for (auto frame : candidateFrames)
//        std::cout << frame.getIdentifier() << ' ';
    // schimba interfatarea mesajelor intre dispozitive:
    // transmite doar mesajul codificat, ca apoi fiecare dispozitiv sa primeasca
    // bitii si sa alcatuiasca frame-ul individual
    for (auto device : subscribedDevices)
        device.receiveFrame(&candidateFrames[0]);
}
