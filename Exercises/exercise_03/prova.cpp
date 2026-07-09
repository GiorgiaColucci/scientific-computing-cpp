#include <iostream>
#include "header.hpp"

int main(){

    /* COSTRUZIONE E NORMALIZZAZIONE */
    std::cout << "Costruzione e semplificazione:\n";

    rational<int> r1(8,12);      // 8/12 -> 2/3
    rational<int> r2(-45,15);    // -45/15 -> -3
    rational<int> r3(-100,-25);  // -100/-25 -> 4
    rational<int> r4(0,0);       // 0/0 -> NaN
    rational<int> r5(7,0);       // 7/0 -> +Inf
    rational<int> r6(-9,0);      // -9/0 -> -Inf
    rational<int> r7(0,5);       // 0/5 -> 0
    rational<int> r8;            // default -> 0/1

    std::cout << "8/12 = " << r1 << "  // 2/3\n";
    std::cout << "-45/15 = " << r2 << "  // -3\n";
    std::cout << "-100/-25 = " << r3 << "  // 4\n";
    std::cout << "0/0 = " << r4 << "  // NaN\n";
    std::cout << "7/0 = " << r5 << "  // +Inf\n";
    std::cout << "-9/0 = " << r6 << "  // -Inf\n";
    std::cout << "0/5 = " << r7 << "  // 0\n";
    std::cout << "default = " << r8 << "  // 0/1\n\n";


    /* ADDIZIONE */
    std::cout << "Addizione:\n";

    rational<int> a(4,10);    // 4/10 -> 2/5
    rational<int> b(-3,7);    // -3/7

    std::cout << "4/10 + (-3/7) = " << (a + b) << "  // 2/5 + (-3/7) = -1/35\n";
    std::cout << "(-3/7) + 0 = " << (b + r7) << "  // -3/7 + 0 = -3/7\n";
    std::cout << "2/5 + NaN = " << (a + r4) << "  // 2/5 + NaN = NaN\n";
    std::cout << "2/5 + Inf = " << (a + r5) << "  // 2/5 + +Inf = +Inf\n";
    std::cout << "2/5 + (-Inf) = " << (a + r6) << "  // 2/5 + -Inf = -Inf\n";
    std::cout << "Inf + Inf = " << (r5 + r5) << "  // +Inf\n";
    std::cout << "Inf + (-Inf) = " << (r5 + r6) << "  // NaN\n";
    std::cout << "(-Inf) + (-Inf) = " << (r6 + r6) << "  // -Inf\n\n";


    /* SOTTRAZIONE */
    std::cout << "Sottrazione:\n";

    std::cout << "4/10 - (-3/7) = " << (a - b) << "  // 2/5 - (-3/7) = 29/35\n";
    std::cout << "(-3/7) - 0 = " << (b - r7) << "  // -3/7 - 0 = -3/7\n";
    std::cout << "2/5 - NaN = " << (a - r4) << "  // NaN\n";
    std::cout << "2/5 - Inf = " << (a - r5) << "  // -Inf\n";
    std::cout << "2/5 - (-Inf) = " << (a - r6) << "  // +Inf\n";
    std::cout << "Inf - Inf = " << (r5 - r5) << "  // NaN\n";
    std::cout << "Inf - (-Inf) = " << (r5 - r6) << "  // +Inf\n";
    std::cout << "(-Inf) - Inf = " << (r6 - r5) << "  // -Inf\n\n";


    /* MOLTIPLICAZIONE */
    std::cout << "Moltiplicazione:\n";

    rational<int> c(5,-15);   // 5/-15 -> -1/3
    rational<int> d(-2,-8);   // -2/-8 -> 1/4

    std::cout << "2/5 * (-3/7) = " << (a * b) << "  // -6/35\n";
    std::cout << "(-1/3) * (-3/7) = " << (c * b) << "  // 1/7\n";
    std::cout << "(-1/3) * (1/4) = " << (c * d) << "  // -1/12\n";
    std::cout << "0 * (2/5) = " << (r7 * a) << "  // 0\n";
    std::cout << "0 * Inf = " << (r7 * r5) << "  // NaN\n";
    std::cout << "Inf * (2/5) = " << (r5 * a) << "  // +Inf\n";
    std::cout << "Inf * (-3/7) = " << (r5 * b) << "  // -Inf\n";
    std::cout << "(-Inf) * (-3/7) = " << (r6 * b) << "  // +Inf\n";
    std::cout << "Inf * (-Inf) = " << (r5 * r6) << "  // -Inf\n";
    std::cout << "Inf * NaN = " << (r5 * r4) << "  // NaN\n\n";


    /* DIVISIONE */
    std::cout << "Divisione:\n";

    std::cout << "2/5 / (-3/7) = " << (a / b) << "  // -14/15\n";
    std::cout << "(-1/3) / (-3/7) = " << (c / b) << "  // 7/9\n";
    std::cout << "(-1/3) / (1/4) = " << (c / d) << "  // -4/3\n";

    std::cout << "Inf / (2/5) = " << (r5 / a) << "  // +Inf\n";
    std::cout << "Inf / (-3/7) = " << (r5 / b) << "  // -Inf\n";

    std::cout << "(2/5) / Inf = " << (a / r5) << "  // 0\n";
    std::cout << "(2/5) / (-Inf) = " << (a / r6) << "  // 0\n";

    std::cout << "0 / (2/5) = " << (r7 / a) << "  // 0\n";
    std::cout << "0 / 0 = " << (r7 / r7) << "  // NaN\n";

    std::cout << "(2/5) / 0 = " << (a / r7) << "  // +Inf\n";

    std::cout << "Inf / Inf = " << (r5 / r5) << "  // NaN\n";
    std::cout << "Inf / (-Inf) = " << (r5 / r6) << "  // NaN\n";
    std::cout << "Inf / NaN = " << (r5 / r4) << "  // NaN\n";
    std::cout << "(2/5) / NaN = " << (a / r4) << "  // NaN\n";

    return 0;
}