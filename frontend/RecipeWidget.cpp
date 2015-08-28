#include "RecipeWidget.h"
#include "ui_RecipeWidget.h"

RecipeWidget::RecipeWidget(QString id, HeadcookerWindow *win, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    recipe = new Recipe(id);
    init(win);
}

RecipeWidget::RecipeWidget(int id, HeadcookerWindow *win, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    recipe = new Recipe(id);
    init(win);
}

RecipeWidget::RecipeWidget(Recipe &recipe, HeadcookerWindow *win, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    this->recipe = &recipe;
    init(win);
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

void RecipeWidget::init(HeadcookerWindow *win)
{
    ui->setupUi(this);

    QFile styleFile("css/style.css");
    if (styleFile.exists()) {
        styleFile.open(QFile::ReadOnly);
        QString style(styleFile.readAll());

        this->setStyleSheet(style);

    } else {
        cerr << "File " << styleFile.fileName().toStdString() << " does not exit." << endl;
    }

    connect(ui->backButton, SIGNAL(clicked()), win, SLOT(showRecipeChooser()));

    ui->recipeName->setText(recipe->getTitle());
    ui->subtitle->setText(recipe->getSubtitle());
    ui->instructions->setText(recipe->getInstructions());

    //Ingredients
    for (DataTypes::IngredientList group : recipe->getIngredientGroups().groups) {
        QGroupBox *ingredientBox = new QGroupBox(group.header);

        QGridLayout *layout = new QGridLayout;
        ingredientBox->setLayout(layout);
        int i = 0;
        for (DataTypes::Ingredient ingredient : group.ingredients) {
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

    tagLayout = new FlowLayout;
    ui->tagWidget->setLayout(tagLayout);
    for (QString tag : recipe->getTags()) {
       addTag(tag);
    }

    addAddTagButton();
}

void RecipeWidget::addAddTagButton() {

    addTagButton = new QPushButton("+");
    tagLayout->addWidget(addTagButton);

    addTagButton->setStyleSheet("font-weight: bold; color: #FFF; background-color: #5D8812; border: none; padding-left: 20; padding-right: 20; border-radius: 5");

    connect(addTagButton, SIGNAL(clicked()), this, SLOT(displayTagInput()));
}

void RecipeWidget::displayTagInput() {
    tagLayout->removeWidget(addTagButton);
    addTagButton->deleteLater();

    addTagInput = new QLineEdit();
    addTagInput->setStyleSheet("border: none; width: 70; padding-left: 5; padding-right: 5; border-radius: 5;");
    tagLayout->addWidget(addTagInput);
    QTimer::singleShot(0, addTagInput, SLOT(setFocus()));

    connect(addTagInput, SIGNAL(returnPressed()), this, SLOT(addNewTag()));
}

void RecipeWidget::addNewTag() {
    QString tag = addTagInput->text();
    tagLayout->removeWidget(addTagInput);
    addTagInput->deleteLater();
    if (!tag.trimmed().isEmpty() && recipe->addTag(tag))
        addTag(tag);
    addAddTagButton();
}

void RecipeWidget::addTag(QString tagname)
{
    //QLabel *tagLabel = new QLabel(tagname);
    //tagLabel->setStyleSheet("color: #FFF; background-color: #90B262; border-radius: 5; padding-left: 5; padding-right: 5;");
    //tagLayout->addWidget(tagLabel);

    QPushButton *tag = new QPushButton(tagname);
    tag->setObjectName("tag");
    tagLayout->addWidget(tag);
}
