#include "stringInput.hpp"

StringInput::StringInput(const String &st) : str(st), offset(0) {
}

long StringInput::getSize() {
    return str.length();
}

int StringInput::seek(long sval) {
    set(offset + sval);
}

int StringInput::set(long sval) {
    offset = sval;

    if(offset >= str.length())
        offset = str.length();

    if(offset < 0)
        offset = 0;
}

int StringInput::rset(long sval) {
    set(str.length() - sval);
}

long StringInput::tell() {
    return offset;
}

int StringInput::get() {
    int c = str.charAt(offset);
    offset++;
    return c;
}

int StringInput::peek(int ahead) {
    if(offset + ahead > str.length()) return 0;
    return str.charAt(offset + ahead);
}

long StringInput::read(void *buf, long sz, long nmemb) {
    int read = str.copy((char*) buf, sz * nmemb, offset);
    offset += read;
    return read;
}

bool StringInput::eof() {
    return offset >= str.length();
}

String StringInput::getName() const {
    return String("");
}
