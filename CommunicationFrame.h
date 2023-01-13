#ifndef COMMUNICATIONFRAME_H
#define COMMUNICATIONFRAME_H

#define FRAME_MAXIMUM_LENGTH    134
#define CHECKSUM_INPUT_LENGTH   84
#define CRC_POLYNOMIAL_LENGTH   16
#define IDENTIFIER_LENGTH       11
#define RTR_LENGTH              1
#define DL_LENGTH               4
#define CRC_LENGTH              15
#define ACK_LENGTH              1
#define EOF_LENGTH              7
#define IFS_LENGTH              3
#define dataMask(x) (1<<x) - 1
// the CRC_POLYNOMIAL_STRING is reversed,
// so as to be usable as input for the
// bitset constructor
#define CRC_POLYNOMIAL_STRING   "1001100110100011"
#include <bitset>

class CommunicationFrame
{
private:
    std::bitset<FRAME_MAXIMUM_LENGTH> encodedMessage;
    unsigned long long transmittedData;

    unsigned identifier     :   IDENTIFIER_LENGTH;
    unsigned rtr            :   RTR_LENGTH;
    unsigned dataLength     :   DL_LENGTH;
    unsigned crc            :   CRC_LENGTH;
    unsigned acknowledge    :   ACK_LENGTH;

    int ackIdx;

    bool isStuffingBit(int index);
    void encodeMessage();
    void decodeMessage();

public:
    friend bool operator <(CommunicationFrame const& a, CommunicationFrame const& b);
    CommunicationFrame(unsigned deviceId, unsigned dataLength, unsigned long long data);
    CommunicationFrame(std::bitset<FRAME_MAXIMUM_LENGTH> receivedMessage);
    int getIdentifier();
    unsigned getDataLength();
    unsigned long long getTransmittedData();
    void setAck(bool received);
    std::bitset<FRAME_MAXIMUM_LENGTH> getEncodedMessage();
};

#endif // COMMUNICATIONFRAME_H
