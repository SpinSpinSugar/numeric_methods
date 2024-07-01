#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "lib.hpp"

double f(double x) { return std::pow(2, x) - 2 * std::cos(x); }

double f_prime(double x) {
  return std::log(2) * std::pow(2, x) + 2 * std::sin(x);
}

double f_pr_pr(double x) {
  return std::log(2) * std::log(2) * std::pow(2, x) + 2 * std::cos(x);
}

enum class METHOD { BISECTIONS = 1, NEWTON = 2, NEWTON_MOD = 3, INTERSECT = 4 };

void print_res(result res) {
  std::cout << "Init guess: " << res.init_guess << " Counter: " << res.counter
            << " Solution: " << res.ans << " Last len: " << res.last_len
            << '\n';
}

int main(int argc, const char **argv) {
  if (argc < 4) {
    std::cout << "USAGE:\n  METHOD_NUMBER A B N\n";
    return 1;
  }
  const int method_type = std::stoi(argv[1]);
  if (method_type < 0 || method_type > 5) {
    std::cerr << "wrong method\n";
    return 1;
  }
  static const std::map<METHOD, std::string_view> method_name = {
      {METHOD::BISECTIONS, "Bisections"},
      {METHOD::NEWTON, "Newton"},
      {METHOD::NEWTON_MOD, "Newton modified"},
      {METHOD::INTERSECT, "Intersections"}};

  const int a = std::stoi(argv[2]);
  const int b = std::stoi(argv[3]);
  const int n = std::stoi(argv[4]);
  std::cout << '[' << a << ',' << b << "]\n";
  const double h = (b - a) / static_cast<double>(n);
  std::vector<interval> intervals;
  double start = a;
  for (double x = a; x <= b; x += h) {
    if (f(start) * f(x) < 0) {
      intervals.push_back({start, x});
      start = x;
    }
  }
#if 0
    if (intervals.back().b < b) {
        intervals.push_back({start, static_cast<double>(b)});
    }
#endif
  print(intervals.begin(), intervals.end());
  std::cout << intervals.size() << '\n';
  auto fun = [](double x) { return f(x); };
  auto fp = [](double x) { return f_prime(x); };
  auto fpp = [](double x) { return f_pr_pr(x); };
  std::cout << "Method: " << method_name.at(static_cast<METHOD>(method_type))
            << '\n';
  for (const auto intvl : intervals) {
    result res{};
    switch (static_cast<METHOD>(method_type)) {
    case METHOD::BISECTIONS:
      res = bisections(fun, intvl);
      print_res(res);
      break;

    case METHOD::NEWTON:
      res = newton(f, fp, fpp, intvl);
      print_res(res);
      break;

    case METHOD::NEWTON_MOD:
      res = newton_mod(f, fp, fpp, intvl);
      print_res(res);
      break;
    case METHOD::INTERSECT:
      res = intersect(f, intvl);
      print_res(res);
      break;
    default:
      std::cerr << "error\n";
      return 1;
    }
  }
  std::cout << '\n';
}
