// Engine.cpp
#include "Engine.h"


namespace engine {
    Engine *Engine::INSTANCE = nullptr;

    Engine::Engine(state::GameState &state) : currentState(state) {
        // Other initialization if needed
        init();
    }

    // Destructor
    Engine::~Engine() = default;

    void Engine::init() {
        // Perform initialization tasks here
    }

    void Engine::addCommand(Command *cmd) {
        listOfCommands.push_back(cmd);
    }


    void Engine::executeAllCommands() {
        //execute all the commands but check before
        for (Command *command: listOfCommands) {
            if (command->check(currentState)) {
                command->execute(currentState);
            }
        }
        //free the memory with processed command
        for (auto p: listOfCommands) {
            delete p;
        }
        listOfCommands.clear();
    }

    Engine *Engine::getInstance(state::GameState &state) {
        if (!INSTANCE) {
            INSTANCE = new Engine(state);
        }
        return INSTANCE;
    }
}
