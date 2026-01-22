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
      x = 0;
      y = 0;
      direction = 1;  // Start facing right
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

    int getX() const {
      return x;
    }

    int getY() const {
      return y;
    }

    void setX(int newX) {
      x = newX;
    }

    void setY(int newY) {
      y = newY;
    }

    int getDirection() const {
      return direction;
    }

    void setDirection(int newDirection) {
      direction = newDirection;
    }

    void walk(int minX, int maxX, int spriteWidth) {
      if (!alive) return;

      // Move in the current direction
      if (direction == 1) {  // Moving right
        x += 1;
        // Check if hit right wall
        if (x + spriteWidth >= maxX) {
          x = maxX - spriteWidth;
          direction = 0;  // Change to left
        }
      } else {  // Moving left (direction == 0)
        x -= 1;
        // Check if hit left wall
        if (x <= minX) {
          x = minX;
          direction = 1;  // Change to right
        }
      }
    }

  private:
    int hunger;
    int play;
    int rave;
    bool alive;

    int x;
    int y;
    int direction;  // 0 = left, 1 = right

    void checkAlive() {
      // Pet dies if any stat reaches 0
      if (hunger <= 0 || play <= 0 || rave <= 0) {
        alive = false;
      }
    }
};

#endif
