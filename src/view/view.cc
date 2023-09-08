#include "view.h"

#include "./ui_view.h"

namespace s21 {

View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), controller_(controller) {
  ui->setupUi(this);
  setWindowTitle("Smart Calculator");
  setFixedSize(geometry().width(), geometry().height());
  ui->lineEdit->setFocus();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(PrintSymb()));

  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(PrintDiv()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_lpar, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_rpar, SIGNAL(clicked()), this, SLOT(PrintSymb()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(PrintSymb()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(PrintSqrt()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(Clear()));

  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(PrintResult()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(MakeGraph()));
}

View::~View() { delete ui; }

void View::PrintSymb() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->insert(button->text());
  } else if (ui->lineEdit_x->hasFocus()) {
    ui->lineEdit_x->insert(button->text());
  }
}

void View::PrintFunc() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->insert(button->text() + "(");
  }
}

void View::PrintDiv() {
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->insert("/");
  } else if (ui->lineEdit_x->hasFocus()) {
    ui->lineEdit_x->insert("/");
  }
}

void View::PrintSqrt() {
  if (ui->lineEdit->hasFocus()) ui->lineEdit->insert("sqrt(");
}

void View::Clear() {
  if (ui->lineEdit->hasFocus())
    ui->lineEdit->setText("");
  else if (ui->lineEdit_x->hasFocus())
    ui->lineEdit_x->setText("");
  else if (ui->label->hasFocus())
    ui->label->setText("");
}

void View::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return) {
    PrintResult();
  } else {
    event->ignore();
  }
}

void View::PrintResult() {
  ui->label->setText(" ");
  std::string expression = ui->lineEdit->text().toStdString();
  std::string var = ui->lineEdit_x->text().toStdString();

  ResultExpression result_expression =
      controller_->CalculationExpression(expression, var);
  if (result_expression.error) {
    ui->label->setText(QString::fromStdString(result_expression.message));
  } else {
    ui->label->setText(QString::number(result_expression.value, 'g', 7));
  }
}

void View::MakeGraph() {
  graph_ = new Graph(this->controller_, this);

  std::string expression = ui->lineEdit->text().toStdString();

  std::string x_begin = graph_->GetBeginX();
  std::string x_end = graph_->GetEndX();
  std::string y_begin = graph_->GetBeginY();
  std::string y_end = graph_->GetEndY();
  std::size_t num_points = graph_->GetPoints();
  ResultGraph result_graph = controller_->CalculationGraph(
      expression, x_begin, x_end, y_begin, y_end, num_points);

  if (result_graph.error) {
    ui->label->setText(QString::fromStdString(result_graph.message));
  } else {
    graph_->SetExpression(expression);
    graph_->PlotNewGraph(result_graph.x, result_graph.y);
    graph_->show();
  }
}

}  // namespace s21
