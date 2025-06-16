#include "Game.h"

int main() {
  sf::RenderWindow mWindow{sf::VideoMode({1000, 700}), "Attack Tower Game"};
  while (mWindow.isOpen()) {
    Game game(mWindow);
    int ret = game.run();  // 1 si victoire ,0 si défaite, -1 si fenêtre fermé
    if (ret == -1) {
      return 0;
    }  // fermeture de la fenêtre
    else {
      End end(mWindow);
      end.setWin(ret);
      bool ret2 = end.run();
      if (ret2 == -1) {  // fermeture de la fenêtre
        return 0;
      }
    }
  }
}