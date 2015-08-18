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

        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(fetchImage(xmlData));
        ui->previewPicture->setScene(new QGraphicsScene);
        ui->previewPicture->scene()->addItem(item);
    }
}

RecipeWidget::~RecipeWidget()
{
    delete ui;
}

QPixmap RecipeWidget::fetchImage(XMLTree &xmlData){
    if (xmlData.getChild("hasImage").getValue() == "true") {
        QString url = "http://api.chefkoch.de/v2/recipes/";
        url += xmlData.getChild("id").getValue();
        url += "/images/";
        url += xmlData.getChild("previewImageId").getValue();

        XMLTree imageXML = RecipeApiParser::parseRecipe(Curler::get(url));

        QString imageUrl = imageXML.getChild("urls").getChild("crop-420x280").getChild("cdn").getValue();
        cout << "image url: " << imageUrl.toStdString() << endl;
        QPixmap pix;
        QByteArray byteArray = Curler::get(imageUrl).toAscii();
        pix.loadFromData(byteArray, "JPG");

        return pix;
    }
}
