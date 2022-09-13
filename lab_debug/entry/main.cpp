#include "sketchify.h"

/**
 * A simple wrapper function that invokes sketchify on files in the current
 * directory. Input is read from`in.png` and the resulting image is written
 * to `out.png`.
 */
int main() {
    // If you get PNG Decoder error, it is because there is no such PNG "in.png".
    // Kindly change the input to one of the inputs you want to test in order to
    // make it work (ie. in_01.png)
    sketchify("../tests/in.png", "../tests/out.png");
    return 0;
}
