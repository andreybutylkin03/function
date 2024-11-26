#include <gtest/gtest.h>
#include "Tfunction.h"

TEST(FunctionCreation, IdentityFunction) {
    auto identity = std::make_shared<IdentityFunction>();
    EXPECT_EQ((*identity)(5), 5);
    EXPECT_EQ((*identity)(-3), -3);
    EXPECT_EQ(identity->ToString(), "x");
}

TEST(FunctionCreation, ConstantFunction) {
    auto constant = std::make_shared<ConstantFunction>(10.5);
    EXPECT_EQ((*constant)(0), 10.5);
    EXPECT_EQ((*constant)(100), 10.5);
    EXPECT_EQ(constant->ToString(), "10.500000");
}

TEST(FunctionCreation, PowerFunction) {
    auto power = std::make_shared<PowerFunction>(2);
    EXPECT_EQ((*power)(3), 9);
    EXPECT_EQ((*power)(-2), 4);
    EXPECT_EQ(power->ToString(), "x^2.000000");
}

TEST(FunctionCreation, ExpFunction) {
    auto exp = std::make_shared<ExpFunction>();
    EXPECT_EQ((*exp)(0), 1);
    EXPECT_EQ((*exp)(2), std::exp(2.0));
    EXPECT_EQ(exp->ToString(), "e^x");
}

TEST(FunctionCreation, PolynomialFunction) {
    auto polynomial = std::make_shared<PolynomialFunction>(std::vector<long double>{1, 1});
    EXPECT_EQ((*polynomial)(3), 4);
    EXPECT_EQ((*polynomial)(-2), -1);
    EXPECT_EQ(polynomial->ToString(), "1 + 1*x^1");
}

TEST(FunctionArithmetic, Addition) {
    auto f = std::make_shared<ConstantFunction>(2);
    auto g = std::make_shared<IdentityFunction>();

    auto sum = (*f) + (*g);
    EXPECT_EQ((*sum)(3), 5);
    EXPECT_EQ((*sum)(-3), -1);
}

TEST(FunctionArithmetic, Sub) {
    auto f = std::make_shared<ConstantFunction>(2);
    auto g = std::make_shared<ExpFunction>();

    auto sum = *f - *g;
    EXPECT_EQ((*sum)(0), 1);
}

TEST(FunctionArithmetic, Multiplication) {
    auto f = std::make_shared<ConstantFunction>(3);
    auto g = std::make_shared<PowerFunction>(2);

    auto product = *f * *g;
    EXPECT_EQ((*product)(2), 12); 
}

TEST(FunctionArithmetic, Div) {
    auto f = std::make_shared<ConstantFunction>(3);
    auto g = std::make_shared<PowerFunction>(2);

    auto product = *f / *g;
    EXPECT_EQ((*product)(1), 3); 
}

TEST(FunctionDerivative, IdentityFunction) {
    auto identity = std::make_shared<IdentityFunction>();
    EXPECT_NEAR(identity->GetDeriv(5), 1.0, 0.01);
}

TEST(FunctionDerivative, ConstantFunction) {
    auto constant = std::make_shared<ConstantFunction>(10.5);
    EXPECT_EQ(constant->GetDeriv(0), 0.0);
}

TEST(FunctionDerivative, PowerFunction) {
    auto power = std::make_shared<PowerFunction>(2);
    EXPECT_EQ(power->GetDeriv(3), 6.0);
}

TEST(FunctionDerivative, ExpFunction) {
    auto exp = std::make_shared<ExpFunction>();
    EXPECT_EQ(exp->GetDeriv(1), std::exp(1));
}

TEST(FunctionDerivative, PolynomialFunction) {
    auto polynomial = std::make_shared<PolynomialFunction>(std::vector<long double>{1, 1});
    EXPECT_EQ(polynomial->GetDeriv(3), 1.0);
}

TEST(GradientDescent, QuadraticEquation) {
    auto polynomial = std::make_shared<PolynomialFunction>(std::vector<long double>{4, -4, 1});

    EXPECT_NEAR(polynomial->GradientDescent(1000), 2.0, 0.01); 
}

TEST(TFunctionTest, LogicError) {
    auto f1 = std::make_shared<PolynomialFunction>(std::vector<long double>{1, 1});
    auto f2 = std::make_shared<PowerFunction>(2);

    EXPECT_NO_THROW({
        auto result = *f1 + *f2;
    });

    EXPECT_THROW({
        auto result = *f1 + "abs";
    }, std::logic_error);

    EXPECT_THROW({
        auto result = 123 + *f1;
    }, std::logic_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS(); 
}
