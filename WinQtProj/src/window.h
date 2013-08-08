#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
class QGridLayout;
class QVBoxLayout;
QT_END_NAMESPACE
class RenderWgt;

//! [0]
class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
	void mainInit(QVBoxLayout *vLayout);
	void tabsInit(QVBoxLayout *vLayout);
	void t1Init(QWidget *tabWgt);
	void t2Init(QWidget *tabWgt);
	void t3Init(QWidget *tabWgt);
	void menuInit();

private slots:
    void shapeChanged();
    void penChanged();
    void brushChanged();

private:
    RenderWgt *renderWgt;
    QLabel *shapeLabel;
    QLabel *penWidthLabel;
    QLabel *penStyleLabel;
    QLabel *penCapLabel;
    QLabel *penJoinLabel;
    QLabel *brushStyleLabel;
    QLabel *otherOptionsLabel;
    QComboBox *shapeComboBox;
    QSpinBox *penWidthSpinBox;
    QComboBox *penStyleComboBox;
    QComboBox *penCapComboBox;
    QComboBox *penJoinComboBox;
    QComboBox *brushStyleComboBox;
    QCheckBox *antialiasingCheckBox;
    QCheckBox *transformationsCheckBox;
};
//! [0]

#endif
