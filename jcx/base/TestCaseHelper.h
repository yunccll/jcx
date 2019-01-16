
#ifndef  JCX_BASE_TESTCASEHELPER_H
#define  JCX_BASE_TESTCASEHELPER_H

namespace jcx { 
namespace base {

class _Base{
public:
    _Base();
    virtual ~_Base();

    bool operator == (const _Base & right) const;

    const int id()const { return _id;}
    void setId(const int id) {_id = id;}

private:
    static int Gid;
    int _id;
};

class _If{
public:
    _If(){}
    ~_If(){}
    virtual void f() = 0;
};

class _Sub : public _Base , public _If{
public:
    _Sub(int id = 0);
    ~_Sub();

    void f() override;
private:
    int _id;
};

} //namespace base
} //namespace jcx

#endif   /* TESTCASEHELPER_H */
