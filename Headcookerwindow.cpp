#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);

    QString id("2138001343651445");
    //id = "424521133318549";
    id = "1235651228459595";


    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/1235651228459595");
    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/814121185712740");
    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/197551083658477");

    RecipeWidget *rw = new RecipeWidget(id);

    ui->centralWidget->layout()->addWidget(rw);
    testDB();
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}

void HeadcookerWindow::testDB() {
    Database &database = Database::DB();

    cout << "id for hans: " << database.getUserID("hans") << endl;
    cout << "id for peter: " << database.getUserID("peter") << endl;
    cout << "id for hans: " << database.getUserID("hans") << endl;
    cout << "id for lara: " << database.getUserID("lara") << endl;
    cout << "id for max: " << database.getUserID("max") << endl;

    cout <<"tag id for meat: " << database.getTagID("meat") << endl;
}
