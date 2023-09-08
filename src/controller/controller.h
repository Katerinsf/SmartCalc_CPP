#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model* model) : model_(model){};
  ResultExpression CalculationExpression(std::string& expression,
                                         std::string& x);
  ResultGraph CalculationGraph(const std::string& expression,
                               const std::string& x_begin,
                               const std::string& x_end,
                               const std::string& y_begin,
                               const std::string& y_end,
                               const std::size_t& num_points);

 private:
  Model* model_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H