namespace STUFF
{
	const double pi = 3.141592653589793;
	const int mod = 1e9 + 7;
	const int mod1 = 998244353;
	const int maxn = 1e6 + 1;

	struct hash_pair
	{
		template <class T1, class T2>
		size_t operator()(const std::pair<T1, T2>& p) const
		{
			auto hash1 = hash<T1>{}(p.first);
			auto hash2 = hash<T2>{}(p.second);
			return hash1 ^ hash2;
		}
	};


	struct Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<float> duration = start - end;

		Timer()
		{
			start = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			end = std::chrono::high_resolution_clock::now();
			duration = end - start;

			float ms = duration.count() * 1000.0f;
			std::cout << "Timer took" << ms << "ms" << std::endl;
		}
	};

	class String
	{
	private:
		char* m_Buffer;
		unsigned int m_size;
	public:
		String(const char* string)
		{
			m_size = strlen(string);
			m_Buffer = new char[m_size + 1];
			memcpy(m_Buffer, string, m_size);
			m_Buffer[m_size] = 0;
		}

		//Copy Constructor
		String(const String& other) : m_size(other.m_size)
		{
			std::cout << "Copied Once" << std::endl;
			m_Buffer = new char[m_size + 1];
			memcpy(m_Buffer, other.m_Buffer, m_size + 1);
		}

		~String()
		{
			delete[] m_Buffer;
		}

		char& operator[](unsigned int index)
		{
			return m_Buffer[index];
		}


		friend std::ostream& operator<<(std::ostream& stream, const String& string);
	};

	std::ostream& operator<<(std::ostream& stream, const String& string)
	{
		stream << string.m_Buffer;
		return stream;
	}
}

namespace stuff
{
    template <class T>
    class Vector
    {
    public:
        typedef T * iterator;

        Vector();
        Vector(unsigned int size);
        Vector(unsigned int size, const T & initial);
        Vector(const Vector<T> & v);      
        ~Vector();

        unsigned int capacity() const;
        unsigned int size() const;
        bool empty() const;
        iterator begin();
        iterator end();
        T & front();
        T & back();
        void push_back(const T & value); 
        void pop_back();  

        void reserve(unsigned int capacity);   
        void resize(unsigned int size);   

        T & operator[](unsigned int index);  
        Vector<T> & operator=(const Vector<T> &);
        void clear();
    private:
        unsigned int my_size;
        unsigned int my_capacity;
        T * buffer;
    };

    template<class T>
    Vector<T>::Vector()
    {
        my_capacity = 0;
        my_size = 0;
        buffer = 0;
    }

    template<class T>
    Vector<T>::Vector(const Vector<T> & v)
    {
        my_size = v.my_size;
        my_capacity = v.my_capacity;
        buffer = new T[my_size];  
        for (unsigned int i = 0; i < my_size; i++)
            buffer[i] = v.buffer[i];  
    }

    template<class T>
    Vector<T>::Vector(unsigned int size)
    {
        my_capacity = size;
        my_size = size;
        buffer = new T[size];
        for (unsigned int i = 0; i < size; i++)
            buffer[i] = T();
    }

    template<class T>
    Vector<T>::Vector(unsigned int size, const T & initial)
    {
        my_size = size;
        my_capacity = size;
        buffer = new T [size];
        for (unsigned int i = 0; i < size; i++)
            buffer[i] = initial;
    }

    template<class T>
    Vector<T> & Vector<T>::operator=(const Vector<T> & v)
    {
        delete[ ] buffer;
        my_size = v.my_size;
        my_capacity = v.my_capacity;
        buffer = new T [my_size];
        for (unsigned int i = 0; i < my_size; i++)
            buffer[i] = v.buffer[i];
        return *this;
    }

    template<class T>
    typename Vector<T>::iterator Vector<T>::begin()
    {
        return buffer;
    }

    template<class T>
    typename Vector<T>::iterator Vector<T>::end()
    {
        return buffer + size();
    }

    template<class T>
    T& Vector<T>::front()
    {
        return buffer[0];
    }

    template<class T>
    T& Vector<T>::back()
    {
        return buffer[my_size - 1];
    }

    template<class T>
    void Vector<T>::push_back(const T & v)
    {
        if (my_size >= my_capacity)
            reserve(my_capacity + 5);
        buffer [my_size++] = v;
    }

    template<class T>
    void Vector<T>::pop_back()
    {
        my_size--;
    }

    template<class T>
    void Vector<T>::reserve(unsigned int capacity)
    {
        if(buffer == 0)
        {
            my_size = 0;
            my_capacity = 0;
        }    
        T * Newbuffer = new T [capacity];
        unsigned int l_Size = capacity < my_size ? capacity : my_size;

        for (unsigned int i = 0; i < l_Size; i++)
            Newbuffer[i] = buffer[i];

        my_capacity = capacity;
        delete[] buffer;
        buffer = Newbuffer;
    }

    template<class T>
    unsigned int Vector<T>::size() const
    {
        return my_size;
    }

    template<class T>
    void Vector<T>::resize(unsigned int size)
    {
        reserve(size);
        my_size = size;
    }

    template<class T>
    T& Vector<T>::operator[](unsigned int index)
    {
        return buffer[index];
    }  

    template<class T>
    unsigned int Vector<T>::capacity() const
    {
        return my_capacity;
    }

    template<class T>
    Vector<T>::~Vector()
    {
        delete[ ] buffer;
    }

    template <class T>
    void Vector<T>::clear()
    {
        my_capacity = 0;
        my_size = 0;
        buffer = 0;
    }
}
// {
// struct iterator
//     {
//         iterator(int* ptr, Dsu* dsu) : m_ptr(ptr), m_dsu(dsu) {}
//         int& operator*() const { return *m_ptr; }
//         iterator& operator++() { m_ptr++; return *this; }
//         // iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
//         friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
//         friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };

//     private:
//         int* m_ptr;
//         Dsu* m_dsu;
//     };

//     iterator begin() { return iterator(&dsu_par[0], this); }
//     iterator end() { return iterator(&dsu_par[m_sz], this); }
//     }