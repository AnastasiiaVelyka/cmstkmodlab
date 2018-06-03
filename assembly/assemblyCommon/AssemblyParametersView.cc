/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//               Copyright (C) 2011-2017 - The DESY CMS Group                  //
//                           All rights reserved                               //
//                                                                             //
//      The CMStkModLab source code is licensed under the GNU GPL v3.0.        //
//      You have the right to modify and/or redistribute this source code      //
//      under the terms specified in the license, which may be found online    //
//      at http://www.gnu.org/licenses or at License.txt.                      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#include <nqlogger.h>
#include <ApplicationConfig.h>

#include <AssemblyParametersView.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolBox>
#include <QFileDialog>

AssemblyParametersView::AssemblyParametersView(QWidget* parent) :
  QWidget(parent),

  dime_wid_(nullptr),
  posi_wid_(nullptr),
  move_wid_(nullptr),
  imag_wid_(nullptr),

  paramIO_button_read_ (nullptr),
  paramIO_button_write_(nullptr)
{
  QVBoxLayout* layout = new QVBoxLayout;
  this->setLayout(layout);

  QToolBox* toolbox = new QToolBox;
  layout->addWidget(toolbox);

  // ---------------------

  // DIMENSIONS ----------
  dime_wid_ = new QWidget;

  toolbox->addItem(dime_wid_, tr("Dimensions of Assembly Components"));

//  QVBoxLayout* dime_lay = new QVBoxLayout;
//  dime_wid_->setLayout(dime_lay);
  // ---------------------

  // POSITIONS -----------
  posi_wid_ = new QWidget;

  toolbox->addItem(posi_wid_, tr("Reference Positions"));

//  QVBoxLayout* posi_lay = new QVBoxLayout;
//  posi_wid_->setLayout(posi_lay);
  // ---------------------

//!!
//!!  XYZA_lay_ = new QHBoxLayout;
//!!
//!!  QLabel* X_label = new QLabel("X");
//!!  QLabel* Y_label = new QLabel("Y");
//!!  QLabel* Z_label = new QLabel("Z");
//!!  QLabel* A_label = new QLabel("A");
//!!
//!!  X_lineed_ = new QLineEdit("");
//!!  Y_lineed_ = new QLineEdit("");
//!!  Z_lineed_ = new QLineEdit("");
//!!  A_lineed_ = new QLineEdit("");
//!!
//!!  XYZA_lay_->addWidget(X_label  );
//!!  XYZA_lay_->addWidget(X_lineed_);
//!!
//!!  XYZA_lay_->addWidget(Y_label  );
//!!  XYZA_lay_->addWidget(Y_lineed_);
//!!
//!!  XYZA_lay_->addWidget(Z_label  );
//!!  XYZA_lay_->addWidget(Z_lineed_);
//!!
//!!  XYZA_lay_->addWidget(A_label  );
//!!  XYZA_lay_->addWidget(A_lineed_);
//!!
//!!  layout_->addLayout(XYZA_lay_);

  // MOVEMENT ------------
  move_wid_ = new QWidget;

  toolbox->addItem(move_wid_, tr("Reference Movements"));

//  QVBoxLayout* move_lay = new QVBoxLayout;
//  move_wid_->setLayout(move_lay);
  // ---------------------

  /// IMAGE ---------------
  imag_wid_ = new QWidget;

  toolbox->addItem(imag_wid_, tr("Image Parameters"));

  QVBoxLayout* imag_lay = new QVBoxLayout;
  imag_wid_->setLayout(imag_lay);

  // pixel dimensions
  QHBoxLayout* imag_pix_lay = new QHBoxLayout;
  imag_lay->addLayout(imag_pix_lay);

  map_lineEdit_["mm_per_pixel_row"] = new QLineEdit(tr(""));
  map_lineEdit_["mm_per_pixel_col"] = new QLineEdit(tr(""));

  imag_pix_lay->addWidget(new QLabel(tr("Pixel Unit Dimensions")), 20);

  imag_pix_lay->addWidget(new QLabel(tr("X")), 5, Qt::AlignRight);
  imag_pix_lay->addWidget(map_lineEdit_["mm_per_pixel_row"], 15);

  imag_pix_lay->addWidget(new QLabel(tr("Y")), 5, Qt::AlignRight);
  imag_pix_lay->addWidget(map_lineEdit_["mm_per_pixel_col"], 15);

  imag_pix_lay->addWidget(new QLabel, 40);

  /// ---------------------

  layout->addStretch(1);

  QHBoxLayout* paramIO_lay = new QHBoxLayout;

  paramIO_button_read_  = new QPushButton(tr("Read From File"));

  paramIO_button_write_ = new QPushButton(tr("Write To File"));

  connect(paramIO_button_read_ , SIGNAL(clicked()), this, SLOT( read_parameters()));
  connect(paramIO_button_write_, SIGNAL(clicked()), this, SLOT(write_parameters()));

  paramIO_lay->addWidget(paramIO_button_read_ , 50);
  paramIO_lay->addWidget(paramIO_button_write_, 50);

  layout->addLayout(paramIO_lay);
}

void AssemblyParametersView::read_parameters()
{
  const QString f_path = QFileDialog::getOpenFileName(this, tr("Read Parameters"), QString::fromStdString(Config::CMSTkModLabBasePath+"/assembly/assembly"), tr("*.cfg"));

  if(f_path.isNull())
  {
    NQLog("AssemblyParametersView", NQLog::Critical) << "read_parameters"
       << ": empty path to input file for assembly parameters, no further action taken";

    return;
  }

  NQLog("AssemblyParametersView", NQLog::Spam) << "read_parameters"
     << ": emitting signal \"read_from_file_request(" << f_path << ")\"";

  emit read_from_file_request(f_path);
}

void AssemblyParametersView::write_parameters()
{
  const QString f_path = QFileDialog::getSaveFileName(this, tr("Write Parameters"), QString::fromStdString(Config::CMSTkModLabBasePath+"/assembly/assembly"), tr("*.cfg"));

  if(f_path.isNull())
  {
    NQLog("AssemblyParametersView", NQLog::Critical) << "write_parameters"
       << ": empty path to output file for assembly parameters, no further action taken";

    return;
  }

  NQLog("AssemblyParametersView", NQLog::Spam) << "write_parameters"
     << ": emitting signal \"write_to_file_request(" << f_path << ")\"";

  emit write_to_file_request(f_path);
}

bool AssemblyParametersView::has(const std::string& key) const
{
  return bool(map_lineEdit_.find(key) != map_lineEdit_.end());
}

QLineEdit* AssemblyParametersView::get(const std::string& key) const
{
  QLineEdit* ptr(nullptr);

  if(this->has(key) == false)
  {
    NQLog("AssemblyParametersView", NQLog::Fatal) << "get"
       << ": no QLineEdit object associated to parameter key \"" << key << "\", closing application";

    QMessageBox::critical(0
     , tr("[AssemblyParametersView::get]")
     , tr("Failed to find QLineEdit for key: \"%1\"\n.").arg(QString(key.c_str()))
     , QMessageBox::Abort
    );

    throw; // must abort
  }
  else
  {
    ptr = map_lineEdit_.at(key);
  }

  if(ptr == nullptr)
  {
    NQLog("AssemblyParametersView", NQLog::Fatal) << "get"
       << ": null pointer to QLineEdit associated to key \"" << key << "\", closing application";

    QMessageBox::critical(0
     , tr("[AssemblyParametersView::get]")
     , tr("Null pointer to QLineEdit for key: \"%1\"\n.").arg(QString(key.c_str()))
     , QMessageBox::Abort
    );

    throw; // must abort
  }

  return ptr;
}

void AssemblyParametersView::copy_values(const std::map<std::string, double>& map_double)
{
  for(const auto& key : map_double)
  {
    this->setText(key.first, key.second);
  }

  return;
}

void AssemblyParametersView::setText(const std::string& key, const double val)
{
  QLineEdit* const ptr = this->get(key);

  std::stringstream strs;
  strs << val;

  ptr->setText(QString::fromStdString(strs.str()));

  return;
}
