#ifndef VIEW_H
#define VIEW_H

#include <QKeyEvent>
#include <QMainWindow>

#include "../controller/controller.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller* controller, QWidget* parent = nullptr);
  ~View();

 protected:
  void keyPressEvent(QKeyEvent* event) override;

 private slots:
  void PrintSymb();
  void PrintFunc();
  void PrintDiv();
  void PrintSqrt();
  void Clear();
  void PrintResult();
  void MakeGraph();

 private:
  Ui::View* ui;
  Controller* controller_;
  Graph* graph_;
};
}  // namespace s21
#endif  // VIEW_H
