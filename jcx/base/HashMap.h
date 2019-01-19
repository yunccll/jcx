
#ifndef  JCX_BASE_HASHMAP_H
#define  JCX_BASE_HASHMAP_H

#include <unordered_map>
#include <jcx/base/Macro.h>

namespace jcx {
namespace base {


template<typename K, typename V>
class IMap {
public:
    IMap(){}
    virtual ~IMap(){}

    virtual int insert(const K & k,  const V & v) = 0;
    virtual bool insertOrReplace(const K & k, const V & v) = 0;
    virtual void remove(const K & k) = 0;
    virtual void clear() = 0;

    virtual unsigned long size() const = 0;
    virtual bool contains(const K & k) const = 0;

    bool getValue(const K & k, V & v){
        //return contains(k) ? (v = get(k), true) : false;
        if(contains(k)){
            v = get(k);
            return true;
        }
        return false;
    }
    virtual V& get(const K & k) = 0;
    virtual bool set(const K & k, const V & v) = 0;
    virtual V& getRef(const K & k)  = 0 ;
private:
    JCX_NO_COPY_CTORS(IMap);
};



template<typename K, typename V>
class HashMap :  public IMap<K, V>{
public:
    HashMap(){}
    ~HashMap() override {}

    int insert(const K & k,  const V & v) override {
        auto it = _imp.find(k);
        if(it == _imp.end()){
            _imp.insert(std::make_pair(k, v));
            return 0;
        }
        return -1;
    }

    bool insertOrReplace(const K & k, const V & v) override {
        auto p = _imp.insert_or_assign(k, v);
        return p.second;
    }
    void remove(const K & k) override {
        _imp.erase(k);
    }
    void clear() override {
        _imp.clear();
    }

    unsigned long size() const override{
        return _imp.size();
    }

    bool contains(const K & k) const override{
        return _imp.find(k) != _imp.end();
    }

    bool set(const K & k, const V & v) override {
        auto p = _imp.insert_or_assign(k, v);
        return p.second;
    }

    V& get(const K & k) override{
        return _imp.at(k); // throw exeception if k not in imp
    }

    /*
     * N0te:
        assert(false == hash->contains("no_exist_key"));
        hash->getRef("no_exist_key");
        assert(true == hash->contains("no_exist_key"));

     * */
    V& getRef(const K & k) override{
        return _imp[k];
    }

private:
    JCX_NO_COPY_CTORS(HashMap);
    typedef typename std::unordered_map<K,V> HashMapImp;
    HashMapImp _imp;
};


template<typename T> using HashMapForPtr = HashMap<std::string, T*>;
template<typename T> using IMapForPtr = IMap<std::string, T*>;

}   //namespace base
}   //namespace jcx

#endif   /* HASHMAP_H */

