#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    curWidget == NULL;
    ui->setupUi(this);

    showWidget(new RecipeChooser(this));
    //ui->centralWidget->layout()->addWidget(curWidget);

    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(menuAction(QAction*)));

    test();

    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}

void HeadcookerWindow::menuAction(QAction * action) {
    if (action == ui->option_menu_Action) {
        OptionsMenu menu(this);
        menu.exec();
    }
}

void HeadcookerWindow::moveWindow(int x, int y) {
    QRect geom = this->geometry();
    this->setGeometry(geom.x() + x, geom.y() + y, geom.width(), geom.height());
}

void HeadcookerWindow::showWidget(QWidget *widget) {
    if (curWidget != NULL) {
        curWidget->setVisible(false);
        ui->centralWidget->layout()->removeWidget(curWidget);
        curWidget->deleteLater();
    }
    curWidget = widget;
    ui->centralWidget->layout()->addWidget(curWidget);
}

void HeadcookerWindow::test() {
}
