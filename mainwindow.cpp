#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout> 
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "mainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QTableWidgetItem>


MainWindow::MainWindow()
  :rows (20),
   cols(4)
{
  qApp->setStyleSheet("QLabel { color: red}");

  QWidget *root = new QWidget(this);
  QWidget *top = new QWidget(this);
  QWidget *content = new QWidget(this);

  /* Top Layout */ 
  QHBoxLayout *topLayout = new QHBoxLayout(top);
  quitButton = new QPushButton(QString ("Quit"), this);
  connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
  topLayout->addWidget(quitButton);

  comboBox = new QComboBox(this);
  comboBox->addItems(buildOrders);
  connect(comboBox, &QComboBox::activated, this, &MainWindow::onActivated);
  topLayout->addWidget(comboBox);

  top->setLayout(topLayout);

  /* Content Layout */
  
  contentLayout = new QVBoxLayout(content);

  QGroupBox *groupBox = new QGroupBox("Icons");
  gridLayout = new QGridLayout;

  /* Init Icons */
  initIconLabels();
  int i = 0;
  for (QLabel* &iconLabel : iconLabels) {
    // gridLayout->addWidget(iconLabel, i+1, 0, 0);
    // QLabel* tmpLabel  = new QLabel("This");
    gridLayout->addWidget(iconLabel,0, i);
    i++; 
  } 
  // contentLayout->addWidget(widget);
  groupBox->setLayout(gridLayout);
  contentLayout->addWidget(groupBox);

  /* Root Layout */
  QVBoxLayout *rootLayout = new QVBoxLayout(root);
  // onActivated(0);

  rootLayout->addWidget(top);
  rootLayout->addWidget(content);  
  setCentralWidget(root);
  // Transparency
  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setParent(0); // Create TopLevel-Widget
  setAttribute(Qt::WA_NoSystemBackground, true);
  setAttribute(Qt::WA_TranslucentBackground, true);
  // setAttribute(Qt::WA_PaintOnScreen);
} 


void MainWindow::onActivated(int index) {
   QLayoutItem *item;
   QLabel *label;
    QString buildOrder;
    // while ((item = contentLayout->takeAt(0)) != NULL) {g
    //     if (item->widget() != nullptr)
    //         delete item->widget();
    //     //delete item;
    // }
    for (int r = 1; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        item = gridLayout->itemAtPosition(r,c);
        if (item != nullptr) {
          if (item->widget() != nullptr) {
            // gridLayout->removeWidget(item->widget());
            delete item->widget();
            //delete item;
          }
        } 
      } 
    } 
    qDebug() << "Chose :  " << index;
    switch(index) {
    case 0:
        buildOrder = buildOrders.at(index);
        qDebug() << buildOrder;
        break;
    case 1:
        buildOrder = buildOrders.at(index);
        qDebug() << buildOrder;
        break;
    case 2:
        buildOrder = buildOrders.at(index);
        qDebug() << buildOrder;
        break;
    default:
        qDebug() << "Unknown";
        break;
    }    


    QString fileName = QString(":/%1").arg(buildOrder);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    int r = 1; 
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
        label = new QLabel(line, this);
        gridLayout->addWidget(label, r, 0);
        r++;
    }
    file.close();
}

void MainWindow::mySetSize() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rec = screen->availableGeometry();
    qDebug() << "Hello " << rec.width() << " x " << rec.height();

    int height = 180;
    int width = rec.width();
    int x=(width - this->width());
    int y= 50;
    this->setGeometry(x,y,this->width(),height);
}

void MainWindow::initIconLabels() {
    iconNames << ":/img/wood.png" << ":/img/food.png" << ":/img/gold.png" << ":/img/stone.png";
    QPixmap *p;
    for (const auto &s : iconNames) {
      qDebug() << s;
      QIcon *icon = new QIcon(s);
      QPixmap pixmap = icon->pixmap(QSize(32, 32));
      p = new QPixmap(pixmap);
      QLabel *iconLabel = new QLabel("Icon");
      iconLabel->setPixmap(*p);
      iconLabels << iconLabel;
      delete icon;
    }
}
