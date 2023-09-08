#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>

#include "../controller/controller.h"

namespace Ui {
class Graph;
}

namespace s21 {

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(Controller* controller, QWidget* parent = nullptr);
  ~Graph();

  void PlotNewGraph(std::vector<double> x, std::vector<double> y);
  void SetExpression(std::string expr);
  std::size_t GetPoints();
  std::string GetBeginX();
  std::string GetEndX();
  std::string GetBeginY();
  std::string GetEndY();

 private slots:
  void PlotGraph();

 private:
  static constexpr double kBeginLimit = -5.0;
  static constexpr double kEndLimit = 5.0;

  Ui::Graph* ui;
  Controller* graph_controller_;
  QVector<double> x_, y_;
  double x_begin_, x_end_, y_begin_, y_end_;
  std::string expression_;
};
}  // namespace s21

#endif  // GRAPH_H
