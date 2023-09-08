#include "controller.h"

namespace s21 {

ResultExpression Controller::CalculationExpression(std::string& expression,
                                                   std::string& x) {
  return model_->CalculationExpression(expression, x);
}

ResultGraph Controller::CalculationGraph(const std::string& expression,
                                         const std::string& x_begin,
                                         const std::string& x_end,
                                         const std::string& y_begin,
                                         const std::string& y_end,
                                         const std::size_t& num_points) {
  return model_->CalculationGraph(expression, x_begin, x_end, y_begin, y_end,
                                  num_points);
}

}  // namespace s21
