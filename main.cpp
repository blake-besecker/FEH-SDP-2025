#include "FEHImages.h"
#include "FEHKeyboard.h"
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHUtility.h"
// images and sprites
// bg, player, bosses
FEHImage background1("images/bg_1.png");
// FEHImage background2("bg_2.png");
// FEHImage background3("bg_3.png");

FEHImage boss1("images/boss_1.png");
// FEHImage boss2("boss_2.png");
// FEHImage boss3("boss_3.png");

FEHImage player1("images/player_1.png");
// FEHImage player2("player2_2.png");
// FEHImage player3("player_3.png");

// attack images
FEHImage line("images/line.png");
FEHImage zone("images/zone.png");
FEHImage selector("images/selector.png");

class Game {
private:
  float startTime, duration = 30, difficulty = 1;
  int hp = 100, state = 0;

public:
  Game();
  int line_attack();
  int match_attack();
  int startScreen();
  int endScreen(bool success);
  void attack();
  void update(bool inAttack);
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

int Game::line_attack() {
  // constructs a line on screen with a zone around it. also moves a
  // 'selector' selector traverses the line, stopping when it gets to the end
  // user must press space before it gets to the end AND within the zone
  // accumulates 'fails' up to 3 (one per round)
  // returns this value times ten so we can calculate HP loss within the loop
  int zone_place;
  int selector_place = 10;
  int round = 1;
  int fails = 0;
  float round_time;

  while (round <= 3) {

    round_time = TimeNow();
    selector_place = 100;
    zone_place = int(120 + (Random.RandInt() / 32767.0) * 60);

    while (!Keyboard.isPressed(KEY_SPACE) && selector_place < 240) {
      LCD.Clear();
      update(true);
      line.Draw(80, 190);
      zone.Draw(zone_place, 190);
      selector.Draw(selector_place, 180);
      selector_place += (2 * difficulty);
      LCD.Update();
      Sleep(0.01);
    }
    Sleep(0.1);
    if (selector_place < zone_place - 20 || selector_place > zone_place + 20) {
      fails++;
    }
    round++;
  }
  LCD.Clear();
  update(false);
  return fails * 10;
}

int Game::match_attack() {
  int fails = 0;
  int round = 1;
  // sequence characters
  char letter;
  int choice;
  float round_start;
  float round_time = 10 / difficulty;

  while (round <= 5) {
    LCD.Clear();
    choice = Random.RandInt() % 4;
    if (choice == 1)
      letter = 'a';
    if (choice == 2)
      letter = 's';
    if (choice == 3)
      letter = 'd';
    if (choice == 4)
      letter = 'f';
    round_start = TimeNow();
    update(true);
    LCD.WriteAt(letter, 160, 120);
    LCD.Update();
    while (!Keyboard.areAnyPressed() && TimeNow() - round_start <= round_time) {
      Sleep(0.1);
    }
    if (Keyboard.lastChar() != choice)
      fails++;
    LCD.Clear();
    update(true);
    LCD.WriteAt(letter, 160, 120);
    LCD.Update();

    Sleep(0.2);
    round++;
  }
  return fails * 10;
}

int Game::startScreen() {
  LCD.Clear();
  // the beginning screen. should have an option for stats, options, etc.
  // returns difficulty (1,2,3 for easy, medium, hard)
  background1.Draw(0, 0);
  player1.Draw(120, 130);
  boss1.Draw(180, 130);
  LCD.Update();
  Sleep(2.0);
}

int Game::endScreen(bool success = false) {
  LCD.Clear();
  state = 0;
  // the end screen. should offer to play again. returns 1 to play again, and
  // 0 to close takes in a success variable(true is a win, false is a lose)
  LCD.Update();
}

void Game::attack() {
  // initiate an attack. depending on the type, does a different type
}

void Game::update(bool inAttack = false) {
  LCD.Clear();
  float time = TimeNow() - startTime;
  if (hp <= 0) {
    endScreen();
    return;
  }
  // update visual elements(background, boss sprite, player, sprite, music,
  // etc)
  int stage;
  if (time < duration / 3) {
    background1.Draw(0, 0);
    if (!inAttack) {
      // player1.Draw(0,0);
      // boss1.Draw(0,0);
    }

  } else if (time < ((2 * duration) / 3)) {
    background1.Draw(0, 0);
    if (!inAttack) {
      // player2.Draw(0,0);
      // boss2.Draw(0,0);
    }
  } else {
    background1.Draw(0, 0);
    if (!inAttack) {
      // player3.Draw(0,0);
      // boss3.Draw(0,0);
    }
  }
  if (!inAttack)
    LCD.Update();
}

void Game::mainloop() {
  // the main loop of the game
  startTime = TimeNow();
  startScreen();
  while (TimeNow() - startTime <= duration) {

    match_attack();
    Sleep(2.0);
    line_attack();
  }

  endScreen(true);
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