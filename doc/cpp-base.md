CPP  base 

    C++, C++11, C++1z


## elmentary

* const & non-const

    ```const int; 
    const int * ;
    const int * const ;
    void f(const int *) const ;
    ```

* static 
    TODO:

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
                _name_owner = name;
            }
            ~A();

        private:
            std::string & name_ref;
            std::string name_owner;
        };
        ```


* auto
    * easy 

        ```int a = 100;
        int b = a; 

        auto b = a; type(a)--> type(b)
        ```

    * complicated

    ```std::vector<int> p;
    std::vector<int>::iterator it = p.begin();
    for(; it != p.end(); ++it){
        ...
    } 

    // --> 
    for( auto it = p.begin(); it != p.end(); ++it){
        ...
    }
    ```

* shared_ptr
    
    ```int * ptr = new int(10);
    delete ptr;

    {
        std::shared_ptr<int> sptr(new int(10)); //memory free 
        std::cout << *sptr << std::endl;
        std::cout << *(sptr->get()) << std::endl;
    }
    ```


* namespace 
    TODO:
* initializer for constructor
    TODO:

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
    ```

    use it 

    ```Base * pBase = new Base();
    Sub * pSub = new Sub();

    Base * pBase1 = pSub;

    Sub * pSub1 = pBase; //compile error

    delete pSub;
    delete pBase;
    ```

    * Polymorphic
    virtual 
    TODO: 

    class Sub{
    };


## STL 

## DP


