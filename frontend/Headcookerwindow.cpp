#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);

    curWidget = new RecipeChooser(this);
    ui->centralWidget->layout()->addWidget(curWidget);

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

void HeadcookerWindow::test() {
    for (QString url : FirefoxParser::parse("bookmark.json")) {
        cout << url.toStdString() << endl;
    }
}

void HeadcookerWindow::moveWindow(int x, int y) {
    QRect geom = this->geometry();
    this->setGeometry(geom.x() + x, geom.y() + y, geom.width(), geom.height());
}

void HeadcookerWindow::clickedID(QString id) {
    showRecipe(id.toInt());
}

void HeadcookerWindow::clear() {
    curWidget->setVisible(false);
    ui->centralWidget->layout()->removeWidget(curWidget);
    curWidget->deleteLater();
}

void HeadcookerWindow::showRecipe(int id) {
    RecipeWidget *rw = new RecipeWidget(id, this);
    connect(rw, SIGNAL(clickedFilter(QString)), this, SLOT(showRecipeChooser(QString)));
    setWidget(rw);
}

void HeadcookerWindow::showRecipeChooser() {
    setWidget(new RecipeChooser(this));
}

void HeadcookerWindow::showRecipeChooser(QString filter) {
    setWidget(new RecipeChooser(this, filter));
}

void HeadcookerWindow::setWidget(QWidget * widget) {
    clear();
    curWidget = widget;
    ui->centralWidget->layout()->addWidget(curWidget);
}
