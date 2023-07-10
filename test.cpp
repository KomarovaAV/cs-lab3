#include "Header.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_same() {
    double min = 0;
    double max = 0;
    find_minmax({ 5, 5, 5 }, min, max);
    assert(min == 5);
    assert(max == 5);
}

void test_one() {
    double min = 0;
    double max = 0;
    find_minmax({ 7 }, min, max);
    assert(min == 7);
    assert(max == 7);
}

void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void test_show_text() {
    string expected1 = "<text x='0.000000' y='0.000000' font-size='15'>text</text>\n";
    string res1 = svg_text(0, 0, "text", 15);
    assert(res1 == expected1);
    string expected2 = "<text x='2.500000' y='5.800000' font-size='20'>text2</text>\n";
    string res2 = svg_text(2.5, 5.8, "text2", 20);
    assert(res2 == expected2);
}

int main() {
    test_positive();
    test_negative();
    test_same();
    test_one();
    test_empty();
    test_show_text();
}
