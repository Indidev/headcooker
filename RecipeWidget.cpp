#include "RecipeWidget.h"
#include "ui_RecipeWidget.h"

RecipeWidget::RecipeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    ui->setupUi(this);
}

RecipeWidget::RecipeWidget(XMLTree xmlData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    ui->setupUi(this);
    ui->recipeName->setText(xmlData.getChild("title").getValue());
    ui->subtitle->setText(xmlData.getChild("subtitle").getValue());
    ui->instructions->setText(xmlData.getChild("instructions").getValue());


    XMLTreeObject ingredientGroup = xmlData.getChild("ingredientGroups");

    //Ingredients
    for ( XMLTreeObject header : ingredientGroup.getChilds()) {
        QGroupBox *ingredientBox = new QGroupBox(header.getChild("header").getValue());

        QTableWidget* tableWidget = new QTableWidget(header.getChild("ingredients").getChilds().size(), 2);
        QGridLayout *layout = new QGridLayout;
        ingredientBox->setLayout(layout);
        XMLTreeObject ingredients = header.getChild("ingredients");
        int i = 0;
        for (XMLTreeObject ingredient : ingredients.getChilds()) {
            QString a = ingredient.getChild("amount").getValue();
            QString u = ingredient.getChild("unit").getValue();

            if (a.toInt() == 0)
                a = "";

            QLabel *amount = new QLabel(a + " " + u);
            QLabel *name = new QLabel(ingredient.getChild("name").getValue());
            layout->addWidget(amount, i, 0, 1, 1, Qt::AlignRight);
            layout->addWidget(name, i, 1, 1, 1, Qt::AlignLeft);
            //cout << amount.toStdString() << " " << name.toStdString() << endl;
            i++;
        }

        ui->ingredientsLayout->addWidget(ingredientBox);
    }
}

RecipeWidget::~RecipeWidget()
{
    delete ui;
}
