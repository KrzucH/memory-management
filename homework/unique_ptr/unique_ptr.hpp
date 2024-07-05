#pragma once

template<typename Type>
class uniq_ptr {
public:
    uniq_ptr() { 
        ptr_ =  nullptr; 
    }

    uniq_ptr(Type* uniq) : ptr_(uniq)
    {}

    uniq_ptr(const uniq_ptr&) = delete;        
   

    uniq_ptr(uniq_ptr&& uniq)  {
            ptr_ = uniq.ptr_;
            uniq.ptr_ = nullptr;
    }

    uniq_ptr& operator=(const uniq_ptr&) = delete;

    uniq_ptr& operator=(const uniq_ptr&& uniq) {
        if(uniq.ptr_ != nullptr) {
            delete ptr_;
            ptr_ = uniq.ptr_;
            uniq.ptr_ = nullptr;
        }
        return *this;
    }   

    ~uniq_ptr() {
        delete ptr_;
    }

    Type* get() const {
        return ptr_;
    }

    Type& operator*() const {
        return *ptr_;
    }

    Type* operator->() const {
        return ptr_;
    }

    Type* release() {
        auto newPtr = ptr_;
        ptr_ = nullptr;
        delete ptr_;
        return newPtr;
    }

    void reset(Type* uniq = nullptr) {
        auto tmpPtr = ptr_;        
        ptr_ = uniq;     
        if(tmpPtr != nullptr) {
            delete tmpPtr;
            tmpPtr = nullptr;
        }
    }

private:
    Type* ptr_ = nullptr;
};