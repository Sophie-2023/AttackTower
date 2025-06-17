#include "Game.h"
#include "Menu.h"
#include "End.h"

int main() {
  sf::RenderWindow mWindow{sf::VideoMode({1280, 720}), "Attack Tower Game"};
  Menu menu(mWindow);
  if (!menu.run()) {
    return (0);
  }  // true si victoire, false si d�faite, -1 si fen�tre ferm�e
  while (mWindow.isOpen()) {
    Game game(mWindow);
    int ret = game.run();  // 1 si victoire ,0 si d�faite, -1 si fen�tre ferm�
    if (ret == -1) {
      return 0;
    }  // fermeture de la fen�tre
    else {
      End end(mWindow);
      end.setWin(ret);
      bool ret2 = end.run();
      if (ret2 == -1) {  // fermeture de la fen�tre
        return 0;
      }
    }
  }
}