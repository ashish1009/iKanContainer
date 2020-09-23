#pragma once

#include <Core.h>

namespace iKan {
    
    using byte = uint8_t;
    
    class Buffer
    {
    public:
        // -------------------------------- Constructors ----------------------------------------------
        Buffer()
        {
            IK_TRACE("Buffer(): Creating Buffer of size %d ", 0);
            // By default allocate the memory of 1 byte
            Allocate(1);
        }
        
        Buffer(size_t size)
        {
            IK_TRACE("Buffer(size_t size): Creating Buffer of size %d ", size);
            Allocate(size);
        }
        
        Buffer(const Buffer& other)
        {
            IK_TRACE("Buffer(const Buffer& other): Copying Buffer of size %d ", other.m_Size);
            Allocate(other.m_Size);
            memcpy(m_Data, other.m_Data, m_Size);
        }
        
        Buffer(Buffer&& other)
        {
            IK_TRACE("Buffer(Buffer&& other): Moving Buffer of size %d ", other.m_Size);
            m_Size = other.m_Size;
            m_Data = other.m_Data;
            
            other.m_Size = 0;
            other.m_Data = nullptr;
        }
        
        // ------------------------------- Assignment operator ----------------------------------------
        Buffer& operator=(Buffer&& other)
        {
            IK_TRACE("Buffer& operator=(Buffer&& other): Moving Buffer of size %d ", other.m_Size);
            m_Size = other.m_Size;
            m_Data = other.m_Data;
            
            other.m_Size = 0;
            other.m_Data = nullptr;
            
            return *this;
        }
        
        // ------------------------------------ Destructor --------------------------------------------
        ~Buffer()
        {
            Delete();
        }
        
        // ------------------------------------ Get member --------------------------------------------
        byte* Get() { return m_Data; }
        size_t Size() { return m_Size; }

        // ----------------------------------- Access member ------------------------------------------
        byte& operator[](size_t size)
        {
            IK_ASSERT( (size < m_Size), "Invalid Size");
            return m_Data[size];
        }
        
        // --------------------------------------- Print ----------------------------------------------
        template<typename T>
        void PrintHex()
        {
            size_t loopLimit = std::ceil(static_cast<double>(m_Size * sizeof(byte)) / static_cast<double>(sizeof(T)));
            for (size_t i = 0; i < loopLimit; i++)
                std::cout << std::hex << "0x" << static_cast<int64_t>(*((T*)m_Data + i)) << ", ";
            std::cout << "\n" << std::dec;
        }

        template<typename T>
        void PrintDec()
        {
            size_t loopLimit = std::ceil(static_cast<double>(m_Size * sizeof(byte)) / static_cast<double>(sizeof(T)));
            for (size_t i = 0; i < loopLimit; i++)
                std::cout << static_cast<int64_t>(*((T*)m_Data + i)) << ", ";
            std::cout << "\n";
        }

    private:
        void Allocate(size_t size)
        {
            if (size == 0)
                return;
            m_Size = size;
            m_Data = new byte[m_Size];
        }
        
        void Delete()
        {
            delete [] m_Data;
            m_Size = 0;
        }
        
    private:
        byte*  m_Data;
        size_t m_Size;
    };
}
