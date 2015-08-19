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
    for (XMLTreeObject header : ingredientGroup.getChilds()) {
        QGroupBox *ingredientBox = new QGroupBox(header.getChild("header").getValue());

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

    ui->previewPicture->setPixmap(fetchImage(xmlData));

    if (ui->tagWidget->layout()) {
        delete ui->tagWidget->layout();
    }

    //Tags

    FlowLayout *flowLayout = new FlowLayout;
    ui->tagWidget->setLayout(flowLayout);
    for (QString tag : xmlData.getChild("tags").getValues()) {
        QLabel *tagLabel = new QLabel(tag);
        tagLabel->setProperty("frameShape", QFrame::Box);
        tagLabel->setProperty("frameShadow", QFrame::Sunken);
        tagLabel->setProperty("lineWidth", 1);
        flowLayout->addWidget(tagLabel);
    }
}

RecipeWidget::~RecipeWidget()
{
    delete ui;
}

QPixmap RecipeWidget::fetchImage(XMLTree &xmlData){
    QPixmap pix(420, 280);
    if (xmlData.getChild("hasImage").getValue() == "true") {
        QString url = "http://api.chefkoch.de/v2/recipes/";
        url += xmlData.getChild("id").getValue();
        url += "/images/";
        url += xmlData.getChild("previewImageId").getValue();

        XMLTree imageXML = RecipeApiParser::parseRecipe(Curler::getQString(url));

        QString imageUrl = imageXML.getChild("urls").getChild("crop-420x280").getChild("cdn").getValue();
        cout << "image url: " << imageUrl.toStdString() << endl;

        int bufferSize;

        const uchar* orgData = (const uchar*)Curler::getCStr(imageUrl, bufferSize);

        pix.loadFromData(orgData, bufferSize, "JPG");
        pix.loadFromData(Curler::getQByteArray(imageUrl), "jpg");

    }
    return pix;
}
