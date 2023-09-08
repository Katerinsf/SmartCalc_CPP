#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

/*! \mainpage Drawing Shapes
 *
 *
 * Very Smart Calculator
 */

/*!
\file
*Header for Calculator
*/

#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

/// Result of calculation
struct ResultExpression {
  double value;
  std::string message;
  bool error;
};

/// Result of graph points
struct ResultGraph {
  std::vector<double> x;
  std::vector<double> y;
  std::string message;
  bool error;
};

/// Class for model that contains the business logic
class Model {
 public:
  /// Default constructor
  Model()
      : infix_({}), postfix_({}), result_(), status_(OK), x_presence_(false){};

  /*!
      Calculates the value of expression
      \param expression Input string
      \param x Varible
      \result Struct with value of expression and error
  */
  ResultExpression CalculationExpression(std::string& expression,
                                         std::string& x);

  /*!
      Calculates points on a graph
      \param expression Input string
      \param x_begin Start of domian
      \param x_end End of domian
      \param y_begin Start of codomian
      \param y_end End of codomian
      \param num_points Number of points on a graph
      \result Struct with vector x, vector y and error
  */
  ResultGraph CalculationGraph(const std::string& expression,
                               const std::string& x_begin,
                               const std::string& x_end,
                               const std::string& y_begin,
                               const std::string& y_end,
                               const std::size_t& num_points);

 private:
  /// Code of error for calculation
  typedef enum ErrorType {
    OK,            /// Expressions was parsed and calculated
    ERROR_SYNTAX,  /// There is error of syntax
    ERROR_X,       /// No find varible
    ERROR_EMPTY,   /// The string is empty
    ERROR_LONG     /// The string is too long
  } ErrorType;

  /// Types of input struct
  typedef enum LexemeType {
    START,    /// Start of expression
    NUM,      /// Number
    VAR,      /// Variable
    LPAR,     /// Left parenthesis
    RPAR,     /// Right parenthesis
    BI_PLUS,  /// Binary plus and minus
    BI_MUL,   /// Binary multiplication, division and mod
    BI_POW,   /// Power
    UNO,      /// Unary plus and minus
    FUNC      /// Function
  } LexemeType;

  /// Struct contains value of number or sumbol of operator and type(priority)
  /// of lexeme
  struct Lexeme {
    /*!
        Constructor with value and type of lexeme
        \param value Value of number or sumbol
        \param t Type(priority) of lexeme
    */
    Lexeme(const double& value, const LexemeType& t)
        : lexeme_value(value), type(t) {}
    /*!
        Constructor with value, which determines a type(priority) of lexeme
        \param symb Value of number or sumbol
    */
    explicit Lexeme(const char& symb);

    double lexeme_value;  ///< Value of number or sumbol of operator
    LexemeType type;      ///< Type/priority of lexeme
  };

  /// Constant with lower bound of domain and codomain
  const double kGraphLimitBegin = -1e6;
  /// Constant with upper bound of domain and codomain
  const double kGraphLimitEnd = 1e6;

  /// Constant containing functions and their designations in postfix string
  const std::vector<std::pair<std::string, char>> kFuncToken = {
      {"sin", 's'},  {"cos", 'c'},  {"tan", 't'}, {"asin", 'S'}, {"acos", 'C'},
      {"atan", 'T'}, {"sqrt", 'V'}, {"ln", 'l'},  {"log", 'g'}};
  /// Constant containing arithmetic operators(in C++) and their symbols
  const std::map<char, std::function<double(double, double)>> kOperatorList = {
      {'+', std::plus<double>()},
      {'-', std::minus<double>()},
      {'*', std::multiplies<double>()},
      {'/', std::divides<double>()}};
  /// Constant containing functions(in C++) and their designations in postfix
  /// string
  const std::map<char, double (*)(double)> kFunctionList = {
      {'s', std::sin},  {'c', std::cos},  {'t', std::tan},
      {'S', std::asin}, {'C', std::acos}, {'T', std::atan},
      {'V', std::sqrt}, {'l', std::log},  {'g', std::log10}};

  /*!
      Converts expression from infix to Reverse Polish notation
      \param expression Input string
  */
  void ConvertToPostfix(const std::string& expression);

  /*!
      Calculates expression in postfix notation with substitution of the value
     of the variable x as a number \param x Variable
  */
  void CalculationPostfix(double x);

  /*!
      Performs an operator action
      \param num_stack Stack of numbers
      \param oper Operator
  */
  void PerformOperation(std::stack<double>& num_stack, Lexeme& oper);

  /*!
      Returns string with error message
      \result String with error message
  */
  [[nodiscard]] std::string GetMessage();

  /// Converts expression from infix to Reverse Polish notation and checks it
  void Parse();

  /*!
      Adds operator to the stack or pops it from the stack, if the priority is
     less \param stack_operators Stack of operators \param symb Symbol of
     operators
  */
  void AddOper(std::stack<Lexeme>& stack_operators, const char& symb);

  /*!
      Checks that lexeme is digit
      \param symb Input symbol
      \param last_lexeme Type of last lexeme for checking a combination
  */
  bool isDigit(const char& symb, LexemeType& last_lexeme) const noexcept;

  /*!
      Checks that lexeme is left parenthesis
      \param symb Input symbol
      \param last_lexeme Type of last lexeme for checking a combination
  */
  bool isLeftPar(const char& symb, LexemeType& last_lexeme) const noexcept;

  /*!
      Checks that lexeme is right parenthesis
      \param symb Input symbol
      \param last_lexeme Type of last lexeme for checking a combination
  */
  bool isRightPar(const char& symb, LexemeType& last_lexeme) const noexcept;

  /*!
      Checks that lexeme is binary operator
      \param i Number of symbol in string
      \param last_lexeme Type of last lexeme for checking a combination
  */
  bool isBinary(std::size_t& i, LexemeType& last_lexeme) const;

  /*!
      Checks that lexeme is unary operator
      \param symb Input symbol
      \param last_lexeme Type of last lexeme for checking a combination
  */
  bool isUnary(const char& symb, LexemeType& last_lexeme) const noexcept;

  /*!
      Checks that lexeme is function
      \param symb Number of symbol in string
      \param last_lexeme Type of last lexeme for checking a combination
      \param stack_operators Stack of operators
  */
  bool isFunc(std::size_t& i, LexemeType& last_lexeme,
              std::stack<Lexeme>& stack_operators);

  /*!
      Checks that lexeme is variable
      \param symb Input symbol
      \param last_lexeme Type of last lexeme for checking a combination
  */
  bool isVariable(const char& symb, LexemeType& last_lexeme) const noexcept;

  /*!
      Searches functions token in expression
      \param str Input string
      \param pos Position of symbol in string
  */
  bool FindFuncToken(const std::string& str, int& pos);

  std::string infix_;            ///< Expression in infix notation
  std::vector<Lexeme> postfix_;  ///< Expression in postfix notation
  double result_;                ///< Result of calculation
  ErrorType status_;             ///< Error
  bool x_presence_;  ///< Variable that indicates there is X in the expression

};  // Model
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H