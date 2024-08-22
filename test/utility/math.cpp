#include <cassert>
#include <utility/math.hpp>

int main(){
    //Values
    assert(Utility::allEqual(5) == true);
    assert(Utility::allEqual(10,10) == true);
    assert(Utility::allEqual(20,20) == true);
    assert(Utility::allEqual(30,20) != true);
}
