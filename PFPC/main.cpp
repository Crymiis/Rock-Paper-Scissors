#include <iostream>
#include <string>
 
typedef enum{
    ROCK=1,
    PAPER,
    SCISSORS,
    EXIT,
}RPC_Enum;
 
class Item
{
public:
    virtual unsigned int getChoice(void) const = 0;
    virtual std::string getChoiceName(void) const = 0;
};
 
class Rock : public Item
{
public:
    unsigned int getChoice(void) const override { return ROCK; }
    std::string getChoiceName(void) const override { return "ROCK"; }
};
 
class Paper : public Item
{
public:
    unsigned int getChoice(void) const override { return PAPER; }
    std::string getChoiceName(void) const override { return "PAPER"; }
};
 
class Scissors : public Item
{
public:
    unsigned int getChoice() const override { return SCISSORS; }
    std::string getChoiceName() const override { return "SCISSORS"; }
};
 
int comparerChoix(Item *Player1, Item *Player2)
{
    unsigned int choixJoueur1 = Player1->getChoice();
    unsigned int choixJoueur2 = Player2->getChoice();
 
    if (choixJoueur1 == choixJoueur2)
    {
        return 1; // Match nul
    }
    else if ((choixJoueur1 == ROCK && choixJoueur2 == SCISSORS) ||
             (choixJoueur1 == PAPER && choixJoueur2 == ROCK) ||
             (choixJoueur1 == SCISSORS && choixJoueur2 == PAPER))
    {
        return 2; // Joueur 1 gagne
    }
    else
    {
        return 0; // Joueur 2 gagne
    }
}
 
int main()
{
    int player1Points = 0;
    int player2Points = 0;
    int i = 0;
 
    std::string player1Name;
    std::string player2Name;
 
    std::cout << "Enter Player 1's name: ";
    std::cin >> player1Name;
 
    std::cout << "Enter Player 2's name: ";
    std::cin >> player2Name;
 
    // Number of game rounds
    std::cout << "How many winning rounds to play?\n";
    int number_of_winning_rounds;
    std::cin >> number_of_winning_rounds;
 
    // Main game loop
    while (player1Points < number_of_winning_rounds && player2Points < number_of_winning_rounds)
    {
        ++i;
        std::cout << "Round " << (i) << std::endl;
 
        // Player 1
        Item *Player1 = nullptr;
        bool is_input_ok = false;
        int user_input_int;
 
        do
        {
            std::cout << player1Name << ", it's your turn!" << std::endl;
            std::cout << ROCK << " - Rock" << std::endl;
            std::cout << PAPER << " - Paper" << std::endl;
            std::cout << SCISSORS << " - Scissors" << std::endl;
            std::cout << EXIT << " - Exit" << std::endl;
 
            std::string user_input;
            std::cin >> user_input;
 
            user_input_int = std::atoi(user_input.c_str());
 
            // Convert the user's choice to an Item object
            switch (user_input_int)
            {
            case ROCK:
                Player1 = new Rock();
                is_input_ok = true;
                break;
            case PAPER:
                Player1 = new Paper();
                is_input_ok = true;
                break;
            case SCISSORS:
                Player1 = new Scissors();
                is_input_ok = true;
                break;

            case EXIT:
                std::cout << "Exiting the program..." << std::endl;
                return 0; 

            default:
                is_input_ok = false;
                std::cout << "Wrong input" << std::endl;
                break;
            }
        } while (!is_input_ok);
 
        // Player 2
        Item *Player2 = nullptr;
        bool is_input_ok_ = false;
        int user_input_int_;
 
 
        do
        {
            std::cout << player2Name << ", it's your turn!" << std::endl;
            std::cout << ROCK << " - Rock" << std::endl;
            std::cout << PAPER << " - Paper" << std::endl;
            std::cout << SCISSORS << " - Scissors" << std::endl;
            std::cout << EXIT << " - Exit" << std::endl;
 
            std::string user_input_;
            std::cin >> user_input_;
 
            user_input_int_ = std::atoi(user_input_.c_str());
 
            switch (user_input_int_)
            {
            case ROCK:
                is_input_ok_ = true;
                Player2 = new Rock();
                break;
            case PAPER:
                is_input_ok_ = true;
                Player2 = new Paper();
                break;
            case SCISSORS:
                is_input_ok_ = true;
                Player2 = new Scissors();
                break;

            case EXIT:
                std::cout << "Exiting the program..." << std::endl;
                return 0; 

            default:
                is_input_ok_ = false;
                std::cout << "Wrong input" << std::endl;
                break;
            }
        } while (!is_input_ok_);
 
        // Determine the winner for this round
        switch (comparerChoix(Player1, Player2))
        {
        case 2:
            std::cout << player1Name << " has chosen " << Player1->getChoiceName() << " and " << player2Name << " has chosen " << Player2->getChoiceName() << ". " << player1Name << " wins!\n";
            player1Points++;
            break;
        case 0:
            std::cout << player1Name << " has chosen " << Player1->getChoiceName() << " and " << player2Name << " has chosen " << Player2->getChoiceName() << ". " << player2Name << " wins!\n";
            player2Points++;
            break;
        case 1:
            std::cout << player1Name << " has chosen " << Player1->getChoiceName() << " and " << player2Name << " has chosen " << Player2->getChoiceName() << ". It's a Tie!\n";
            break;
        default:
            std::cerr << "Error: Invalid result from comparerChoix()\n";
            break;
        }
 
        // Free memory allocated for Player1 and Player2
        delete Player1;
        delete Player2;
    }
 
    // Display total points
    std::cout << "Total points:" << std::endl;
    std::cout << player1Name << ": " << player1Points << std::endl;
    std::cout << player2Name << ": " << player2Points << std::endl;
 
    return 0;
}