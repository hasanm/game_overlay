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
  qApp->setStyleSheet("QLabel { color: red; font: bold 14px;}");
  
  QWidget *root = new QWidget(this);
  QWidget *top = new QWidget(this);
  QWidget *content = new QWidget(this);

  /* Top Layout */ 
  QHBoxLayout *topLayout = new QHBoxLayout(top);
  quitButton = new QPushButton(QString ("Quit"), this);
  connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
  topLayout->addWidget(quitButton);

  colorBox = new QComboBox(this);
  colorBox->addItems(colors);
  connect(colorBox, &QComboBox::activated, this , &MainWindow::onColorChanged);
  topLayout->addWidget(colorBox); 

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


void MainWindow::onColorChanged(int index) {
  QString color;
  qDebug() << "Chose :  " << index;
  color = colors.at(index);
  qApp->setStyleSheet(QString("QLabel { color: %1; font: bold 14px;}").arg(color));
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
    buildOrder = buildOrders.at(index);
    
    QString fileName = QString(":/%1").arg(buildOrder);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    int r = 1; 
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;        
        QStringList parts = line.split(QLatin1Char(','));
        for (int i =0; i< parts.size() && i < 4; ++i){
          label = new QLabel(parts.at(i), this);
          gridLayout->addWidget(label, r, i);          
        }
        r++;
    }
    file.close();
}

void MainWindow::mySetSize() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rec = screen->availableGeometry();
    qDebug() << "Hello " << rec.width() << " x " << rec.height();

    int targetWidth = this->width();
    // int targetWidth = 300;

    int height = 180;
    int width = rec.width();
    int x=(width - targetWidth);
    int y= 50;
    this->setGeometry(x,y,targetWidth,height);
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
