#include "UseWonderAbilityCommand.h"

namespace engine {

    // Constructor
    UseWonderAbilityCommand::UseWonderAbilityCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer, state::Card card) : card(card) {
        this->authorPlayer = authorPlayer;
        this->targetPlayer = targetPlayer;
        this->card = card;
    }

    // Destructor
    UseWonderAbilityCommand::~UseWonderAbilityCommand() {
    }

    // Execute method
    void UseWonderAbilityCommand::execute(state::GameState& state) {
        // Getting the players corresponding to the Ids
        state::Player player = state.getPlayer(authorPlayer);
        state::Player targeted = state.getPlayer(targetPlayer);

        // Applying the wonder ability 
        if (card.getNameOfCard() == "Laboratoire") 
        {
            // Une fois par tour, défausser une carte contre 1 pièce
            std::vector<state::Card> hand = player.getHand();
        }
        else if (card.getNameOfCard() == "Manufacture") 
        { // Once per turn, you can use 3 coins to draw 3 cards
            // Getting the player's hand and coins
            std::vector<state::Card> hand = player.getHand();
            int coins = player.getNumberOfCoins();

            // Creating a DrawCommand of three cards
            auto* command = new DrawCommand(authorPlayer, 3);
            Engine::getInstance(state).addCommand(command);

            // Deducing the coins
            coins = coins - 3;
            player.setNumberOfCoins(coins);

            // Updating the state
            state.updatePlayer(player);
        }
    }

    // Check method
    bool UseWonderAbilityCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
