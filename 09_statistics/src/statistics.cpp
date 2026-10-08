#include "statistics.hpp"

#include <algorithm>
#include <cmath>

namespace {

const double no_data = std::numeric_limits<double>::quiet_NaN();  // ответ, когда чисел не было

}  // namespace

void Min::update(double next) {
    if (next < min_) {
        min_ = next;
    }
}

double Min::eval() const { return min_; }

const char *Min::name() const { return "min"; }

void Max::update(double next) {
    if (next > max_) {
        max_ = next;
    }
}

double Max::eval() const { return max_; }

const char *Max::name() const { return "max"; }

void Mean::update(double next) {
    sum_ += next;
    ++count_;
}

double Mean::eval() const { return count_ == 0 ? no_data : sum_ / static_cast<double>(count_); }

const char *Mean::name() const { return "mean"; }

void Std::update(double next) {  // обновляю среднее и сумму квадратов сразу, без второго прохода
    ++count_;
    const double delta = next - mean_;
    mean_ += delta / static_cast<double>(count_);
    m2_ += delta * (next - mean_);
}

double Std::eval() const {
    return count_ == 0 ? no_data : std::sqrt(m2_ / static_cast<double>(count_));
}

const char *Std::name() const { return "std"; }

Percentile::Percentile(int percent)
    : percent_(percent)
    , name_("pct" + std::to_string(percent)) {}

void Percentile::update(double next) { values_.push_back(next); }

double Percentile::eval() const {  // беру элемент с рангом ceil(p * n / 100)
    if (values_.empty()) {
        return no_data;
    }

    const std::size_t n = values_.size();
    const std::size_t p = static_cast<std::size_t>(percent_);
    const std::size_t rank = std::max<std::size_t>(1, (p * n + 99) / 100);  // ceil в целых числах, без ошибок округления

    std::vector<double> copy(values_);  // eval константный, поэтому работаю с копией
    const auto nth = copy.begin() + static_cast<std::ptrdiff_t>(rank - 1);
    std::nth_element(copy.begin(), nth, copy.end());  // ставит нужный элемент на место без полной сортировки
    return *nth;
}

const char *Percentile::name() const { return name_.c_str(); }
