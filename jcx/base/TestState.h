#ifndef  TESTSTATE_H
#define  TESTSTATE_H
#include <string>
#include <vector>

namespace jcx { 
namespace base {

/*
 * States Interface:  
 *      operator = (std::string)
 *      operator += (std::string)
 *      reset()
 *      opeartor == (std::string)
 *      operator [] (int index)
 */
template<typename States>
class ITestState{
public:
    ITestState(){};
    virtual ~ITestState(){};

    template<typename T>
    void __set(T curState){
        _states = std::to_string(curState);
    }
    void __set(const char * curState){
        _states = std::string(curState);
    }
    void __set(const std::string  & curState){
        _states = curState;
    }

    template<typename T>
    void __add(T curState){
        _states += std::to_string(curState);
    }
    void __add(const char * curState){
        _states += std::string(curState);
    }
    void __add(const std::string  & curState){
        _states += curState;
    }
    
    void __reset(){
        _states.reset();
    }

    bool operator == (const char * curState){
        return _states == std::string(curState);
    }
    bool operator == (const std::string & curState){
        return _states == curState;
    }
    typename States::__Element & operator [] (int index){
        return _states[index];
    }
private:
    States _states; 
};

class __States{
public:
    typedef char __Element;
   __States & operator = (const std::string & state){
       _states = state;
       return *this;
   }
   __States & operator += (const std::string & state){
       _states += state; 
       return *this;
   }
   void reset(){
      _states.assign(NULL);
   }
   bool operator == (const std::string & str){
       return _states == str;
   }
   __Element & operator [] (int index){
       return _states[index];
   }
private:
    std::string  _states;
};
typedef ITestState<__States> TestState;



class __Processes{
public:
    typedef std::string __Element;
   __Processes & operator = (const std::string & state){
       _processes.clear();
       _processes.push_back(state);
       return *this;
   }
   __Processes & operator += (const std::string & state){
       _processes.push_back(state);
       return *this;
   }
   void reset(){
       _processes.clear();
   }
   bool operator == (const std::string & str){
       std::string tmp;
       std::vector<std::string>::iterator it = _processes.begin();
       for( ;it != _processes.end(); ++it){
            tmp += *it;
       }
       return tmp== str;
   }
   __Element & operator [] (int index){
       return _processes[index];
   }
private:
    std::vector<std::string>  _processes;
};
typedef ITestState<__Processes> TestProcess;

} //namespace base
} //namespace jcx


#endif   /* TESTSTATE_H */
