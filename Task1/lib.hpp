#include <cmath>
#include <iosfwd>
#include <stdexcept>

constexpr double EPS = 1e-6;
struct interval {
  double a{};
  double b{};
};

struct result {
  double init_guess = 0;
  int counter = 0;
  double ans = 0;
  double last_len = 0;
};

result bisections(auto f, interval i, int cnt = 0) {
  int counter = cnt;
  if (i.b - i.a < 2 * EPS) {
    return {0, counter, (i.b + i.a) / 2, i.b - i.a};
  }
  interval left = {i.a, (i.b + i.a) / 2};
  interval right = {(i.b + i.a) / 2, i.b};
  if (f(left.a) * f(left.b) < 0)
    return bisections(f, left, counter + 1);
  else {
    return bisections(f, right, counter + 1);
  }
}

result newton(auto f, auto f_prime, auto fpp, interval i) {
  int counter = 0;
  double x = (i.a + i.b) / 2;
  int tmp_cnt = 0;
  while (f(x) * fpp(x) > 0 && tmp_cnt < 100) {
    ++tmp_cnt;
    x += 100 * EPS;
  }
  if (tmp_cnt == 100)
    throw std::runtime_error("can't guess");
  const double init = x;
  double prev = x;
  while (std::abs(f(x)) >= EPS && counter < 1000) {
    prev = x;
    x = x - f(x) / f_prime(x);
    ++counter;
  }
  return {init, counter, x, std::abs(prev - x)};
}

result newton_mod(auto f, auto f_prime, auto fpp, interval i) {
  int counter = 0;
  double x = (i.a + i.b) / 2;
  int tmp_cnt = 0;
  while (f(x) * fpp(x) > 0 && tmp_cnt < 100) {
    ++tmp_cnt;
    x += 100 * EPS;
  }
  if (tmp_cnt == 100)
    throw std::runtime_error("can't guess");
  const double init = x;

  const double x_0 = x;
  double prev = x;
  while (std::abs(f(x)) >= EPS && counter < 1000) {
    ++counter;
    prev = x;
    x = x - f(x) / f_prime(x_0);
  }
  return {init, counter, x, std::abs(prev - x)};
}

result intersect(auto f, interval i) {
  int counter = 0;
  double x = (i.b + i.a) / 2;
  int itr = 0;
  double x0 = i.b;
  double prev = 0;
  while (std::abs(f(x)) >= EPS && counter < 1000) {
    ++counter;
    prev = x;
    x = x - itr * (f(x) / (f(x) - f(x0)) * (x - x0));
    itr = 1;
  }
  return {i.b, counter, x, std::abs(prev - x)};
}

template <typename T> void print(T begin, T end) {
  for (auto it = begin; it < end; ++it) {
    std::cout << "[" << (*it).a << "," << (*it).b << "]";
  }
  std::cout << '\n';
}
