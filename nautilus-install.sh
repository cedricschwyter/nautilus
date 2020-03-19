#!/bin/bash
echo "Thank you for choosing to install nautilus created by D3PSI!"
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
else
    build=true
    while [ "$1" != "" ]; do
        case $1 in
            --no-build )            shift
                                    build=false
                                    ;;
        esac
        shift
    done
    arch=$(uname -m)
    kernel=$(uname -r)
    declare -A osInfo;
    osInfo[/etc/redhat-release]=yum
    osInfo[/etc/arch-release]=pacman
    osInfo[/etc/gentoo-release]=emerge
    osInfo[/etc/SuSE-release]=zypp
    osInfo[/etc/debian_version]=apt
    docker=false
    if [ -f /.dockerenv ]; then
        echo "Running inside docker contained environment";
        docker=true
    else
        echo "Running standalone";
    fi
    sessiontype=$(echo ${XDG_SESSION_TYPE})
    for f in ${!osInfo[@]}; do
        if [[ -f $f ]]; then
            echo "Found package manager: ${osInfo[$f]}."
            pkgman=${osInfo[$f]}
        fi
    done
    if [[ -n "$(command -v lsb_release)" ]]; then
        distroname=$(lsb_release -s -d)
    elif [[ -f "/etc/os-release" ]]; then
        distroname=$(grep PRETTY_NAME /etc/os-release | sed 's/PRETTY_NAME=//g' | tr -d '="')
    elif [[ -f "/etc/debian_version" ]]; then
        distroname="Debian $(cat /etc/debian_version)"
    elif [[ -f "/etc/redhat-release" ]]; then
        distroname=$(cat /etc/redhat-release)
    else
        distroname="$(uname -s) $(uname -r)"
    fi
    if [ ${sessiontype}==x11 ]; then
        session=x11
    elif [ ${sessiontype}==gnome-wayland ]; then
        session=wayland
    fi
    echo "Trying to install dependencies for ${distroname} using ${pkgman} on ${session}."
    if [[ ${pkgman} == yum ]]; then
        if yum -y update && yum -y install git cmake make pkgconf-pkg-config gcc g++ glm-devel glfw glfw-devel assimp assimp-devel SDL2 SDL2-devel SDL2_image SDL2_image-devel mesa-libGL-devel boost boost-system boost-devel boost-filesystem; then
            echo "Successfully installed dependencies for your system." 
        else
            echo "Failed to install some dependencies!"
            echo "Going full kamikaze. Hoping relevant dependencies (git, cmake, make, pkg-config g++/clang++ (or any other C++17-capable compiler)) 
                and necessary libraries are installed or included in the repository in this case. Good luck!"
        fi
    elif [[ ${pkgman} == pacman ]]; then
        if pacman -Syu --noconfirm && pacman -Sy --noconfirm git cmake make pkg-config gcc gdb glm glfw-${session} assimp sdl2 sdl2_image boost boost-libs; then
            echo "Successfully installed dependencies for your system." 
        else
            echo "Failed to install some dependencies!"
            echo "Going full kamikaze. Hoping relevant dependencies (git, cmake, make, pkg-config g++/clang++ (or any other C++17-capable compiler)) 
                and necessary libraries are installed or included in the repository in this case. Good luck!"
        fi
    elif [[ ${pkgman} == apt ]]; then
        if apt-get -y update && apt-get -y --fix-missing install git cmake make pkg-config gcc g++ gdb libglfw3 libglfw3-dev libglm-dev libassimp-dev assimp-utils libegl1-mesa-dev libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libboost-all-dev; then
            echo "Successfully installed dependencies for your system." 
        else
            echo "Failed to install some dependencies!"
            echo "Going full kamikaze. Hoping relevant dependencies (git, cmake, make, pkg-config g++/clang++ (or any other C++17-capable compiler)) 
                and necessary libraries are installed or included in the repository in this case. Good luck!"
            exit 1
        fi
    else
        echo "No supported package manager found!"
        echo "Going full kamikaze. Hoping relevant dependencies (git, cmake, make, pkg-config g++/clang++ (or any other C++17-capable compiler)) 
            and necessary libraries are installed or included in the repository in this case. Good luck!"
    fi
    git submodule sync
    git submodule update --init --recursive
    if [[ "$build" = true ]]; then
        echo "Generating build files..."
        if cmake CMakeLists.txt; then
            echo "Building project..."
            threads=$(grep -c ^processor /proc/cpuinfo)
            if [[ "$docker" = true ]]; then
                if make; then
                    echo "You can now run the examples which have been built and written to bin/. Enjoy!"
                else
                    echo "Failed to build the project!"
                    exit 1
                fi
            else
                echo "Compiling using $threads threads..."
                if make -j$threads; then
                    echo "You can now run the examples which have been built and written to bin/. Enjoy!"
                else
                    echo "Failed to build the project!"
                    exit 1
                fi
            fi
        else
            echo "Failed to generate build files!"
            exit 1
        fi
    fi
    chown ${SUDO_USER:-${USER}} -R .
    exit 0
fi
