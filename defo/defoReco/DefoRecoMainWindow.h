#ifndef DEFORECOMAINWINDOW_H
#define DEFORECOMAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QImage>
#include <QTimer>

#include "DefoMeasurementListModel.h"

#include "DefoMeasurementSelectionModel.h"
#include "DefoMeasurementListComboBox.h"
#include "DefoImageWidget.h"

#include "DefoPointRecognitionModel.h"
#include "DefoPointRecognitionWidget.h"

class DefoRecoMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit DefoRecoMainWindow(QWidget *parent = 0);

public slots:

protected:

  QDir currentDir_;

  QTabWidget* tabWidget_;

  DefoMeasurementListModel *listModel_;

protected slots:
  void loadMeasurementButtonClicked();
};

#endif // DEFORECOMAINWINDOW_H
