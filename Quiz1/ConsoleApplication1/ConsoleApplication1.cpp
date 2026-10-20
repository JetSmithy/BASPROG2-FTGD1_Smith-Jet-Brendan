
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <limits>
using namespace std;

string cardName(int card)
{
    if (card == 1) return "Warrior";
    if (card == 2) return "Khan";
    return "Assassin";
}



vector<int> createHand(int side)
{
    vector<int> hand = { 1, 1, 1, 1 };

    if (side == 1)
        hand.push_back(2);
    else
        hand.push_back(3);

    return hand;
}



int chooseCard(vector<int>& hand)
{
    int choice;

    while (true)
    {
        cout << "\nYour hand: \n";

        for (int i = 0; i < hand.size(); i++)
            cout << i + 1 << ". " << cardName(hand[i]) << '\n';

        cout << "Choose a card by number: ";

        if (cin >> choice &&
            choice >= 1 && choice <= hand.size())
        {
            int card = hand[choice - 1];
            hand.erase(hand.begin() + choice - 1);
            return card;
        }

        cout << "Invalid option\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}



int chooseRivalCard(vector<int>& hand, mt19937& rng)
{
    uniform_int_distribution<int> randomCard(0, hand.size() - 1);

    int index = randomCard(rng);
    int card = hand[index];

    hand.erase(hand.begin() + index);

    return card;
}



int getStake(int lifeLeft)
{
    int stake;

    while (true)
    {
        cout << "\nYour current life: " << lifeLeft;
        cout << "\nChoose your life stake (1-" << lifeLeft << "): ";

        if (cin >> stake && stake >= 1 && stake <= lifeLeft)
            return stake;

        cout << "Invalid stake \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}



int evaluateMatchup(int side, int player, int rival)
{
    if (player == 1 && rival == 1)
        return 0; //tie

    if (side == 1)
    {
        if ((player == 2 && rival == 1) ||
            (player == 1 && rival == 3))
            return 1; //win
    }
    else
    {
        if ((player == 3 && rival == 2) ||
            (player == 1 && rival == 3))
            return 1; //win
    }

    return -1; //loss
}

void playRound(int round, int& lifeLeft,
    int& chargeCounters, mt19937& rng)
{
    int side;

    if (round <= 3 || (round >= 7 && round <= 9))
        side = 1; //khan
    else
        side = 2; //assassin

    int rivalSide = (side == 1) ? 2 : 1;


    vector<int> playerHand = createHand(side);
    vector<int> rivalHand = createHand(rivalSide);

    cout << "Round " << round << " of 12\n";
    cout << "Your side: " << (side == 1 ? "Khan" : "Assassin") << '\n';
    cout << "Rival side: " << (rivalSide == 1 ? "Khan" : "Assassin") << '\n';

    int stake = getStake(lifeLeft);
    int result = 0;

    while (result == 0)
    {
        cout << "\nLife stake: " << stake << '\n';

        int playerCard = chooseCard(playerHand);
        int rivalCard = chooseRivalCard(rivalHand, rng);

        cout << "\nYou played: " << cardName(playerCard) << '\n';
        cout << "Rival played: " << cardName(rivalCard) << '\n';

        result = evaluateMatchup(side, playerCard, rivalCard);

        if (result == 0)
            cout << "Tie, both of the warriors are removed. Play again with the same stake.\n";
    }

    if (result == 1)
    {
        int reward = (side == 1) ? stake : stake * 5;
        chargeCounters += reward;

        cout << "\nYou won the round!\n";
        cout << "You gained " << reward << " charge counters.\n";
    }
    else
    {
        lifeLeft -= stake;

        cout << "\nYou lost the round!\n";
        cout << "You lost " << stake << " life.\n";
    }

    cout << "Life remaining: " << lifeLeft << '\n';
    cout << "Charge counters: " << chargeCounters << '\n';
}



int main()
{
    int round = 1;
    int lifeLeft = 30;
    int chargeCounters = 0;

    random_device device;
    mt19937 rng(device());

    cout << "Planewalkers Trial\n";
    cout << "Survive 12 rounds with at least 200 counters.\n";

    while (round <= 12 && lifeLeft > 0)
    {
        playRound(round, lifeLeft, chargeCounters, rng);
        ++round;
    }

    cout << "\nTrial has ended\n";



    if (lifeLeft == 0)
        cout << "Ending: Failure\n";
    else if (chargeCounters >= 200)
        cout << "Ending: Champion of the trial\n";
    else
        cout << "Ending: Survivor of the trial\n";

    cout << "Final life: " << lifeLeft << '\n';
    cout << "Final charge counters: " << chargeCounters << '\n';

    return 0;
}
