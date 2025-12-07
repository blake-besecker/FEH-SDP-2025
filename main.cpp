#include "FEHImages.h"
#include "FEHKeyboard.h"
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHSound.h"
#include "FEHUtility.h"
// sounds
FEHSound hurt_noise("sounds/hurt.wav");
FEHSound attack_noise("sounds/attack.wav");
FEHSound button_click("sounds/button.wav");
FEHSound bg_music("sounds/music.wav");
FEHSound end_music("sounds/end_music.wav");
FEHSound lose_music("sounds/lose.wav");
//attack sounds
FEHSound ice_warn_s("sounds/ice_warn_sound.wav");
FEHSound ice_danger_s("sounds/ice_danger_sound.wav");

FEHSound fire_warn_s("sounds/fire_warn_sound.wav");
FEHSound fire_danger_s("sounds/fire_danger_sound.wav");

FEHSound ln_warn_s("sounds/lightning_warn_sound.wav");
FEHSound ln_danger_s("sounds/lightning_danger_sound.wav");

FEHSound life_warn_s("sounds/life_warn_sound.wav");
FEHSound life_danger_s("sounds/life_danger_sound.wav");

FEHSound final_warn_s("sounds/final_warn_sound.wav");
FEHSound final_danger_s("sounds/final_danger_sound.wav");
//boss reveal sounds(roughly played in this order)
FEHSound evil_final_break("sounds/evil_final_break.wav");
FEHSound evil_final_reveal("sounds/evil_final_reveal.wav");
FEHSound evil_soul_reveal("sounds/evil_soul_reveal.wav");
//todo, need beam charge and beam noises
FEHSound beam("sounds/beam.wav");

//player sounds
FEHSound player_hurt_sound("sounds/player_hurt_sound.wav");
//music
FEHSound menu_music("sounds/menu_music.wav");
FEHSound game_music("sounds/game_music.wav");
FEHSound final_music("sounds/final_music.wav");
//images and sprites
//tiles
FEHImage tile("images/floor_tile.png");

FEHImage ice_warn("images/floor_ice_warn.png");
FEHImage ice_danger("images/floor_ice_danger.png");

FEHImage fire_warn("images/floor_fire_warn.png");
FEHImage fire_danger("images/floor_fire_danger.png");

FEHImage ln_warn("images/floor_lightning_warn.png");
FEHImage ln_danger("images/floor_lightning_danger.png");

FEHImage life_warn("images/floor_life_warn.png");
FEHImage life_danger("images/floor_life_danger.png");

FEHImage final_warn("images/floor_final_warn.png");
FEHImage final_danger("images/floor_final_danger.png");

FEHImage bad_tile("images/floor_fire_warn.png");
//backgrounds
FEHImage background1("images/game_bg.png");
FEHImage background2("images/game_bg_final.png");
FEHImage menuBackground("images/menubg.png");
FEHImage difficultyBackground("images/castledoor.png");
FEHImage loseBackground("images/losebackground.png");
FEHImage winBackground("images/winbackground.png");
//boss sprites
FEHImage boss1("images/evil_fire.png");
FEHImage boss_fire("images/evil_fire.png");
FEHImage boss_ice("images/evil_ice.png");
FEHImage boss_ln("images/evil_lightning.png");
FEHImage boss_life("images/evil_life.png");
FEHImage boss_reveal_1("images/evil_reveal_1.png");
FEHImage boss_reveal_2("images/evil_reveal_2.png");
FEHImage boss_reveal_3("images/evil_reveal_3.png");
FEHImage boss_final("images/evil_final.png");
//player sprites
FEHImage player1("images/hero_forward.png");

FEHImage hero_forward("images/hero_forward.png");
FEHImage hero_left("images/hero_left.png");
FEHImage hero_right("images/hero_right.png");
FEHImage hero_back("images/hero_back.png");

FEHImage hero_dmg("images/hero_damage.png");
//sword charge frames
FEHImage sword("images/no_damage.png");
FEHImage sword1("images/leg_charge_1.png");
FEHImage sword2("images/leg_charge_2.png");
FEHImage sword3("images/leg_charge_3.png");
FEHImage sword4("images/leg_charge_4.png");
FEHImage sword5("images/leg_charge_5.png");
FEHImage sword6("images/leg_charge_6.png");
FEHImage sword7("images/leg_charge_7.png");
FEHImage sword8("images/leg_charge_8.png");
FEHImage sword9("images/leg_charge_9.png");
FEHImage sword10("images/leg_charge_10.png");
FEHImage sword11("images/leg_charge_11.png");
FEHImage sword12("images/leg_charge_12.png");
FEHImage sword13("images/leg_charge_13.png");
FEHImage sword14("images/leg_charge_14.png");
FEHImage sword15("images/leg_charge_15.png");
//ending beam frames
FEHImage beam1("images/leg_beam_1.png");
FEHImage beam2("images/leg_beam_2.png");
FEHImage beam3("images/leg_beam_3.png");
// board constants
const int MAX_X = 200, MIN_X = 100, MAX_Y = 260, MIN_Y = 120, INCREMENT = 20;
const int BOARD_ROWS = 5, BOARD_COLUMNS = 5;

// Unused but could be useful for different attack images
enum Tiles { NORMAL = 0, WARNING = 1, ACTIVE = 2 };

/**
 * Game class. holds most variables for the game like the board, player
 * position, attacks, and state. This allows for most functions to not have
 * parameters as all important variables are class level.
 *
 * @author Blake Besecker
 */
class Game {
private:
  // game duration and difficuilty variables
  float startTime, duration;
  int difficulty;
  // hit variables
  float hitCoolDown, lastHit;
  int hp, damage;
  // player variables
  int x, y;
  // boss variables
  int boss_x = 50, boss_y = 15, boss_inc_x = 1, boss_inc_y = 1;
  int attackState, attackProgress, attackType, framesPerAttack, numAttacks;
  // stats (given declarations because they are kept through multiple runs)
  int wins = 0, runs = 0;
  float timeSurvived = 0.0;
  // flow control variables
  int state;
  bool success;
  // game board
  int board[BOARD_ROWS][BOARD_COLUMNS];

public:
  // TODO order functions in a logical way
  Game();
  void resetVariables();
  void resetBoard();
  void getInput(int *deltaX, int *deltaY);
  int checkHit(int attackType);
  void drawMap();
  void attack(int attackType);
  void move();
  void refreshScreen(float time);
  void gameloop();
  void pause();
  void menuLoop();
  void difficultyScreen();
  void statsScreen();
  void creditsScreen();
  void guideScreen();
  int endScreen();
  int stateMachine();
  void ending();
  void drawSword(int x, int y);
};

/**
 * Main fuction that creates a game object and sets its variabels and board
 * before entering the state machine.
 *
 * @author Aaron Bernys
 */
int main() {
  Game main;
  main.resetVariables();
  main.resetBoard();
  // state machine active until quit case
  while (main.stateMachine() != -1) {
  }
  return 0;
}

/**
 * Remove this?
 */
Game::Game() {}

/**
 * Initalize variables to starting values for multiple runs and to set them
 * before the first run.
 *
 * @author Aaron Bernys
 */
void Game::resetVariables() {
  hitCoolDown = 0.9;
  lastHit = TimeNow();
  hp = 100;
  damage = 10;

  x = 0;
  y = 0;

  attackState = 0;
  attackProgress = 0;
  numAttacks = 9;
  attackType = Random.RandInt() % numAttacks;
  sword = FEHImage("images/no_damage.png");
  boss_x = 50;
  boss_y=15;
  state = 0;
}

/**
 * Sets the board to all 0 to clear any attacks.
 *
 * @author Aaron Bernys
 */
void Game::resetBoard() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      board[i][j] = 0;
    }
  }
}

/**
 * Receive last key pressed from user. Sets deltaX and deltaY corresponding to
 * the key pressed and checks for ESC to TODO pause the game.
 *
 * @author Blake Besecker
 * @author Aaron Bernys
 */
void Game::getInput(int *deltaX, int *deltaY) {
  char key = Keyboard.lastChar();
  switch (key) {
  case 'w':
    // case:
    player1 = FEHImage("images/hero_back.png");
    *deltaY = -1;
    break;
  case 'a':
    // case:
    player1 = FEHImage("images/hero_left.png");
    *deltaX = -1;
    break;
  case 's':
    // case:
    player1 = FEHImage("images/hero_forward.png");
    *deltaY = 1;
    break;
  case 'd':
    // case:
    player1 = FEHImage("images/hero_right.png");
    *deltaX = 1;
    break;
  case 27:
    std::cout << "PRESSED ESC" << "\n";
    break;
  }
}

/**
 * Checks board at player position to see if they are hit. Only registers hit if
 * attackState is 2 and the time from last hit is greater than the hitCoolDown.
 *
 * @author Blake Besecker
 */
int Game::checkHit(int attackType) {
  int damage = 0;
  if (TimeNow() - lastHit > hitCoolDown && attackState == 2 &&
      board[x][y] == 1) {
    std::cout << "HIT" << "\n";
    lastHit = TimeNow();
    player_hurt_sound.setVolume(0.5);
    player_hurt_sound.play();
    damage = 10;
  }
  return damage;
}

/**
 * Draw board for no attack and for each attack. Draws bad tiles that are
 * warning or active attacks and regular tiles based on the boards value at each
 * position.
 *
 * @author Blake Besecker
 */
void Game::drawMap() {
  // have to change to get warning and attack type choice one then the other or
  // set a variable to get the name (either warn or danger)
  //  set "bad tile" the type of tile that's bad to stand on.
  if (attackState == 1) {
    // switch to warn tiles and play respective attack noise
    switch (attackType) {
    // assign attack image based on type
    case 1:
      bad_tile = FEHImage("images/floor_lightning_warn.png");
      ln_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) ln_danger_s.play();
      break;
    case 2:
      bad_tile = FEHImage("images/floor_ice_warn.png");
      ice_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) ice_danger_s.play();
      break;
    case 3:
      bad_tile = FEHImage("images/floor_fire_warn.png");
      fire_danger_s.setVolume(0.5);
      if (TimeNow() - startTime < duration) fire_danger_s.play();
      break;
    case 4:
      bad_tile = FEHImage("images/floor_life_warn.png");
      life_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) life_danger_s.play();
      break;
    case 5:
      bad_tile = FEHImage("images/floor_fire_warn.png");
      fire_danger_s.setVolume(0.5);
      if (TimeNow() - startTime < duration) fire_danger_s.play();
      break;
    case 6:
      bad_tile = FEHImage("images/floor_lightning_warn.png");
      ln_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) ln_danger_s.play();
      break;
    case 7:
      bad_tile = FEHImage("images/floor_ice_warn.png");
      ice_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) ice_danger_s.play();
      break;
    case 8:
      bad_tile = FEHImage("images/floor_life_warn.png");
      life_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) life_danger_s.play();
      break;
    case 9:
      bad_tile = FEHImage("images/floor_ice_warn.png");
      ice_danger_s.setVolume(0.7);
      if (TimeNow() - startTime < duration) ice_danger_s.play();
      break;
    }
  } else if (attackState == 2) {
    // switch to danger tiles
    switch (attackType) {
    case 1:
      bad_tile = FEHImage("images/floor_lightning_danger.png");
      break;
    case 2:
      bad_tile = FEHImage("images/floor_ice_danger.png");
      break;
    case 3:
      bad_tile = FEHImage("images/floor_fire_danger.png");
      break;
    case 4:
      bad_tile = FEHImage("images/floor_life_danger.png");
      break;
    case 5:
      bad_tile = FEHImage("images/floor_fire_danger.png");
      break;
    case 6:
      bad_tile = FEHImage("images/floor_lightning_danger.png");
      break;
    case 7:
      bad_tile = FEHImage("images/floor_ice_danger.png");
      break;
    case 8:
      bad_tile = FEHImage("images/floor_life_danger.png");
      break;
    case 9:
      bad_tile = FEHImage("images/floor_ice_danger.png");
      break;
    }
  }
  if (attackState == 0) {
    for (int i = MIN_X; i < MAX_X; i += INCREMENT) {
      for (int j = MIN_Y; j < MAX_Y-INCREMENT*2; j += INCREMENT) {
        tile.Draw(i, j);
      }
    }
  } else {
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        if (board[i][j] == 0) {
          tile.Draw((i * INCREMENT + MIN_X - 2), (j * INCREMENT + MIN_Y));
        } else {
          bad_tile.Draw((i * INCREMENT + MIN_X - 1), (j * INCREMENT + MIN_Y));
        }
      }
    }
  }
}

/**
 * Define each attackType and add it to the board to change its values at each
 * position.
 *
 * @author Aaron Bernys
 */
void Game::attack(int attackType) {
  int hashAttack[BOARD_ROWS][BOARD_COLUMNS] = {{0, 1, 0, 1, 0},
                                               {1, 1, 1, 1, 1},
                                               {0, 1, 0, 1, 0},
                                               {1, 1, 1, 1, 1},
                                               {0, 1, 0, 1, 0}};
  int gridAttack[BOARD_ROWS][BOARD_COLUMNS] = {{1, 1, 1, 1, 1},
                                               {1, 0, 1, 0, 1},
                                               {1, 1, 1, 1, 1},
                                               {1, 0, 1, 0, 1},
                                               {1, 1, 1, 1, 1}};
  int diamondAttack[BOARD_ROWS][BOARD_COLUMNS] = {{0, 0, 1, 0, 0},
                                                  {0, 1, 1, 1, 0},
                                                  {1, 1, 1, 1, 1},
                                                  {0, 1, 1, 1, 0},
                                                  {0, 0, 1, 0, 0}};
  int checkerAttack[BOARD_ROWS][BOARD_COLUMNS] = {{0, 1, 0, 1, 0},
                                                  {1, 0, 1, 0, 1},
                                                  {0, 1, 0, 1, 0},
                                                  {1, 0, 1, 0, 1},
                                                  {0, 1, 0, 1, 0}};
  int inverseCheckerAttack[BOARD_ROWS][BOARD_COLUMNS] = {{1, 0, 1, 0, 1},
                                                         {0, 1, 0, 1, 0},
                                                         {1, 0, 1, 0, 1},
                                                         {0, 1, 0, 1, 0},
                                                         {1, 0, 1, 0, 1}};
  int targetAttack[BOARD_ROWS][BOARD_COLUMNS] = {{1, 1, 1, 1, 1},
                                                 {1, 1, 1, 1, 1},
                                                 {1, 1, 0, 1, 1},
                                                 {1, 1, 1, 1, 1},
                                                 {1, 1, 1, 1, 1}};
  switch (attackType) {
    // static attacks
  case 0:
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        board[i][j] += hashAttack[i][j];
      }
    }
    break;
  case 1:
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        board[i][j] += gridAttack[i][j];
      }
    }
    break;
  case 2:
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        board[i][j] += diamondAttack[i][j];
      }
    }
    break;
  case 3:
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        board[i][j] += checkerAttack[i][j];
      }
    }
    break;
  case 4:
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        board[i][j] += inverseCheckerAttack[i][j];
      }
    }
    break;
  case 5:
    for (int i = 0; i < BOARD_ROWS; i++) {
      for (int j = 0; j < BOARD_COLUMNS; j++) {
        board[i][j] += targetAttack[i][j];
      }
    }
    break;
  // moving attacks
  case 6: {
    std::cout << "ROW ATTACK" << "\n";
    int row = Random.RandInt() % BOARD_ROWS;
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board[row][j] = 1;
    }
    break;
  }
  case 7: {
    std::cout << "COLUMN ATTACK" << "\n";
    int column = Random.RandInt() % BOARD_COLUMNS;
    for (int i = 0; i < BOARD_ROWS; i++) {
      board[i][column] = 1;
    }
    break;
  }
  case 8: {
    std::cout << "SNIPER ATTACK" << "\n";
    int currentX = x;
    int currentY = y;
    board[currentX][currentY] = 1;
    break;
  }
  }
}

/**
 * Moves the player clamping it inside the board. Changes the player image based
 * on time since last hit.
 *
 * @author Blake Besecker
 */
void Game::move() {
  float time = TimeNow() - startTime;
  int delta_x = 0, delta_y = 0;
  if (TimeNow() - lastHit <= hitCoolDown) {
    hero_dmg = FEHImage("images/hero_damage.png");
  } else {
    hero_dmg = FEHImage("images/no_damage.png");
  }
  getInput(&delta_x, &delta_y);

  if (x + delta_x >= 0 && x + delta_x < 5) {
    x += delta_x;
  }
  if (y + delta_y >= 0 && y + delta_y < 5) {
    y += delta_y;
  }
  refreshScreen(time);
}

/**
 * Redraws the screen and draws UI.
 *
 * @author Blake Besecker
 */
void Game::refreshScreen(float time) {
  background1.Draw(0, 0);
  drawMap();
  player1.Draw((x * INCREMENT + MIN_X - 2), (y * INCREMENT + MIN_Y - 7));
  hero_dmg.Draw((x * INCREMENT + MIN_X - 4), (y * INCREMENT + MIN_Y - 9));
  if ((TimeNow() - startTime < duration) && (boss_x == 150 || boss_x == 40))
    boss_inc_x *= -1;
  if ((TimeNow() - startTime < duration) && (boss_y == 40 || boss_y == 0))
    boss_inc_y *= -1;
  boss_x += boss_inc_x;
  boss_y += boss_inc_y;
  if (TimeNow() - startTime < duration) boss1.Draw(boss_x, boss_y);
  else boss1.Draw(115, 20);
  LCD.SetFontColor(DARKBLUE);
  LCD.SetFontScale(0.5);
  LCD.WriteAt("MANA: ", 126, 225);
  LCD.SetFontColor(BLUE);
  LCD.WriteAt(hp, 156, 225);
  float currentTime = TimeNow() - startTime;
  timeSurvived += currentTime;
  if (TimeNow() - startTime < duration) drawSword(16, 135);
  if (TimeNow() - startTime > duration-30 && TimeNow()-startTime < duration-28) {
      LCD.SetFontColor(GOLD);
      LCD.SetFontScale(0.5);
      LCD.WriteAt("i found it",100, 95);
  }
}

void Game::drawSword(int x, int y) {
  if (TimeNow() - startTime > duration-30) sword= FEHImage("images/leg_charge_1.png");
  if (TimeNow() - startTime > duration-28) sword=FEHImage("images/leg_charge_2.png");
  if (TimeNow() - startTime > duration-26) sword=FEHImage("images/leg_charge_3.png");
  if (TimeNow() - startTime > duration-24) sword=FEHImage("images/leg_charge_4.png");
  if (TimeNow() - startTime > duration-22) sword=FEHImage("images/leg_charge_5.png");
  if (TimeNow() - startTime > duration-20) sword=FEHImage("images/leg_charge_6.png");
  if (TimeNow() - startTime > duration-18) sword=FEHImage("images/leg_charge_7.png");
  if (TimeNow() - startTime > duration-16) sword=FEHImage("images/leg_charge_8.png");
  if (TimeNow() - startTime > duration-14) sword=FEHImage("images/leg_charge_9.png");
  if (TimeNow() - startTime > duration-12) sword=FEHImage("images/leg_charge_10.png");
  if (TimeNow() - startTime > duration-10) sword=FEHImage("images/leg_charge_11.png");
  if (TimeNow() - startTime > duration-8) sword=FEHImage("images/leg_charge_12.png");
  if (TimeNow() - startTime > duration-6) sword=FEHImage("images/leg_charge_13.png");
  if (TimeNow() - startTime > duration-4) sword=FEHImage("images/leg_charge_14.png");
  if (TimeNow() - startTime > duration-2) sword=FEHImage("images/leg_charge_15.png");
  sword.Draw(x,y);
}

void Game::ending() {
  bg_music.pause();
  end_music.setVolume(1);
  end_music.play();
  refreshScreen(TimeNow()-startTime);
  drawSword(16,135);
  LCD.SetFontColor(RED);
  LCD.SetFontScale(0.5);
  LCD.WriteAt("oh it charged",100, 95);
  Sleep(1.0);

  refreshScreen(TimeNow()-startTime);
  drawSword(17,134);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(18,133);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(19,132);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(20,130);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(21,129);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(22,128);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(23,127);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(24,125);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(25,123);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(26,121);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(27,120);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(28,118);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(29,115);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(30,110);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(32,105);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(33,100);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(34,95);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(36,90);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(37,85);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(38,80);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(40,75);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(41,65);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(42,55);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(44,50);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(45,45);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(46,40);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(48,35);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(46,30);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(44,25);
  Sleep(0.005);

  refreshScreen(TimeNow()-startTime);
  drawSword(42,20);
  LCD.SetFontColor(RED);
  LCD.SetFontScale(0.5);
  LCD.WriteAt("uh oh",100, 95);

  Sleep(0.5);
  beam.setVolume(0.5);
  beam.play();
  Sleep(1.5);
  FEHImage("images/leg_beam_1.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_2.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_3.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_1.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_2.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_3.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_1.png").Draw(90,0);
  Sleep(0.7);
  FEHImage("images/leg_beam_2.png").Draw(90,0);
  Sleep(0.7);
  beam.pause();
}

/**
 * Main loop of the game attack progress is the progress towards an attack
 * happening. increases by 1000 a second attack state. 0, nothing happens. 1,
 * warning. 2, attack is going on attack type, 1-4. each one does something
 * different
 *
 * @author Blake Besecker
 */
void Game::gameloop() {
  switch (difficulty) {
  case 1:
    duration = 30;
    framesPerAttack = 40;
    break;
  case 2:
    duration = 60;
    framesPerAttack = 35;
    break;
  case 3:
    duration = 90;
    framesPerAttack = 30;
    break;
  }

  startTime = TimeNow();
  bg_music.setVolume(0.6);
  bg_music.play();

  while (TimeNow() - startTime <= duration) {
    LCD.Clear();

    if (attackState == 0 && attackProgress == 0) {
      resetBoard();
      attackType = Random.RandInt() % numAttacks;
      attack(attackType);
      switch (attackType) {
      case 1:
        boss1 = FEHImage("images/evil_lightning.png");
        break;
      case 2:
        boss1 = FEHImage("images/evil_ice.png");
        break;
      case 3:
        boss1 = FEHImage("images/evil_fire.png");
        break;
      case 4:
        boss1 = FEHImage("images/evil_life.png");
        break;
      case 5:
        boss1 = FEHImage("images/evil_fire.png");
        break;
      case 6:
        boss1 = FEHImage("images/evil_lightning.png");
        break;
      }
    }

    if (TimeNow() - startTime < duration) attackProgress++;

    if (attackProgress >= framesPerAttack) {
      attackProgress = 0;
      attackState++;

      if (attackState > 2) {
        attackState = 0;
      }
    }

    move();

    if (hp <= 0) {
      success = false;
      game_music.pause();
      lose_music.setVolume(0.7);
      lose_music.play();
      state = 6;
      return;
    }

    hp -= checkHit(attackType);

    LCD.Update();
    // Sleep(sleepTime);
  }
  success = true;
  wins++;
  ending();
  state = 6;
}

/**
 * Pause menu during gameplay.
 *
 * @author Aaron Bernys
 */
void Game::pause() {
  // Clear screen and draw stats screen
  FEHIcon::Icon resumeButton;
  resumeButton.SetProperties("Resume", 100, 80, 60, 40, WHITE, PURPLE);
  resumeButton.Draw();
  // Wait for touch and select button when under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (resumeButton.Pressed(x, y, 0)) {
      resumeButton.Select();
    } else {
      resumeButton.Deselect();
    }
  }

  // Detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (resumeButton.Pressed(x, y, 0)) {
      button_click.play();
      state = 0;
    }
  }
}

/**
 * Draw menu screen and control button inputs to set state to other screens.
 *
 * @author Aaron Bernys
 */
void Game::menuLoop() {
  // Clear screen and draw menu screen
  LCD.Clear();
  menuBackground.Draw(0, 0);
  FEHIcon::Icon menu[4];
  char menu_labels[4][20] = {"START", "STATS", "CREDITS", "GUIDE"};
  FEHIcon::DrawIconArray(menu, 2, 2, 100, 20, 30, 30, menu_labels, PURPLE,
                         BLUE);
  LCD.SetFontScale(2.0);
  LCD.SetFontColor(PURPLE);
  LCD.WriteAt("BOSS FIGHT", 38, 30);
  LCD.WriteAt("BOSS FIGHT", 39, 31);
  LCD.SetFontColor(BLUE);
  LCD.WriteAt("BOSS FIGHT", 40, 32);
  LCD.SetFontScale(1.0);
  LCD.Update();

  // wait for touch allowing user to quit with ESC and selecting buttons under
  // cursor
  Sleep(100);
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (Keyboard.isPressed(KEY_ESCAPE)) {
      LCD.Clear(BLACK);
      LCD.SetFontColor(PURPLE);
      LCD.WriteLine("Exiting...");
      state = 7;
      Sleep(0.25);
      break;
    }
    if (menu[0].Pressed(x, y, 0)) {
      menu[0].Select();
      menu[1].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
    } else if (menu[1].Pressed(x, y, 0)) {
      menu[1].Select();
      menu[0].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
    } else if (menu[2].Pressed(x, y, 0)) {
      menu[2].Select();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[3].Deselect();
    } else if (menu[3].Pressed(x, y, 0)) {
      menu[3].Select();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[2].Deselect();
    } else {
      menu[0].Deselect();
      menu[1].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
    }
  }

  // Detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (menu[0].Pressed(x, y, 0)) {
      menu[0].Select();
      button_click.play();
      menu[1].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
      state = 1;
    } else if (menu[1].Pressed(x, y, 0)) {
      menu[1].Select();
      button_click.play();
      menu[0].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
      state = 3;
    } else if (menu[2].Pressed(x, y, 0)) {
      menu[2].Select();
      button_click.play();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[3].Deselect();
      state = 4;
    } else if (menu[3].Pressed(x, y, 0)) {
      menu[3].Select();
      button_click.play();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[2].Deselect();
      state = 5;
    }
  }
}

/**
 * Allow user to choose difficulty for the run and then go to game state.
 *
 * @author Aaron Bernys
 */
void Game::difficultyScreen() {
  // Clear screen and draw end screen
  LCD.Clear();
  difficultyBackground.Draw(0, 0);
  LCD.SetFontColor(BLUE);
  LCD.WriteLine("        ");
  LCD.WriteLine("        ");
  LCD.WriteLine("        Difficulty");
  FEHIcon::Icon difficultySelect[3];
  char difficulties[3][20] = {"EASY", "MEDIUM", "HARD"};
  FEHIcon::DrawIconArray(difficultySelect, 3, 1, 100, 10, 60, 60, difficulties,
                         PURPLE, BLUE);
  LCD.Update();

  // Wait for touch and select button under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (Keyboard.isPressed(KEY_ESCAPE)) {
      state = 0;
      break;
    }
    if (difficultySelect[0].Pressed(x, y, 0)) {
      difficultySelect[0].Select();
      difficultySelect[1].Deselect();
      difficultySelect[2].Deselect();
    } else if (difficultySelect[1].Pressed(x, y, 0)) {
      difficultySelect[0].Deselect();
      difficultySelect[1].Select();
      difficultySelect[2].Deselect();
    } else if (difficultySelect[2].Pressed(x, y, 0)) {
      difficultySelect[0].Deselect();
      difficultySelect[1].Deselect();
      difficultySelect[2].Select();
    } else {
      difficultySelect[0].Deselect();
      difficultySelect[1].Deselect();
      difficultySelect[2].Deselect();
    }
  }

  // detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (difficultySelect[0].Pressed(x, y, 0)) {
      difficulty = 1;
      difficultySelect[0].Select();
      button_click.play();
      difficultySelect[1].Deselect();
      difficultySelect[2].Deselect();
      state = 2;
    } else if (difficultySelect[1].Pressed(x, y, 0)) {
      difficulty = 2;
      difficultySelect[0].Deselect();
      difficultySelect[1].Select();
      button_click.play();
      difficultySelect[2].Deselect();
      state = 2;
    } else if (difficultySelect[2].Pressed(x, y, 0)) {
      difficulty = 3;
      difficultySelect[0].Deselect();
      difficultySelect[1].Deselect();
      difficultySelect[2].Select();
      button_click.play();
      state = 2;
    }
  }
}

/**
 * Allow user to view stats for thier runs (does not transfer between closeing
 * and opening game).
 *
 * @author Aaron Bernys
 */
void Game::statsScreen() {
  // Clear screen and draw stats screen
  LCD.Clear();
  menuBackground.Draw(0, 0);
  FEHIcon::Icon backButton;
  backButton.SetProperties("BACK", 15, 140, 80, 80, PURPLE, BLUE);
  backButton.Draw();
  LCD.WriteLine("           Stats");
  LCD.SetFontScale(0.5);
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Runs: ", 120, 30);
  LCD.WriteAt(runs, 260, 30);
  LCD.WriteAt("Wins: ", 120, 40);
  LCD.WriteAt(wins, 260, 40);
  LCD.WriteAt("Time Survived: ", 120, 50);
  LCD.WriteAt(timeSurvived, 260, 50);
  LCD.SetFontScale(1.0);
  LCD.Update();

  // Wait for touch and select button when under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      backButton.Select();
    } else {
      backButton.Deselect();
    }
  }

  // Detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      button_click.play();
      state = 0;
    }
  }
}

/**
 * Allow user to view the credits and inspiration for the game.
 *
 * @author Aaron Bernys
 */
void Game::creditsScreen() {
  // Clear screen and draw credits screen
  LCD.Clear();
  menuBackground.Draw(0, 0);
  FEHIcon::Icon backButton;
  backButton.SetProperties("BACK", 15, 140, 80, 80, PURPLE, BLUE);
  backButton.Draw();
  LCD.WriteLine("         Credits");
  LCD.SetFontScale(0.5);
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Made by", 130, 30);
  LCD.WriteAt("Aaron Bernys and Blake Besecker", 70, 40);
  LCD.WriteAt("Inspiration:", 120, 50);
  LCD.WriteAt("https://tinyurl.com/nh92xe69", 70, 60);
  LCD.SetFontScale(1.0);
  LCD.Update();

  // Wait for touch and select button when under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      backButton.Select();
    } else {
      backButton.Deselect();
    }
  }

  // Detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      button_click.play();
      state = 0;
    }
  }
}

/**
 * Allow user to view controls of the game.
 *
 * @author Aaron Bernys
 */
void Game::guideScreen() {
  // Clear screen and draw instructions screen
  LCD.Clear();
  menuBackground.Draw(0, 0);
  FEHIcon::Icon backButton;
  backButton.SetProperties("BACK", 15, 140, 80, 80, PURPLE, BLUE);
  backButton.Draw();
  LCD.WriteLine("           Guide");
  LCD.SetFontScale(0.5);
  LCD.SetFontColor(WHITE);
  // TODO Finish controls and add more flavor
  LCD.WriteAt("Use the arrow keys", 185, 110);
  LCD.WriteAt("or wasd to move", 185, 120);
  LCD.WriteAt("around and avoid", 185, 130);
  LCD.WriteAt("attacks to survive.", 185, 140);
  LCD.WriteAt("Press ESC on the", 185, 150);
  LCD.WriteAt("main menu to quit", 185, 160);
  LCD.SetFontScale(1.0);
  LCD.Update();

  // Wait for touch and select button when under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      backButton.Select();
    } else {
      backButton.Deselect();
    }
  }

  // Detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      button_click.play();
      state = 0;
    }
  }
}

/**
 * Show user if they won or lost and allow them to go back to the menu screen or
 * quit the game.
 *
 * @author Aaron Bernys
 */
int Game::endScreen() {
  resetVariables();
  // Clear screen and draw end screen
  LCD.Clear();
  FEHIcon::Icon end[2];
  char endLabels[2][20] = {"RESTART", "QUIT"};
  if (success) {
    winBackground.Draw(0, 0);
    LCD.SetFontColor(GREEN);
    LCD.SetFontScale(1);
    LCD.WriteAt("YOU WIN", 20, 20);
  } else {
    loseBackground.Draw(40, 0);
    LCD.SetFontColor(RED);
    LCD.SetFontScale(1);
    LCD.WriteAt("YOU DIED", 20, 20);
  }
  FEHIcon::DrawIconArray(end, 2, 1, 140, 5, 10, 200, endLabels, PURPLE, BLUE);
  LCD.Update();

  // Wait for touch and select button under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (end[0].Pressed(x, y, 0)) {
      end[0].Select();
      end[1].Deselect();
    } else if (end[1].Pressed(x, y, 0)) {
      end[0].Deselect();
      end[1].Select();
    } else {
      end[0].Deselect();
      end[1].Deselect();
    }
  }

  // detect touch and change state
  while (LCD.Touch(&x, &y)) {
    if (end[0].Pressed(x, y, 0)) {
      end[0].Select();
      button_click.play();
      state = 0;
    } else if (end[1].Pressed(x, y, 0)) {
      end[1].Select();
      button_click.play();
      state = 7;
    } else {
      state = 6;
    }
  }
}

/**
 * Control flow for the enitre game. Each case calls the respective screen or
 * loop function that retruns to this function when it is done. Continuiuly is
 * called by main function until quit case and stateMachine returns -1.
 *
 * @author Aaron Bernys
 */
int Game::stateMachine() {
  switch (state) {
  case 0: // menu state
    std::cout << "CASE 0: MENU" << "\n";
    menuLoop();
    break;
  case 1: // difuculty select
    std::cout << "CASE 1: DIFFICULTY" << "\n";
    difficultyScreen();
    break;
  case 2: // game state
    std::cout << "CASE 2: GAME" << "\n";
    runs++;
    gameloop();
    break;
  case 3: // stats menu
    std::cout << "CASE 3: STATS" << "\n";
    statsScreen();
    break;
  case 4: // credits
    std::cout << "CASE 4: CREDITS" << "\n";
    creditsScreen();
    break;
  case 5: // guide
    std::cout << "CASE 5: GUIDE" << "\n";
    guideScreen();
    break;
  case 6: // end screen
    std::cout << "CASE 6: END" << "\n";
    endScreen();
    break;
  case 7: // quit
    std::cout << "CASE 7: QUIT" << "\n";
    return -1;
    break;
  }
}