#pragma once

namespace my {

template <typename Type>
class unique_ptr {
public:

    unique_ptr(Type* uniq = nullptr)
        : ptr_(uniq) {}

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& uniq) {
        ptr_ = uniq.ptr_;
        uniq.ptr_ = nullptr;
    }

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr& operator=(unique_ptr&& uniq) {
        if (this != &uniq) {
            delete ptr_;
            ptr_ = uniq.ptr_;
            uniq.ptr_ = nullptr;
        }
        return *this;
    }

    ~unique_ptr() {
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
        if (tmpPtr != nullptr) {
            delete tmpPtr;
            tmpPtr = nullptr;
        }
    }

private:
    Type* ptr_ = nullptr;
};
}  // namespace my