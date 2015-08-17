#include "Headcookerwindow.h"
#include <QApplication>
#include "RecipeParser.h"
#include "Curler.h"

//testincludes
#include <iostream>
#include <QString>
#include <iomanip>
using namespace std;
void test();
QString getUrl(string url);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HeadcookerWindow w;
    //w.show();

    test();

    //return a.exec();
    return 0;
}

void test() {

    QString text = Curler::getHTML("http://www.chefkoch.de/rezepte/197551083658477/Sivi-s-Semmelknoedel.html");
    RecipeParser parser;

        if (!parser.hasError(text)) {
        cout << "Recipe Name: " << parser.getRecipeName(text).toStdString() << endl << endl;
        cout << "Instruction:\n" << parser.getInstructions(text).toStdString() << endl;

        cout << endl << "Ingredients: \n";
        QList<RecipeParser::Ingredient> ingredients = parser.getIngrediants(text);

        for (RecipeParser::Ingredient item : ingredients) {
            cout << setw(10) << right << item.amount.toStdString() << "    " << item.name.toStdString() << endl;
        }

        cout << endl << "Tags: " << endl;

        QList<QString> tags = parser.getTags(text);

        for (auto& item : tags) {
            cout << item.toStdString() << endl;
        }

        cout << endl <<"Image Links: " << endl;

        QList<QString> imgLinks = parser.getImageLinks(text);

        for (auto& item : imgLinks) {
            cout << item.toStdString() << endl;
        }

        cout << endl << "Num portions: " << parser.getNumPortions(text) << endl;
    } else {
            cerr << "An error occurred." << endl;
        }
}
