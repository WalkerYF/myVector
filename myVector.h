// my vector class
// begin : 2017/4/29

#include <string>
#include <memory>
#include <utility>

class myVector
{
public:
    typedef int size_t;
    typedef std::string data_t;
    typedef std::string *  pointer_t;
    typedef const std::string * const_pointer_t;



    myVector():elements(nullptr), first_free(nullptr), cap(nullptr){}
    myVector(const myVector & __m);
    ~myVector();
    void push_back(const data_t &);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements; }
    pointer_t begin() const {return elements; }
    pointer_t end() const {return first_free; }

    myVector & operator=(const myVector & __m);
    //.....

private:
    static std::allocator<data_t> alloc;

    void chk_n_alloc();
    std::pair<pointer_t, pointer_t> alloc_n_copy(const_pointer_t, const_pointer_t);

    void free();
    void reallocate();


    pointer_t elements;  // point to the first element.
    pointer_t first_free; // point to the position behind the last element.
    pointer_t cap; // point to the position behind the available memory.

};


void myVector::push_back(const data_t & __data){
    chk_n_alloc();

    alloc.construct(first_free, __data);
    first_free++;
}

std::pair<myVector::pointer_t, myVector::pointer_t>
myVector::alloc_n_copy(myVector::const_pointer_t __b , myVector::const_pointer_t __e) 
{
    auto data = alloc.allocate(__e - __b);

    return {data, std::uninitialized_copy(__b, __e, data) };
}

void myVector::free()
{
    if (elements){
        for (auto p = first_free; p != elements; ){
            --p;
            alloc.destroy(p);

        }
        alloc.deallocate(elements, cap - elements);
    }
}

myVector::myVector(const myVector & __m)
{
    auto newdata = alloc_n_copy(__m.begin(), __m.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

myVector::~myVector()
{
    free();
}

myVector & myVector::operator=(const myVector & rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this; 
}

void myVector::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;

    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto old = elements;
    for (size_t i = 0; i != size(); ++i){
        alloc.construct(dest, *old);// move????
        ++dest;
        ++old;
    }
    
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}



