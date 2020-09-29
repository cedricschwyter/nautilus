#ifndef RUBIKS_CUBE_CPP
#define RUBIKS_CUBE_CPP

#include "RubiksCube.hpp"


namespace rubiks {

    RubiksCube::RubiksCube(int _sidelength) : m_sidelength(_sidelength) {
    }

    RubiksCube::RubiksCube(int _width, int _height, int _depth) 
        : m_width(_width), m_height(_height), m_depth(_depth) {
    }

    void RubiksCube::scramble(int _moves) {
        // TODO: implement lol
    }

    void RubiksCube::turn() {
        // TODO: implement lol
    }

    bool RubiksCube::isSolved() {
        // TODO: query cube state and set the flag variable m_solved accordingly
        return m_solved;
    }

    RubiksCube::~RubiksCube() {
    }

}


#endif      // RUBIKS_CUBE_CPP
