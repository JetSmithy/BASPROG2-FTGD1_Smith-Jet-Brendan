#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

struct Item
{
    string name;
    int gold;
};



Item* generateRandomItem()
{
    int random = rand() % 5;

    Item* item = new Item;

    if (random == 0)
    {
        item->name = "Mithril Ore";
        item->gold = 100;
    }
    else if (random == 1)
    {
        item->name = "Sharp Talon";
        item->gold = 50;
    }
    else if (random == 2)
    {
        item->name = "Thick Leather";
        item->gold = 25;
    }
    else if (random == 3)
    {
        item->name = "Jellopy";
        item->gold = 5;
    }
    else
    {
        item->name = "Cursed Stone";
        item->gold = 0;
    }

    return item;
}



void enterDungeon(int& playerGold)
{
    playerGold -= 25;

    int dungeonGold = 0;
    int multiplier = 1;
    bool continueLooting = true;

    cout << "\nYou entered the dungeon!" << endl;
    cout << "25 gold paid. Remaining gold: " << playerGold << endl;

    while (continueLooting)
    {
        Item* item = generateRandomItem();

        cout << "\nYou found: " << item->name << endl;

        if (item->name == "Cursed Stone")
        {
            cout << "Oh no! The Cursed Stone has destroyed all of your dungeon loot." << endl;
            cout << "You've lost all the gold that you have collected in this dungeon." << endl;

            delete item;
            break;
        }

        int itemGold = item->gold * multiplier;
        dungeonGold += itemGold;

        cout << "Base gold: " << item->gold << endl;
        cout << "Multiplier: x" << multiplier << endl;
        cout << "Gold gained from item: " << itemGold << endl;
        cout << "Dungeon gold: " << dungeonGold << endl;

        delete item;

        char choice;
        cout << "Continue looting? Yes or no?: ";
        cin >> choice;

        if (choice == 'yes' || choice == 'Yes')
        {
            multiplier++;
        }
        else
        {
            playerGold += dungeonGold;
            continueLooting = false;

            cout << "You exited the dungeon safetly." << endl;
            cout << "Gold has been added to your total." << endl;
        }
    }

    cout << "Player gold: " << playerGold << endl;
}




int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int playerGold = 50;
    bool gameOver = false;

    cout << "Minigame: Loot" << endl;
    cout << "Starting gold: " << playerGold << endl;
    cout << "Goal: Reach 500 gold!" << endl;

    while (!gameOver)
    {
        if (playerGold >= 500)
        {
            cout << "\nYou won" << endl;
            cout << "Final gold count: " << playerGold << endl;
            gameOver = true;
        }
        else if (playerGold < 25)
        {
            cout << "\nGame Over. Sadly you don't have enough gold to enter the dungeon." << endl;
            cout << "Final gold count: " << playerGold << endl;
            gameOver = true;
        }
        else
        {
            enterDungeon(playerGold);
        }
    }




    return 0;
}
