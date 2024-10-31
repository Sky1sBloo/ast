#include <iostream>
#include "ParseNodes.hpp"

int main()
{
    ConstExpr<int> test(5);
    std::cout << test.getValue() << std::endl;
}
