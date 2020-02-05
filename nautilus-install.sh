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
            echo "Failed to install dependencies!"
            exit 1
        fi
    elif [[ ${pkgman} == pacman ]]; then
        if pacman -Syu --noconfirm && pacman -Sy --noconfirm git cmake make pkg-config gcc gdb glm glfw-${session} assimp sdl2 sdl2_image boost boost-libs; then
            echo "Successfully installed dependencies for your system." 
        else
            echo "Failed to install dependencies!"
            exit 1
        fi
    elif [[ ${pkgman} == apt ]]; then
        if apt-get -y update && apt-get -y --fix-missing install git cmake make pkg-config gcc g++ gdb libglfw3 libglfw3-dev libglm-dev libassimp-dev assimp-utils libegl1-mesa-dev libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libboost-all-dev; then
            echo "Successfully installed dependencies for your system." 
        else
            echo "Failed to install dependencies!"
            exit 1
        fi
    else
        echo "No supported package manager found!"
        exit 1
    fi
    if [[ "$build" = true ]]; then
        git clone https://github.com/D3PSI/nautilus.git
        cd nautilus/
        echo "Generating build files..."
        if cmake CMakeLists.txt; then
            echo "Building project..."
            if make; then
                /bin/cp -Rf "bin/linux/x64/nautilus" "nautilus"
            else
                echo "Failed to build the project!"
                exit 1
            echo "Creating shortcuts..."
            if mkdir -p /usr/bin/nautilus; then
                /bin/cp -Rf res/ nautilus Nautilus\ by\ D3PSI.desktop /usr/bin/nautilus/
                ln -s -f /usr/bin/nautilus/Nautilus\ by\ D3PSI.desktop /usr/share/applications/Nautilus\ by\ D3PSI.desktop
                echo "Successfully installed shortcuts"
            else
                echo "Failed to install shortcuts!"
                exit
            fi
            fi
        else
            echo "Failed to generate build files!"
            exit 1
        fi
    fi
    exit 0
fi
