// Copyright 2022 Daniil mnogolapiy@gmail.com
#include <gtest/gtest.h>

#include <polynomial.hpp>
#include <vector>

TEST(Polynomial, Init) {
  std::vector<int> Vec{14, 2, 5, 2, 18, 4, 21};
  Polynomial<int> polynomOne(Vec);

  Polynomial<int> polynomTwo({7, 21, 3, 1, 3, 2});
  polynomTwo = polynomOne;

  EXPECT_EQ(Vec, polynomOne.get_data());
  EXPECT_EQ(polynomOne, polynomTwo);
}

TEST(Polynomial, sum) {
  std::vector<int> Vec{7, 2, 11, 2, 11, 4, 36};
  Polynomial<int> polynomOne(Vec);

  Polynomial<int> polynomTwo({22, 11, 3, 4});
  std::vector<int> result{7, 2, 11, 24, 22, 7, 40};

  polynomOne = Vec;
  Polynomial<int> polynomThree  = polynomOne + polynomTwo;
  EXPECT_EQ(result, polynomThree.get_data());

  Polynomial<int> polynom4({7, 2, 11, 2, 11, 4, 36});
  Polynomial<int> diffsize({22, 11, 3, 4});
  diffsize = diffsize + polynomOne;
  EXPECT_EQ(result, diffsize.get_data());
}

TEST(Polynomial, minus) {
  Polynomial<int> dwindling({21, 30 , 17, 24});
  Polynomial<int> subtracted({12, 24, -5, 20});
  Polynomial<int> difference;
  difference = dwindling - subtracted;
  std::vector<int> result{9, 6, 22, 4};

  EXPECT_EQ(difference.get_data(), result);

  Polynomial<int> dwindling1({21, 30, 17, 24});
  Polynomial<int> subtracted1( {24, -5, 20});
  Polynomial<int> difference1;
  difference1 = dwindling1 - subtracted1;
  std::vector<int> result1{21, 6, 22, 4};
  EXPECT_EQ(difference1.get_data(), result1);
}

TEST(Polynomial, lambMult) {
  Polynomial<int> polynomOne({12,3,45, 23, 11, 23, 7});
  polynomOne *= 2;
  std::vector<int> result {24, 6, 90, 46, 22, 46, 14};
  EXPECT_EQ(result, polynomOne.get_data());
}

TEST(Polynomial, justMult) {
  Polynomial<int> multiplier1({1, 9, 2, 76});
  Polynomial<int> multiplier2({1, 4, 2, 5});
  Polynomial<int> product;
  product = multiplier1 * multiplier2;
  std::vector<int> result{1, 13, 40, 107, 353, 162, 380};
  EXPECT_EQ(result, product.get_data());
}

TEST(Polynomial, div) {
  Polynomial<int> polyDivider({-51, 0, -24, 4});
  Polynomial<int> polyDivisible({-2, 1});
  Polynomial<int> polyQuotient;
  polyQuotient = polyDivider / polyDivisible;
  std::vector<int> result{4, -16, -32};
  EXPECT_EQ(result, polyQuotient.get_data());
}

TEST(Polynomial, degree) {
  Polynomial<int> diff({5, 2, 4, 7, 9, 2, 12, 3});
  int s = diff.get_deg();
  EXPECT_EQ(7, s);
}

TEST(Polynomial, count) {
  Polynomial<double> calc({14., 3., 2., 67., 9., 4.});
  double s = calc.count(1.8);
  EXPECT_DOUBLE_EQ(4 + 9 * 1.8 + 67 * 1.8 * 1.8 + 2 * 1.8 * 1.8 * 1.8 +
                       3 * 1.8 * 1.8 * 1.8 * 1.8 + 14 * 1.8 * 1.8 * 1.8 * 1.8 * 1.8,
                   s);
}

TEST(Polynomial, CEF) {
  Polynomial<int> polyDivider({-42, 0, -12, 1});
  Polynomial<int> polyDivisible({-3, 1});
  Polynomial<int> polyQuotient;
  polyQuotient = polyDivider % polyDivisible;
  std::vector<int> result{-123};
  EXPECT_EQ(result, polyQuotient.get_data());
}
