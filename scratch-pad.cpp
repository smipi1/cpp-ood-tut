#include <iomanip>
#include <iostream>

class BcdCounter {
private:
    uint8_t _buffer[4];

public:
    BcdCounter() : _buffer{0} {}

    void increment() {
        for (size_t nibbleIdx = 0; nibbleIdx < (sizeof(_buffer) * 2);
             nibbleIdx++) {
            auto byteIdx = nibbleIdx / 2;
            auto shiftSize = (nibbleIdx % 2) * 4;
            unsigned nibbleValue = (_buffer[byteIdx] >> shiftSize) & 0xf;

            if (nibbleValue < 9) {
                _buffer[byteIdx] += 1u << shiftSize;
                break;
            } else {
                unsigned rollMaskValue = ~(0xf << shiftSize);
                _buffer[byteIdx] &= rollMaskValue;
            }
        }
    }

    void operator++() { increment(); }

    void operator++(int) { increment(); }

    void print() {
        std::cout << __PRETTY_FUNCTION__ << ":";

        for (auto i = sizeof(_buffer); i-- > 0;) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << (int)_buffer[i];
        }
        std::cout << std::endl;
    }
};

int main(int argc, char const *argv[]) {
    BcdCounter c;

    for (auto i = 0; i < 100; i++) {
        c++;
        c.print();
    }

    std::cout << std::endl;
    return 0;
}
