#include "../Table.hh"

#include <cassert>
#include <iostream>

void test_slide() {
    Table table;
    Value v = {0x000000, 0};
    std::cout << v << std::endl;
    table.slide(0x00000000);
    assert(v == table.slide(0x00000000));
    v = {0x00000001, 0};
    std::cout << v << std::endl;
    assert(v == table.slide(0x00000001));
    v = {0x00000002, 0};
    std::cout << v << std::endl;
    assert(v == table.slide(0x00000200));
    v = {0x00000003, 0};
    std::cout << v << std::endl;
    assert(v == table.slide(0x00030000));
    v = {0x00000004, 0};
    std::cout << v << std::endl;
    assert(v == table.slide(0x04000000));
    v = {0x00000002, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x00000101));
    v = {0x00000002, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x00010001));
    v = {0x00000002, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01000001));
    v = {0x00000102, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01010001));
    v = {0x00000102, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x00010101));
    v = {0x00000102, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01010100));
    v = {0x00000002, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01000100));
    v = {0x00000202, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01010200));
    v = {0x00020201, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01010201));
    v = {0x00000202, 8};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01010101));
    v = {0x00000203, 12};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01010202));
    v = {0x01020304, 0};
    std::cout << v << std::endl;
    assert(v == table.slide(0x01020304));
    v = {0x04030201, 0};
    std::cout << v << std::endl;
    assert(v == table.slide(0x04030201));
    v = {0x00020202, 4};
    std::cout << v << std::endl;
    assert(v == table.slide(0x02010102));
    v = {0x00000302, 12};
    std::cout << v << std::endl;
    assert(v == table.slide(0x02020101));
}

int main() {
    test_slide();
}
