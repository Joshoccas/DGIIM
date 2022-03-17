/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include "datatools.h"
using namespace std;
string trim(string s, int max) {
    return s.substr(0, MIN(max, s.length()));
}

string format(string f, int v) {
    char aux[1000];
    sprintf(aux, f.c_str(), v);
    return aux;
}

string format(string f, double v) {
    char aux[1000];
    sprintf(aux, f.c_str(), v);
    return aux;
}

string format(string f, string v) {
    char aux[1000];
    sprintf(aux, f.c_str(), v.c_str());
    return aux;
}


bool is_utf8(const char * string) {
    if (!string)
        return false;

    const unsigned char * bytes = (const unsigned char *) string;
    while (*bytes) {
        if ((// ASCII
                // use bytes[0] <= 0x7F to allow ASCII control characters
                bytes[0] == 0x09 ||
                bytes[0] == 0x0A ||
                bytes[0] == 0x0D ||
                (0x20 <= bytes[0] && bytes[0] <= 0x7E)
                )
                ) {
            bytes += 1;
            continue;
        }

        if ((// non-overlong 2-byte
                (0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
                (0x80 <= bytes[1] && bytes[1] <= 0xBF)
                )
                ) {
            bytes += 2;
            continue;
        }

        if ((// excluding overlongs
                bytes[0] == 0xE0 &&
                (0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                ) ||
                (// straight 3-byte
                ((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
                bytes[0] == 0xEE ||
                bytes[0] == 0xEF) &&
                (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                ) ||
                (// excluding surrogates
                bytes[0] == 0xED &&
                (0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF)
                )
                ) {
            bytes += 3;
            continue;
        }

        if ((// planes 1-3
                bytes[0] == 0xF0 &&
                (0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                ) ||
                (// planes 4-15
                (0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
                (0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                ) ||
                (// plane 16
                bytes[0] == 0xF4 &&
                (0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
                (0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
                (0x80 <= bytes[3] && bytes[3] <= 0xBF)
                )
                ) {
            bytes += 4;
            continue;
        }

        return false;
    }

    return true;
}

std::string toUTF(std::string in) {
    return toUTF(in.c_str());
}

std::string toUTF(char in) {
    string s = "-";
    s[0] = in;
    return toUTF(s.c_str());
}

std::string toUTF(const char * i) {
    const unsigned char *in = (unsigned char*) i;
    string res = "";
    while (*in)
        if (*in < 128) res.append(1, static_cast<char> (*in++));
        else res.append(1, static_cast<char> (0xc2 + (*in > 0xbf))), res.append(1, static_cast<char> ((*in++&0x3f) + 0x80)); //    string out;
    return res;
}

std::string toISO(std::string in) {
    return toISO(in.c_str());
}

std::string toISO(const char * in) {
    std::string out;
    if (in == NULL)
        return out;
    if (!is_utf8(in))
        return in;
    unsigned int codepoint;
    while (*in != 0) {
        unsigned char ch = static_cast<unsigned char> (*in);
        if (ch <= 0x7f)
            codepoint = ch;
        else if (ch <= 0xbf)
            codepoint = (codepoint << 6) | (ch & 0x3f);
        else if (ch <= 0xdf)
            codepoint = ch & 0x1f;
        else if (ch <= 0xef)
            codepoint = ch & 0x0f;
        else
            codepoint = ch & 0x07;
        ++in;
        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff)) {
            if (codepoint <= 255) {
                out.append(1, static_cast<char> (codepoint));
            } else {
                // do whatever you want for out-of-bounds characters
            }
        }
    }
    return out;
}
