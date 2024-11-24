#include "Tfunction.h"

const double eps = 1e-6;

std::shared_ptr<TFunction> TFunction::operator+(const TFunction& other) const {
    return std::make_shared<Function>(shared_from_this(), other.shared_from_this(), '+');
}

std::shared_ptr<TFunction> TFunction::operator-(const TFunction& other) const {
    return std::make_shared<Function>(shared_from_this(), other.shared_from_this(), '-');
}

std::shared_ptr<TFunction> TFunction::operator*(const TFunction& other) const {
    return std::make_shared<Function>(shared_from_this(), other.shared_from_this(), '*');
}

std::shared_ptr<TFunction> TFunction::operator/(const TFunction& other) const {
    return std::make_shared<Function>(shared_from_this(), other.shared_from_this(), '/');
}

double IdentityFunction::operator()(double x) const {
    return x;
}

double IdentityFunction::GetDeriv(double x) const {
    return 1;
}

std::string IdentityFunction::ToString() const {
    return "x";
}

ConstantFunction::ConstantFunction(double v) {
    value_ = v;
}

double ConstantFunction::operator()(double x) const {
    return value_;
}

double ConstantFunction::GetDeriv(double x) const {
    return 0;
}

std::string ConstantFunction::ToString() const {
    return std::to_string(value_);
}

PowerFunction::PowerFunction(double exp) {
    exponent_ = exp; 
}

double PowerFunction::operator()(double x) const {
    return std::pow(x, exponent_);
}

double PowerFunction::GetDeriv(double x) const {
    return exponent_ * std::pow(x, exponent_ - 1);
}

std::string PowerFunction::ToString() const {
    return "x^" + std::to_string(exponent_);
}

double ExpFunction::operator()(double x) const {
    return std::exp(x);
}

double ExpFunction::GetDeriv(double x) const {
    return std::exp(x);
}

std::string ExpFunction::ToString() const {
    return "e^x";
}

PolynomialFunction::PolynomialFunction(const std::vector<double>& coeffs) {
    coeff_ = coeffs; 
}

double PolynomialFunction::operator()(double x) const {
    double result = 0;
    double power = 1;
    for (double coeff : coeff_) {
        result += coeff * power;
        power *= x;
    }
    return result;
}

double PolynomialFunction::GetDeriv(double x) const {
    double result = 0;
    double power = 1;
    for (size_t i = 1; i < coeff_.size(); ++i) {
        result += i * coeff_[i] * power;
        power *= x;
    }
    return result;
}

std::string PolynomialFunction::ToString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < coeff_.size(); ++i) {
        if (i > 0) oss << " + ";
        oss << coeff_[i];
        if (i > 0) oss << "*x^" << i;
    }
    return oss.str();
}


Function::Function(std::shared_ptr<const TFunction> f, std::shared_ptr<const TFunction> s, char op) {
    f_ = std::move(f);
    s_ = std::move(s);
    op_ = op;
}

double Function::operator()(double x) const {
    double res = 0;

    switch (op_) {
        case '+':
            res = (*f_)(x) + (*s_)(x);
            break;
        case '-':
            res = (*f_)(x) - (*s_)(x);
            break;
        case '*':
            res = (*f_)(x) * (*s_)(x);
            break;
        case '/':
            res = (*f_)(x) / (*s_)(x);
            break;
    }
    return res;
}

double Function::GetDeriv(double x) const {
    double res = ((*this)(x + eps) - (*this)(x + eps)) / eps;

    return res;
}

std::string Function::ToString() const {
    return "(" + f_->ToString() + ")" + op_ + "(" + s_->ToString() + ")";
}

std::shared_ptr<TFunction> FunctionFactory::Create(const std::string& type, const std::any& param) {
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




