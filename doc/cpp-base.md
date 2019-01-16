CPP  base  training

    C++ 发展了许多年，特别的臃肿。
    组成部分有： 语言特性; 面向对象; 泛型编程; 库(STL), 新增加的库和语法(C++11,C++1z)。

    综合考虑，我们项目里面只使用其中最基础，最有效，最重要的部分；
    特别注意：禁止炫技代码在工作代码中出现。

    最重要的部分：类型系统，面向过程，面向对象，少部分模板技巧&STL, 内存管理部分


## ref book
    <c++ primer plus> 基础语法
    <effective C++>  工程实践
    <Generic Programming and the STL> 泛型编程概念和ＳＴＬ分析
    <www.boost.org>  C++11, C++1z 新lib

    书很多，除了用于入门的可以先看看，还是靠写码先多实践了再说。


## 与C的最大区别
* base
    * 强类型
    * 面向对象 (OOP)
    * 泛型编程 (GP)

* standard library
    * 常用数据结构      (container, string...)
    * base io
    * 与之配套的算法    (sort, find, ....)
    * 语言特性补充
        MM, Functor, lambda

* non-standard library
    * 功能扩充 (boost)
    network, filesystem, datetime,


## elmentary

* const & non-const

    ```const int; 
    const int * ptr ;  //这个用的很多
    const int * const  ptr;


    class A {
        void f(const int *) const ;
        void f(const int *);
    }

    ```

* static 
    
    ```//A.cpp 
    static int f(){
        return 0;
    }

    
    // global function of A
    class A {
    public:
        static int f(){
            return 0;
        }
    };

    // use static function 
    typedef int (*pf_t)();
    pf_t  p_f = &f;
    pf_t  p_a_f = &A::f;
    ```

* ptr & Ref 

    * base

        ```int p = 10;
        int * ptr &p;
        int & ref = p;
        ```

    * function argument

        ```void f(std::string & str);

        std::string str;
        f(str);

        const char * cstr = "hello";
        f(cstr); //Error
        

        void f_val(std::string str);
        f_val(cstr);  // Bad 

        
        void f_cons_val(const std::string & str);
        f_const_val(cstr);
        ```

    * class member 
    
        ```class A {
        public: 
            A(const std::string & name){
                _name_ref = name;
                _name_owner = name; }
            ~A();

        private:
            std::string & name_ref;
            std::string name_owner;
        };
        ```

* auto  类型推演
    * 1

        ```int a = 100;
        int b = a; 

        auto b = a; type(a)--> type(b)
        ```

    * 2

        ```std::vector<int> p;
        std::vector<int>::iterator it = p.begin();
        for(; it != p.end(); ++it){
        } 

        // --> 
        for( auto it = p.begin(); it != p.end(); ++it){
        }
        ```

* shared_ptr
    
    ```int * ptr = new int(10);
    delete ptr;

    {
        std::shared_ptr<int> sptr(new int(10)); //memory free 
        std::cout << *sptr << std::endl;
        std::cout << *(sptr->get()) << std::endl;


        std::shared_ptr<int> sptr1  = sptr;   // owner sptr --> sptr1
    }
    ```

    extend:
    unique_ptr, weak_ptr

* namespace 


    ```//a.h
    namespace jcx{
    namespace base {

    class A{
    public:
        A();
        ~A();
    };

    }  //namespace base
    }  //namespace jcx

    //a.cpp
    namespace jcx{
    namespace base {
        
    A::A(){
    }
    A::~A(){
    }
        
    }  //namespace base
    }  //namespace jcx
  
    //forward reference  in XXX.h
    namespace jcx {
        namespace base {
            class A;
        }
    }
    ```


* initializer for constructor
    
    ```class A {
    public:
        A()
        :_a(0)      // note the order
        ,_b(0)
        ,_c(0)
        {
        }
        ~A(){
        }
    private:
        int a;   //Note the order 
        int b;
        int c;
    };
    ```

## OOP

* Encapsulation

    private, public 

    ```class BaseFinal final {
    public :
        BaseFinal()
        :_seq(0)
        {
        }
        ~BaseFinal(){
        }

        const int seq() const {
            //inc();
            return _seq;
        }

    private:
        int inc(){
            return _seq+1;
        }  
        
    private:
        int _seq;
    };
    ```

* Inherit 
    protected

    ```class Base {
    public :
        Base()
        :_seq(0)
        {
        }
        virtual ~Base(){
        }

        const int seq() const {
            //inc();
            //dec(); 
            return _seq;
        }

    protected:
        int dec(){
            return _seq - 1 ;
        }
    private:
        int inc(){
            return _seq+1;
        }  
        
    private:
        int _seq;
    };
    class Sub : public Base {
    public:
        Sub(){
        }
        virtual Sub(){
        }
    };

    // use it 
    Base * pBase = new Base();
    Sub * pSub = new Sub();

    Base * pBase1 = pSub;

    Sub * pSub1 = pBase; //compile error

    delete pSub;
    delete pBase;
    ```

* Polymorphic
    virtual 
    TODO: 

    ```class Sub{
    };
    ```


## STL  TODO:

* Container 
    vector, list, deque, queue,  std::map,  std::unordered_map(C++11)
* iterator
    for
* algorithm
    std::find,  std::advance, .....
* function
    

## DP Evolution TODO: 

* Observer Pattern Evolution
    * callback 
    * listener 
    * Observer

* Status Pattern Evolution
    * if-everywhere
    * Status-transfer-table
    * Status

