#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/GameState.h"

using namespace ::state;


BOOST_AUTO_TEST_CASE(TestState)
{
  {
    Card card{"card1", CardType::Military, 2};
    BOOST_CHECK_EQUAL(card.getNameOfCard(), std::string("card1"));
    BOOST_CHECK_EQUAL(card.getColorOfCard(), CardType::Military);
    BOOST_CHECK_EQUAL(card.getCostOfCard(), 2);

    Player plr {"player1", PlayerId::PlayerA};
    BOOST_CHECK_EQUAL(plr.getNameOfPlayer(),"player1");
    BOOST_CHECK_EQUAL(plr.getIdOfPlayer(),PlayerId::PlayerA);
    BOOST_CHECK_EQUAL(plr.getCharacter(),CharacterType::NoCharacter);
    std::vector<Card> hand {card};
    plr.setHand(hand);
    BOOST_CHECK_EQUAL(plr.getHand()[0].getNameOfCard(),hand[0].getNameOfCard());
    BOOST_CHECK_EQUAL(plr.getNumberOfCards(),1);
    plr.setNumberOfCoins(5);
    BOOST_CHECK_EQUAL(plr.getNumberOfCoins(),5);
    std::vector<Card> board;
    plr.setBoardOfPlayer(board);
    BOOST_CHECK_EQUAL(plr.getBoardOfPlayer().size(),board.size());
    plr.setCharacter(CharacterType::Warlord);
    BOOST_CHECK_EQUAL(plr.getCharacter(),CharacterType::Warlord);

    GameState gameState{std::vector<Player>{plr}};
    BOOST_CHECK_EQUAL(gameState.getListOfPlayer().size(),1);
    BOOST_CHECK_EQUAL(gameState.getNbCardToDraw(), 52);
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(),CharacterType::NoCharacter);
    BOOST_CHECK_EQUAL(gameState.getGamePhase(),GamePhase::DrawCharacters);

    gameState.setCrownOwner(PlayerId::PlayerA);
    BOOST_CHECK_EQUAL((gameState.getCrownOwner()), plr.getIdOfPlayer());

    gameState.setNbCardToDraw(48);
    BOOST_CHECK_EQUAL(gameState.getNbCardToDraw(),48);

    gameState.setCurrentCharacter(CharacterType::King);
    BOOST_CHECK_EQUAL(gameState.getCurrentCharacter(),CharacterType::King);

    gameState.nextGamePhase();
    BOOST_CHECK_EQUAL(gameState.getGamePhase(),GamePhase::PlayTurn);

    gameState.endGame();
    BOOST_CHECK_EQUAL(gameState.getGamePhase(),GamePhase::EndOfGame);

  }
}

/* vim: set sw=2 sts=2 et : */
