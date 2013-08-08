#include <QtGui>

#include "renderwgt.h"
#include "window.h"
#include "moc_window.h"

const int IdRole = Qt::UserRole;

void Window::menuInit()
{
   QMenuBar* menuBar = new QMenuBar;

   QMenu* fileMenu = new QMenu(tr("&File"), this);
   QAction* exitAction = fileMenu->addAction(tr("E&xit"));
   menuBar->addMenu(fileMenu);
   layout()->setMenuBar(menuBar);

   connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void Window::shapeChanged()
{
    RenderWgt::Shape shape = RenderWgt::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), IdRole).toInt());
    renderWgt->setShape(shape);
}

void Window::penChanged()
{
    int width = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
            penStyleComboBox->currentIndex(), IdRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
            penCapComboBox->currentIndex(), IdRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
            penJoinComboBox->currentIndex(), IdRole).toInt());

    renderWgt->setPen(QPen(Qt::blue, width, style, cap, join));
}

void Window::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
//! [13]
            brushStyleComboBox->currentIndex(), IdRole).toInt());

//! [14]
    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::black);
        renderWgt->setBrush(linearGradient);
//! [14] //! [15]
    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::black);
        renderWgt->setBrush(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::black);
        renderWgt->setBrush(conicalGradient);
//! [15] //! [16]
    } else if (style == Qt::TexturePattern) {
        renderWgt->setBrush(QBrush(QPixmap(":/images/brick.png")));
//! [16] //! [17]
    } else {
        renderWgt->setBrush(QBrush(Qt::green, style));
    }
}

void Window::mainInit(QVBoxLayout *vLayout)
{
    renderWgt = new RenderWgt;

	vLayout->addWidget(renderWgt);//, 0, 0, 1, 4);


    setWindowTitle(tr("imgprcstd"));
}

void Window::tabsInit(QVBoxLayout *vLayout)
{
	QTabWidget *tabs = new QTabWidget;
	vLayout->addWidget(tabs);

	QWidget *tabWgt = new QWidget;
	tabs->addTab(tabWgt, tr("t1"));
	t1Init(tabWgt);

	tabWgt = new QWidget;
	tabs->addTab(tabWgt, tr("t2"));
	t2Init(tabWgt);

	tabWgt = new QWidget;
	tabs->addTab(tabWgt, tr("t3"));
	t3Init(tabWgt);
}

void Window::t1Init(QWidget *tabWgt)
{

}

void Window::t2Init(QWidget *tabWgt)
{
	QGridLayout *gLayout = new QGridLayout(tabWgt);
	gLayout->setColumnStretch(0, 1);
    gLayout->setColumnStretch(3, 1);

    shapeComboBox = new QComboBox;
#if 0
	shapeComboBox->addItem(tr("Polygon"), renderWgt::Polygon);
	shapeComboBox->addItem(tr("Rectangle"), renderWgt::Rect);
	shapeComboBox->addItem(tr("Rounded Rectangle"), renderWgt::RoundedRect);
	shapeComboBox->addItem(tr("Ellipse"), renderWgt::Ellipse);
	shapeComboBox->addItem(tr("Pie"), renderWgt::Pie);
	shapeComboBox->addItem(tr("Chord"), renderWgt::Chord);
	shapeComboBox->addItem(tr("Path"), renderWgt::Path);
	shapeComboBox->addItem(tr("Line"), renderWgt::Line);
	shapeComboBox->addItem(tr("Polyline"), renderWgt::Polyline);
	shapeComboBox->addItem(tr("Arc"), renderWgt::Arc);
	shapeComboBox->addItem(tr("Points"), renderWgt::Points);
	shapeComboBox->addItem(tr("Text"), renderWgt::Text)

#endif // 0

    shapeComboBox->addItem(tr("Pixmap"), RenderWgt::Pixmap);

    shapeLabel = new QLabel(tr("&Shape:"));
    shapeLabel->setBuddy(shapeComboBox);

	penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 20);
    penWidthSpinBox->setSpecialValueText(tr("0 (cosmetic pen)"));

    penWidthLabel = new QLabel(tr("Pen &Width:"));
    penWidthLabel->setBuddy(penWidthSpinBox);

	penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem(tr("Solid"), Qt::SolidLine);
    penStyleComboBox->addItem(tr("Dash"), Qt::DashLine);
    penStyleComboBox->addItem(tr("Dot"), Qt::DotLine);
    penStyleComboBox->addItem(tr("Dash Dot"), Qt::DashDotLine);
    penStyleComboBox->addItem(tr("Dash Dot Dot"), Qt::DashDotDotLine);
    penStyleComboBox->addItem(tr("None"), Qt::NoPen);

    penStyleLabel = new QLabel(tr("&Pen Style:"));
    penStyleLabel->setBuddy(penStyleComboBox);

    penCapComboBox = new QComboBox;
    penCapComboBox->addItem(tr("Flat"), Qt::FlatCap);
    penCapComboBox->addItem(tr("Square"), Qt::SquareCap);
    penCapComboBox->addItem(tr("Round"), Qt::RoundCap);

    penCapLabel = new QLabel(tr("Pen &Cap:"));
    penCapLabel->setBuddy(penCapComboBox);

    penJoinComboBox = new QComboBox;
    penJoinComboBox->addItem(tr("Miter"), Qt::MiterJoin);
    penJoinComboBox->addItem(tr("Bevel"), Qt::BevelJoin);
    penJoinComboBox->addItem(tr("Round"), Qt::RoundJoin);

    penJoinLabel = new QLabel(tr("Pen &Join:"));
    penJoinLabel->setBuddy(penJoinComboBox);

	brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem(tr("Linear Gradient"),
            Qt::LinearGradientPattern);
    brushStyleComboBox->addItem(tr("Radial Gradient"),
            Qt::RadialGradientPattern);
    brushStyleComboBox->addItem(tr("Conical Gradient"),
            Qt::ConicalGradientPattern);
    brushStyleComboBox->addItem(tr("Texture"), Qt::TexturePattern);
    brushStyleComboBox->addItem(tr("Solid"), Qt::SolidPattern);
    brushStyleComboBox->addItem(tr("Horizontal"), Qt::HorPattern);
    brushStyleComboBox->addItem(tr("Vertical"), Qt::VerPattern);
    brushStyleComboBox->addItem(tr("Cross"), Qt::CrossPattern);
    brushStyleComboBox->addItem(tr("Backward Diagonal"), Qt::BDiagPattern);
    brushStyleComboBox->addItem(tr("Forward Diagonal"), Qt::FDiagPattern);
    brushStyleComboBox->addItem(tr("Diagonal Cross"), Qt::DiagCrossPattern);
    brushStyleComboBox->addItem(tr("Dense 1"), Qt::Dense1Pattern);
    brushStyleComboBox->addItem(tr("Dense 2"), Qt::Dense2Pattern);
    brushStyleComboBox->addItem(tr("Dense 3"), Qt::Dense3Pattern);
    brushStyleComboBox->addItem(tr("Dense 4"), Qt::Dense4Pattern);
    brushStyleComboBox->addItem(tr("Dense 5"), Qt::Dense5Pattern);
    brushStyleComboBox->addItem(tr("Dense 6"), Qt::Dense6Pattern);
    brushStyleComboBox->addItem(tr("Dense 7"), Qt::Dense7Pattern);
    brushStyleComboBox->addItem(tr("None"), Qt::NoBrush);

    brushStyleLabel = new QLabel(tr("&Brush:"));
    brushStyleLabel->setBuddy(brushStyleComboBox);

	otherOptionsLabel = new QLabel(tr("Options:"));

	antialiasingCheckBox = new QCheckBox(tr("&Antialiasing"));

	transformationsCheckBox = new QCheckBox(tr("&Transformations"));

	
	connect(shapeComboBox, SIGNAL(activated(int)),
            this, SLOT(shapeChanged()));
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(penChanged()));
    connect(penStyleComboBox, SIGNAL(activated(int)),
            this, SLOT(penChanged()));
    connect(penCapComboBox, SIGNAL(activated(int)),
            this, SLOT(penChanged()));
    connect(penJoinComboBox, SIGNAL(activated(int)),
            this, SLOT(penChanged()));
    connect(brushStyleComboBox, SIGNAL(activated(int)),
            this, SLOT(brushChanged()));
    connect(antialiasingCheckBox, SIGNAL(toggled(bool)),
            renderWgt, SLOT(setAntialiased(bool)));
    connect(transformationsCheckBox, SIGNAL(toggled(bool)),
            renderWgt, SLOT(setTransformed(bool)));

    gLayout->addWidget(shapeLabel, 2, 0, Qt::AlignRight);
    gLayout->addWidget(shapeComboBox, 2, 1);
    gLayout->addWidget(penWidthLabel, 3, 0, Qt::AlignRight);
    gLayout->addWidget(penWidthSpinBox, 3, 1);
    gLayout->addWidget(penStyleLabel, 4, 0, Qt::AlignRight);
    gLayout->addWidget(penStyleComboBox, 4, 1);
    gLayout->addWidget(penCapLabel, 3, 2, Qt::AlignRight);
    gLayout->addWidget(penCapComboBox, 3, 3);
    gLayout->addWidget(penJoinLabel, 2, 2, Qt::AlignRight);
    gLayout->addWidget(penJoinComboBox, 2, 3);
    gLayout->addWidget(brushStyleLabel, 4, 2, Qt::AlignRight);
    gLayout->addWidget(brushStyleComboBox, 4, 3);
    gLayout->addWidget(otherOptionsLabel, 5, 0, Qt::AlignRight);
    gLayout->addWidget(antialiasingCheckBox, 5, 1, 1, 1, Qt::AlignRight);
    gLayout->addWidget(transformationsCheckBox, 5, 2, 1, 2, Qt::AlignRight);

    shapeChanged();
    penChanged();
    brushChanged();
    antialiasingCheckBox->setChecked(true);
}

void Window::t3Init(QWidget* tabWgt)
{

}

Window::Window()
{
	QVBoxLayout *mainLayout = new QVBoxLayout;


	mainInit( mainLayout );
	tabsInit( mainLayout );

	setLayout(mainLayout);
	menuInit();
}


