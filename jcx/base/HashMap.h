
#ifndef  JCX_BASE_HASHMAP_H
#define  JCX_BASE_HASHMAP_H


#include <unordered_map>


namespace jcx {
namespace base {


template<typename K, typename V>
class IMap {
public:
    virtual ~IMap(){}

    virtual int insert(const K & k,  const V & v) = 0;
    virtual bool insertOrReplace(const K & k, const V & v) = 0;
    virtual void remove(const K & k) = 0;
    virtual void clear() = 0;

    virtual unsigned long size() const = 0;
    virtual bool contains(const K & k) const = 0;

    virtual const V& get(const K & k) const = 0;
    virtual bool set(const K & k, const V & v) = 0;
    virtual V& getRef(const K & k)  = 0 ;
};



template<typename K, typename V>
class HashMap :  public IMap<K, V>{
public:
    HashMap(){}
    virtual ~HashMap(){}

    virtual int insert(const K & k,  const V & v){
        auto it = _imp.find(k);
        if(it == _imp.end()){
            _imp.insert(std::make_pair(k, v));
            return 0;
        }
        return -1;
    }

    virtual bool insertOrReplace(const K & k, const V & v){
        auto p = _imp.insert_or_assign(k, v);
        return p.second;
    }
    virtual void remove(const K & k){
        _imp.erase(k);
    }
    virtual void clear(){
        _imp.clear();
    }

    virtual unsigned long size() const{
        return _imp.size();
    }

    virtual bool contains(const K & k) const{
        return _imp.find(k) != _imp.end();
    }

    virtual bool set(const K & k, const V & v){
        auto p = _imp.insert_or_assign(k, v);
        return p.second;
    }

    bool getValue(const K & k, V & v) const {
        return contains(k) ? (v = get(k), true) : false;
    }

    virtual const V& get(const K & k) const {
        return _imp.at(k); // throw exeception if k not in imp
    }

    /*
     * N0te:
        assert(false == hash->contains("no_exist_key"));
        hash->getRef("no_exist_key");
        assert(true == hash->contains("no_exist_key"));

     * */
    virtual V& getRef(const K & k) {
        return _imp[k];
    }

private:
    //TODO: How to move the Imp into cpp
    typedef typename std::unordered_map<K,V> HashMapImp;
    HashMapImp _imp;
};


typedef HashMap<const char *, void *> HashMapForPtr;
typedef IMap<const char *, void *> IHashMapForPtr;

}   //namespace base
}   //namespace jcx

#endif   /* HASHMAP_H */

