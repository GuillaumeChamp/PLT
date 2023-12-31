# PLT 2023-2024 - Citadelles

[![Actions Status](https://github.com/cbares/plt/workflows/PLT%20build/badge.svg)](https://github.com/cbares/plt/actions)

This project is a school project lead by a group of 4 students at the [ENSEA]([https://www.ensea.fr/en) :
- [Karl Lubbos](https://github.com/KarlLbs)
- [Simon Tristant](https://github.com/Cinortas)
- [Nordine Laouedj](https://github.com/LNordine)
- Guillaume Champtoussel (me)

The goal is to reproduce a board game using Cpp. We chose "Citadelles" and set up the game for 4 players.
AI is implemented to fill the party if need with different strategies.
We also use [SFML](https://www.sfml-dev.org/index-fr.php) for the graphic part.
The application is a client base application and the players use their client.
This repository holds both the server and the client.

School report can be found in [Rapport](https://github.com/GuillaumeChamp/PLT/tree/master/rapport) as Markdown files.

This project came with a CMake which generate the headers from dia2code.
Code coverage is ensure with BOOTS.
A Github action is setup to validate builds.
