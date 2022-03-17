/**
 * @file AnsiTerminal.h
 * @author DECSAI
 * @brief Full functional static library of tools to use a coloured terminal (4 bits per pixel),
 * manage cursor position, resize the terminal window according to standard
 * ANSI escape codes. See https://en.wikipedia.org/wiki/ANSI_escape_code for further details
 * @note Fully implemented. No further implementation required.
 */
#ifndef ANSITERMINAL_H
#define ANSITERMINAL_H
#include <ios>
#include <fstream>
#include <sstream>

#define ANSI_FIELD_LENGTH 5

/**
 * @brief Encodes a RGB color as an integer value with 4 bits per pixel. 
 * Each RGB value is specified as a real number in the range 
 * from 0 (darker) to 1 (brighter). 
 * @param r Red value
 * @param g Green Value
 * @param b Blue Value
 * @return An integer value which can be used to reference the color
 * @warning Since only 4 bpp are used, that is, 16 possible values for each RGB, rounding differences might appear.
 */
int defColor(double r, double g, double b);

int brighter(int color);
int darker(int color);
int negColor(int color);

/**
 * @brief Given an integer value which encodes a color, it returns 
 * its Red component
 * @param color Encoding a 4bpp RGB color
 * @return A real number in the range from 0 (darker) to 1 (brighter)
 */
double getRed(int color);
/**
 * @brief Given an integer value which encodes a color, it returns 
 * its Green component
 * @param color Encoding a 4bpp RGB color
 * @return A real number in the range from 0 (darker) to 1 (brighter)
 */
double getGreen(int color);
/**
 * @brief Given an integer value which encodes a color, it returns 
 * its Blue component
 * @param color Encoding a 4bpp RGB color
 * @return A real number in the range from 0 (darker) to 1 (brighter)
 */
double getBlue(int color);

const int black = defColor(0, 0, 0),
red = defColor(0.5, 0, 0),
green = defColor(0, 0.5, 0),
brown = defColor(0.5, 0.5, 0),
blue = defColor(0, 0, 0.5),
magenta = defColor(0.5, 0, 0.5),
cyan = defColor(0, 0.5, 0.5),
gray = defColor(0.5, 0.5, 0.5),
lightgray = defColor(0.75, 0.75, 0.75),
lightred = defColor(1, 0, 0),
lightgreen = defColor(0, 1, 0),
yellow = defColor(1, 1, 0),
lightblue = defColor(0, 0, 1),
lightmagenta = defColor(1, 0, 1),
lightcyan = defColor(0, 1, 1),
white = defColor(1, 1, 1),
graphite = defColor(0.3, 0.3, 0.3);

//#define PALETTE(X) (x == PAL_REGULAR ? _paletteR : paletteBW);
//
//#define C_MAIN_T 0
//#define C_MAIN_B 1
//#define C_CANVAS_T 2
//#define C_CANVAS_B 3
//#define C_COLOR_1 4
//#define C_COLOR_2 (C_COLOR_1+1)
//#define C_COLOR_3 (C_COLOR_1+2)
//#define C_COLOR_4 (C_COLOR_1+3)
//#define C_COLOR_5 (C_COLOR_1+4)
//#define C_COLOR_6 (C_COLOR_1+5)
//#define C_COLOR_7 (C_COLOR_1+6)
//#define C_COLOR_8 (C_COLOR_1+7)
//#define C_COLOR_9 (C_COLOR_1+8)
//#define C_COLOR_10 (C_COLOR_1+9)
//#define C_COLOR_11 (C_COLOR_1+10)
//#define C_COLOR_12 (C_COLOR_1+11)
//#define C_COLOR_13 (C_COLOR_1+12)
//#define C_COLOR_14 (C_COLOR_1+13)
//#define C_COLOR_15 (C_COLOR_1+14)

//const    int _paletteR[]={black,graphite,black,white,/**/defColor(0.33,0.0,0.0),defColor(0.0,0.33,0.0),defColor(0.33,0.33,0.0),defColor(0.0,0.0,0.33),defColor(0.33,0.33,0.33),defColor(0.66,0.0,0.0),defColor(0.0,0.66,0.0),defColor(0.66,0.66,0.0),defColor(0.0,0.0,0.66),defColor(0.66,0.66,0.66),defColor(1.0,0.0,0.0),defColor(0.0,1.0,0.0),defColor(1.0,1.0,0.0),defColor(1.0,0.0,1.0),defColor(1.0,1.0,1.0)};
//    int _paletteBW[]={white,black,graphite,white,black,/**/defColor(0.33,0.0,0.0),defColor(0.0,0.33,0.0),defColor(0.33,0.33,0.0),defColor(0.0,0.0,0.33),defColor(0.33,0.33,0.33),defColor(0.66,0.0,0.0),defColor(0.0,0.66,0.0),defColor(0.66,0.66,0.0),defColor(0.0,0.0,0.66),defColor(0.66,0.66,0.66),defColor(1.0,0.0,0.0),defColor(0.0,1.0,0.0),defColor(1.0,1.0,0.0),defColor(1.0,0.0,1.0),defColor(1.0,1.0,1.0)};

class AnsiTerminal {
public:
    int _bgconsole = -1, _fgconsole = -1, _defbg = -1, _deftext = -1, _cursorx = 1, _cursory = 1,
            _width, _height, _palette;
    int main_t, main_b, canv_t, canv_b, pal[15];
    std::string _title, _consoleinputfile="", _tty;
    std::ofstream _out;
    std::ifstream _in;
    std::stringstream _sos;
    FILE *fp;


    AnsiTerminal(int w, int h);
    
    std::istream & getTTY() { return _in;}

    bool isOpenWindow();
    AnsiTerminal & openWindow();
    /**
     * @brief Returns the current color of text as an encoded color (4 bpp)
     * @return An integer that encodes the RGB color with 4 bits per pixel
     */
    int getText();
    /**
     * @brief Returns the current color of the background as an encoded color (4 bpp)
     * @return An integer that encodes the RGB color with 4 bits per pixel
     */
    int getBackground();
    /**
     * @brief Defines the color of the background
     * @param color To be assigned to the background of the terminal
     */
    AnsiTerminal &setBackground(int color);
    /**
     * @brief Defines the color of the text in the terminal
     * @param color The color to be assigned to the text
     */
    AnsiTerminal &setText(int color);
    /**
     * @brief Clears the screen with the existing background color.
     */
    AnsiTerminal &clearScreen();
    /**
     * @brief Locates the cursor, and therfore any further cout operation, 
     * in a position of the screen of the terminal given by @p x and @p y
     * @param x Horizontal coordinate from top-left corner, which is x=1
     * @param y vertical coordinate from top-left corner, which is y=1
     */
    AnsiTerminal &setCursorXY(int x, int y);
    /**
     * @brief Shows the cursor in the screen
     */
    AnsiTerminal &setCursorOn();
    /**
     * @brief Hides the cursor in the screen
     */
    AnsiTerminal &setCursorOff();

    AnsiTerminal &print(std::string s);

    AnsiTerminal &println(std::string s);

    /**
     * @brief Fills a rectangle in the screen
     * @param x Top ledt
     * @param y Top left
     * @param w Width of the rectangle, specified as text-columns in the terminal
     * @param h Height of the rectangle, specified as text-rows in the terminal
     * @param color Filling color
     */
    AnsiTerminal &doRectangle(int x, int y, int w, int h);

    AnsiTerminal &doRectangleFrame(int x, int y, int w, int h);

    AnsiTerminal &doFrame(int x, int y, int x2, int y2);

    AnsiTerminal &doGrid(int x, int y, int x2, int y2);

    AnsiTerminal &doFrameTitle(std::string title, int x, int y, int w, int h);

    AnsiTerminal &printHRulerTop(int x, int y, int width, int each, int valmax);
    double printHRuler(int x, int y, int width, int valmax, std::string []);
    double printHRuler(int x, int y, int width, int valmax, int skip);
    double printVRuler(int x, int y, int height, int valmax, std::string []);
    double printVRuler(int x, int y, int height, double valmax, int skip);
    AnsiTerminal & printMinibarV(int x, int y, int height, double valmax, double level);
    AnsiTerminal & printMinibarH(int x, int y, int width, double valmax, double level);
    AnsiTerminal & printMiniSpectrumH(int x, int y, int width, double valmax, double level);
    AnsiTerminal & printMiniSpectrumV(int x, int y, int height, double valmax, double level);



    /**
     * @brief Waits until RETURN is pressed and does not leave any trail
     * in cin
     */
    AnsiTerminal &pressReturn(std::string message="");
    
    bool doConfirm(std::string msg);
    
    /**
     * @brief Fixes the size of the terminal 
     * @param r Number of rows
     * @param c Number of columns
     */
    AnsiTerminal &setSize(int r, int c);

    std::string to_string();

    AnsiTerminal & setMain();
    AnsiTerminal & setCanvas();
    AnsiTerminal & setSerie(int s);
    void openExternalTerminal(std::string title, int columns, int rows, int fontsize);
    void close();

};



#endif /* ANSITERMINAL_H */

