//injection functions
void* p_malloc(unsigned int size);
void p_free(void* ptr);
void* p_realloc(void* ptr, unsigned int newsize);

//memory keeper helpers
void p_introduced_reference(void* ptr);
void p_removed_reference(void* ptr);

//pointer wrapper
#include <stdio.h>
template<typename T> class Ptr{
    T* ptr;
public:
    Ptr(){
        ptr = NULL;
    }

    Ptr(void* val){
        p_introduced_reference(val);
        ptr = (T*) val;
    }

    Ptr(const Ptr<T>& other){
        p_introduced_reference(other.ptr);
        ptr = other.ptr;
    }

    ~Ptr(){
        p_removed_reference(ptr);
    }
    T& operator*(){
        //TODO check if not freed
        return *ptr;
    }
    T& operator->(){
        return operator*();
    }

    /*Ptr<T>& operator=(const void* val){
        p_removed_reference(ptr);
        p_introduced_reference(val);
        ptr = (T*)val;
        return *this;
    }*/

    Ptr<T>& operator=(const Ptr& other){
        p_introduced_reference(other.ptr);
        p_removed_reference(ptr);
        ptr = other.ptr;
    }

    operator T*(){
        return ptr;
    }
};