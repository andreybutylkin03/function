#include "Tfunction.h"

const long double eps = 1e-12;

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

long double TFunction::GradientDescent(int i) const {
    long double ans = 0, alpha = 1.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<long double> dis(-1000.0, 1000.0); 

    ans = dis(gen);

    for (int j = 0; j < i; ++j) {
        std::cout << ans << std::endl;

        long double val = (*this)(ans);
        if (std::abs(val) < eps) 
            break;

        if (val > 0) {
            ans = ans - alpha * this->GetDeriv(ans);
        } else {
            ans = ans + alpha * this->GetDeriv(ans);
        }
    }

    return ans;
}

long double IdentityFunction::operator()(long double x) const {
    return x;
}

long double IdentityFunction::GetDeriv(long double x) const {
    return 1;
}

std::string IdentityFunction::ToString() const {
    return "x";
}

ConstantFunction::ConstantFunction(long double v) {
    value_ = v;
}

long double ConstantFunction::operator()(long double x) const {
    return value_;
}

long double ConstantFunction::GetDeriv(long double x) const {
    return 0;
}

std::string ConstantFunction::ToString() const {
    return std::to_string(value_);
}

PowerFunction::PowerFunction(long double exp) {
    exponent_ = exp; 
}

long double PowerFunction::operator()(long double x) const {
    return std::pow(x, exponent_);
}

long double PowerFunction::GetDeriv(long double x) const {
    return exponent_ * std::pow(x, exponent_ - 1);
}

std::string PowerFunction::ToString() const {
    return "x^" + std::to_string(exponent_);
}

long double ExpFunction::operator()(long double x) const {
    return std::exp(x);
}

long double ExpFunction::GetDeriv(long double x) const {
    return std::exp(x);
}

std::string ExpFunction::ToString() const {
    return "e^x";
}

PolynomialFunction::PolynomialFunction(const std::vector<long double>& coeffs) {
    coeff_ = coeffs; 
}

long double PolynomialFunction::operator()(long double x) const {
    long double result = 0;
    long double power = 1;
    for (long double coeff : coeff_) {
        result += coeff * power;
        power *= x;
    }
    return result;
}

long double PolynomialFunction::GetDeriv(long double x) const {
    long double result = 0;
    long double power = 1;
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

long double Function::operator()(long double x) const {
    long double res = 0;

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

long double Function::GetDeriv(long double x) const {
    long double res = ((*this)(x + eps) - (*this)(x)) / eps;

    return res;
}

std::string Function::ToString() const {
    return "(" + f_->ToString() + ")" + op_ + "(" + s_->ToString() + ")";
}

std::shared_ptr<TFunction> FunctionFactory::Create(const std::string& type, const std::any& param) {
    if (type == "ident") {
        return std::make_shared<IdentityFunction>();
    } else if (type == "const") {
        return std::make_shared<ConstantFunction>(std::any_cast<long double>(param));
    } else if (type == "power") {
        return std::make_shared<PowerFunction>(std::any_cast<long double>(param));
    } else if (type == "exp") {
        return std::make_shared<ExpFunction>();
    } else if (type == "polynomial") {
        return std::make_shared<PolynomialFunction>(std::any_cast<std::vector<long double>>(param));
    } else {
        throw std::logic_error("Unknown function type");
    }
}




