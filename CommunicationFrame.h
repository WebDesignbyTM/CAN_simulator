#ifndef COMMUNICATIONFRAME_H
#define COMMUNICATIONFRAME_H

#define FRAME_MAXIMUM_LENGTH    134
#define IDENTIFIER_LENGTH       11
#define RTR_LENGTH              1
#define DL_LENGTH               4
#define CRC_LENGTH              15
#define ACK_LENGTH              1
#define dataMask(x) (1<<x) - 1
#include <bitset>

class CommunicationFrame
{
private:
    std::bitset<FRAME_MAXIMUM_LENGTH> encodedMessage;
    long long transmittedData;

    int identifier      :   IDENTIFIER_LENGTH;
    int rtr             :   RTR_LENGTH;
    int dataLength      :   DL_LENGTH;
    int crc             :   CRC_LENGTH;
    int acknowledge     :   ACK_LENGTH;

    int ackIdx;

    bool isStuffingBit(int index);
    void encodeMessage();
    void decodeMessage();

public:
    CommunicationFrame(int deviceId, int dataLength, long long data);
    CommunicationFrame(std::bitset<FRAME_MAXIMUM_LENGTH> receivedData);
    int getIdentifier();
    int getTransmittedData();
    void setAck(bool received);
    std::bitset<FRAME_MAXIMUM_LENGTH> getEncodedMessage();
};

#endif // COMMUNICATIONFRAME_H
