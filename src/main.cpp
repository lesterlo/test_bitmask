

#include <iostream>

#include <bitset>
#include <cstdint>
#include <array>

constexpr size_t My_POST_MASK_MAX = 65;
constexpr size_t NUM_WORDS = (My_POST_MASK_MAX + 31) / 32; // Compute number of uint32_t needed

using MyBitset = std::bitset<My_POST_MASK_MAX>;
using MyMaskArray = std::array<uint32_t, NUM_WORDS>;

// Convert array of uint32_t to std::bitset<My_POST_MASK_MAX>
MyBitset combineToBitset(const MyMaskArray& maskGroup) {
    MyBitset bitmask;
    
    for (size_t i = 0; i < My_POST_MASK_MAX; ++i) 
    {
        int word = i / 32;
        int bit = i % 32;

        size_t bitIndex = word * 32 + bit;
        if (maskGroup[word] & (1U << bit)) {
            bitmask.set(bitIndex);
        }
    }

    return bitmask;
}

// Convert std::bitset<My_POST_MASK_MAX> to array of uint32_t
MyMaskArray splitBitset(const MyBitset& bitmask) {
    MyMaskArray maskGroup = {0};

    for (size_t bitIndex = 0; bitIndex < My_POST_MASK_MAX; ++bitIndex) {
        if (bitmask.test(bitIndex)) {
            size_t word = bitIndex / 32;
            size_t bit = bitIndex % 32;
            maskGroup[word] |= (1U << bit);
        }
    }
    return maskGroup;
}

int main() {
    MyBitset bitmask;
    bitmask.set(0);
    bitmask.set(1);
    bitmask.set(5);
    bitmask.set(33);
    bitmask.set(64); // Last bit (65th type)

    // Convert bitset to database format
    MyMaskArray maskGroup = splitBitset(bitmask);

    std::cout << "Stored maskGroup:\n";
    for (size_t i = 0; i < NUM_WORDS; ++i) {
        std::cout << "maskGroup[" << i << "]: " << std::bitset<32>(maskGroup[i]) << " (" << maskGroup[i] << ")\n";
    }

    // Retrieve from database
    MyBitset restored_bitmask = combineToBitset(maskGroup);
    std::cout << "Restored bitset:  " << restored_bitmask << "\n";

    return 0;
}