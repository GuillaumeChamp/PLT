#include "UseCharacterAbilityCommand.h"

namespace engine {

    UseCharacterAbilityCommand::UseCharacterAbilityCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer = state::NO_PLAYER, state::CharacterType targetCharacter = state::NO_CHARACTER, state::Card* targetCard = nullptr){
        this->authorPlayer = authorPlayer;
        this->targetPlayer = targetPlayer;
        this->targetCharacter = targetCharacter;
        this->targetCard = targetCard;
    }

    UseCharacterAbilityCommand::~UseCharacterAbilityCommand() = default;

    void UseCharacterAbilityCommand::execute(state::GameState& state) {
        // Getting the players corresponding to the Ids
        state::Player player = state.getPlayer(authorPlayer);
        state::Player targeted = state.getPlayer(targetPlayer);

        // Getting the character of the author player to know which power to apply
        state::CharacterType character = player.getCharacter();

        // Applying the character ability 
        if (character == state::CharacterType::ASSASSIN)
        {
            state.setKilledCharacter(targetCharacter);
        }


        else if (character == state::CharacterType::THIEF)
        {
            state.setRobbedCharacter(targetCharacter);
        }


        else if (character == state::CharacterType::MAGICIAN)
        {
            // Getting the author player's hand
            std::vector<state::Card> authorHand = player.getHand();

            // He either targets a player to switch his cards with
            if (targetPlayer != state::PlayerId::NO_PLAYER)
            {
                // Getting the target player's hand
                std::vector<state::Card> targetHand = targeted.getHand();

                // Inverting their hands
                player.setHand(targetHand);
                targeted.setHand(authorHand);

                // Updating the players in the state
                state.updatePlayer(player);
                state.updatePlayer(targeted);
            } 
            else // or if he didn't target any character, he switches his cards with the stack
            {
                // Getting the current stack and initializing a new hand for the player
                std::vector<state::Card> stack = state.getStack();
                std::vector<state::Card> newHand;

                // Switching the cards
                newHand.insert(newHand.end(), stack.begin(), stack.begin() + (int) authorHand.size());
                stack.insert(stack.begin(), authorHand.begin(), authorHand.end());

                // Updating the state
                player.setHand(newHand);
                state.updatePlayer(player);
                state.setStack(stack);
            }

        }



        else if (character == state::CharacterType::KING)
        {
            state.setCrownOwner(authorPlayer);
        }


        else if (character == state::CharacterType::BISHOP)
        {
            // Nothing to do
        }


        else if (character == state::CharacterType::MERCHANT)
        {
            // Getting the player's coins and adding one
            int coins = player.getNumberOfCoins();
            coins++;
            // Updating the state
            player.setNumberOfCoins(coins);
            state.updatePlayer(player);
        }


        else if (character == state::CharacterType::ARCHITECT)
        {
            // Creating a DrawCommand of two cards
            auto* command = new DrawCommand(authorPlayer, 2);
            Engine::getInstance(state)->addCommand(command);
        }


        else if (character == state::CharacterType::WARLORD)
        {
            // Getting the targeted player's board
            std::vector<state::Card> targetBoard = targeted.getBoardOfPlayer();
            
            // Destroying the building
            for (auto i = targetBoard.begin(); i < targetBoard.end(); i++) {
                if (targetBoard[i - targetBoard.begin()].getNameOfCard() == targetCard->getNameOfCard()) {
                   targetBoard.erase(i);
                }
            }

            // Updating the Warlord's coins
            int coins = player.getNumberOfCoins();
            coins = coins - targetCard->getCostOfCard();

            // Updating the state
            player.setNumberOfCoins(coins);
            targeted.setBoardOfPlayer(targetBoard);
            state.updatePlayer(player);
            state.updatePlayer(targeted);
        }

    }

    void UseCharacterAbilityCommand::serialize() {
    }

    bool UseCharacterAbilityCommand::check(state::GameState &state) {
        return Command::check(state);
    }
} // namespace engine