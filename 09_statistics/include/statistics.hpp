// 212-Терский-Илья-Задача(статистические характеристики последовательности)

#pragma once

#include <cstddef>
#include <limits>
#include <string>
#include <vector>

class IStatistics {  // общий интерфейс: даю числа по одному, потом спрашиваю ответ
  public:
    virtual ~IStatistics() = default;

    virtual void update(double next) = 0;
    virtual double eval() const = 0;
    virtual const char *name() const = 0;
};

class Min : public IStatistics {  // минимум
  public:
    void update(double next) override;
    double eval() const override;
    const char *name() const override;

  private:
    double min_ = std::numeric_limits<double>::infinity();  // не numeric_limits::min() — это самое маленькое положительное, а не самое маленькое число
};

class Max : public IStatistics {  // максимум
  public:
    void update(double next) override;
    double eval() const override;
    const char *name() const override;

  private:
    double max_ = -std::numeric_limits<double>::infinity();
};

class Mean : public IStatistics {  // среднее арифметическое
  public:
    void update(double next) override;
    double eval() const override;
    const char *name() const override;

  private:
    double sum_ = 0.0;
    std::size_t count_ = 0;
};

class Std : public IStatistics {  // СКО по всем числам (делю на n), метод Уэлфорда — без хранения чисел
  public:
    void update(double next) override;
    double eval() const override;
    const char *name() const override;

  private:
    std::size_t count_ = 0;
    double mean_ = 0.0;
    double m2_ = 0.0;  // сумма квадратов отклонений от текущего среднего
};

class Percentile : public IStatistics {  // процентиль методом ближайшего ранга, тут числа приходится хранить
  public:
    explicit Percentile(int percent);

    void update(double next) override;
    double eval() const override;
    const char *name() const override;

  private:
    int percent_;
    std::string name_;
    std::vector<double> values_;
};
