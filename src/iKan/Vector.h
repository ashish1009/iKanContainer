#pragma once

#include <Core.h>

// Allocate memory equal to 1 if it is first allocation else allocate the double memory
#define NEW_CAPACITY ((m_Capacity * 2) >= 1) ? m_Capacity << 1 : 1

namespace iKan {
    
    template<typename Vector>
    class VectorIterator
    {
    public:
        using ValueType     = typename Vector::ValueType;
        using PointerType   = ValueType*;
        using ReferenceType = ValueType&;
        
    public:
        VectorIterator(PointerType ptr)
        : m_Ptr(ptr) {}
        
        // Prefix opperator
        VectorIterator& operator++()
        {
            m_Ptr++;
            return *this;
        }
        
        // Postfix opperator
        VectorIterator operator++(int)
        {
            VectorIterator iterator = *this;
            ++(*this);
            return iterator;
        }
        
        // Prefix opperator
        VectorIterator& operator--()
        {
            m_Ptr--;
            return *this;
        }
        
        // Postfix opperator
        VectorIterator operator--(int)
        {
            VectorIterator iterator = *this;
            --(*this);
            return iterator;
        }
        
        ReferenceType operator[](int index) { return *(m_Ptr + index); }
        PointerType operator->() { return m_Ptr; }
        ReferenceType operator*() { return *m_Ptr; }
        bool operator==(const VectorIterator& other) { return m_Ptr == other.m_Ptr; }
        bool operator!=(const VectorIterator& other) { return !(*this == other); }
        
    private:
        PointerType m_Ptr;
    };

    template<typename T>
    class Vector
    {
    public:
        using ValueType = T;
        using Iterator = VectorIterator<Vector<T>>;
        
    public:
        // ----------------- Constructor ---------------------------------
        Vector()
        {
            IK_VECTOR_TRACE("Vector::Vector(): Creating Vector of size %d ", m_Size);
        }
        
        Vector(std::initializer_list<T> values)
        {
            IK_VECTOR_TRACE("Vector::Vector(std::initializer_list<T> values): Creating Vector of size %d ", values.size());
            ReAlloc(values.size());
            for (auto val = values.begin(); val != values.end(); val++)
                PushBack(*val);
        }
        
        Vector(const Vector& other)
        : m_Size(0), m_Capacity(other.m_Capacity)
        {
            IK_VECTOR_TRACE("Vector::Vector(const Vector& other): Creating Vector of size %d ", other.m_Size);
            T* newBlock = (T*)(::operator new(m_Capacity * sizeof(T)));
            
            for(size_t i = 0; i < other.m_Size; i++)
                newBlock[m_Size++] = std::move(other.m_Data[i]);
            
            m_Data = newBlock;
        }
        
        Vector(Vector&& other)
        : m_Size(other.m_Size), m_Capacity(other.m_Capacity), m_Data(other.m_Data)
        {
            IK_VECTOR_TRACE("Vector::Vector(Vector&& other): Creating Vector of size %d ", other.m_Size);
            other.m_Size = 0;
            other.m_Data = nullptr;
        }
        
        Vector(size_t size, const T& other)
        : m_Capacity(size), m_Size(0)
        {
            IK_VECTOR_TRACE("Vector::Vector(size_t size, const T& other): Creating Vector of size %d ", size);
            T* newBlock = (T*)(::operator new(m_Size * sizeof(T)));
            
            for(size_t i = 0; i < size; i++)
                newBlock[m_Size++] = std::move(other);
            
            m_Data = newBlock;
        }
        
        // ----------------- Destructor ---------------------------------
        ~Vector()
        {
            IK_VECTOR_TRACE("Vector:: ~Vector: Destroying Vector");
            Clear();
            ::operator delete(m_Data, m_Capacity * sizeof(T));
            m_Data = nullptr;
        }
        
        // ----------------- Clearing ---------------------------------
        void PopBack()
        {
            IK_VECTOR_TRACE("Vector::PopBack(): Popping Element from end");
            if (m_Size > 0)
            {
                m_Size--;
                m_Data[m_Size].~T();
            }
        }
        
        void Clear()
        {
            IK_VECTOR_TRACE("Vector::Clear(): Clearing Vector");
            // Calling destructor of all elemebts
            for (size_t i = 0; i < m_Size; i++)
                m_Data[i].~T();
            
            m_Size = 0;
        }
        
        // ---------------- Emplace Back ---------------------------------
        template<typename... Args>
        T& EmplaceBack(Args&&... args)
        {
            IK_VECTOR_TRACE("Vector::EmplaceBack(Args&&... args): Emplacing back Vector");

            if (m_Size >= m_Capacity)
                ReAlloc(NEW_CAPACITY);
            
            /*
             Assigning the data to already allocated memory
             Note: this new is not allocating new memory in heap
             */
            new(&m_Data[m_Size++])T(std::forward<Args>(args)...);
            
            return m_Data[m_Size];
        }
        
        // ---------------- Push Back ---------------------------------
        void PushBack(const T& value)
        {
            IK_VECTOR_TRACE("Vector::PushBack(const T& value): Pushing value ");
            if(m_Size >= m_Capacity)
                ReAlloc(NEW_CAPACITY);
            
            m_Data[m_Size++] = value;
        }
        
        void PushBack(T&& value)
        {
            IK_VECTOR_TRACE("Vector::PushBack(const T&& value): Pushing value ");
            if (m_Size >= m_Capacity)
                ReAlloc(NEW_CAPACITY);
            
            m_Data[m_Size++] = std::move(value);
        }
        
        // ---------------- operator = ---------------------------------
        Vector& operator=(const Vector& other)
        {
            size_t tempSize = m_Size;
            AllocIfNeeded(other.m_Capacity);
            
            for(size_t i = 0; i < other.m_Size; i++)
                m_Data[m_Size++] = std::move(other.m_Data[i]);
            
            for (size_t i = m_Size; i < tempSize; i++)
                m_Data[i].~T();
            
            return *this;
        }
        
        Vector& operator=(Vector&& other)
        {
            if (this != &other)
            {
                Clear();
                
                m_Size = 0;
                m_Capacity = other.m_Capacity;
                m_Data = other.m_Data;
                
                other.m_Size = 0;
                other.m_Data = nullptr;
            }
            return *this;
        }
        
        Vector& operator=(std::initializer_list<T> values)
        {
            Assign(values);
            return *this;
        }
        
        // ---------------- Assign Function ---------------------------------
        void Assign(size_t size, const T& other)
        {
            IK_VECTOR_TRACE("Vector::Assign(size_t size, const T& other): Pushing value ");
            size_t tempSize = m_Size;
            AllocIfNeeded(size);
            
            for(size_t i = 0; i < size; i++)
                m_Data[m_Size++] = std::move(other);
            
            for (size_t i = m_Size; i < tempSize; i++)
                m_Data[i].~T();
        }
        
        void Assign(std::initializer_list<T> values)
        {
            IK_VECTOR_TRACE("Vector::Assign(std::initializer_list<T> values): Pushing value ");
            size_t tempSize = m_Size;
            AllocIfNeeded(values.size());
            
            for (auto val = values.begin(); val != values.end(); val++)
                m_Data[m_Size++] = std::move(*val);
            
            for (size_t i = m_Size; i < tempSize; i++)
                m_Data[i].~T();
        }
        
        // ---------------- Access Elements ---------------------------------
        T& operator[](size_t index)
        {
            ASSERT(index < m_Capacity, "\n Index overflow \n");
            return m_Data[index];
        }
        
        const T& operator[](size_t index) const
        {
            ASSERT(index < m_Capacity, "\n Index overflow \n");
            return m_Data[index];
        }
        
        T& At(size_t index)
        {
            return this[index];
        }
        
        const T& At(size_t index) const
        {
            return this[index];
        }
        
        T& Front()
        {
            return this[0];
        }
        
        const T& Front() const
        {
            return this[0];
        }
        
        T& Back()
        {
            return this[m_Size - 1];
        }
        
        const T& Back() const
        {
            return this[m_Size - 1];
        }
        
        // ---------------- Sizes ---------------------------------
        size_t Size() const { return m_Size; }
        size_t Capacity() const { return m_Capacity; }

        // ---------------- Data ---------------------------------
        T* Data() { return m_Data; }
        const T* Data() const { return m_Data; }
        
        // --------------- Iterators -----------------------------
        Iterator begin() { return Iterator(m_Data); }
        Iterator end() { return Iterator (m_Data + m_Size);}

    private:
        void ReAlloc(size_t size)
        {
            IK_VECTOR_TRACE("Vector::ReAlloc(size_t size): Allocating of size %d, previous capacity %d ", size, m_Capacity);
            
            // Allocate the memory without calling the constructor
            T* newBlock = (T*)(::operator new(size * sizeof(T)));
            
            // Change size of vector only if we are increasing the container else keep previous
            if (m_Size > size)
                m_Size = size;
            
            // Copy(Move) all the element to new buffer
            for(size_t i = 0; i < m_Size; i++)
                newBlock[i] = std::move(m_Data[i]);
            
            // before deleting Destruct the copied element (old values)
            for(size_t i = 0; i < m_Size; i++)
                m_Data[i].~T();
            
            // Delete the m_Data allocated previosuly of size m_Capacity
            ::operator delete(m_Data, m_Capacity * sizeof(T));
            
            m_Data = newBlock;
            m_Capacity = size;
        }
        
        void ClearAndReAlloc(size_t size)
        {
            Clear();
            ReAlloc(size);
        }
        
        void AllocIfNeeded(size_t size)
        {
            if (m_Capacity < size)
                ClearAndReAlloc(size);
            m_Size = 0;
        }
        
    private:
        T* m_Data = nullptr;
        size_t m_Size = 0;
        size_t m_Capacity = 0;
    };
    
}
