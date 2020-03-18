# nautilus

![Nautilus Icon](https://github.com/D3PSI/nautilus/blob/master/res/images/icons/nautilus.png)

[![Build Status](https://travis-ci.com/D3PSI/nautilus.svg?branch=master)](https://travis-ci.com/D3PSI/nautilus)
[![C/C++ CI](https://github.com/D3PSI/nautilus/workflows/C/C++%20CI/badge.svg)](https://github.com/D3PSI/nautilus/actions?query=workflow%3A"C%2FC%2B%2B+CI")
[![Build status](https://ci.appveyor.com/api/projects/status/6cp2udvipkuchs42/branch/master?svg=true)](https://ci.appveyor.com/project/D3PSI/nautilus/branch/master)
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

You must have the Vulkan SDK installed and added to your PATH environment variable on Windows systems for the installation process to work. CMake will not find Vulkan otherwise.

The project further depends on libraries like GLFW, SDL2, SDL2_image, GLM and IMGUI.

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

Currently and in the near future, there will be no official support for macOS.

## Getting started

Tutorial here.

## Troubleshoot

Troubleshoot instructions here.
