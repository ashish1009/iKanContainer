#include <iostream>

#include <iKan/Buffer.h>
#include <vector>

int main(int argc, const char * argv[])
{
    iKan::Buffer buffer(11);
    
    for (size_t i = 0; i < buffer.Size(); i ++)
        buffer[i] = i;
    
    iKan::Buffer copyBuffer = buffer;
    
    copyBuffer.PrintHex<iKan::byte>();
    copyBuffer.PrintHex<int>();
    copyBuffer.PrintDec<iKan::byte>();
    copyBuffer.PrintDec<int32_t>();
    
    iKan::Buffer moveBuffer = std::move(buffer);
    iKan::Buffer moveBuffer2;
    moveBuffer2 = std::move(buffer);
    
    std::cout << "\n";
    
    return 0;
}
