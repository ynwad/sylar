/*
 * @Author: error: git config user.name & please set dead value or install git
 * @Date: 2022-08-05 22:18:40
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-09-15 23:26:29
 * @FilePath: /sylar/tests/test_config.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include "sylar/config.h"
#include "sylar/log.h"
#include <yaml-cpp/yaml.h>
#include <vector>

sylar::ConfigVar<int>::ptr g_int_value_config = 
    sylar::Config::Lookup("system.port", (int)8088, "system port");


sylar::ConfigVar<float>::ptr g_float_value_config = 
    sylar::Config::Lookup("system.value", (float)10.2f, "system value");

sylar::ConfigVar<std::vector<int>>::ptr g_vec_value_config = 
    sylar::Config::Lookup("system.port", std::vector<int>({1, 2, 3, 4, 5}), "system port");



void print_yaml(const YAML::Node& node, int level){
    if(node.IsScalar()){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    }else if(node.IsNull()){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    }else if(node.IsMap()){
        for(auto it = node.begin();
                it != node.end(); ++it){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
                                    << it->first << " ****** " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}


void test_yaml(){
    YAML::Node root = YAML::LoadFile("/home/ynwad/workspace/sylar/bin/conf/test_config.yaml");
    // YAML::Node root = YAML::LoadFile("/home/sylar/workspace/sylar/bin/conf/test.yml");
    sylar::Config::LoadFromYaml(root);
    // print_yaml(root, 0);
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}

class Person {
public:
    Person(){};
    Person(const std::string name, const int age, const bool sex)
        :m_name(name),
        m_age(age),
        m_sex(sex){
    };
    std::string m_name;
    int m_age = 0;
    bool m_sex = false;

    bool operator==(const Person& oth) const {
        return m_name == oth.m_name
            && m_age == oth.m_age
            && m_sex == oth.m_sex;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name=" << m_name
           << " age=" << m_age
           << " sex=" << m_sex
           << "]";
        return ss.str();
    }
};

sylar::ConfigVar<Person>::ptr g_person =
    sylar::Config::Lookup("class.person", Person(), "system person");

sylar::ConfigVar<std::map<std::string, Person> >::ptr g_person_map =
    sylar::Config::Lookup("class.map", std::map<std::string, Person>(), "system person");

sylar::ConfigVar<std::map<std::string, std::vector<Person> > >::ptr g_person_vec_map =
    sylar::Config::Lookup("class.vec_map", std::map<std::string, std::vector<Person> >(), "system person");

namespace sylar{

template<>
class LexicalCast<std::string, Person>{
public:
    Person operator()(const std::string& str){
        YAML::Node node = YAML::Load(str);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<>
class LexicalCast<Person, std::string>{
public:
    std::string operator()(const Person& p){
        YAML::Node node;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};
}

void printValue(int a, int b)
{
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << a << " hhhhhh " << b ;
}



std::function<void(int, int)> fuc = printValue;

int main(int args, char** argv){
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_vec_value_config->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_person_map->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << sylar::Config::GetDatas()["class.person"]->toString();
    g_person->addListener([](const Person& old_value, const Person& new_value){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "old_value=" << old_value.toString()
                << " new_value=" << new_value.toString();
    });
    g_int_value_config->addListener(fuc);
    g_int_value_config->setValue(7777);
    g_person->setValue(Person("eeeeeeeeeeeeeeee", 44, true));

    test_yaml();
}

