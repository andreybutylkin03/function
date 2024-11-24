#include "Tfunction.h"
// === Пример использования ===
int main() {
    FunctionFactory factory;

    auto f = factory.Create("power", (long double)2.0); // x^2
    auto g = factory.Create("polynomial", std::vector<long double>{7, 0, 3, 15}); // 7 + 3*x^2 + 15*x^3

    std::cout << f->ToString() << " for x = 10 is " << (*f)(10) << " " << f->GetDeriv(10) << std::endl;
    std::cout << g->ToString() << " for x = 10 is " << (*g)(10) << " " <<  g->GetDeriv(10) << std::endl;

    auto q = factory.Create("const", (long double)3.0);

    auto h = (*((*((*f) * (*q))) + (*((*g) / (*q))))) - (*q);

    std::cout << h->ToString() << " for x = 10 is " << (*h)(10) << " " << h->GetDeriv(10) << std::endl;

    return 0;
}
