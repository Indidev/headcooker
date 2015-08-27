#include "RecipeWidget.h"
#include "ui_RecipeWidget.h"

RecipeWidget::RecipeWidget(QString id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    recipe = new Recipe(id);
    ui->setupUi(this);
    ui->recipeName->setText(recipe->getTitle());
    ui->subtitle->setText(recipe->getSubtitle());
    ui->instructions->setText(recipe->getInstructions());

    //Ingredients
    for (auto& group : recipe->getIngredientGroups()) {
        QGroupBox *ingredientBox = new QGroupBox(group.first);

        QGridLayout *layout = new QGridLayout;
        ingredientBox->setLayout(layout);
        int i = 0;
        for (Recipe::Ingredient ingredient : group.second) {
            QString a = QString::number(ingredient.amount);
            QString u(ingredient.unit);

            if (a.toFloat() == 0)
                a = "";

            QLabel *amount = new QLabel(a + " " + u);
            QLabel *name = new QLabel(ingredient.name + ingredient.usageInfo);
            layout->addWidget(amount, i, 0, 1, 1, Qt::AlignRight);
            layout->addWidget(name, i, 1, 1, 1, Qt::AlignLeft);
            //cout << amount.toStdString() << " " << name.toStdString() << endl;
            i++;
        }
        ui->ingredientsLayout->addWidget(ingredientBox);
    }

    //Metainformations
    if (ui->metaInfoWidget->layout() != NULL)
        delete ui->metaInfoWidget->layout();
    FlowLayout *metaInfoLayout = new FlowLayout;
    ui->metaInfoWidget->setLayout(metaInfoLayout);
    for (QPair<QString, QString> metaInfo : recipe->getMetaInfo()) {
        QLabel *name = new QLabel(metaInfo.first);
        QFont font = name->font();
        font.setBold(true);
        name->setFont(font);

        QLabel *value = new QLabel(metaInfo.second);
        metaInfoLayout->addWidget(name);
        metaInfoLayout->addWidget(value);
    }

    //Picture
    ui->previewPicture->setPixmap(recipe->getImage());


    //Tags
    if (ui->tagWidget->layout()) {
        delete ui->tagWidget->layout();
    }

    FlowLayout *tagLayout = new FlowLayout;
    ui->tagWidget->setLayout(tagLayout);
    for (QString tag : recipe->getKeyWords()) {
        QLabel *tagLabel = new QLabel(tag);
        tagLabel->setProperty("frameShape", QFrame::Box);
        tagLabel->setProperty("frameShadow", QFrame::Sunken);
        tagLabel->setProperty("lineWidth", 1);
        tagLayout->addWidget(tagLabel);
    }
}

RecipeWidget::~RecipeWidget()
{
    delete recipe;
    delete ui;
}

Recipe *RecipeWidget::getRecipe()
{
    return recipe;
}
