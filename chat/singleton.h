#ifndef SINGLETON_H
#define SINGLETON_H
#include <global.h>
/******************************************************************************
 *
 * @file       singleton.h
 * @brief      单例模板类
 *
 * @author     zhy
 * @date       2024/11/25
 * @history
 *****************************************************************************/
template <typename T>
class Singleton{
protected: // 把构造函数设为protected是因为希望派生类能够构造它
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>& st) = delete;
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        // 初始化只会调用一次
        std::call_once(s_flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

// static变量必须初始化，但因为这是模板类，初始化放在.h文件中而不是.cpp文件里
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
