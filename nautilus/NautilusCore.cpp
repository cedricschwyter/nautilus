#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"

NautilusCore::NautilusCore() {

}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    _shell->onAttach();
    return NAUTILUS_OK;
}

NautilusCore::~NautilusCore() {
    
}

#endif      // NAUTILUS_CORE_CPP