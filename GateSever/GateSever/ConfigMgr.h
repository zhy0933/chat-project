#pragma once
#include "const.h"

/// <summary>
/// 自己创建一个类用于管理config配置中的键值对
/// </summary>
struct SectionInfo {
    SectionInfo() {}
    ~SectionInfo() {
        _section_datas.clear();
    }
    /// <summary>
    /// 拷贝构造
    /// </summary>
    /// <param name="src"></param>
    SectionInfo(const SectionInfo& src) {
        _section_datas = src._section_datas;
    }

    /// <summary>
    /// 拷贝赋值重载
    /// </summary>
    /// <param name="src"></param>
    /// <returns></returns>
    SectionInfo& operator = (const SectionInfo& src) {
        if (&src == this) {
            return *this;
        }
        this->_section_datas = src._section_datas;
        return *this;
    }

    /// <summary>
    /// 映射config中的键值对
    /// </summary>
    std::map<std::string, std::string> _section_datas;

    /// <summary>
    /// 重载[]，查找是否有对应的key，没有就返回空，有就返回value
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::string  operator[](const std::string& key) {
        if (_section_datas.find(key) == _section_datas.end()) {
            return "";
        }
        // 这里可以添加一些边界检查  
        return _section_datas[key];
    }
};

/// <summary>
/// 定义ComigMgr管理section和其包含的key与value
/// </summary>
class ConfigMgr
{
public:
    ~ConfigMgr() {
        _config_map.clear();
    }

    // 和上面的重载逻辑一样，这里相当于有两层map，第一层是section的名字，第二层是config中的参数名如GateServer
    SectionInfo operator[](const std::string& section) {
        if (_config_map.find(section) == _config_map.end()) {
            return SectionInfo();
        }
        return _config_map[section];
    }

    // 不同于CRTP，用另一种方式实现的单例类
    static ConfigMgr& Inst() { // 静态函数
        static ConfigMgr cfg_mgr; // 使用局部静态变量，只有在第一次调用时会初始化
        return cfg_mgr;
    }

    // 拷贝赋值
    ConfigMgr& operator=(const ConfigMgr& src) {
        if (&src == this) {
            return *this;
        }
        this->_config_map = src._config_map;
    };

    // 拷贝构造
    ConfigMgr(const ConfigMgr& src) {
        this->_config_map = src._config_map;
    }


private:
    // 默认构造 
    ConfigMgr();
    // key值是section的名字如GateServer，value是整个section管理的键值对
    std::map<std::string, SectionInfo> _config_map;
};
