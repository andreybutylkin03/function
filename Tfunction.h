#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <functional>
#include <any>

class TFunction {
public:
    virtual ~TFunction() = default;

    virtual double operator()(double x) const = 0;

    virtual double GetDeriv(double x) const = 0;

    virtual std::string ToString() const = 0;

    TFunction& operator+(const TFunction& other);
    TFunction& operator-(const TFunction& other);
    TFunction& operator*(const TFunction& other);
    TFunction& operator/(const TFunction& other);
};

class IdentityFunction : public TFunction {
public:
    double operator()(double x) const override {
        return x;
    }

    double GetDeriv(double x) const override {
        return 1;
    }

    std::string ToString() const override {
        return "x";
    }
};

class ConstantFunction : public TFunction {
private:
    double value;

public:
    explicit ConstantFunction(double v) : value(v) {}

    double operator()(double x) const override {
        return value;
    }

    double GetDeriv(double x) const override {
        return 0;
    }

    std::string ToString() const override {
        return std::to_string(value);
    }
};

class PowerFunction : public TFunction {
private:
    double exponent;

public:
    explicit PowerFunction(double exp) : exponent(exp) {}

    double operator()(double x) const override {
        return std::pow(x, exponent);
    }

    double GetDeriv(double x) const override {
        return exponent * std::pow(x, exponent - 1);
    }

    std::string ToString() const override {
        return "x^" + std::to_string(exponent);
    }
};

class ExpFunction : public TFunction {
public:
    double operator()(double x) const override {
        return std::exp(x);
    }

    double GetDeriv(double x) const override {
        return std::exp(x);
    }

    std::string ToString() const override {
        return "e^x";
    }
};

class PolynomialFunction : public TFunction {
private:
    std::vector<double> coeff_;

public:
    explicit PolynomialFunction(const std::vector<double>& coeffs) : coeff_(coeffs) {}

    double operator()(double x) const override {
        double result = 0;
        double power = 1;
        for (double coeff : coeff_) {
            result += coeff * power;
            power *= x;
        }
        return result;
    }

    double GetDeriv(double x) const override {
        double result = 0;
        double power = 1;
        for (size_t i = 1; i < coeff_.size(); ++i) {
            result += i * coeff_[i] * power;
            power *= x;
        }
        return result;
    }

    std::string ToString() const override {
        std::ostringstream oss;
        for (size_t i = 0; i < coeff_.size(); ++i) {
            if (i > 0) oss << " + ";
            oss << coeff_[i];
            if (i > 0) oss << "*x^" << i;
        }
        return oss.str();
    }
};

class FunctionFactory {
public:
    /*std::shared_ptr<TFunction> Create(const std::string& type) {
        if (type == "ident") {
            return std::make_shared<IdentityFunction>();
        } else if (type == "exp") {
            return std::make_shared<ExpFunction>();
        } else {
            throw std::logic_error("Unknown function type");
        }
    }

    std::shared_ptr<TFunction> Create(const std::string& type, const double &param) {
        if (type == "const") {
            return std::make_shared<ConstantFunction>(param);
        } else if (type == "power") {
            return std::make_shared<PowerFunction>(param);
        } else {
            throw std::logic_error("Unknown function type");
        }
    }

    std::shared_ptr<TFunction> Create(const std::string& type, const std::vector<double> &param) {
        if (type == "polynomial") {
            return std::make_shared<PolynomialFunction>(param);
        } else {
            throw std::logic_error("Unknown function type");
        }
    }*/
    std::shared_ptr<TFunction> Create(const std::string& type, const std::any& param = {}) {
        if (type == "ident") {
            return std::make_shared<IdentityFunction>();
        } else if (type == "const") {
            return std::make_shared<ConstantFunction>(std::any_cast<double>(param));
        } else if (type == "power") {
            return std::make_shared<PowerFunction>(std::any_cast<double>(param));
        } else if (type == "exp") {
            return std::make_shared<ExpFunction>();
        } else if (type == "polynomial") {
            return std::make_shared<PolynomialFunction>(std::any_cast<std::vector<double>>(param));
        } else {
            throw std::logic_error("Unknown function type");
        }
    }
};

