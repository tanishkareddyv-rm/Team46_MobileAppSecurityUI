#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>

class SHA256 {
public:
    static std::string hash(const std::string &data);

private:
    static const uint32_t k[64];
    static void transform(uint32_t state[8], const uint8_t block[64]);
};

#endif
