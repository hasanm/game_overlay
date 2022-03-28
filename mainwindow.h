#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QComboBox;
class QVBoxLayout;
class QIcon;
class QTableWidget;
class QGridLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
 public:
  MainWindow();
  void onActivated(int index);
  void onColorChanged(int index); 
  void mySetSize();

private:
  int totalItems = 3;
  QPushButton *loadButton;
  QPushButton *quitButton;
  QComboBox* comboBox;
  QComboBox* colorBox; 
  QStringList buildOrders = {"scout", "maa", "drush", "archer"};
  QStringList colors = {"red", "black", "green", "maroon", "purple", "fuchsia", "lime", "olive", "yellow", "navy", "blue", "teal", "aqua"};
  QVBoxLayout *contentLayout;
  QTableWidget *tableWidget; 
  QGridLayout *gridLayout;

  QList<QString> iconNames;
  QList<QLabel*> iconLabels;

  int rows;
  int cols; 

  void initIconLabels();

};
