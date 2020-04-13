# nautilus

<link rel="shortcut icon" type="image/x-icon" href="favicon.ico">

[![Build Status](https://travis-ci.com/D3PSI/nautilus.svg?branch=master)](https://travis-ci.com/D3PSI/nautilus)
[![build](https://ci.appveyor.com/api/projects/status/6cp2udvipkuchs42/branch/master?svg=true)](https://ci.appveyor.com/project/D3PSI/nautilus/branch/master)
![Windows C/C++ CI](https://github.com/D3PSI/nautilus/workflows/Windows%20C/C++%20CI/badge.svg)
![Linux C/C++ CI](https://github.com/D3PSI/nautilus/workflows/Linux%20C/C++%20CI/badge.svg)
![macOS C/C++ CI](https://github.com/D3PSI/nautilus/workflows/macOS%20C/C++%20CI/badge.svg)
[![CircleCI](https://circleci.com/gh/D3PSI/nautilus.svg?style=svg)](https://circleci.com/gh/D3PSI/nautilus)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/D3PSI/nautilus/graphs/commit-activity)
[![GitHub issues](https://img.shields.io/github/issues/D3PSI/nautilus.svg)](https://github.com/D3PSI/nautilus/issues/)
[![GitHub issues-closed](https://img.shields.io/github/issues-closed/D3PSI/nautilus.svg)](https://github.com/D3PSI/nautilus/issues?q=is%3Aissue+is%3Aclosed)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](https://github.com/D3PSI/nautilus/compare)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/D3PSI/nautilus.svg)](https://GitHub.com/D3PSI/nautilus/pull/)
[![GitHub pull-requests closed](https://img.shields.io/github/issues-pr-closed/D3PSI/nautilus.svg)](https://GitHub.com/D3PSI/nautilus/pull/)
[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](http://perso.crans.org/besson/LICENSE.html)
[![Awesome Badges](https://img.shields.io/badge/badges-awesome-green.svg)](https://github.com/D3PSI/nautilus)

This repository includes a complete render engine with multiple graphics APIs, including the Khronos APIs OpenGL and Vulkan. It is currently in the construction phase aka. pre-alpha stage.

# Installation

## Dependencies

You must have the Vulkan SDK installed and added to your PATH environment variable on Windows and macOS systems for the installation process to work. CMake will not find Vulkan otherwise.

The project further depends on libraries like ASSIMP, GLFW, GLM, irrklang and IMGUI, which are installed through your systems package manager if possible or compiled with the project itself. They are mostly included in the repository as a submodule, making dependency management really easy. The project is thus fully cross-platform (at least amongst the platforms that support the API's)

## Linux

The project comes with an install script for Linux systems. It offers support for Debian, Fedora and Arch/Manjaro. Download and run the installer:

    git clone https://github.com/D3PSI/nautilus.git
    cd nautilus/
    sudo bash nautilus-install.sh

## Windows

Generate the Visual Studio build files with CMake. Download and install the CMake GUI from [their official website](cmake.org/download). Clone the repository and initialize all submodules by cloning the repository recursively:

    git clone --recursive https://github.com/D3PSI/nautilus.git

Then generate the Visual Studio build files, either via the command line:

    cmake -G "Visual Studio 16 2019" -S nautilus/ -B nautilus/build

or the GUI by specifying the project root directory as the source directory and the `build/` folder in the project root directory as the output directory. Click configure and then generate. If there are any errors, make sure you have all the [dependencies](#dependencies) installed correctly.

Open the generated Visual Studio solution file in Microsoft Visual Studio, change the configuration to Release and the architexture to x64. You should now be able to build and run the examples which can be found in `build/bin/`.

## macOS

For macOS you can also run the integrated installer from the repository after cloning, just like the [Linux installation instructions](#linux) say:

    git clone https://github.com/D3PSI/nautilus.git
    cd nautilus/
    bash nautilus-install.sh

## Getting started

The nautilus-project is a graphics, windowing, sound and physics library with focus to user simplicity. There are various different examples whose source can be found in the `examples` subdirectory of the repository. The library works on a basic concept: The `NautilusCore` object and attachable `NautilusShell` objects.
To create a basic window with your favorite graphics API (OpenGL in the example) create a new derived class from the `NautilusOpenGLShell` (other possibilities include `NautilusVulkanShell`) object and override the required functions `onAttach` and `onRender`: 

    class ExampleShell 
        : public NautilusOpenGLShell {
        using NautilusOpenGLShell::NautilusOpenGLShell;
    public:

        /**
         * Gets executed when the shell is attached to the core
         */
        void onAttach(void) {
            // statements to execute on attachment here
        }

        /**
         * Gets executed at the specified frequency to compute rendering operations
         */
        void onRender(void) {
            // OpenGL rendering statements here
        }

    };

You can then instantiate a `NautilusShell` object from the class implementation you have just written and attach it with optional settings to the `NautilusCore` object:

    NautilusShell*  shell;

    /**
     * Initializes everything
     * @return Returns a nautilus::NautilusStatus status code
     */
    nautilus::NautilusStatus run(void) {
        shell = new ExampleShell();

        shell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        shell->setShellTitle("Dev Example 1");
        shell->setShellExtent(1280, 720);
        shell->setShellIcon("res/images/icons/nautilus.png");
        NautilusCore::attachShell(shell);

        return nautilus::NAUTILUS_STATUS_OK;
    }

A call to `NautilusCore::terminate()` is required before the program exits, as the thread running the application loop is joined then. Otherwise, the application loop will not even get started and you will not see any window or other visual output. The `NautilusCore`-object is implemented as a singleton, meaning there will only ever be one instance of the class which you never have to instantiate (you can just use the functions defined in the class straight-out-of-the-box):

    /**
     * Cleans allocated resources
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus clean(void) {
        NautilusCore::terminate();
        delete shell;
        return nautilus::NAUTILUS_STATUS_OK;
    }

    /**
     * Main entry point for the application
     */
    int main() {
        run();
        clean();
        return nautilus::NAUTILUS_STATUS_OK;
    }

You can create as many different shell objects and derived classes of it, as long as you always write the necessary function implementations. A `NautilusShell` object essentially represents a window containing a graphics context from the chosen graphics API.

### Linking the library

To use the library in your own C++ project is really simple: The only file you have to manually include in your sourcecode is `#include <nautilus/Nautilus.hpp>`. Put the either self-compiled or pre-compiled binary library file (Windows: `nautilus.lib`, Linux: `libnautilus.a`) in the same folder as your `CMakeLists.txt`. In your `CMakeLists.txt` link against the `nautilus` library target and include the necessary include directories (the `include`-subfolder of the repository):

    include_directories("path/to/include")
    target_link_libraries(myProject nautilus)

### Note

At the time of writing this guide, the `nautilus`-library is still a header-only capable library, meaning you do not have to link the binary library file to the project to make it work as long as you link to the `nautilus`-subfolder as the include directory instead of the dedicated `include` directory. The instructions are here for the potential future case of a non-header-only library.

## Troubleshoot

In the worst case scenario, the compilation of the entire project takes about 20 to 30 minutes on a single thread (view continuous integration services for more information). To accelerate the process you can run the compilation on multiple threads:

    make -j<number_of_threads>

where `<number_of_threads>` is at max the amount of supported threads of your CPU. This depends strongly on the manufacturer, whether hyperthreading is supported and other factors. Usually a good number to start is to just input the value 4 as this is supported on a wide variety of systems.
