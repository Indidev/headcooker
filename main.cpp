#include "Headcookerwindow.h"
#include <QApplication>

//testincludes
#include <iostream>
#include <QString>
#include <iomanip>
#include "RecipeApiParser.h"
#include "xml/XMLTree.h"
#include "Curler.h"

using namespace std;
void test();
QString getUrl(string url);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HeadcookerWindow w;
    w.show();

    test();

    return a.exec();
    //return 0;
}

void test() {

    QString text = Curler::getHTML("http://api.chefkoch.de/v2/recipes/1235651228459595");
/*    RecipeParser parser;

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
*/

    XMLTree input = RecipeApiParser::parseRecipe(text);

    XMLTreeObject ingredientGroup = input.getChild("ingredientGroups");
    cout << "Ingredients: \n";
    for ( XMLTreeObject header : ingredientGroup.getChilds()) {
        cout << header.getChild("header").getValue().toStdString() << endl;
        XMLTreeObject ingredients = header.getChild("ingredients");
        for (XMLTreeObject ingredient : ingredients.getChilds()) {
            cout << right << setw(10) << ingredient.getChild("amount").getValue().toStdString() +
                    ingredient.getChild("unit").getValue().toStdString() <<
                    "    " <<
                    ingredient.getChild("name").getValue().toStdString() <<
                    ingredient.getChild("usageInfo").getValue().toStdString() << endl;
        }
    }
    cout << "instructions:\n" << input.getChild("instructions").getValue().toStdString() << endl;
}
