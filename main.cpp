// read https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/

// Matthew Levin
// 12/1/2022
// cosc a211
// term project v1.0

// each drink is assigned it's own file with 5 lines
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

#define DRINK_ARRAY_LENGTH 500

// This is my struct, there are many like it but this one is mine.
struct Drink
{
    bool exists; // useful for logic
    int numOfIngredients; // useful because i hate while loops
    string drinkName;       // well DUH
    string ingredients[20]; // Max 20 ingredients
    string instructions;    // UH HOW DO I MAKE THIS
    float standardDrinks;   // number of standard drinks in the drink
};



string betterGetLine() // <---- me trying to make getline actually work in the console properly and failing 
{
    string stringToFill;
    getline(cin, stringToFill);
    return stringToFill;
}



void writeDrinkToFile(int drinkIndex,struct Drink newDrink)
{
    ofstream drinkFile; // create a file stream
    drinkFile.open("drink" + to_string(drinkIndex) + ".txt", ios::app); // open the file

    drinkFile << newDrink.numOfIngredients << endl;                     // write data from struct to file
    drinkFile << newDrink.drinkName << endl;

    for (int i = 0; i < newDrink.numOfIngredients; i++) // write the ingredients (on the same line delimited by a ";")
    {
        drinkFile << newDrink.ingredients[i] << ';';
    }
    drinkFile << endl; // New line to denote end of ingredient list


    drinkFile << newDrink.instructions << endl;
    drinkFile << newDrink.standardDrinks << endl;

    drinkFile.close(); // close the file
}



void displayDrink(struct Drink newDrink) // this is pretty self expalnatory it just displays the drink to the console
{
    cout << "Drink Name: " << newDrink.drinkName << endl;
    cout << "Num of Ingredients: " << newDrink.numOfIngredients << endl;
    cout << "Ingredients: " << endl;
    for (int i = 0; i < newDrink.numOfIngredients; i++)
    {
        cout << newDrink.ingredients[i] << endl;
    }
    cout << "Instructions: " << newDrink.instructions << endl;
    cout << "Standard Drinks: " << newDrink.standardDrinks << endl;
}



Drink readDrinkFromFile(string fileName)
{
    Drink drink;
    int position = 0;
    int ingredientIndex = 0;
    string ingredientListString;
    string ingredient;
    ifstream drinkFile;

    drinkFile.open(fileName);

    drinkFile >> drink.numOfIngredients;

    drinkFile.ignore();
    getline(drinkFile, drink.drinkName); // Read the rest of the line

    getline(drinkFile, ingredientListString); // read the list of ingredients line as a string

    // Split the string into individual ingredients delimiter is a ";"
    while ((position = ingredientListString.find(";")) != string::npos)// this delimiter routine is pretty wicked and I had to read a lot to try and get it to work
    {
        ingredient = ingredientListString.substr(0, position); // make a substring of the ingredient by shifting to the the delimiter
        drink.ingredients[ingredientIndex] = ingredient;       // add the ingredient to the array
        ingredientListString.erase(0, position + 1);           // erase the delimiter 
        ingredientIndex++;                                     // increment the ingredient index so we can do it AGAIN
    }

    getline(drinkFile, drink.instructions); // read the instructions for the drink to the drink struct
    drinkFile >> drink.standardDrinks;

    drinkFile.close();

    return drink;
}



// To the reader, firstly, this is a mess of a function. I'm sorry.
// Secondly the cin.ignore()'s had to go in some weird places to get it to work. I don't know why. My best guess is that it's because of the way getline() works.
Drink addDrink()
{
    system("cls");
    struct Drink newDrink;
    // get info about the drink and put it into the struct newDrink and then return it so it can be used elsewhere
    cout << "Please enter the name of the drink: ";
    cin.ignore();
    newDrink.drinkName = betterGetLine();

    cout << "Please enter the number of ingredients in the drink: ";
    cin >> newDrink.numOfIngredients;
    cout << endl;

    cout << "Please enter the ingredients in the drink: ";
    cin.ignore();
    for (int i = 0; i < newDrink.numOfIngredients; i++) // for loop to get each ingredient and put them in the ingredients array in the struct
    {
        cout << "Ingredient number " << (i+1) << ": ";
        newDrink.ingredients[i] = betterGetLine();
    }

    cout << "Please enter the instructions for the drink: ";

    newDrink.instructions = betterGetLine(); // get the instructions for the drink

    cout << "Please enter the number of standard drinks in the drink: ";
    cin >> newDrink.standardDrinks; // get the number of standard drinks in the drink

    newDrink.exists = true;
    cout << "Drink added successfully!"<< endl;
    return newDrink; // return the drink so we can add it to the array of drinks or write it to the file
}



Drink removeDrink(int drinkIndex, Drink d)
{
    // delete the file that contains the drink
    string fileName = "drink" + to_string(drinkIndex) + ".txt";
    if (remove(fileName.c_str()) == 0) // had to convert the name to an old c string to get this to work
    {
        cout << "File successfully deleted" << endl;   
    }
    else
    {
        cout << "Error deleting file" << endl;
    }
    // return a blank drink and set the exists bool to false
    d.exists = false;
    d.drinkName = "";
    d.numOfIngredients = NULL;
    d.instructions = "";
    d.standardDrinks = NULL;
    return d;

}


// these are almost all the same
Drink searchByName(string name, Drink drinkArray[])
{
    for (int i = 0; i < DRINK_ARRAY_LENGTH; i++) // check each drink in the array for the name (case sensitive)
    {
        if (drinkArray[i].drinkName == name)
        {
            return drinkArray[i];
        }
    }// if it doesn't find it return a blank drink with the exists bool set to false
    Drink d;
    d.exists = false;
    return d;
}



Drink searchByIngredient(string ingredient, Drink drinkArray[])
{
    for (int i = 0; i < DRINK_ARRAY_LENGTH; i++) // check each drink in the array for the ingredient
    {
        for (int j = 0; j < drinkArray[i].numOfIngredients; j++) // check each ingredient in the array for the drink
        {
            if (drinkArray[i].ingredients[j] == ingredient)
            {
                return drinkArray[i]; // if it finds it return the drink
            }
        }
    }
    Drink d;
    d.exists = false;
    return d;
}



Drink searchByStandardDrinks(float standardDrinks, Drink drinkArray[]) // same thing here with floats 
{
    for (int i = 0; i < DRINK_ARRAY_LENGTH; i++)
    {
        if (drinkArray[i].standardDrinks == standardDrinks)
        {
            return drinkArray[i];
        }
    }
    Drink d;
    d.exists = false;
    return d;
}



Drink searchByIndex(int index, Drink drinkArray[])
{
    if (drinkArray[index].exists == true)
    {
        return drinkArray[index];
    }
    else
    {
        Drink d;
        d.exists = false;
        return d;
    }
}



int mainMenu()// function to display the main menu and get a selection on what the user wants to do
{
    int menuSelection;
    cout << "Welcome to the drink managment system!\n Please Select an option:" << endl;
    cout << "1. Add a drink" << endl;
    cout << "2. Remove a drink" << endl;
    cout << "3. View a random drink" << endl;
    cout << "4. View all drinks" << endl;
    cout << "5. Search for a drink" << endl;
    cout << "6. Exit" << endl;
    cout << "Selection: ";
    cin >> menuSelection;
    system("cls");
    return menuSelection;
}



int searchMenu() // all of the options for searching
{
    int selection;
    cout << "Please select a search option:" << endl;
    cout << "1. Search by name" << endl;
    cout << "2. Search by ingredient" << endl;
    cout << "3. Search by standard drinks" << endl;
    cout << "4. Search by index" << endl;
    cout << "5. Exit program" << endl;
    cout << "Selection: ";
    cin >> selection;
    return selection;
}



int main()
{
    int totalNumOfDrinks;
    int menuSelection;
    int i;
    int searchInt;
    float searchFloat;
    string searchString;
    ifstream fileCounter;
    Drink drinkToAdd;
    Drink searchResult;
    Drink drinkArray [DRINK_ARRAY_LENGTH];
    srand(time(0));

    for (i = 0; (i < DRINK_ARRAY_LENGTH); ++i)
    {
        fileCounter.open("drink" + to_string(i) + ".txt"); // check to see if each file contains a drink
        if(fileCounter.is_open() && fileCounter.peek() != std::ifstream::traits_type::eof()) // if the file exists and is not empty
        {
            drinkArray[i] = readDrinkFromFile("drink" + to_string(i) + ".txt"); // write all the data from the file to the array of structs
            drinkArray[i].exists = true; // if the file for the drink exists reflect that in the struct
        } 
        else
        {
            drinkArray[i].exists = false; // if not then dont
        }
        fileCounter.close(); // this is important dont get rid of it or this whole sequence breaks and none of the logic that relies on it works
    }
    


    while (true) // while true loop so you can use it over and  over and over and over and over and over and over and over and over and over!
    {
    
        switch (mainMenu())
        {
            case 1: // add a drink
                i = 0;
                drinkToAdd = addDrink();
                while (drinkArray[i].exists == true) // crawl through the array of drinks until we find a blank spot
                {
                    i++;
                }
                writeDrinkToFile(i,drinkToAdd); // write the drink to the file
                displayDrink(drinkToAdd);       // display the drink to the user
                break;


            case 2:
                cout << "Please enter the index of the drink you would like to remove: ";
                cin >> i;
                drinkArray[i] = removeDrink(i, drinkArray[i]); // remove the drink from the array and delete the file
                break;


            case 3:
                do
                {
                    i = rand() % DRINK_ARRAY_LENGTH; // get a random number between 0 and the DRINK_ARRAY_LENGTH (the number of drinks we can store)
                }
                while(drinkArray[i].exists != true); // make sure we have a drink that exists
                displayDrink(drinkArray[i]);         // display the drink
                break;


            case 4: // display all drinks in the array
                for (i = 0; i < DRINK_ARRAY_LENGTH; ++i)
                {
                    if (drinkArray[i].exists) // check to see if the drink exists 
                    {
                        cout << endl << endl;
                        cout << "Drink " << i << endl; // tell the user what drink index it is
                        displayDrink(drinkArray[i]);   // display the drink
                    }
                    else
                        break;
                }
                break;


            case 5:
                switch (searchMenu()) // these all do the same thing but with different search types. I'm not commenting the same thing 5 times.....
                {
                    case 1: 
                        cout << "Please enter the name of the drink you would like to search for: "; // find out what the user wants to search for
                        cin.ignore();
                        getline(cin, searchString);

                        searchResult = searchByName(searchString, drinkArray); // search for the drink
                    
                        if (searchResult.exists)                               // if it exists yay we can display it with the displayDrink function
                        {                                                      // this is actually a bit of unintentional corruption proctection
                            displayDrink(searchResult);
                        }
                        else
                        {
                            cout << "Drink not found" << endl;                  // if it doesnt exist tell the user
                        }
                        break;

                    case 2: // I really could have incorporated these all into their own respecrtive functions but I wanted modularity
                        cout << "Please enter the ingredient you would like to search for: ";
                        cin.ignore();
                        getline(cin, searchString);

                        searchResult = searchByIngredient(searchString, drinkArray);

                        if (searchResult.exists)
                        {
                            displayDrink(searchResult);
                        }
                        else
                        {
                            cout << "Drink not found" << endl;
                        }
                        break;

                    case 3:
                        cout << "Please enter the number of standard drinks you would like to search for: ";
                        cin >> searchFloat;

                        searchResult = searchByStandardDrinks(searchFloat, drinkArray);

                        if (searchResult.exists)
                        {
                            displayDrink(searchResult);
                        }
                        else
                        {
                            cout << "Drink not found" << endl;
                        }
                        break;

                    case 4:
                        cout << "Please enter the index of the drink you would like to search for: ";
                        cin >> searchInt;

                        searchResult = searchByIndex(searchInt, drinkArray);

                        if (searchResult.exists)
                        {
                            displayDrink(searchResult);
                        }
                        else
                        {
                            cout << "Drink not found" << endl;
                        }
                        break;

                    case 5:
                        break;

                    default:
                        cout << "Invalid selection" << endl;
                        break;
                }

            case 6:
                return 0; // close the program if the user selects 6

            default:
                cout << "Invalid selection" << endl; // let the user know they are dumb and picked an invalid option
                break;
        }

    }
    return 0;
}



