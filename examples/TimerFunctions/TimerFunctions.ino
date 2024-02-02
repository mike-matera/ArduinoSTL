#include <iostream>
//#include <chrono>
//#include <thread>

int main() {
    std::cout << "等待1秒钟..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "完成等待。" << std::endl;
    return 0;
}