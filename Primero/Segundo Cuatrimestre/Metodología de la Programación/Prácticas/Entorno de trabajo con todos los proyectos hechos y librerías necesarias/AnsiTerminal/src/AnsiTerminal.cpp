/**
 * @file AnsiTerminal.cpp
 * @author DECSAI
 * @brief Full functional static library of tools to use a coloured terminal (4 bits per pixel),
 * manage cursor position, resize the terminal window according to standard
 * ANSI escape codes. See https://en.wikipedia.org/wiki/ANSI_escape_code for further details
 * @note Fully i, int options=0mplemented. No further implementation required.
 */
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "AnsiTerminal.h"
#include "datatools.h"

using namespace std;

const int bpp = 10, bmax = (int) pow(2, bpp), base = bmax - 1;
int bg = black, fg = white;

//const string windowFrames = {toISO("┌┐└┘─│┬┴┼┤├▄"), "++++-|", "▁▂▃▄▅▆▇█", "▏▎▍▌▋▊▉█"};
//const string windowFrames = "┌┐└┘─│┬┴┼┤├▄";
const string windowFrames[][11] = {
    {"┌", "┐", "└", "┘", "─", "│", "┬", "┴", "┼", "┤", "├"},
    {"+", "+", "+", "+", "-", "|", "+", "+", "+", "+", "+"}
};

const string VBARS[] = {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"};
const string HBARS[] = {" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"};
const string ESC = "\033", EMPTY = "";

/**
 * Encodes a RGB color as an integer value with 4 bits per pixel. Each RGB
 * value is specified as a real number in the range from 0 (darker) to 1
 * (brighter).
 *
 * @param r Red value
 * @param g Green Value
 * @param b Blue Value
 * @return An integer value which can be used to reference the color Since
 * only 4 bpp are used, that is, 16 possible values for each RGB, rounding
 * differences might appear.
 */
int defColor(double r, double g, double b) {
    int ir = (int) (r * base) % bmax,
            ig = (int) (g * base) % bmax,
            ib = (int) (b * base) % bmax;
    int res = ir + (ig << bpp) + (ib << (2 * bpp));
    return res;
}

int negColor(double r, double g, double b) {
    return defColor((1 - r) * (1 - r), (1 - g) * (1 - g), (1 - b) * (1 - b));
}

int negColor(int color) {
    return defColor(1 - getRed(color), 1 - getGreen(color), 1 - getBlue(color));
}

double getRed(int color) {
    return (color & base)*1.0 / base;
}

double getGreen(int color) {
    return ((color & (base << bpp)) >> bpp)*1.0 / base;
}

double getBlue(int color) {
    return ((color & (base << (2 * bpp)))>>(2 * bpp))*1.0 / base;
}

string defBackground(int color) {
    //    bg=color;
    int r = (int) (255 * getRed(color)),
            g = (int) (255 * getGreen(color)),
            b = (int) (255 * getBlue(color));
    string s = (string) "[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    s = ESC + s;
    return s;
}

int darker(int color) {
    double coef = 4;
    double r = getRed(color), g = getGreen(color), b = getBlue(color);
    r = r - 1.0 / coef;
    b = b - 1.0 / coef;
    g = g - 1.0 / coef;
    return defColor(r, g, b);
}

int brighter(int color) {
    double coef = 4;
    double r = getRed(color), g = getGreen(color), b = getBlue(color);
    r = r + 1.0 / coef;
    b = b + 1.0 / coef;
    g = g + 1.0 / coef;
    return defColor(r, g, b);
}

AnsiTerminal::AnsiTerminal(int w, int h) {
    _sos << "";
    _width = w;
    _height = h;
    main_t = defColor(0.75, 0.75, 0.75);
    main_b = defColor(0.3, 0.3, 0.3);
    canv_b = defColor(1, 1, 1);
    canv_t = defColor(0, 0, 0);
    //    pal[0] = defColor(0.33, 0.0, 0.0);
    //    pal[1] = defColor(0.0, 0.33, 0.0);
    //    pal[2] = defColor(0.33, 0.33, 0.0);
    //    pal[3] = defColor(0.0, 0.0, 0.33);
    //    pal[4] = defColor(0.33, 0.00, 0.33);
    //    pal[5] = defColor(0.0, 0.33, 0.33);
    //    pal[6] = defColor(0.66, 0.33, 0.33);
    //    pal[7] = defColor(0.33, 0.66, 0.33);
    //    pal[8] = defColor(0.66, 0.66, 0.33);
    //    pal[9] = defColor(0.33, 0.33, 0.66);
    //    pal[10] = defColor(0.66, 0.33, 0.66);
    //    pal[11] = defColor(0.33, 0.66, 0.66);
    //    pal[12] = defColor(1, 0.66, 0.66);
    //    pal[13] = defColor(0.66, 1.0, 0.66);
    //    pal[14] = defColor(0.66, 0.66, 1.0);

    pal[14] = defColor(0.33, 0.0, 0.0);
    pal[13] = defColor(0.0, 0.33, 0.0);
    pal[12] = defColor(0.33, 0.33, 0.0);
    pal[11] = defColor(0.0, 0.0, 0.33);
    pal[10] = defColor(0.33, 0.00, 0.33);
    pal[9] = defColor(0.0, 0.33, 0.33);
    pal[8] = defColor(0.66, 0.33, 0.33);
    pal[7] = defColor(0.33, 0.66, 0.33);
    pal[6] = defColor(0.66, 0.66, 0.33);
    pal[5] = defColor(0.33, 0.33, 0.66);
    pal[4] = defColor(0.66, 0.33, 0.66);
    pal[3] = defColor(0.33, 0.66, 0.66);
    pal[2] = defColor(1, 0.66, 0.66);
    pal[1] = defColor(0.66, 1.0, 0.66);
    pal[0] = defColor(0.66, 0.66, 1.0);
}

bool AnsiTerminal::isOpenWindow() {
    return this->_consoleinputfile != "";
}

AnsiTerminal & AnsiTerminal::openWindow() {
    if (!isOpenWindow()) {
        this->openExternalTerminal("REPORTS", _width, _height, 7);
        setMain().clearScreen();
    }
    return *this;
}

string AnsiTerminal::to_string() {
    string res = _sos.str();
    _sos.flush();
    return res;
}

int AnsiTerminal::getText() {
    return fg;
}

int AnsiTerminal::getBackground() {
    return bg;
}

AnsiTerminal &AnsiTerminal::setCursorXY(int x, int y) {
    print(ESC + "[" + std::to_string(y) + ";" + std::to_string(x) + "f");
    return *this;
}

AnsiTerminal &AnsiTerminal::clearScreen() {
    print(ESC + "[2J");
    setCursorXY(1, 1);
    return *this;
}

AnsiTerminal &AnsiTerminal::setBackground(int color) {
    bg = color;
    int r = (int) (255 * getRed(color)),
            g = (int) (255 * getGreen(color)),
            b = (int) (255 * getBlue(color));
    string s = "[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    print(ESC + s);
    return *this;
}

AnsiTerminal &AnsiTerminal::setText(int color) {
    fg = color;
    int r = (int) (255 * getRed(color)),
            g = (int) (255 * getGreen(color)),
            b = (int) (255 * getBlue(color));
    string s = "[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    print(ESC + s);
    return *this;
}

AnsiTerminal &AnsiTerminal::setCursorOn() {
    print(ESC + "[?25h");
    return *this;
}

AnsiTerminal &AnsiTerminal::setCursorOff() {
    print(ESC + "[?25l");
    return *this;
}

AnsiTerminal &AnsiTerminal::print(string s) {
    _out.open(_tty);
    _out << s;
    _out.close();
    //_sos << s;
    return *this;
}

AnsiTerminal &AnsiTerminal::println(string s) {
    print(s).print("\n");
    return *this;
}

AnsiTerminal &AnsiTerminal::doRectangle(int x, int y, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            setCursorXY(x + i, y + j);
            print(" ");
        }
    }
    return *this;
}

AnsiTerminal &AnsiTerminal::doRectangleFrame(int x, int y, int w, int h) {
    doRectangle(x, y, w, h);
    doFrame(x, y, x + w - 1, y + h - 1);
    return *this;
}

AnsiTerminal &AnsiTerminal::doFrame(int x, int y, int x2, int y2) {
    for (int i = y; i <= y2; i++) {
        setCursorXY(x, i);
        print(EMPTY + windowFrames[0][5]);
        setCursorXY(x2, i);
        print(EMPTY + windowFrames[0][5]);
    }
    for (int j = x; j <= x2; j++) {
        setCursorXY(j, y);
        print(EMPTY + windowFrames[0][4]);
        setCursorXY(j, y2);
        print(EMPTY + windowFrames[0][4]);
    }

    setCursorXY(x, y);
    print(EMPTY + windowFrames[0][0]);
    setCursorXY(x2, y);
    print(EMPTY + windowFrames[0][1]);
    setCursorXY(x, y2);
    print(EMPTY + windowFrames[0][2]);
    setCursorXY(x2, y2);
    print(EMPTY + windowFrames[0][3]);

    return *this;
}

AnsiTerminal &AnsiTerminal::doGrid(int x, int y, int x2, int y2) {
    for (int i = y; i <= y2; i++) {
        setCursorXY(x, i);
        print("" + windowFrames[0][5]);
        setCursorXY(x2, i);
        print("" + windowFrames[0][5]);
    }
    for (int j = x; j <= x2; j++) {
        setCursorXY(j, y);
        print("" + windowFrames[0][4]);
        setCursorXY(j, y2);
        print("" + windowFrames[0][4]);
    }
    setCursorXY(x, y);
    print("" + windowFrames[0][8]);
    setCursorXY(x2, y);
    print("" + windowFrames[0][8]);
    setCursorXY(x, y2);
    print("" + windowFrames[0][8]);
    setCursorXY(x2, y2);
    print("" + windowFrames[0][8]);
    return *this;
}

AnsiTerminal &AnsiTerminal::doFrameTitle(string title, int x, int y, int w, int h) {
    doFrame(x, y, x + w - 1, y + h - 1);
    if (title.length() > 0) {
        setCursorXY(x + 1, y);
        print(windowFrames[0][9] + " ").setText(brighter(main_t)).print(trim(title, w - 4)).
                setMain().print(" " + windowFrames[0][10]);
    }
    return *this;
}

AnsiTerminal &AnsiTerminal::printHRulerTop(int x, int y, int width, int skip, int valmax) {
    int threshold = 0, each = (skip < 0 ? -skip : skip);
    for (int i = 0; i <= width; i++) {
        setCursorXY(i + x, y + 1);
        if ((i * valmax / width) >= threshold || i == width) {
            threshold += each;
            if (i == 0) {
                print("" + windowFrames[0][8]);
            } else if (i == width) {
                print("" + windowFrames[0][7]);
            } else {
                print("" + windowFrames[0][7]);
            }
            if (skip > 0) {
                setCursorXY(i + x, y);
                print("" + (int) ((i * valmax) / width));
            }
        } else {
            print("" + windowFrames[0][4]);
        }

    }
    return *this;
}

double AnsiTerminal::printHRuler(int x, int y, int width, int valmax, int skip) {
    double counter = 0, threshold = 0;
    double each = (valmax * 1.0 / (width - 1));
    int eachskip = std::round(skip / each);
    for (int i = 0; i <= width; i++) {
        setCursorXY(i + x, y + 1);
        if (i % eachskip == 0) {
            if (i == 0) {
                print("" + windowFrames[0][8]);
            } else if (i == width) {
                print("" + windowFrames[0][6]);
            } else {
                print("" + windowFrames[0][6]);
            }
            setCursorXY(x + i, y + 2);
            string f = (string) "%-" + STR(ANSI_FIELD_LENGTH - 1) + ".0f";
            print(format(f, threshold));
            threshold += skip;
        } else {
            print("" + windowFrames[0][4]);
        }
        counter = std::round(counter + each);

    }
    return each;
}

double AnsiTerminal::printVRuler(int x, int y, int height, double valmax, int skip) {
    double counter = 0, threshold = 0;
    double each = (valmax / (height - 1));
    int eachskip = std::round(skip / each);
    for (int i = 0; i <= height; i++) {
        setCursorXY(x, y + height - i);
        if (i % eachskip == 0) {
            if (i == 0) {
                print("" + windowFrames[0][8]);
            } else if (i == height) {
                print("" + windowFrames[0][1]);
            } else {
                print("" + windowFrames[0][9]);
            }
            setCursorXY(x - ANSI_FIELD_LENGTH, y + height - i);
            string f = (string) "%" + STR(ANSI_FIELD_LENGTH - 1) + ".0f";
            print(format(f, threshold));
            threshold += skip;
        } else {
            print("" + windowFrames[0][5]);
        }
        counter = std::round(counter + each);
    }
    return each;
}

double AnsiTerminal::printVRuler(int x, int y, int height, int valmax, string labels[]) {
    int each = 1; //(int) std::round((height - 1)*1.0 / valmax);
    for (int i = 0; i <= height; i++) {
        setCursorXY(x, y + height - i);
        if (i % each == 0 && i / each < valmax) {
            if (i == 0) {
                print("" + windowFrames[0][8]);
            } else if (i == height) {
                print("" + windowFrames[0][5]);
            } else {
                print("" + windowFrames[0][9]);
                setCursorXY(x - ANSI_FIELD_LENGTH, y + height - i);
                print(trim(labels[(i - 1) / each], ANSI_FIELD_LENGTH));
            }
        } else {
            print("" + windowFrames[0][5]);
        }

    }
    return each;
}

double AnsiTerminal::printHRuler(int x, int y, int width, int valmax, string labels[]) {
    int each = (int) std::round((width - 1)*1.0 / valmax);
    for (int i = 0; i <= width; i++) {
        setCursorXY(i + x, y + 1);
        if (i % each == 0 && i / each < valmax) {
            if (i == 0) {
                print("" + windowFrames[0][8]);
            } else if (i == width) {
                print("" + windowFrames[0][6]);
            } else {
                print("" + windowFrames[0][6]);
                setCursorXY(x + i - each + 2, y + 2);
                string f = (string) "%" + STR(each - 1) + "s";
                print(format(f, trim(labels[(i - 1) / each], each - 1)));
            }
        } else {
            print("" + windowFrames[0][4]);
        }

    }
    return each;
}

AnsiTerminal &AnsiTerminal::printMinibarV(int x, int y, int height, double valmax, double level) {
    int front = getText(), back = getBackground();
    level = level * (height * 9) / valmax;
    int bx = x, by = y;
    while (level > 0) {
        setCursorXY(bx, by);
        if (level >= 9) {
            setBackground(front);
            print(VBARS[8]);
            by--;
        } else {
            setBackground(back);
            print("" + VBARS[(int) level % 9]);
        }
        level = level - 9;
    }
}

AnsiTerminal &AnsiTerminal::printMinibarH(int x, int y, int width, double valmax, double level) {
    int front = getText(), back = getBackground();
    level = (int) (9 * level * width * 1.0 / valmax);
    int bx = x, by = y;
    double d = 0;
    while (level > 0) {
        setCursorXY(bx, by);
        if (level >= 9) {
            setBackground(front);
            d += 1 * valmax / (width + 9);
            print(VBARS[8]);
            bx++;
        } else {
            setBackground(back);
            print("" + HBARS[(int) level % 9]);
        }
        level = level - 9;
    }
}

AnsiTerminal &AnsiTerminal::printMiniSpectrumH(int x, int y, int width, double valmax, double level) {
    int front = getText(), back = getBackground();
    double r, g;
    int maxlocallevel = 9 * width, locallevel = (int) (level * maxlocallevel * 1.0 / valmax), icolor = 0;
    int bx = x, by = y, color;
    double d = 0, base = 10;
    while (locallevel > 0) {
        setCursorXY(bx, by);
        r = (icolor + base)*1.0 / (maxlocallevel + base);
        g = 1 - r;
        color = defColor(g, r, 0);
        setText(color);
        if (locallevel >= 9) {
            setBackground(color);
            d += 1 * valmax / (width + 9);
            print(VBARS[8]);
            bx++;
        } else {
            setBackground(back);
            print("" + HBARS[(int) locallevel % 9]);
        }
        locallevel = locallevel - 9;
        icolor += 9;
    }
}

AnsiTerminal &AnsiTerminal::printMiniSpectrumV(int x, int y, int height, double valmax, double level) {
    int front = getText(), back = getBackground();
    double r, g, d, base = 10;
    int maxlocallevel = 9 * height, locallevel = (int) (level * maxlocallevel * 1.0 / valmax), icolor = 0;
    int bx = x, by = y, color;
    while (locallevel > 0) {
        setCursorXY(bx, by);
        r = (icolor + base)*1.0 / (maxlocallevel + base);
        g = 1 - r;
        color = defColor(g, r, 0);
        setText(color);
        if (locallevel >= 9) {
            setBackground(color);
            d += 1 * valmax / (height + 9);
            print(VBARS[8]);
            by--;
        } else {
            setBackground(back);
            print("" + VBARS[(int) level % 9]);
        }
        locallevel = locallevel - 9;
    }
}

AnsiTerminal &AnsiTerminal::pressReturn(string msg) {
    string aux;
    if (msg == "")
        msg = "PRESIONA RETURN PARA CONTINUAR";
    setCursorXY(1, this->_height-2).setBackground(green).
            print(format("%-25s", msg));
    getline(_in, aux);
    setCursorXY(1, this->_height-2).setBackground(black).
            print(format("%-25s", "                                                                  "));
    return *this;
}

bool AnsiTerminal::doConfirm(string msg) {
    string aux;
    if (msg == "")
        msg = "Presiona [INTRO] para continuar";
    setBackground(green).setText(white).print(format("%-25s", msg+"          "));
    getline(_in, aux);
    return aux == "";
}


AnsiTerminal &AnsiTerminal::setSize(int r, int c) {
    string command = "resize -s " + std::to_string(r) + " " + std::to_string(c);
    //    system(command.c_str());
    return *this;
}

AnsiTerminal & AnsiTerminal::setMain() {
    return setBackground(main_b).setText(main_t);
}

AnsiTerminal & AnsiTerminal::setCanvas() {
    return setBackground(canv_b).setText(canv_t);
}

AnsiTerminal & AnsiTerminal::setSerie(int s) {
    return setBackground(pal[s % 15]).setText(pal[s % 15]);
}

void AnsiTerminal::openExternalTerminal(string title, int columns, int rows, int fontsize) {
    bool readtty = false;
    _consoleinputfile = trim(title, 8) + ".tty";
    _height = rows;
    _width = columns;
    ifstream filetty;

    filetty.open(_consoleinputfile);
    if (filetty) {
        filetty.close();
        remove(_consoleinputfile.c_str());
    }
    string command = (string) "xterm " + " -sb " + " -rightbar " + " -title " + title + " -fa " + " fixed " + " -fs " + STR(fontsize) + " -geometry " + STR(_width) + "x" + STR(_height)
            +(string) " -e \"" + " tty  > " + _consoleinputfile + "; while [ true ]; do sleep 1; if [ ! -f " + _consoleinputfile + " ]; then exit; fi; done\" &";
    fp = popen(command.c_str(), "r");

    while (!readtty) {
        filetty.open(_consoleinputfile);
        if (filetty) {
            filetty >> _tty;
            if (_tty != "") {
                _title = title;
                readtty = true;
            }
            filetty.close();
        }
    }
    //pclose(fp);
    _out.open(_tty);
    _in.open(_tty);
}

void AnsiTerminal::close() {
   // setCursorXY(1, _height - 1).setText(white).setBackground(lightred).print("   RETURN TO CLOSE  ");
    string c;
    //getline(cin, c);
    pclose(fp);
    remove(_consoleinputfile.c_str());
}