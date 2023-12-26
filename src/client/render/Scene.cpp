#include "Scene.h"
#include <iostream>
#include "config.h"


namespace render {

    Scene::Scene(SceneId sceneId, state::GameState *state) {
        std::string res = RES_DIR;
        this->sceneId = sceneId;
        this->state = state;
        this->height = 900;
        this->width = 1600;
        this->fontText.loadFromFile(res + "Garet-Book.ttf");
        this->fontTitle.loadFromFile(res + "OldLondon.ttf");

        listOfButtons.emplace_back(ButtonType::bank, 700, 350);
        listOfButtons.emplace_back(ButtonType::draw, 900, 350);
        listOfButtons.emplace_back(ButtonType::endOfTurn, 780, 500);
        //listOfButtons.emplace_back(ButtonType::hand, 1500,850);
        listOfButtons.emplace_back(ButtonType::hand, 600, 300);
        listOfButtons.emplace_back(ButtonType::help, 1500, 50);

        //Background
        this->background = sf::RectangleShape();
        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(21, 25, 29));

        //logo crown + gold + cartes

        sf::Texture crown, gold, card;
        crown.loadFromFile(res + "crown.png");
        gold.loadFromFile(res + "coin.png");
        card.loadFromFile(res + "coin.png");
        this->crownTexture = crown;
        this->goldTexture = gold;
        this->cardTexture = card;

        // Texte pour le helpMenu

        this->helpMenuText = sf::Text();
        helpMenuText.setFont(fontText);
        helpMenuText.setString("Regles du jeu.\n\n"
                               "Voici les regles de Citadelles\nLigne 2\nLigne 3\nLigne 4\nLigne 5\n"
                               "Ligne 6\nLigne 7\nLigne 8\nLigne 9\nLigne 10\n"
                               "Ligne 11\nLigne 12\nLigne 13\nLigne 14\nLigne 15");
        helpMenuText.setCharacterSize(20);
        helpMenuText.setFillColor(sf::Color(55, 53, 53));
        helpMenuText.setPosition(370, 220);


    }

    Scene::~Scene() {
        this->listOfButtons.clear();
        this->displayedCard.clear();
    }

    void Scene::draw(sf::RenderWindow &window) {
        // dessine les éléments communs à toutes les scenes
        displayedCard.clear();

        //Background
        window.draw(background);



        //Affichage des fonds boards + emplacements cartes
        std::vector<std::pair<int, int>> coordinatesList = {
                {615,  622}, //en bas
                {0,    311},  //a gauche
                {615,  0}, //en haut
                {1240, 311} // a droite
        };

        for (const auto &coordinates: coordinatesList) {
            //Board background
            sf::RectangleShape board(sf::Vector2f(360, 278));

            int x = coordinates.first;
            int y = coordinates.second;

            board.setPosition(x, y);
            board.setFillColor(sf::Color(165, 134, 105));

            window.draw(board);

            //Cards location
            sf::RectangleShape cardsLocation(sf::Vector2f(80, 124));
            cardsLocation.setFillColor(sf::Color(233, 220, 205));

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 2; j++) {
                    cardsLocation.setPosition(x + 10 + 90 * i, y + 10 + 134 * j);
                    window.draw(cardsLocation);
                }
            }


        }


        std::vector<std::pair<float, float>> posLogo = {
                //Coordonné du pixel en haut a gauche du logo couronne de chaqe board
                {985,  624}, //en bas
                {370,  313},  //a gauche
                {985,  2}, //en haut
                {1150, 313} // a droite
        };

        for (const auto &coordinates: posLogo) {
            float pos_x = coordinates.first;
            float pos_y = coordinates.second;

            sf::RectangleShape crownIcon, goldIcon, cardIcon;
            crownIcon.setSize(sf::Vector2f(40, 40));
            goldIcon.setSize(sf::Vector2f(40, 40));
            cardIcon.setSize(sf::Vector2f(40, 40));

            crownIcon.setPosition(pos_x, pos_y);
            crownIcon.setTexture(&crownTexture);
            goldIcon.setPosition(pos_x + 40, pos_y + 50);     //Emplacement réfléchis pour garder la place pour le texte
            goldIcon.setTexture(&goldTexture);
            cardIcon.setPosition(pos_x + 40, pos_y + 100);
            cardIcon.setTexture(&cardTexture);

            window.draw(crownIcon);
            window.draw(goldIcon);
            window.draw(cardIcon);
        }



        // Affichage des boutons
        for (auto &button: listOfButtons) {
            button.draw(window);
        }



        //Affichage des cartes des joueurs

        std::vector<state::Player> listOfPlayer = state->getListOfPlayer();
        std::vector<state::Player> listOfPlayerOrder;

        int idOfSceneOwner = sceneId;
        listOfPlayerOrder.push_back(listOfPlayer[sceneId - 1]);

        for (int i = 0; i < 3; i++) {
            idOfSceneOwner++;
            idOfSceneOwner > 4 ? 1 : idOfSceneOwner;
            for (auto &player2: listOfPlayer) {
                if (player2.getIdOfPlayer() == idOfSceneOwner) {
                    listOfPlayerOrder.push_back(player2);
                    break;
                }
            }
        }



        //Affichage info par joueur
        int i = 0;
        int indexCurrentCharacter, indexCharacterPlayer;

        for (auto &player: listOfPlayerOrder) {

            bool isCrownOwner = false;
            bool isRevealed = false;
            if (player.getIdOfPlayer() == state->getCrownOwner()) {
                isCrownOwner = true;
            }

            for (int k = 0; k < 8; ++k) {
                if (static_cast<state::CharacterType>(k) == player.getCharacter()) {
                    indexCharacterPlayer = k;
                }
                if (static_cast<state::CharacterType>(k) == state->getCurrentCharacter()) {
                    indexCurrentCharacter = k;
                }
            }
            if (indexCharacterPlayer >= indexCurrentCharacter) { isRevealed = true; }

            std::vector<VisualCard> temp = PlayerRender::drawPlayer(window, &player, i, isCrownOwner, isRevealed,
                                                                    fontTitle);
            displayedCard.insert(std::end(displayedCard), std::begin(temp), std::end(temp));
            i++;
        }

        //IDF
        const char *CharacterTypeString[] = {
                "Assassin",
                "Thief",
                "Magician",
                "King",
                "Bishop",
                "Merchant",
                "Architect",
                "Warlord",
                "NoCharacter"
        };
        std::string currentCharacterName = CharacterTypeString[state->getCurrentCharacter()];
        VisualCard currentCharacterCard = VisualCard(currentCharacterName, 10, 10);
        currentCharacterCard.draw(window);

        sf::Text IDFText;
        IDFText.setFont(fontTitle);
        IDFText.setString(std::to_string(indexCurrentCharacter + 1) + " / 8");
        IDFText.setCharacterSize(20);
        IDFText.setFillColor(sf::Color::White);
        IDFText.setPosition(33, 140);
        window.draw(IDFText);

        //Hand
        if (IHMState::getInstance()->isHandDisplayed) {
            drawPlayerHand(window);
        }
        //HelpMenu
        if (IHMState::getInstance()->isHelpDisplayed) {
            drawHelp(window);
        }
        if (IHMState::getInstance()->hoverButton != nullptr) {
            std::cout << "you are hover a button : " << IHMState::getInstance()->hoverButton->name << std::endl;
            //Todo add highlight

        }
        if (IHMState::getInstance()->hoverCard != nullptr){
            std::cout<<"you are hover a card : " <<std::endl;
        }


        //Choose Character
        if (state->getGamePhase()==0 ){
            std::vector<state::CharacterType> availableCharacter = state->getAvailableCharacter();
            int indexFirstCharacterX = 445 + (8-availableCharacter.size())/2*90;
            int indexFirstCharacterY = 388;
            sf::RectangleShape characterChoiceBackground = sf::RectangleShape(sf::Vector2f(90*availableCharacter.size()+10,134));
            characterChoiceBackground.setFillColor(sf::Color::Blue);
            window.draw(characterChoiceBackground);
            
            for (auto& character : availableCharacter) {
                std::string characterName = CharacterTypeString[character];
                VisualCard characterCard = VisualCard(characterName, indexFirstCharacterX, indexFirstCharacterY);
                displayedCard.push_back(characterCard);
                }
        }

        // Card Zoom
        VisualCard * cardToZoom = (IHMState::getInstance()->hoverCard);
        if (cardToZoom != nullptr){
        (*cardToZoom).zoomCard();
        (*cardToZoom).draw(window);
        }

    }


    void Scene::handleEvent(sf::Event event) {
        if (event.type == sf::Event::MouseMoved) {
            IHMState::getInstance()->hoverCard = nullptr;
            for (auto &cards: displayedCard) {
                if (cards.checkHover(event.mouseMove.x, event.mouseMove.y)) {
                    cards.onHoverEvent();
                    break;
                }
            }
            IHMState::getInstance()->hoverButton = nullptr;
            for (auto &button: listOfButtons) {
                if (button.checkHover(event.mouseMove.x, event.mouseMove.y)) {
                    button.onHoverEvent();
                    break;
                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            for (auto &cards: displayedCard) {
                if (cards.checkClick(event.mouseButton.x, event.mouseButton.y)) {
                    cards.onClickEvent();
                    break;
                }
            }
            for (auto &button: listOfButtons) {
                if (button.checkClick(event.mouseButton.x, event.mouseButton.y)) {
                    button.onClickEvent();
                    break;
                }
            }
        }
    }

    void Scene::drawPlayerHand(sf::RenderWindow &window) {

        // fond
        sf::RectangleShape boardBackground(sf::Vector2f(1360, 144));
        boardBackground.setPosition(120, 600);
        boardBackground.setFillColor(sf::Color(76, 68, 53));
        window.draw(boardBackground);

        std::vector<state::Player> listOfPlayer = state->getListOfPlayer();
        for (auto &player: listOfPlayer) {
            if ((int)player.getIdOfPlayer() == sceneId) {

                //Creation des cartes de la main du joueur
                int posFirstCardHandX = 130;
                int posFirstCardHandY = 610;
                int i = 0;
                for (auto &card: player.getHand()) {

                    std::string filename = card.getNameOfCard();
                    displayedCard.emplace_back(filename, posFirstCardHandX + 90 * i, posFirstCardHandY);
                    i++;

                }
            }

        }
    }


    void Scene::drawHelp(sf::RenderWindow &window) {

        sf::RectangleShape helpMenu(sf::Vector2f(900, 500));
        helpMenu.setPosition(350, 200);
        helpMenu.setFillColor(sf::Color(238, 225, 208));
        helpMenu.setOutlineThickness(3.0f);
        helpMenu.setOutlineColor(sf::Color::Black);
        window.draw(helpMenu);
        window.draw(helpMenuText);
    }
}