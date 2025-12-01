#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "FEHLCD.h"
#include "FEHKeyboard.h"
// images and sprites
// bg, player, bosses
FEHImage tile("tile.png");
FEHImage tile_danger("tile_danger.png");

FEHImage background1("images/bg_1.png");
//FEHImage background2("bg_2.png");
//FEHImage background3("bg_3.png");

FEHImage boss1("images/boss_1.png");
//FEHImage boss2("boss_2.png");
//FEHImage boss3("boss_3.png");

FEHImage player1("images/player_1.png");

class Game {
private:
  float startTime, duration = 30, difficulty = 1;
  int hp = 100, state = 0;

public:
  Game();
  int startScreen();
  int endScreen(bool success);
  void attack();
  void draw_map(int attack_type);
  void update(bool inAttack);
  void move(char lastkey);
  void mainloop();
  void menuLoop();
  void stats();
  void credits();
  int stateMachine();
};

int main() {
  Game main;
  // state machine active until quit case
  while (main.stateMachine() != -1) {
  }

  return 0;
}

Game::Game() {}

void Game::draw_map(int attack_type) { 
    for (int i = 120; i<260; i+=20) {
        for (int j = 120; j<260; j+=20) {
            tile.Draw(i, j);
        }
    }
    LCD.Update();
}

void Game::move(char lastKey) {
  LCD.Clear();
 float time = TimeNow()-startTime;
 int delta_x = 0, delta_y = 0;
 if (lastKey == 'w') delta_y = 1;
 if (lastKey == 'a') delta_x = -1;
    if (lastKey == 's') delta_y = -1;
    if (lastKey == 'd') delta_x = 1;
    if (hp <= 0) {
        endScreen();
        return;
    }
    //update visual elements(background, boss sprite, player, sprite, music, etc)
    int stage;
    if (time < duration/3) {
        background1.Draw(0,0);
        //player1.Draw(x+delta_x,y+delta_y);
        //boss1.Draw(0,0);
    } else if (time < ((2 * duration) / 3)) {
        background1.Draw(0,0);
        //player2.Draw(x+delta_x,y+delta_y);
        //boss2.Draw(0,0);
    }
    else {
        background1.Draw(0,0);
        //player3.Draw(x+delta_x,y+delta_y);
        //boss3.Draw(0,0);
    }
}

int Game::endScreen(bool success = false) {
  LCD.Clear();
  state = 0;
  // the end screen. should offer to play again. returns 1 to play again, and
  // 0 to close takes in a success variable(true is a win, false is a lose)
  LCD.Update();
}

void Game::attack(bool danger, int attack_type) {
   LCD.Clear();
    draw_map();

        //initiate an attack. depending on the type, does a different type. 
        // if danger is true, then highlight tiles as in "danger".
        // danger tiles are highlighted to signify that an attack is coming so the player can move
        // if danger is false, then set tiles as "hurt"
        // while player is within these tiles, decrement hp
}

void Game::mainloop() {
    //the main loop of the game
    int attack_progress = 0;
    bool inAttack = false;
    int attack_type = Random.RandInt() % 4;
    startTime = TimeNow();
    startScreen();

    while (TimeNow()-startTime <= duration) {
            //wait for a key to be pressed and increase attack timer(1000 = 1 second passed)
        while (!Keyboard.areAnyPressed()) {
            if (attack_progress == 5000) {
                attack(true, attack_type);
            }
            else if (attack_progress == 7000) {
                attack(false, attack_type);
            }
            else if (attack_progress == 9000) {
                draw_map();
                attack_type = Random.RandInt() % 4;
                attack_progress = 0;
            }
            Sleep(0.001);
            if (attack_progress < 9000) attack_progress++;
        }
        move(Keyboard.lastChar());
            

    }

    //endScreen(true);
}

void Game::menuLoop() {
  LCD.Clear();
  // declare an array of four icons called menu
  FEHIcon::Icon menu[4];
  // define the four menu labels
  char menu_labels[4][20] = {"START", "STATS", "CREDITS", "QUIT"};

  // draw the menu in a 2 by 2 array with top and bottom
  // margins of 10 and left and right margins of 5
  // with the menu labels, gold borders, and green text
  FEHIcon::DrawIconArray(menu, 2, 2, 10, 10, 5, 5, menu_labels, GOLD, GREEN);

  float x, y;
  while (!LCD.Touch(&x, &y)) {
  }
  while (LCD.Touch(&x, &y)) {
    // check for each button being pressed and update state acordingly
    // Also std::cout are for debugging
    if (menu[0].Pressed(x, y, 0)) {
      menu[0].Select();
      menu[1].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
      state = 1;
      std::cout << state << "\n";
    } else if (menu[1].Pressed(x, y, 0)) {
      menu[1].Select();
      menu[0].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
      state = 2;
      std::cout << state << "\n";
    } else if (menu[2].Pressed(x, y, 0)) {
      menu[2].Select();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[3].Deselect();
      state = 3;
      std::cout << state << "\n";
    } else if (menu[3].Pressed(x, y, 0)) {
      menu[3].Select();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[2].Deselect();
      state = 4;
      std::cout << state << "\n";
    }
    LCD.Update();
  }
}

void Game::stats() {
  // basic new screen
  LCD.Clear();
  LCD.Write("Stats"); // for some reason this line only is written when you
                      // click anywhere but the button. also moves if you click
                      // multiple times
  FEHIcon::Icon backButton;
  backButton.SetProperties("Back", 120, 80, 80, 80, SCARLET, GRAY);
  backButton.Draw();
  LCD.Update();
  float x, y;
  while (!LCD.Touch(&x, &y)) {
  }
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      state = 0;
    }
  }
}

void Game::credits() {
  // basic credits screen
  LCD.Clear();
  LCD.Write("Credits"); // for some reason this line only is written when you
                        // click anywhere but the button. also moves if you
                        // click multiple times
  FEHIcon::Icon backButton;
  backButton.SetProperties("Back", 120, 80, 80, 80, SCARLET, GRAY);
  backButton.Draw();
  LCD.Update();
  float x, y;
  while (!LCD.Touch(&x, &y)) {
  }
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      state = 0;
    }
  }
}

int Game::stateMachine() {
  // couts are for debugging and could be removed
  switch (state) {
  case 0: // menu state
    std::cout << "CASE 0: MENU";
    menuLoop();
    break;
  case 1: // game state
    std::cout << "CASE 1: GAME";
    mainloop();
    break;
  case 2: // stats menu
    std::cout << "CASE 2: STATS";
    stats();
    break;
  case 3: // credits
    std::cout << "CASE 3: CREDITS";
    credits();
    break;
  case 4: // quit
    std::cout << "CASE 4: QUIT";
    return -1;
    break;
  }
}
