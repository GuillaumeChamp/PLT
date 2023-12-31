#include "Button.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "config.h"

using namespace render;

Button::Button(ButtonType buttonType, float posX, float posY) : InteractiveElement(posX, posY) {
    this->name = buttonType;
    this->surface.setPosition(posX, posY);
    this->surface.setSize(sf::Vector2f(50, 50));
}

Button::~Button() = default;

void Button::onHoverEvent() {
    IHMState::getInstance()->hoverButton = this;
}

void Button::onClickEvent() {
    std::string buttonText;
    switch (name) {
        case ButtonType::bank:
            buttonText = "Recevez deux pièces d'or";
            break;
        case ButtonType::draw:
            buttonText = "Piochez une carte parmis 2";
            break;
        case ButtonType::endOfTurn:
            buttonText = "Fin du tour";
            break;
        case ButtonType::hand:
            buttonText = "Ouvre la main du joueur";
            IHMState::getInstance()->isHandDisplayed = !IHMState::getInstance()->isHandDisplayed;
            break;
        case ButtonType::help:
            buttonText = "Ouvre le menu d'aide";
            IHMState::getInstance()->isHelpDisplayed = !IHMState::getInstance()->isHelpDisplayed;
            break;
        case ButtonType::capacity:
            IHMState::getInstance()->isCapacityButtonPressed = !IHMState::getInstance()->isCapacityButtonPressed;

            break;
    }
    std::cout << "Clic sur le bouton : " << buttonText << std::endl;
}

void Button::draw(sf::RenderWindow &render) {
    std::string res = RES_DIR;
    sf::Texture texture;
    switch (this->name) {
        case ButtonType::bank:
            texture.loadFromFile(res + "chest.png");
            break;
        case ButtonType::draw :
            texture.loadFromFile(res + "draw_icon.png");
            break;
        case endOfTurn:
            texture.loadFromFile(res + "end_of_turn_icon.png");
            break;
        case hand:
            texture.loadFromFile(res + "dos.png");
            break;
        case help:
            texture.loadFromFile(res + "help.png");
            break;
        case capacity:
            texture.loadFromFile(res + "capacity.png");
            break;
    }
    this->surface.setTexture(&texture);
    render.draw(surface);
}

ButtonType Button::getType() const {
    return this->name;
}


