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

class TFunction : public std::enable_shared_from_this<TFunction>{
public:
    virtual ~TFunction() = default;

    virtual double operator()(double x) const = 0;

    virtual double GetDeriv(double x) const = 0;

    virtual std::string ToString() const = 0;

    virtual std::shared_ptr<TFunction> operator+(const TFunction& other) const;
    virtual std::shared_ptr<TFunction> operator-(const TFunction& other) const;
    virtual std::shared_ptr<TFunction> operator*(const TFunction& other) const;
    virtual std::shared_ptr<TFunction> operator/(const TFunction& other) const;
};

class IdentityFunction : public TFunction {
public:
    double operator()(double x) const override;

    double GetDeriv(double x) const override;

    std::string ToString() const override;
};

class ConstantFunction : public TFunction {
private:
    double value_;

public:
    explicit ConstantFunction(double v);

    double operator()(double x) const override;

    double GetDeriv(double x) const override;

    std::string ToString() const override;
};

class PowerFunction : public TFunction {
private:
    double exponent_;

public:
    explicit PowerFunction(double exp);

    double operator()(double x) const override;

    double GetDeriv(double x) const override;

    std::string ToString() const override;
};

class ExpFunction : public TFunction {
public:
    double operator()(double x) const override;

    double GetDeriv(double x) const override;

    std::string ToString() const override;
};

class PolynomialFunction : public TFunction {
private:
    std::vector<double> coeff_;

public:
    explicit PolynomialFunction(const std::vector<double>& coeffs);

    double operator()(double x) const override;

    double GetDeriv(double x) const override;

    std::string ToString() const override;
};

class Function : public TFunction {
private:
    std::shared_ptr<const TFunction> f_;
    std::shared_ptr<const TFunction> s_;
    char op_;

public:
    explicit Function(std::shared_ptr<const TFunction> f, std::shared_ptr<const TFunction> s, char op);

    double operator()(double x) const override;

    double GetDeriv(double x) const override;

    std::string ToString() const override;
};

class FunctionFactory {
public:
    std::shared_ptr<TFunction> Create(const std::string& type, const std::any& param = {});
};

