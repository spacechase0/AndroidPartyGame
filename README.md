Game code is in game-integrate branch. Had problems with linker error 'undefined reference to typeof sf::Socket' or something (Despite having RTTI enabled on both SFML and this, and not ever using typeof directly. Grr).

The test client in gameserver/ works (although obviously no UI for logging in or any meaningful validation or anything).
