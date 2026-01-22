#ifndef GAMESTATE_H
#define GAMESTATE_H


// everything related to the game state 
// goes here


class GameState {
  public:
    GameState() {
      hunger = 100;
      play = 100;
      rave = 100;
      alive = true;
    }

    void feed() {
      if (!alive) return;
      hunger = min(100, hunger + 20);
      checkAlive();
    }

    void doPlay() {
      if (!alive) return;
      play = min(100, play + 15);
      checkAlive();
    }

    void doRave() {
      if (!alive) return;
      rave = min(100, rave + 25);
      checkAlive();
    }

    void decay() {
      if (!alive) return;

      if (hunger > 0) {
        hunger -= 5;
      }
      if (play > 0) {
        play -= 3;
      }
      if (rave > 0) {
        rave -= 2;
      }

      checkAlive();
    }

    bool isAlive() const {
      return alive;
    }

    int getHunger() const {
      return hunger;
    }

    int getPlay() const {
      return play;
    }

    int getRave() const {
      return rave;
    }

  private:
    int hunger;
    int play;
    int rave;
    bool alive;

    void checkAlive() {
      // Pet dies if any stat reaches 0
      if (hunger <= 0 || play <= 0 || rave <= 0) {
        alive = false;
      }
    }
};

#endif
