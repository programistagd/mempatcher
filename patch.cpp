#include "patch.hpp"
#include <stdlib.h>

#include <map>
#include <exception>
#include <string>

static std::map<void*, int> p_usage;

static void error(std::string msg){
    printf("%s\n",msg.c_str());
    throw msg;
}

void p_introduced_reference(void* ptr){
    std::map<void*, int>::iterator it = p_usage.find(ptr);
    if(it == p_usage.end()){
        p_usage[ptr] = 1;
    }
    else{
        p_usage[ptr] += 1;
    }
}

void p_removed_reference(void* ptr){
    std::map<void*, int>::iterator it = p_usage.find(ptr);
    if(it == p_usage.end()){
        //do nothing or notify? it may happen after an ok free probably
    }
    else{
        p_usage[ptr] -= 1;
        if(p_usage[ptr] == 0){
            error("Last reference to a not-freed pointer removed");
        }
    }
}

void* p_malloc(unsigned int size){
    void* ptr = malloc(size);
    p_usage[ptr] = 0;//not really needed but why not, could be used for detecting not assigned pointers, so maybe -1?
    return ptr;
}

void p_free(void* ptr){
    p_usage.erase(ptr);
    free(ptr);
}

void* p_realloc(void* ptr, unsigned int newsize){
    void* p2 = realloc(ptr, newsize);
    if(p2 != ptr){
        //if something changed
        //TODO maybe do something if p_usage[ptr] > 1 as other references become dangling
        int old = p_usage[ptr];//should be 1
        p_usage.erase(ptr);
        p_usage[p2] = old;
    }
    return p2;
}

/*void terminate_handler()
{
    try { throw; }
    catch(const std::exception& e) { log(e.what()); }
    catch(...) {}
}

void prepare_terminate(){
    std::set_terminate(terminate_handler);
}*/