#include <cassert>
#include <utility/string.hpp>

int main(){
    //a-z
    assert(Utility::isCharacter('a') == true);
    assert(Utility::isCharacter('b') == true);
    assert(Utility::isCharacter('c') == true);
    assert(Utility::isCharacter('d') == true);
    assert(Utility::isCharacter('e') == true);
    assert(Utility::isCharacter('f') == true);
    assert(Utility::isCharacter('g') == true);
    assert(Utility::isCharacter('h') == true);
    assert(Utility::isCharacter('i') == true);
    assert(Utility::isCharacter('j') == true);
    assert(Utility::isCharacter('k') == true);
    assert(Utility::isCharacter('l') == true);
    assert(Utility::isCharacter('m') == true);
    assert(Utility::isCharacter('n') == true);
    assert(Utility::isCharacter('o') == true);
    assert(Utility::isCharacter('p') == true);
    assert(Utility::isCharacter('q') == true);
    assert(Utility::isCharacter('r') == true);
    assert(Utility::isCharacter('s') == true);
    assert(Utility::isCharacter('t') == true);
    assert(Utility::isCharacter('u') == true);
    assert(Utility::isCharacter('v') == true);
    assert(Utility::isCharacter('w') == true);
    assert(Utility::isCharacter('x') == true);
    assert(Utility::isCharacter('y') == true);
    assert(Utility::isCharacter('z') == true);

    //A-Z
    assert(Utility::isCharacter('A') == true);
    assert(Utility::isCharacter('B') == true);
    assert(Utility::isCharacter('C') == true);
    assert(Utility::isCharacter('D') == true);
    assert(Utility::isCharacter('E') == true);
    assert(Utility::isCharacter('F') == true);
    assert(Utility::isCharacter('G') == true);
    assert(Utility::isCharacter('H') == true);
    assert(Utility::isCharacter('I') == true);
    assert(Utility::isCharacter('J') == true);
    assert(Utility::isCharacter('K') == true);
    assert(Utility::isCharacter('L') == true);
    assert(Utility::isCharacter('M') == true);
    assert(Utility::isCharacter('N') == true);
    assert(Utility::isCharacter('O') == true);
    assert(Utility::isCharacter('P') == true);
    assert(Utility::isCharacter('Q') == true);
    assert(Utility::isCharacter('R') == true);
    assert(Utility::isCharacter('S') == true);
    assert(Utility::isCharacter('T') == true);
    assert(Utility::isCharacter('U') == true);
    assert(Utility::isCharacter('V') == true);
    assert(Utility::isCharacter('W') == true);
    assert(Utility::isCharacter('X') == true);
    assert(Utility::isCharacter('Y') == true);
    assert(Utility::isCharacter('Z') == true);

    assert(Utility::isCharacter("Hello world") == true);
    assert(Utility::isCharacter("Hello world123") != true);

    //Failing
    assert(Utility::isCharacter('!') != true);
    assert(Utility::isCharacter('"') != true);
    assert(Utility::isCharacter('^') != true);
    assert(Utility::isCharacter('@') != true);

    //1-9
    assert(Utility::isNumber('0') == true);
    assert(Utility::isNumber('1') == true);
    assert(Utility::isNumber('2') == true);
    assert(Utility::isNumber('3') == true);
    assert(Utility::isNumber('4') == true);
    assert(Utility::isNumber('5') == true);
    assert(Utility::isNumber('6') == true);
    assert(Utility::isNumber('7') == true);
    assert(Utility::isNumber('8') == true);
    assert(Utility::isNumber('9') == true);

    assert(Utility::isNumber("1234") == true);
    assert(Utility::isNumber("123A") != true);

    //Failing
    assert(Utility::isNumber('a') != true);
    assert(Utility::isNumber('x') != true);
    assert(Utility::isNumber('#') != true);
    assert(Utility::isNumber('<') != true);

}
