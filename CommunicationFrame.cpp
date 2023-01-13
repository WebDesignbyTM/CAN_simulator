#include "CommunicationFrame.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

enum FrameComponent {
    FrameStart,
    FrameIdentifier,
    FrameRTR,
    FrameIDE,
    FrameReserved,
    FrameDataLength,
    FrameData,
    FrameCRC,
    FrameCRCDelimiter,
    FrameACK,
    FrameACKDelimiter,
    FrameEOF,
    FrameIFS,
    FrameEnded
};

CommunicationFrame::CommunicationFrame(unsigned deviceId, unsigned dataLength, unsigned long long data)
{
    this->transmittedData = data;
    this->identifier = dataMask(IDENTIFIER_LENGTH) & deviceId;
    this->rtr = 0;
    this->dataLength = dataMask(DL_LENGTH) & dataLength;
    this->crc = 0;
    this->acknowledge = 1;

    encodeMessage();
}

CommunicationFrame::CommunicationFrame(std::bitset<FRAME_MAXIMUM_LENGTH> receivedMessage)
{
    this->encodedMessage = receivedMessage;
//    std::cout << receivedMessage << '\n' << encodedMessage << '\n';
    receivedMessage[0] = 1;
//    std::cout << receivedMessage << '\n' << encodedMessage << '\n';
    this->transmittedData = 0;
    this->identifier = 0;
    this->rtr = 0;
    this->dataLength = 0;
    this->crc = 0;
    this->acknowledge = 1;

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

static int calculateCRC(std::bitset<CHECKSUM_INPUT_LENGTH> input, int length)
{
    std::bitset<CHECKSUM_INPUT_LENGTH + CRC_POLYNOMIAL_LENGTH> quotient;
    static std::bitset<CRC_POLYNOMIAL_LENGTH + CHECKSUM_INPUT_LENGTH> denominator(CRC_POLYNOMIAL_STRING);
    int result = 0;
    bool aux;

    for (int i = 0; i < length; ++i)
        quotient[i] = input[i];
    for (int i = length; i < length + CRC_POLYNOMIAL_LENGTH - 1; ++i)
        quotient[i] = 0;

//    std::cout << "The working copy is " << quotient << '\n';

    while (length)
    {
        while (length && !quotient[0])
        {
            quotient >>= 1;
            --length;
        }

        if (!length)
            break;

        quotient ^= denominator;
    }

//    std::cout << "The remainder is " << quotient << '\n';

    for (int i = 0; i < (CRC_POLYNOMIAL_LENGTH - 1) / 2; ++i)
    {
        aux = quotient[i];
        quotient[i] = quotient[CRC_POLYNOMIAL_LENGTH-2-i];
        quotient[CRC_POLYNOMIAL_LENGTH-2-i] = aux;
    }

//    std::cout << "The remainder is " << quotient << '\n';

    return quotient.to_ulong();
}

void CommunicationFrame::encodeMessage()
{
    bool checkStuffing = true;
    int consecutiveIdenticalBits = 0;
    int idx = 0;
    int currentComponentBits = 0;
    int crcIdx = 0;
    std::bitset<CHECKSUM_INPUT_LENGTH> crcInput;
    FrameComponent state = FrameStart;

    while (state != FrameEnded)
    {
        if (idx > 1 && encodedMessage[idx-1] == encodedMessage[idx-2])
            ++consecutiveIdenticalBits;
        else
            consecutiveIdenticalBits = 1;

        if (checkStuffing && consecutiveIdenticalBits == 5)
        {
//            std::cout << "inserted stuffing at " << idx << '\n';
            consecutiveIdenticalBits = 1;
            encodedMessage[idx] = !encodedMessage[idx-1];
            ++idx;
            continue;
        }

        ++currentComponentBits;
        switch(state) {
        case FrameStart:
            encodedMessage[idx] = 0;
            currentComponentBits = 0;
            state = FrameIdentifier;
            break;

        case FrameIdentifier:
            encodedMessage[idx] = identifier & (1 << (IDENTIFIER_LENGTH - currentComponentBits));
            if (currentComponentBits == IDENTIFIER_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameRTR;
            }
            break;

        case FrameRTR:
            encodedMessage[idx] = 0;
            currentComponentBits = 0;
            state = FrameIDE;
            break;

        case FrameIDE:
            encodedMessage[idx] = 0;
            currentComponentBits = 0;
            state = FrameReserved;
            break;

        case FrameReserved:
            encodedMessage[idx] = 0;
            currentComponentBits = 0;
            state = FrameDataLength;
            break;

        case FrameDataLength:
            encodedMessage[idx] = dataLength & (1 << (DL_LENGTH - currentComponentBits));
            if (currentComponentBits == DL_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameData;
            }
            break;

        case FrameData:
            encodedMessage[idx] = transmittedData & (1 << (dataLength * 8 - currentComponentBits));
            if (currentComponentBits == dataLength * 8)
            {
                currentComponentBits = 0;
                state = FrameCRC;
            }
            break;

        case FrameCRC:
            if (currentComponentBits == 1)
                crc = calculateCRC(crcInput, crcIdx) & dataMask(CRC_LENGTH);
            encodedMessage[idx] = crc & (1 << (CRC_LENGTH - currentComponentBits));
            if (currentComponentBits == CRC_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameCRCDelimiter;
            }
            break;

        case FrameCRCDelimiter:
            encodedMessage[idx] = 1;
            checkStuffing = false;
            currentComponentBits = 0;
            state = FrameACK;
            break;

        case FrameACK:
            encodedMessage[idx] = 1;
            currentComponentBits = 0;
            state = FrameACKDelimiter;
            ackIdx = idx;
            break;

        case FrameACKDelimiter:
            encodedMessage[idx] = 1;
            currentComponentBits = 0;
            state = FrameEOF;
            break;

        case FrameEOF:
            encodedMessage[idx] = 1;
            if (currentComponentBits == EOF_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameIFS;
            }
            break;

        case FrameIFS:
            encodedMessage[idx] = 1;
            if (currentComponentBits == IFS_LENGTH)
                state = FrameEnded;
            break;

        default:
            state = FrameEnded;
            break;
        }

        if (state <= FrameCRC)
            crcInput[crcIdx++] = encodedMessage[idx];

        ++idx;
    }
}

void CommunicationFrame::decodeMessage()
{
    bool checkStuffing = true;
    int consecutiveIdenticalBits = 0;
    int idx = 0;
    int currentComponentBits = 0;
    int crcIdx = 0;
    std::bitset<CHECKSUM_INPUT_LENGTH> crcInput;
    FrameComponent state = FrameStart;

    while (state != FrameEnded)
    {
        if (checkStuffing && consecutiveIdenticalBits == 5)
        {
//            std::cout << "detected stuffing at " << idx << '\n';
            consecutiveIdenticalBits = 1;
            ++idx;
            continue;
        }

        if (idx && encodedMessage[idx] == encodedMessage[idx-1])
            ++consecutiveIdenticalBits;
        else
            consecutiveIdenticalBits = 1;
        ++currentComponentBits;

        if (state < FrameCRC)
            crcInput[crcIdx++] = encodedMessage[idx];

        switch (state) {
        case FrameStart:
            consecutiveIdenticalBits = 1;
            if (encodedMessage[idx])
                throw std::runtime_error("The frame start bit should be dominant!");
            currentComponentBits = 0;
            state = FrameIdentifier;
//            std::cout << "finished start at "<< idx << '\n';
            break;

        case FrameIdentifier:
            identifier <<= 1;
            identifier += encodedMessage[idx];
            if (currentComponentBits == IDENTIFIER_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameRTR;
//                std::cout << "finished id at " << idx << '\n';
            }
            break;

        case FrameRTR:
            rtr = encodedMessage[idx];
            currentComponentBits = 0;
            state = FrameIDE;
//            std::cout << "finished rtr at " << idx << '\n';
            break;

        case FrameIDE:
            if (encodedMessage[idx])
                throw std::runtime_error("Only supporting base frame format!");
            currentComponentBits = 0;
            state = FrameReserved;
//            std::cout << "finished ide at " << idx << '\n';
            break;

        case FrameReserved:
            currentComponentBits = 0;
            state = FrameDataLength;
//            std::cout << "finished reserved at " << idx << '\n';
            break;

        case FrameDataLength:
            dataLength <<= 1;
            dataLength += encodedMessage[idx];
            if (currentComponentBits == DL_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameData;
//                std::cout << "finished data length at " << idx << '\n';
            }
            break;

        case FrameData:
            transmittedData <<= 1;
            transmittedData += encodedMessage[idx];
            if (currentComponentBits == dataLength * 8)
            {
                currentComponentBits = 0;
                state = FrameCRC;
//                std::cout << "finished data at " << idx << '\n';
            }
            break;

        case FrameCRC:
            crc <<= 1;
            crc += encodedMessage[idx];
            if (currentComponentBits == CRC_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameCRCDelimiter;
                if (crc != calculateCRC(crcInput, crcIdx))
                    throw std::runtime_error("The CRC failed!");
//                std::cout << "finished crc at " << idx << '\n';
            }
            break;

        case FrameCRCDelimiter:
            checkStuffing = false;
            if (!encodedMessage[idx])
            {
//                std::cout << "was called for " << idx << '\n';
                throw std::runtime_error("The CRC delimiter bit must be recessive!");
            }
            currentComponentBits = 0;
            state = FrameACK;
            break;

        case FrameACK:
            acknowledge = encodedMessage[idx];
            currentComponentBits = 0;
            state = FrameACKDelimiter;
            ackIdx = idx;
            break;

        case FrameACKDelimiter:
            if (!encodedMessage[idx])
                throw std::runtime_error("The ACK delimiter bit must be recessive!");
            currentComponentBits = 0;
            state = FrameEOF;
            break;

        case FrameEOF:
            if (!encodedMessage[idx])
                throw std::runtime_error("The EOF bits must be recessive!");
            if (currentComponentBits == EOF_LENGTH)
            {
                currentComponentBits = 0;
                state = FrameIFS;
            }
            break;

        case FrameIFS:
            if (!encodedMessage[idx])
                throw std::runtime_error("The IFS bits must be recessive!");
            if (currentComponentBits == IFS_LENGTH)
                state = FrameEnded;
            break;

        default:
            state = FrameEnded;
            break;
        }

        ++idx;
    }


//    std::cout << encodedMessage << '\n';
}

bool operator <(CommunicationFrame const& a, CommunicationFrame const& b)
{
    std::string aStr = a.encodedMessage.to_string();
    std::string bStr = b.encodedMessage.to_string();
    std::reverse(aStr.begin(), aStr.end());
    std::reverse(bStr.begin(), bStr.end());
    return aStr < bStr;
}

int CommunicationFrame::getIdentifier()
{
    return identifier;
}

unsigned CommunicationFrame::getDataLength()
{
    return dataLength;
}

unsigned long long CommunicationFrame::getTransmittedData()
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
    acknowledge = encodedMessage[ackIdx];
}
