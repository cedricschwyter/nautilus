#ifndef RUBIKS_SHELL_HPP
#define RUBIKS_SHELL_HPP

#include <nautilus/Nautilus.hpp>


namespace rubiks {

    class RubiksShell 
        : public nautilus::NautilusShellOpenGL {
        using nautilus::NautilusShellOpenGL::NautilusShellOpenGL;
    public:

        /**
         * Gets executed when the shell is attached to the core
         */ 
        void onAttach(void); 

        /**
         * Gets executed at the specified frequency to compute rendering operations
         */ 
        void onRender(void);

    private:



    };

}

#endif      // RUBIKS_SHELL_HPP
