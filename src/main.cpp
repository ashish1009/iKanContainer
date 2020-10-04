#include <iostream>

#include <iKan/Buffer.h>
#include <iKan/Vector.h>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

#if 0
static void PrintVector(const std::vector<iKan::Buffer>& vec)
{
    for (auto val : vec)
    {
//        val.PrintDec<iKan::Buffer>();
    }
    std::cout << "\n";
}
#endif

int main(int argc, const char * argv[])
{
#if 0
    LOG("---------- Default Constructor ----------");
    iKan::Buffer defaultBuffer;
    defaultBuffer.PrintHex<iKan::byte>();
    
    LOG("---------- Sized Constructor ------------");
    iKan::Buffer sizedBuffer(11);
    sizedBuffer.PrintHex<iKan::byte>();

    LOG("--------- [] Operator and Size ----------");
    for (size_t i = 0; i < sizedBuffer.Size(); i ++)
        sizedBuffer[i] = i;
    sizedBuffer.PrintHex<iKan::byte>();

    LOG("----------- Copy Constructor ------------");
    iKan::Buffer copyBuffer = sizedBuffer;
    copyBuffer.PrintHex<iKan::byte>();

    LOG("---------- Move Constructor -------------");
    iKan::Buffer moveBuffer = std::move(sizedBuffer);
    moveBuffer.PrintHex<iKan::byte>();

    LOG("---------- = Move Operator --------------");
    defaultBuffer = std::move(sizedBuffer);
    defaultBuffer.PrintHex<iKan::byte>();
#endif
    
    LOG("---------- Default Constructor ----------");
    std::vector<iKan::Buffer> defaultStdVector;
    iKan::Vector<iKan::Buffer> defaultIkanVector;
    
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    
    iKan::Buffer buffer1(11);
    iKan::Buffer buffer2(10);
    iKan::Buffer buffer3(17);
    iKan::Buffer buffer4(12);
    iKan::Buffer buffer5(15);
    iKan::Buffer buffer6(13);
    
    LOG("-------------------------        STD        -------------------------------");
    defaultStdVector.push_back(buffer1);
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";
    LOG("-----------------------------------------");
    defaultStdVector.push_back(buffer2);
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";
    LOG("-----------------------------------------");
    defaultStdVector.push_back(buffer3);
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";
    LOG("-----------------------------------------");
    defaultStdVector.push_back(buffer4);
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";
    LOG("-----------------------------------------");
    defaultStdVector.push_back(buffer5);
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";
    LOG("-----------------------------------------");
    defaultStdVector.push_back(buffer6);
    std::cout << "STD  : Size: " << defaultStdVector.size() << ", Capacity: " << defaultStdVector.capacity() << "\n";

    LOG("-------------------------        IKAN        ------------------------------");
    defaultIkanVector.PushBack(std::move(buffer1));
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    LOG("-----------------------------------------");
    defaultIkanVector.PushBack(buffer2);
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    LOG("-----------------------------------------");
    defaultIkanVector.PushBack(buffer3);
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    LOG("-----------------------------------------");
    defaultIkanVector.PushBack(buffer4);
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    LOG("-----------------------------------------");
    defaultIkanVector.PushBack(buffer5);
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    LOG("-----------------------------------------");
    defaultIkanVector.PushBack(buffer6);
    std::cout << "IKAN : Size: " << defaultIkanVector.Size() << ", Capacity: " << defaultIkanVector.Capacity() << "\n";
    LOG("-----------------------------------------");
    
    std::cout << "\n";
    
    return 0;
}
