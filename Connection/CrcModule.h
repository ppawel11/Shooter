//
// Created by pawel on 02.06.2020.
//

#ifndef TIN_CRCMODULE_H
#define TIN_CRCMODULE_H

#include <string>
#include <boost/crc.hpp>
#include <array>

class CrcModule {
    uint32_t getCrc32(std::string &message);
    std::array<char, 4> getSumArray(uint32_t sum);
public:
    std::string getMessageWithCrc(std::string & message);
    bool checkAndRemoveMessageSum(std::string & message);
};


#endif //TIN_CRCMODULE_H
