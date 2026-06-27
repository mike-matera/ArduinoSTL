
#include <memory>
std::unique_ptr<char[]> UPI = std::make_unique_for_overwrite<char[]>(1);
std::shared_ptr<char> SPI = std::make_shared<char>('c');