#ifndef  JCX_BASE_ITERATOR_H
#define  JCX_BASE_ITERATOR_H

namespace jcx {
namespace base {
/* 
 *  iterator pattern adapter for stl container
 * e.g. :
 *      class X {
 *      public:
 *          Iterator<Container> getIteartor(){
 *              return Iterator<Container>(_c.begin(), _c.end());
 *          }
 *      private:
 *          typedef std::vector<int *> Container;
 *          Container _c;
 *      };
 *      
 *      X x; 
 *      auto it = x.getIteartor();
 *      while(it.hasNext()){
 *          int* ptrInt = it.next();
 *          cout << *ptrInt << std::endl;
 *      }
 *
 * Advanced use: TODO: need test code
 * not just only for stl container 
 * adapter to all container  with this concept as follow: 
 *      template<typename T> 
 *      typedef Container {
 *          typedef T value_type;  //OK
 *          typedef _Iterator<Container> iterator; //OK
 *
 *          template<typename  Container>
 *          class _Iterator< {
 *              Iterator & operator ++(); //OK
 *              typename Container::value_type & operator *(); //OK
 *          };
 *      }
 */
template<typename C>
class Iterator {
public:
    Iterator(const typename C::iterator & begin, const typename C::iterator & end)
    : _it(begin)
    , _end(end)
    {
    }
    virtual ~Iterator(){
    }

    bool hasNext() {
        return _it != _end;
    }
    
    typename C::value_type next(){
        typename C::value_type  v = *_it;
        ++_it;
        return v;
    }

private:
    Iterator();
    typename C::iterator _it;
    const typename C::iterator _end;
};

}   //namespace base
}   //namespace jcx

#endif   /* JCX_BASE_ITERATOR_H */
