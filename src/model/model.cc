#include "model.h"

#include <iomanip>

namespace s21 {

ResultExpression Model::CalculationExpression(std::string& expression,
                                              std::string& x) {
  ResultExpression result_expression;
  double x_value;
  ConvertToPostfix(expression);
  if (status_ == OK && x_presence_) {
    try {
      x_value = std::stod(x);
    } catch (...) {
      status_ = ERROR_X;
    }
  }
  if (status_ == OK) {
    CalculationPostfix(x_value);
    result_expression.value = result_;
    result_expression.error = false;
  } else {
    result_expression.error = true;
    result_expression.message = GetMessage();
  }

  return result_expression;
}

ResultGraph Model::CalculationGraph(const std::string& expression,
                                    const std::string& x_begin,
                                    const std::string& x_end,
                                    const std::string& y_begin,
                                    const std::string& y_end,
                                    const std::size_t& num_points) {
  ResultGraph graph;
  graph.error = false;
  ConvertToPostfix(expression);
  if (status_ == OK) {
    double x_min, x_max, y_min, y_max;
    try {
      x_min = std::stod(x_begin);
      x_max = std::stod(x_end);
      y_min = std::stod(y_begin);
      y_max = std::stod(y_end);
    } catch (...) {
      graph.error = true;
    }

    if (!graph.error) {
      if (std::fabs(x_min - x_max) < 1e-6 || x_min > x_max ||
          x_min < kGraphLimitBegin || x_max > kGraphLimitEnd ||
          std::fabs(y_min - y_max) < 1e-6 || y_min > y_max ||
          y_min < kGraphLimitBegin || y_max > kGraphLimitEnd) {
        graph.error = true;
      } else {
        double h = (x_max - x_min) / (num_points - 1);
        for (double i = x_min; i <= x_max; i += h) {
          CalculationPostfix(i);
          graph.x.push_back(i);
          graph.y.push_back(result_);
        }
        graph.error = false;
      }
    }
  } else {
    graph.message = GetMessage();
    graph.error = true;
  }
  return graph;
}

void Model::ConvertToPostfix(const std::string& expression) {
  if (expression.empty()) {
    status_ = ERROR_EMPTY;
  } else if (expression.size() > (std::size_t)255) {
    status_ = ERROR_LONG;
  } else if (infix_ != expression) {
    infix_ = expression;
    Parse();
  } else if (status_ == ERROR_X) {
    status_ = OK;
  }
}

void Model::CalculationPostfix(double x) {
  std::stack<double> num_stack;
  for (size_t i = 0; i < postfix_.size(); i++) {
    if (postfix_[i].type == NUM) {
      num_stack.push(postfix_[i].lexeme_value);
    } else if (postfix_[i].type == VAR) {
      num_stack.push(x);
    } else {
      PerformOperation(num_stack, postfix_[i]);
    }
  }
  result_ = num_stack.top();
}

void Model::PerformOperation(std::stack<double>& num_stack, Lexeme& oper) {
  double result, number = num_stack.top();  // operand
  num_stack.pop();
  if (oper.type == FUNC) {
    result = (*kFunctionList.find(oper.lexeme_value)).second(number);
  } else if (oper.lexeme_value == '^') {
    result = std::pow(num_stack.top(), number);
    num_stack.pop();
  } else if (oper.lexeme_value == 'm') {
    result = -number;
  } else if (oper.lexeme_value == '%') {
    result = std::fmod(num_stack.top(), number);
    num_stack.pop();
  } else {
    result = (*kOperatorList.find(oper.lexeme_value))
                 .second(num_stack.top(), number);
    num_stack.pop();
  }
  num_stack.push(result);
}

std::string Model::GetMessage() {
  std::string str_result;
  if (status_ == ERROR_SYNTAX) {
    str_result = "Неверное выражение";
  } else if (status_ == ERROR_X) {
    str_result = "Введите значение переменной";
  } else if (status_ == ERROR_EMPTY) {
    str_result = "Введите выражение";
  } else if (status_ == ERROR_LONG) {
    str_result = "Слишком длинное выражение";
  }
  return str_result;
}

void Model::Parse() {
  status_ = OK;
  x_presence_ = false;
  postfix_.clear();
  std::size_t i = 0, j;  // i - current index of expression, j - index of the
                         // first unconverted character(stod)
  LexemeType last_lexeme = START;
  std::stack<Lexeme> stack_operators;  // Stack of operators and functions

  while (i < infix_.size() && status_ == OK) {
    if (isDigit(infix_[i], last_lexeme)) {
      postfix_.push_back({std::stod(infix_.substr(i), &j), NUM});
      i += j - 1;
      last_lexeme = NUM;
    } else if (isLeftPar(infix_[i], last_lexeme)) {
      stack_operators.push((Lexeme)infix_[i]);
      last_lexeme = LPAR;
    } else if (isRightPar(infix_[i], last_lexeme)) {
      AddOper(stack_operators, infix_[i]);
      last_lexeme = RPAR;
    } else if (isBinary(i, last_lexeme)) {
      if (infix_.find("mod") == i) {
        AddOper(stack_operators, '%');
        i += 2;
      } else {
        AddOper(stack_operators, infix_[i]);
      }
      last_lexeme = BI_MUL;
    } else if (isUnary(infix_[i], last_lexeme)) {
      if (infix_[i] == '-') AddOper(stack_operators, 'm');
      last_lexeme = UNO;
    } else if (isFunc(i, last_lexeme, stack_operators)) {
      last_lexeme = FUNC;
    } else if (isVariable(infix_[i], last_lexeme)) {
      postfix_.push_back({(double)infix_[i], VAR});
      x_presence_ = true;
      last_lexeme = VAR;
    } else if (infix_[i] != ' ') {
      status_ = ERROR_SYNTAX;
    }
    i++;
  }

  if (status_ == OK && (last_lexeme == LPAR || last_lexeme > RPAR))
    status_ = ERROR_SYNTAX;

  while (status_ == OK && !stack_operators.empty()) {
    postfix_.push_back(stack_operators.top());
    stack_operators.pop();
    if (postfix_.back().lexeme_value == '(') status_ = ERROR_SYNTAX;
  }
}

void Model::AddOper(std::stack<Model::Lexeme>& stack_operators,
                    const char& symb) {
  Lexeme currentOper(symb);
  while (!stack_operators.empty() &&
         stack_operators.top().type >= currentOper.type &&
         stack_operators.top().type > RPAR) {
    postfix_.push_back(stack_operators.top());
    stack_operators.pop();
  }
  if (symb != ')') {
    stack_operators.push(currentOper);
  } else if (!stack_operators.empty()) {
    stack_operators.pop();
  } else {
    status_ = ERROR_SYNTAX;
  }
}

bool Model::isDigit(const char& symb, LexemeType& last_lexeme) const noexcept {
  bool last_lexeme_check = (last_lexeme != FUNC && last_lexeme != RPAR &&
                            last_lexeme != VAR && last_lexeme != NUM);
  return (symb >= '0' && symb <= '9' && last_lexeme_check);
}

bool Model::isLeftPar(const char& symb,
                      LexemeType& last_lexeme) const noexcept {
  return (symb == '(' &&
          (last_lexeme > RPAR || last_lexeme == START || last_lexeme == LPAR));
}

bool Model::isRightPar(const char& symb,
                       LexemeType& last_lexeme) const noexcept {
  return (symb == ')' &&
          (last_lexeme == NUM || last_lexeme == RPAR || last_lexeme == VAR));
}

bool Model::isBinary(std::size_t& i, LexemeType& last_lexeme) const {
  std::string token = "+-*/^";
  bool binaryOk =
      token.find(infix_[i]) != token.npos || infix_.find("mod") == i;
  bool last_lexeme_check =
      (last_lexeme == NUM || last_lexeme == RPAR || last_lexeme == VAR);

  return (binaryOk && last_lexeme_check);
}

bool Model::isUnary(const char& symb, LexemeType& last_lexeme) const noexcept {
  bool last_lexeme_check = (last_lexeme == START || last_lexeme == BI_MUL ||
                            last_lexeme == LPAR || last_lexeme == VAR);
  return (symb == '+' || symb == '-') && last_lexeme_check;
}

bool Model::isFunc(std::size_t& i, LexemeType& last_lexeme,
                   std::stack<Model::Lexeme>& stack_operators) {
  bool last_lexeme_check = (last_lexeme != NUM && last_lexeme != RPAR &&
                            last_lexeme != VAR && last_lexeme != FUNC);
  int pos;
  bool result = last_lexeme_check && FindFuncToken(infix_.substr(i), pos);

  if (result) {
    AddOper(stack_operators, kFuncToken[pos].second);
    i += kFuncToken[pos].first.size() - 1;
  }
  return result;
}

bool Model::isVariable(const char& symb,
                       LexemeType& last_lexeme) const noexcept {
  return symb == 'x' && last_lexeme != NUM && last_lexeme != RPAR &&
         last_lexeme != FUNC;
}

bool Model::FindFuncToken(const std::string& str, int& pos) {
  auto token_num = (int)kFuncToken.size();
  for (pos = 0; pos < token_num && str.find(kFuncToken[pos].first) != 0; pos++)
    ;
  return pos < token_num;
}

Model::Lexeme::Lexeme(const char& symb) : lexeme_value(symb) {
  if (symb == '(') {
    type = LPAR;
  } else if (symb == ')') {
    type = RPAR;
  } else if (symb == '+' || symb == '-') {
    type = BI_PLUS;
  } else if (symb == '*' || symb == '/' || symb == '%') {
    type = BI_MUL;
  } else if (symb == '^') {
    type = BI_POW;
  } else if (symb == 'm') {
    type = UNO;
  } else {
    type = FUNC;
  }
}

}  // namespace s21
