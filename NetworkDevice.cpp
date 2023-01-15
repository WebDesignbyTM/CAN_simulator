#include "NetworkDevice.h"
#include <iostream>

NetworkDevice::NetworkDevice(unsigned id, std::string name)
{
    this->deviceId = id;
    this->deviceName = name;
}

void NetworkDevice::receiveFrame(CommunicationFrame* frame)
{
    this->receivedFrames.push_back(frame);
}

std::string NetworkDevice::getName()
{
    return deviceName;
}

void NetworkDevice::setName(std::string newName)
{
    this->deviceName = newName;
}

unsigned NetworkDevice::getId()
{
    return deviceId;
}

std::vector<CommunicationFrame*> NetworkDevice::getReceivedFrames()
{
    return receivedFrames;
}
