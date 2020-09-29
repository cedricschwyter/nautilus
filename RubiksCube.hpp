#ifndef RUBIKS_CUBE_HPP
#define RUBIKS_CUBE_HPP


namespace rubiks {

    class RubiksCube {
    public:

        /**
         * Constructor with arguments
         * @param _sidelength The sidelength of the cube in blocks
         */
        RubiksCube(int _sidelength = 3);

        /**
         * Constructor with arguments
         * @param _width The width of the cube in blocks
         * @param _height The height of the cube in blocks
         * @param _depth The depth of the cube in blocks
         */
        RubiksCube(int _width = 3, int _height = 3, int _depth = 3);

        /**
         * Scrambles the rubiks cube with the desired amount of moves
         * @param _moves The amount of moves to scramble the rubiks cube with
         */ 
        void scramble(int _moves = 100);

        /**
         * Turns a cube face
         */ 
        void turn(void);

        /**
         * Returns true if the cube is solved
         * @return Returns true if the cube is solved
         */ 
        bool isSolved(void);

        /**
         * Default destructor
         */ 
        ~RubiksCube(void);

    private:

        bool m_solved               = true;
        int  m_sidelength           = 0;
        int  m_width                = 0;
        int  m_height               = 0;
        int  m_depth                = 0;

    };

}


#endif      // RUBIKS_CUBE_HPP
