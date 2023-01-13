#include "NetworkDevice.h"

NetworkDevice::NetworkDevice(int id, std::string name)
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
