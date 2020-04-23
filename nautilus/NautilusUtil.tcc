#ifndef NAUTILUS_UTIL_TCC
#define NAUTILUS_UTIL_TCC

#include <vector>
#include <future>
#include <stdint.h>

namespace nautilus {

    namespace util {

        template< template< typename, typename > typename _Titer, typename _T >
        std::pair< bool, int32_t > getIndexOfElement(const _Titer< _T , std::allocator< _T > >& _container, const _T& _element) {
            std::pair< bool, int32_t > result;
            auto it = std::find(_container.begin(), _container.end(), _element);
            if(it != _container.end()) {
                result.first = true;
                result.second = std::distance(_container.begin(), it);
            } else {
                result.first = false;
                result.second = -1;
            }
            return result;
        }

        template< template< typename, typename > typename _Titer, typename _T >
        std::pair< bool, int32_t > getIndexOfElement(const _Titer< _T* , std::allocator< _T* > >& _container, const _T*& _element) {
            std::pair< bool, int32_t > result;
            auto it = std::find(_container.begin(), _container.end(), _element);
            if(it != _container.end()) {
                result.first = true;
                result.second = std::distance(_container.begin(), it);
            } else {
                result.first = false;
                result.second = -1;
            }
            return result;
        }

    }

}

#endif      // NAUTILUS_UTIL_TCC