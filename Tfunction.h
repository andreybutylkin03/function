#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <any>
#include <random>
#include <cfloat>
#include <iomanip>

class TFunction : public std::enable_shared_from_this<TFunction>{
public:
    virtual ~TFunction() = default;

    virtual long double operator()(long double x) const = 0;

    virtual long double GetDeriv(long double x) const = 0;

    virtual std::string ToString() const = 0;

    std::shared_ptr<TFunction> operator+(const TFunction& other) const;
    std::shared_ptr<TFunction> operator-(const TFunction& other) const;
    std::shared_ptr<TFunction> operator*(const TFunction& other) const;
    std::shared_ptr<TFunction> operator/(const TFunction& other) const;

    template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
    std::shared_ptr<TFunction> operator+(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
    std::shared_ptr<TFunction> operator-(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
    std::shared_ptr<TFunction> operator*(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
    std::shared_ptr<TFunction> operator/(const T& other) const {
        throw std::logic_error("Invalid operand type for TFunction arithmetic");
    }

    virtual long double GradientDescent(int i = 100) const;
};

template <typename T, size_t N>
T operator+(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
T operator+(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, size_t N>
T operator-(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
T operator-(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, size_t N>
T operator*(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
T operator*(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, size_t N>
T operator/(const T (&lhs)[N], const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

template <typename T, typename = std::enable_if_t<!std::is_base_of_v<TFunction, T>>>
T operator/(const T& lhs, const TFunction& rhs) {
    throw std::logic_error("Invalid operand type for TFunction arithmetic");
}

class IdentityFunction : public TFunction {
public:
    long double operator()(long double x) const override;

    long double GetDeriv(long double x) const override;

    std::string ToString() const override;
};

class ConstantFunction : public TFunction {
private:
    long double value_;

public:
    explicit ConstantFunction(long double v);

    long double operator()(long double x) const override;

    long double GetDeriv(long double x) const override;

    std::string ToString() const override;
};

class PowerFunction : public TFunction {
private:
    long double exponent_;

public:
    explicit PowerFunction(long double exp);

    long double operator()(long double x) const override;

    long double GetDeriv(long double x) const override;

    std::string ToString() const override;
};

class ExpFunction : public TFunction {
public:
    long double operator()(long double x) const override;

    long double GetDeriv(long double x) const override;

    std::string ToString() const override;
};

class PolynomialFunction : public TFunction {
private:
    std::vector<long double> coeff_;

public:
    explicit PolynomialFunction(const std::vector<long double>& coeffs);

    long double operator()(long double x) const override;

    long double GetDeriv(long double x) const override;

    std::string ToString() const override;
};

class Function : public TFunction {
private:
    std::shared_ptr<const TFunction> f_;
    std::shared_ptr<const TFunction> s_;
    char op_;

public:
    explicit Function(std::shared_ptr<const TFunction> f, std::shared_ptr<const TFunction> s, char op);

    long double operator()(long double x) const override;

    long double GetDeriv(long double x) const override;

    std::string ToString() const override;
};

class FunctionFactory {
public:
    std::shared_ptr<TFunction> Create(const std::string& type, const std::any& param = {});
};

