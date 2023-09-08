#include "graph.h"

#include "ui_graph.h"

namespace s21 {

Graph::Graph(Controller* controller, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::Graph),
      graph_controller_(controller),
      x_begin_(kBeginLimit),
      x_end_(kEndLimit),
      y_begin_(kBeginLimit),
      y_end_(kEndLimit) {
  ui->setupUi(this);
  setWindowTitle("Graph");
  setFixedSize(geometry().width(), geometry().height());
  ui->lineEdit_x_min->setText(QString::number(x_begin_));
  ui->lineEdit_x_max->setText(QString::number(x_end_));
  ui->lineEdit_y_min->setText(QString::number(y_begin_));
  ui->lineEdit_y_max->setText(QString::number(y_end_));
  ui->widget->clearGraphs();

  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(PlotGraph()));
}

Graph::~Graph() { delete ui; }

void Graph::PlotNewGraph(std::vector<double> x, std::vector<double> y) {
  x_ = QVector<double>(x.begin(), x.end());
  y_ = QVector<double>(y.begin(), y.end());
  ui->widget->clearGraphs();

  ui->widget->xAxis->setRange(x_begin_, x_end_);
  ui->widget->yAxis->setRange(y_begin_, y_end_);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->addGraph();
  ui->widget->graph(0)->setPen(QPen(QColor(151, 146, 237)));
  ui->widget->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc, 2));

  ui->widget->graph(0)->addData(x_, y_);
  ui->widget->replot();
}

void Graph::PlotGraph() {
  std::string x_begin, x_end, y_begin, y_end;
  x_begin = ui->lineEdit_x_min->text().toStdString();
  x_end = ui->lineEdit_x_max->text().toStdString();
  y_begin = ui->lineEdit_y_min->text().toStdString();
  y_end = ui->lineEdit_y_max->text().toStdString();
  std::size_t num_points = GetPoints();

  ResultGraph result_graph = graph_controller_->CalculationGraph(
      expression_, x_begin, x_end, y_begin, y_end, num_points);
  if (result_graph.error) {
    QMessageBox msgBox;
    msgBox.setFixedSize(QSize(600, 120));
    msgBox.addButton("Ok", QMessageBox::YesRole);
    msgBox.setText("Упс! Неверные значения для границ!");
    msgBox.setStyleSheet("QDialogButtonBox { qproperty-centerButtons: true; }");
    msgBox.exec();
  } else {
    x_begin_ = ui->lineEdit_x_min->text().toDouble();
    x_end_ = ui->lineEdit_x_max->text().toDouble();
    y_begin_ = ui->lineEdit_y_min->text().toDouble();
    y_end_ = ui->lineEdit_y_max->text().toDouble();
    PlotNewGraph(result_graph.x, result_graph.y);
  }
}

void Graph::SetExpression(std::string expr) { expression_ = expr; }

std::size_t Graph::GetPoints() {
  return (std::size_t)ui->widget->geometry().width();
}

std::string Graph::GetBeginX() { return std::to_string(x_begin_); }

std::string Graph::GetEndX() { return std::to_string(x_end_); }

std::string Graph::GetBeginY() { return std::to_string(y_begin_); }

std::string Graph::GetEndY() { return std::to_string(y_end_); }

}  // namespace s21
