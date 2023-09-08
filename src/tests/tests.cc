#include <gtest/gtest.h>

#include <random>

#include "../controller/controller.h"

TEST(Parser_test, parcer_error_num_1) {
  std::string expr = "3^4+1*(2-4) 1 ";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_num_2) {
  std::string expr = "1*(2-4)^4-5 (3+6)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_num_3) {
  std::string expr = "3^4+1*(2-4)/1sin(2)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_num_4) {
  std::string expr = "1*(2-4)^4-sin 5/(3+6)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_num_5) {
  std::string expr = "3^4+1*(2-4x)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_num_6) {
  std::string expr = "1*(2-4)^4-sin(5)-x3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_ok_num_1) {
  std::string expr = "33+1.1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_num_2) {
  std::string expr = "33+1.1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_error_point_1) {
  std::string expr = "1..+3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_2) {
  std::string expr = "1.1.1+3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_3) {
  std::string expr = ".1+3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_4) {
  std::string expr = "1.(4-6)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_5) {
  std::string expr = "3^4+1*(.2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_6) {
  std::string expr = "3^4+1*(2-4).1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_7) {
  std::string expr = "3^4+1*(2-4)/.1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_8) {
  std::string expr = "3^4+1*(2-4)/-.1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_9) {
  std::string expr = "3^4+sin .2";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_10) {
  std::string expr = "3^4+1.ln(2)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_11) {
  std::string expr = "3^4+1*(2-4)^x.1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_point_12) {
  std::string expr = "3^4+1*(2-4)/1.x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_ok_point_1) {
  std::string expr = "11.1+2.2";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_point_2) {
  std::string expr = "3.+2.2";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_point_3) {
  std::string expr = "3.11+2.";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_1) {
  std::string expr = "3^4+1*9(2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_2) {
  std::string expr = "3^4+9.(2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_3) {
  std::string expr = "3^4+1*(.2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_4) {
  std::string expr = "3^4*1^()";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_5) {
  std::string expr = "7*(2-4)(6+9)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_6) {
  std::string expr = "3^4+1*9+(*2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_7) {
  std::string expr = "3^4+1*(";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_8) {
  std::string expr = "3^4+1*x(-2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_ok_leftpar_1) {
  std::string expr = "3^4+7*9/(2^(5+6)-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_leftpar_2) {
  std::string expr = "3^4+7*9/((5+6)^2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_leftpar_3) {
  std::string expr = "-(7+1)*8^3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_leftpar_4) {
  std::string expr = "3^4*2+(9-1)/6";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_leftpar_5) {
  std::string expr = "7*(-2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_leftpar_6) {
  std::string expr = "(4-5)^7";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_error_leftpar_9) {
  std::string expr = "4-5)^7";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_1) {
  std::string expr = "3^4+1*(2-4)7";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_2) {
  std::string expr = "3^4+1*(2-4).7";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_3) {
  std::string expr = "3^4+1*()";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_4) {
  std::string expr = "3^4+1*(2-4)(7)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_5) {
  std::string expr = "3^4+1*(2-4+)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_6) {
  std::string expr = ")7+3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_7) {
  std::string expr = "3^4+1*(2-atan)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_8) {
  std::string expr = "3^4+1*(2-4)sqrt(3)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_rightpar_9) {
  std::string expr = "3^4+1*(2-4)x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_ok_rightpar_1) {
  std::string expr = "3^4+7*9/(2^(5+6)-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_rightpar_2) {
  std::string expr = "3^4+7.1*9/((5+6.)^2-4.)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_rightpar_3) {
  std::string expr = "-(7+1)*8^(2-(4.2-5.1))";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_rightpar_4) {
  std::string expr = "3^4*2+(9-1)/6";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_ok_rightpar_5) {
  std::string expr = "7*(-2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
}

TEST(Parser_test, parcer_error_binary_1) {
  std::string expr = "3^4+1*.7";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_2) {
  std::string expr = "3^4+1*(2-4^)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_3) {
  std::string expr = "3^4+1*/5";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_4) {
  std::string expr = "3^4+1*(-^2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_5) {
  std::string expr = "3^4+1*cos*(2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_6) {
  std::string expr = "5^(*2-3)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_7) {
  std::string expr = "^3";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_binary_8) {
  std::string expr = "3^4+1*(2-4)^";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_unary_1) {
  std::string expr = "3^4+1*(-.7)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_unary_2) {
  std::string expr = "2-4.-";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_unary_3) {
  std::string expr = "3^4+1*(8/5-)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_unary_4) {
  std::string expr = "3^4+1*(-+2-4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_unary_5) {
  std::string expr = "-";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_unary_6) {
  std::string expr = "x-*7";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_1) {
  std::string expr = "3^4+1*(2-4)^sin 8";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_2) {
  std::string expr = "3^4+1*(2-4)-sin -8";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_3) {
  std::string expr = "3^4+1*sin sin (7)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_4) {
  std::string expr = "3^4+1*(2-4)-4 sin(3)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_5) {
  std::string expr = "3^4+1*(2-4+4.1 sin(10))";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_6) {
  std::string expr = "3+sin .1";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_7) {
  std::string expr = "3^4+1*(2-1)atan(6)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_8) {
  std::string expr = "3^4+1*(2-4*sqrt)/(3)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_9) {
  std::string expr = "3^4+1*(2-4)/sin *x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_10) {
  std::string expr = "3^4+1*(2-4)/sin   ";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_11) {
  std::string expr = "3^4+1*(2-4)/sin x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_func_12) {
  std::string expr = "3^4+1*(2-4)/x sin(3)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_1) {
  std::string expr = "3^4+1 x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_2) {
  std::string expr = "3^4+1*(2-x 4)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_3) {
  std::string expr = "3^4+1*5/x(5)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_4) {
  std::string expr = "3^4+1*(-2-4)x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_5) {
  std::string expr = "3^4+1*cos(2-4. x)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_6) {
  std::string expr = "5^(2-x.3)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_7) {
  std::string expr = "1^3-sin x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parcer_error_x_8) {
  std::string expr = "3^4+1*(2-4)^x sin(19)";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parser_error_input_0) {
  std::string expr = "";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parser_error_input_1) {
  std::string expr =
      "123456789012345678901234567890123456789012345678901234567890123456789012"
      "345678901234567890123456789012345678901234567890123456789012345678901234"
      "567890123456789012345678901234567890123456789012345678901234567890123456"
      "7890123456789012345678901234567890123456";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parser_error_input_2) {
  std::string expr = "123456789/(11.1+4";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
}

TEST(Parser_test, parser_error_input_3) {
  std::string expr = "22.2/11.1+x";
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_TRUE(result.error);
  x = "-5";
  result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, -3.0);
}

TEST(Parser_test, calc_1) {
  std::string expr = "1234.9824+89812.1246";
  double value_real = 1234.9824 + 89812.1246;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_2) {
  std::string expr = "1234.9824+x";
  double value_real = 1234.9824 + 89812.1246;
  std::string x = "89812.1246";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_3) {
  std::string expr = "1.2+2.3-4.5+6.7-9.8-2.3*10.11/12.13";
  double value_real = 1.2 + 2.3 - 4.5 + 6.7 - 9.8 - 2.3 * 10.11 / 12.13;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_4) {
  std::string expr =
      "tan( 3.764) ^sin( 9.445-sin( 7.2889 /  8.0438 -cos( sin(cos( "
      "tan(8.4448))) - 4.482)  )  / tan(cos(cos(sin(cos( "
      "cos(2.003)) )  ) / 0.1315) ))  -  8.8453/ 0.3612";
  double value_real = -23.76667454586336;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_5) {
  std::string expr = "1234.9824-89812.1246";
  double value_real = 1234.9824 - 89812.1246;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_6) {
  std::string expr = "-3-4+5";
  double value_real = -3 - 4 + 5;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_7) {
  std::string expr = "-3*-2";
  double value_real = -3 * -2;
  std::string x = "89812.1246";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_8) {
  std::string expr = "sin(-3)";
  double value_real = sin(-3);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_9) {
  std::string expr = "1234.98234*89812.12456";
  double value_real = 1234.98234 * 89812.12456;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_10) {
  std::string expr = "1234.98234 / 89812.12456";
  double value_real = 1234.98234 / 89812.12456;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_11) {
  std::string expr = "12^3.123";
  double value_real = pow(12, 3.123);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_12) {
  std::string expr = "2^(2^3)";
  double value_real = 256.0;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_13) {
  std::string expr = "sqrt(980987)";
  double value_real = sqrt(980987);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_14) {
  std::string expr = "1235.432mod12398793.234";
  double value_real = fmod(1235.432, 12398793.234);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_15) {
  std::string expr = "1235.432mod12398793.234 * 37";
  double value_real = fmod(1235.432, 12398793.234) * 37;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_16) {
  std::string expr = "cos(1.98087)";
  double value_real = cos(1.98087);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_17) {
  std::string expr = "tan(1.98087)";
  double value_real = tan(1.98087);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_18) {
  std::string expr = "asin(0.98087)";
  double value_real = asin(0.98087);
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_DOUBLE_EQ(result.value, value_real);
}

TEST(Parser_test, calc_19) {
  std::string expr = "(1+2)*4*cos(x*7-2)+sin(x*2)";
  double value_real = 9.36944500948197;
  std::string x = "2";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_NEAR(result.value, value_real, 1e-7);
}

TEST(Parser_test, calc_20) {
  std::string expr = "acos(0.123)";
  double value_real = 1.44748405;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_NEAR(result.value, value_real, 1e-7);
}

TEST(Parser_test, calc_21) {
  std::string expr = "atan(1.98087)";
  double value_real = 1.103293234;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_NEAR(result.value, value_real, 1e-7);
}

TEST(Parser_test, calc_22) {
  std::string expr = "ln(1.98087)";
  double value_real = 0.683536142;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_NEAR(result.value, value_real, 1e-7);
}

TEST(Parser_test, calc_23) {
  std::string expr = "log(1.98087)";
  double value_real = 0.29685597;
  std::string x = "";
  s21::Model M;
  s21::Controller C(&M);
  s21::ResultExpression result = C.CalculationExpression(expr, x);
  EXPECT_FALSE(result.error);
  EXPECT_NEAR(result.value, value_real, 1e-7);
}

TEST(Graph_test, graph_ok_1) {
  std::string expr = "x^2";
  s21::Model M;
  s21::Controller C(&M);
  std::string x_begin = "-1", x_end = "1", y_begin = "-1", y_end = "1";
  unsigned int num_points = 3;
  s21::ResultGraph result =
      C.CalculationGraph(expr, x_begin, x_end, y_begin, y_end, num_points);
  std::vector<double> x = {-1, 0, 1};
  std::vector<double> y = {-1, 0, 1};
  EXPECT_FALSE(result.error);
  EXPECT_EQ(result.x.size(), x.size());
  for (int i = 0; i < (int)result.x.size(); i++) {
    EXPECT_EQ(result.x[i], x[i]);
  }
}

TEST(Graph_test, graph_error_1) {
  std::string expr = "x^2";
  s21::Model M;
  s21::Controller C(&M);
  std::string x_begin = "cat-1", x_end = "1", y_begin = "-1", y_end = "1";
  unsigned int num_points = 3;
  s21::ResultGraph result =
      C.CalculationGraph(expr, x_begin, x_end, y_begin, y_end, num_points);
  EXPECT_TRUE(result.error);
}

TEST(Graph_test, graph_error_2) {
  std::string expr = "x^2";
  s21::Model M;
  s21::Controller C(&M);
  std::string x_begin = "-1", x_end = "1", y_begin = "2", y_end = "1";
  unsigned int num_points = 3;
  s21::ResultGraph result =
      C.CalculationGraph(expr, x_begin, x_end, y_begin, y_end, num_points);
  EXPECT_TRUE(result.error);
}

TEST(Graph_test, graph_error_3) {
  std::string expr = "x^2...";
  s21::Model M;
  s21::Controller C(&M);
  std::string x_begin = "-1", x_end = "1", y_begin = "-1", y_end = "1";
  unsigned int num_points = 3;
  s21::ResultGraph result =
      C.CalculationGraph(expr, x_begin, x_end, y_begin, y_end, num_points);
  EXPECT_TRUE(result.error);
}

TEST(Graph_test, graph_error_4) {
  std::string expr = "x^2...";
  s21::Model M;
  s21::Controller C(&M);
  std::string x_begin = "-1", x_end = "1", y_begin = "-1", y_end = "1";
  unsigned int num_points = 3;
  s21::ResultGraph result =
      C.CalculationGraph(expr, x_begin, x_end, y_begin, y_end, num_points);
  EXPECT_TRUE(result.error);
}
