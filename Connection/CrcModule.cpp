//
// Created by pawel on 02.06.2020.
//

#include "CrcModule.h"

uint32_t CrcModule::getCrc32(std::string &message) {
    boost::crc_32_type result;
    result.process_bytes(message.data(), message.length());
    return result.checksum();
}

std::string CrcModule::getMessageWithCrc(std::string & message) {
    std::string message_with_crc(message);
    std::array<char, 4> sum = getSumArray(getCrc32(message));
    message_with_crc.append(sum.begin(), sum.end());
    return message_with_crc;
}

bool CrcModule::checkAndRemoveMessageSum(std::string & message) {
    if(message.size() < 4)
        return false;

    std::string message_without_sum(message.begin(), message.end()-4);
    std::array<char, 4> sum_array= getSumArray(getCrc32(message_without_sum));

    if(!std::equal(sum_array.begin(), sum_array.end(), message.end()-4))
        return false;

    message.resize(message.size()-4);
    return true;
}

std::array<char, 4> CrcModule::getSumArray(uint32_t sum) {
    std::array<char, 4> sum_array = {
            (char) ((sum >> 24) & 0xFF),
            (char) ((sum >> 16) & 0xFF),
            (char) ((sum >> 8) & 0xFF),
            (char) ((sum) & 0xFF)
    };

    return sum_array;
}
