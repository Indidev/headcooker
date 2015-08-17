#include "RecipeParser.h"

/**
 * @brief RecipeParser::RecipeParser
 * creates a new recipe parser
 */
RecipeParser::RecipeParser()
{
}

/**
 * @brief RecipeParser::getRecipeName
 * @param html html input as a single string
 * @return recipe name
 */
QString RecipeParser::getRecipeName(const QString html)
{
    QString recipeName(getBetween(html, "<h1 class=\"page-title fn\">", "</h1>"));

    recipeName = replaceMutations(recipeName);
    recipeName = recipeName.trimmed();

    return recipeName;
}

/**
 * @brief RecipeParser::getSummary the summary located beneath the headline
 * @param html html to parse from
 * @return summary
 */
QString RecipeParser::getSummary(const QString html) {
    QString summary(getBetween(html, "<div class=\"summary\">"), "</div>");

    summary = replaceMutations(summary);
    summary = summary.trimmed();

    return summary;
}

/**
 * @brief RecipeParser::getMetaInfo info such as prepare- and cooktime
 * @param html html input to parse from
 * @return meta information as a list
 */
QList<QString> RecipeParser::getMetaInfo(const QString html) {
    QList<QString> metaInfo;
    //TODO
    return metaInfo;
}

/**
 * @brief RecipeParser::getInstructions get instruction for the recipe
 * @param html html input to parse from
 * @return instructions as a QString
 */
QString RecipeParser::getInstructions(const QString html) {
    QString instructions(getBetween(html, "class=\"instructions\">", "</div>"));

    instructions = instructions.trimmed();
    instructions = replaceMutations(instructions);

    return instructions;
}

/**
 * @brief RecipeParser::getIngrediants get a list of ingrediants for the recipe
 * @param html html input to parse from
 * @return ingrediants as a list
 */
QList<RecipeParser::Ingredient> RecipeParser::getIngrediants(const QString html) {
    QList<Ingredient> ingredients;
    QString allIng(getBetween(html, "<table class=\"incredients\">", "</table>"));

    QString start("<tr class=\"ingredient\">");
    QString end("</tr>");

    int index = allIng.indexOf(start);

    while (index >= 0) {
        int endIndex = allIng.indexOf(end);
        QString substring(allIng);
        substring.chop(substring.length() - endIndex);
        allIng.remove(0, endIndex + end.length());

        Ingredient ingredient;

        QString amount = getBetween(substring, "<td class=\"amount\">", "</td>");
        QString name = removeLink(getBetween(substring, "<td class=\"name\">", "</td>"));

        amount = replaceMutations(amount);
        amount = amount.trimmed();
        name = replaceMutations(name);
        name = name.trimmed();

        ingredient.amount = amount;
        ingredient.name = name;
        ingredients.append(ingredient);

        index = allIng.indexOf(start);
    }
    return ingredients;
}

/**
 * @brief RecipeParser::getTags gets tags of the Recipe
 * @param html html input to parse from
 * @return a list of tags
 */
QList<QString> RecipeParser::getTags(const QString html) {
    QList<QString> tags;

    QString allTags(getBetween(html, "<ul class=\"tagcloud\">", "</ul>"));

    QString start("<li>");
    QString end("</li>");

    int index = allTags.indexOf(start);

    while (index >= 0) {
        int endIndex = allTags.indexOf(end, index);
        QString tagLine(getBetween(allTags.trimmed(), "<li>", "</li>"));
        allTags.remove(0, endIndex + end.length());

        tags.append(replaceMutations(removeLink(tagLine)).trimmed());

        index = allTags.indexOf(start);
    }
    return tags;
}

/**
 * @brief RecipeParser::getImageLinks returns a list of image links for a specific recipe
 * @param html html input to parse from
 * @return list of image links (all jpg)
 */
QList<QString> RecipeParser::getImageLinks(const QString html) {
    QList<QString> imageLinks;

    QString sliderDiv(getBetween(html, "class=\"nivoSlider\">", "</div>"));

    QString start("<a");
    QString end("</a>");

    int index = sliderDiv.indexOf(start);

    while (index >= 0) {
        int endIndex = sliderDiv.indexOf(end, index);
        QString imageLink(getBetween(sliderDiv, "href=\"", "\"").trimmed());
        sliderDiv.remove(0, endIndex + end.length());

        if (imageLink.endsWith(".jpg"))
            imageLinks.append(imageLink);

        index = sliderDiv.indexOf(start);
    }

    return imageLinks;
}

/**
 * @brief RecipeParser::getNumPortions returns for how many portions this recipe is
 * @param html html input to parse from
 * @return number of portions
 */
int RecipeParser::getNumPortions(const QString html) {
    QString portions = getBetween(getBetween(html, "id=\"divisor\"", ">"), "value=\"", "\"");
    return portions.toInt();
}

/**
 * @brief RecipeParser::hasError returns if chefkoch.de has an error
 * @param html html input to parse from
 * @return whether there is an error or not
 */
bool RecipeParser::hasError(const QString html) {
    return getBetween(html, "<title>", "</title>").contains("Oops", Qt::CaseInsensitive);
}

/**
 * @brief RecipeParser::getBetween returns the content between two tags
 * @param input input string
 * @param start start tag (e.g.: <div>)
 * @param end end tag (e.g.; </div>)
 * @return the string between "start" end "end"
 */
QString RecipeParser::getBetween(const QString input, QString start, QString end) {
    QString output(input);
    //search for "start"
    int index = output.indexOf(start);
    if (index != -1) {

        index += start.length();

        //remove everything befor "start"
        output.remove(0, index);

        //search "end"
        int endIndex = output.indexOf(end);

        //remove everything after "end"
        output.chop(output.length() - endIndex);
    }

    return output;
}

/**
 * @brief RecipeParser::removeLink removes links from a string
 * @param input a string where a link should be removed from (e.g.: <a href="abc.html">this is the content we want</a>)
 * @return content without <a> </a> tags
 */
QString RecipeParser::removeLink(const QString input) {
    QString output(input);
    int indexOfa = output.indexOf("<a");
    while (indexOfa >= 0) {
        int endOfa = output.indexOf(">", indexOfa);
        output.remove(indexOfa, endOfa - indexOfa + 1);

        indexOfa = output.indexOf("</a");
        endOfa = output.indexOf(">", indexOfa);
        output.remove(indexOfa, endOfa - indexOfa + 1);

        indexOfa = output.indexOf("<a");
    }
    return output;
}

/**
 * @brief RecipeParser::replaceMutations replaces mutations like &auml; to ä
 * @param input input string
 * @return mutation replaced output string
 */
QString RecipeParser::replaceMutations(const QString input) {
    QString output(input);
    output.replace("&auml;", "ä");
    output.replace("&Auml;", "Ä");
    output.replace("&ouml;", "ö");
    output.replace("&Ouml;", "Ö");
    output.replace("&uuml;", "ü");
    output.replace("&Uuml;", "Ü");
    output.replace("<br />", "");
    output.replace("&nbsp;", " ");
    output.replace("&szlig;", "ß");

    return output;
}
