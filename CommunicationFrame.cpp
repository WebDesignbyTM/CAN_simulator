#include "CommunicationFrame.h"

CommunicationFrame::CommunicationFrame(int deviceId, int dataLength, long long data)
{
    this->identifier = dataMask(IDENTIFIER_LENGTH) & deviceId;
    this->dataLength = dataMask(DL_LENGTH) & dataLength;
    this->transmittedData = data;

    encodeMessage();
}

CommunicationFrame::CommunicationFrame(std::bitset<FRAME_MAXIMUM_LENGTH> receivedData)
{
    decodeMessage();
}

bool CommunicationFrame::isStuffingBit(int index)
{
    if (index < 5)
        return false;

    bool stuffing = true;
    for (int i = index - 1; stuffing && i >= index - 5; --i)
        stuffing = (encodedMessage[i] != encodedMessage[index]);

    return stuffing;
}
void CommunicationFrame::encodeMessage()
{

}

void CommunicationFrame::decodeMessage()
{

}

int CommunicationFrame::getIdentifier()
{
    return identifier;
}

int CommunicationFrame::getTransmittedData()
{
    return transmittedData;
}

std::bitset<FRAME_MAXIMUM_LENGTH> CommunicationFrame::getEncodedMessage()
{
    return encodedMessage;
}

void CommunicationFrame::setAck(bool received)
{
    int ackBit = received ? 0 : 1;
    encodedMessage[ackIdx] = encodedMessage[ackIdx] & ackBit;
}
