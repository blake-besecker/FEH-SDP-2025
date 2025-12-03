#include "FEHImages.h"
#include "FEHKeyboard.h"
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHSound.h"
#include "FEHUtility.h"
// sounds
FEHSound hurt_noise("sounds/hurt.wav");
FEHSound attack_noise("sounds/attack.wav");
FEHSound bg_music("sounds/music.wav");
// images and sprites
// bg, player, bosses
FEHImage tile("images/tile.png");
FEHImage bad_tile("images/tile_warn.png");

FEHImage background1("images/bg_1.png");
// FEHImage background2("bg_2.png");
// FEHImage background3("bg_3.png");

FEHImage boss1("images/boss.png");
// FEHImage boss2("boss_2.png");
// FEHImage boss3("boss_3.png");

FEHImage player1("images/player.png");
FEHImage hurt_player("images/player_hurt.png");

class Game {
private:
  float startTime, duration = 90, difficulty = 1;
  float hitCD = 0.9, lastHit = TimeNow();
  int hp = 100, damage = -10, state = 0;
  int x = 100, y = 80;
  int attack_state = 0;
  int attack_progress = 0;
  int attack_type = 3;
  int max_x = 150, min_x = 100, max_y = 130, min_y = 80, increment = 10;
  bool success;

public:
  Game();
  int startScreen();
  int endScreen();
  void draw_map();
  void move(char lastkey);
  void mainloop();
  void menuLoop();
  void statsScreen();
  void creditsScreen();
  void instructionsScreen();
  int stateMachine();
  int check_hit();
};

int main() {
  Game main;
  // state machine active until quit case
  while (main.stateMachine() != -1) {
  }

  return 0;
}

Game::Game() {}

int Game::check_hit() {
  if (TimeNow() - lastHit < hitCD)
    return 0; // hit buffer active
  if (attack_state == 2) {
    if (attack_type == 1) {
      if (((x / 10) % 2 == 0) && ((y / 10) % 2) == 1 ||
          ((x / 10) % 2 == 1) && ((y / 10) % 2) == 0) {
        lastHit = TimeNow();
        hurt_noise.play();
        return damage;
      }
    } else if (attack_type == 2) {
      if (((x / 10) % 2 == 1) && ((y / 10) % 2) == 0 ||
          ((x / 10) % 2 == 0) && ((y / 10) % 2) == 1) {
        lastHit = TimeNow();
        hurt_noise.play();
        return damage;
      }
    } else if (attack_type == 3) {
      if (x > min_x && x < max_x - increment && y > min_y &&
          y < max_y - increment) {
        lastHit = TimeNow();
        hurt_noise.play();
        return damage;
      } else if (x == max_x - min_x / 2 + increment * 2 ||
                 y == max_y - min_y / 2 + increment) {
        lastHit = TimeNow();
        hurt_noise.play();
        return damage;
      }
    } else if (attack_type == 4) {
    }
  }
  return 0;
}

void Game::draw_map() {
  // set "bad tile" the type of tile that's bad to stand on.
  if (attack_state == 1) {
    bad_tile = FEHImage("images/tile_warn.png");
    attack_noise.play();
  } else if (attack_state == 2) {
    bad_tile = FEHImage("images/tile_danger.png");
  };
  if (attack_state > 0 && attack_type == 1) {
    // alternating rows and columns are dangerous
    for (int i = min_x; i < max_x; i += 10) {
      for (int j = min_y; j < max_y; j += 10) {
        if (((i / 10) % 2 == 0) || ((j / 10) % 2) == 0) {
          bad_tile.Draw(i, j);
        } else {
          tile.Draw(i, j);
        }
      }
    }

  }
  // alternate, but the other way
  else if (attack_state > 0 && attack_type == 2) {
    for (int i = min_x; i < max_x; i += increment) {
      for (int j = min_y; j < max_y; j += increment) {
        if (((i / 10) % 2 == 1) || ((j / 10) % 2) == 1) {
          bad_tile.Draw(i, j);
        } else {
          tile.Draw(i, j);
        }
      }
    }
  } else if (attack_state > 0 && attack_type == 3) {
    for (int i = min_x; i < max_x; i += increment) {
      for (int j = min_y; j < max_y; j += increment) {
        if (i > min_x && i < max_x - increment && j > min_y &&
            j < max_y - increment) {
          bad_tile.Draw(i, j);
        } else if (i == max_x - min_x / 2 + increment * 2 ||
                   j == max_y - min_y / 2 + increment) {
          bad_tile.Draw(i, j);
        } else {
          tile.Draw(i, j);
        }
      }
    }
  } else {
    // default
    for (int i = min_x; i < max_x; i += increment) {
      for (int j = min_y; j < max_y; j += increment) {
        tile.Draw(i, j);
      }
    }
  }
}

void Game::move(char lastKey) {
  float time = TimeNow() - startTime;
  int delta_x = 0, delta_y = 0;
  if (TimeNow() - lastHit <= hitCD)
    player1 = FEHImage("images/player_hurt.png");
  else
    player1 = FEHImage("images/player.png");
  if (lastKey == 'w')
    delta_y = -10;
  if (lastKey == 'a')
    delta_x = -10;
  if (lastKey == 's')
    delta_y = 10;
  if (lastKey == 'd')
    delta_x = 10;
  if (hp <= 0) {
    success = false;
    state = 5;
    return;
  }
  if (x + delta_x < max_x && x + delta_x > min_x - increment)
    x += delta_x;

  if (y + delta_y < max_y && y + delta_y > min_y - increment)
    y += delta_y;
  // update visual elements(background, boss sprite, player, sprite, music, etc)
  if (time < duration / 3) {
    background1.Draw(0, 0);
    draw_map();
    player1.Draw(x, y);
    boss1.Draw(115, 20);
  } else if (time < ((2 * duration) / 3)) {
    background1.Draw(0, 0);
    draw_map();
    player1.Draw(x, y);
    boss1.Draw(115, 20);
  } else {
    background1.Draw(0, 0);
    draw_map();
    player1.Draw(x, y);
    boss1.Draw(115, 20);
  }
  LCD.WriteAt("hp: ", 10, 30);
  LCD.WriteAt(hp, 50, 30);
  LCD.WriteAt((TimeNow() - startTime), 90, 30);
}

int Game::endScreen() {

  // the end screen. should offer to play again. returns 1 to play again, and
  // 0 to close takes in a success variable(true is a win, false is a lose)
  LCD.Clear();
  FEHIcon::Icon end[2];
  FEHIcon::Icon result;
  char endLabels[2][20] = {"RESTART", "QUIT"};
  char resultText[2][20] = {"YOU WIN", "YOU LOSE"};
  FEHIcon::DrawIconArray(end, 2, 1, 100, 10, 60, 60, endLabels, PURPLE, BLUE);
  LCD.SetFontColor(BLACK);
  LCD.DrawRectangle(60, 100, 200, 65);
  LCD.DrawRectangle(60, 165, 200, 65);
  if (success) {
    LCD.SetFontColor(GREEN);
    result.SetProperties(resultText[0], 60, 10, 200, 65, BLACK, GREEN);
  } else {
    LCD.SetFontColor(RED);
    result.SetProperties(resultText[0], 60, 10, 200, 65, BLACK, RED);
  }
  result.Draw();
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
  while (LCD.Touch(&x, &y)) {
    if (end[0].Pressed(x, y, 0)) {
      end[0].Select();
      state = 0;
    } else if (end[1].Pressed(x, y, 0)) {
      end[1].Select();
      state = 6;
    }
  }
  LCD.Update();
}

void Game::mainloop() {
  // the main loop of the game
  // attack progress is the progress towards an attack happening. increases by
  // 1000 a second attack state. 0, nothing happens. 1, warning. 2, attack is
  // going on attack type, 1-4. each one does something different

  startTime = TimeNow();
  bg_music.setVolume(0.6);
  bg_music.play();
  while (TimeNow() - startTime <= duration) {
    LCD.Clear();

    // increment attack progress based on elapsed time
    // cycles every 5 seconds
    attack_progress++;
    if (attack_progress >= 40) {
      attack_progress = 0;
      attack_state++;
      if (attack_state > 2) {
        attack_state = 0;
        attack_type = Random.RandInt() % 4;
      }
    }

    char lastKey = 'n';
    if (Keyboard.areAnyPressed())
      lastKey = Keyboard.lastChar();
    move(lastKey);
    hp += check_hit();
    LCD.Update();
    Sleep(0.01);
  }
  success = true;
  state = 5;
}

void Game::menuLoop() {
  LCD.Clear();
  // declare an array of four icons called menu
  FEHIcon::Icon menu[4];
  // define the four menu labels
  char menu_labels[4][20] = {"START", "STATS", "CREDITS", "INSTRUCTIONS"};
  // draw the menu in a 2 by 2 array with top and bottom
  // margins of 10 and left and right margins of 5
  // with the menu labels, gold borders, and green text
  FEHIcon::DrawIconArray(menu, 2, 2, 10, 10, 5, 5, menu_labels, PURPLE, BLUE);
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (Keyboard.isPressed(KEY_ESCAPE)) {
      LCD.Clear(BLACK);
      LCD.SetFontColor(PURPLE);
      LCD.WriteLine("Exiting...");
      state = 6;
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
    }
  }
  while (LCD.Touch(&x, &y)) {
    // check for each button being pressed and update state acordingly
    if (menu[0].Pressed(x, y, 0)) {
      menu[0].Select();
      menu[1].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
      state = 1;
    } else if (menu[1].Pressed(x, y, 0)) {
      menu[1].Select();
      menu[0].Deselect();
      menu[2].Deselect();
      menu[3].Deselect();
      state = 2;
    } else if (menu[2].Pressed(x, y, 0)) {
      menu[2].Select();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[3].Deselect();
      state = 3;
    } else if (menu[3].Pressed(x, y, 0)) {
      menu[3].Select();
      menu[0].Deselect();
      menu[1].Deselect();
      menu[2].Deselect();
      state = 4;
    }
    LCD.Update();
  }
}

void Game::statsScreen() {
  // basic stats screen
  LCD.Clear();
  FEHIcon::Icon backButton;
  backButton.SetProperties("Back", 15, 30, 80, 80, PURPLE, BLUE);
  backButton.Draw();
  LCD.WriteLine("Stats");
  LCD.SetFontScale(0.5);
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Runs: 0", 100, 20);
  LCD.WriteAt("Wins: 0", 100, 30);
  LCD.WriteAt("Total play time: 0", 100, 40);
  LCD.SetFontScale(1.0);
  LCD.Update();
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      backButton.Select();
    } else {
      backButton.Deselect();
    }
  }
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      state = 0;
    }
  }
}

void Game::creditsScreen() {
  // basic credits screen
  LCD.Clear();
  FEHIcon::Icon backButton;
  backButton.SetProperties("Back", 15, 30, 80, 80, PURPLE, BLUE);
  backButton.Draw();
  LCD.WriteLine("Credits");
  LCD.SetFontScale(0.5);
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Made by", 100, 20);
  LCD.WriteAt("Aaron Bernys and Blake Besecker", 100, 30);
  LCD.WriteAt("Inspiration:", 100, 40);
  LCD.WriteAt("https://tinyurl.com/nh92xe69", 100, 50);
  LCD.SetFontScale(1.0);
  LCD.Update();
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      backButton.Select();
    } else {
      backButton.Deselect();
    }
  }
  while (LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      state = 0;
    }
  }
}

void Game::instructionsScreen() {
  // basic instructions screen
  LCD.Clear();
  FEHIcon::Icon backButton;
  backButton.SetProperties("Back", 15, 30, 80, 80, PURPLE, BLUE);
  backButton.Draw();
  LCD.WriteLine("Instructions");
  LCD.SetFontScale(0.5);
  LCD.SetFontColor(WHITE);
  LCD.WriteAt("Use the arrow keys", 100, 20);
  LCD.WriteAt("or wasd to move ", 100, 30);
  LCD.WriteAt("around and avoid attacks", 100, 40);
  LCD.WriteAt("to survive.", 100, 50);
  LCD.WriteAt("Press ESC on the main", 100, 60);
  LCD.WriteAt("menu to quit", 100, 70);
  LCD.SetFontScale(1.0);
  LCD.Update();
  float x, y;
  while (!LCD.Touch(&x, &y)) {
    if (backButton.Pressed(x, y, 0)) {
      backButton.Select();
    } else {
      backButton.Deselect();
    }
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
    std::cout << "CASE 0: MENU" << "\n";
    menuLoop();
    break;
  case 1: // game state
    std::cout << "CASE 1: GAME" << "\n";
    mainloop();
    break;
  case 2: // stats menu
    std::cout << "CASE 2: STATS" << "\n";
    statsScreen();
    break;
  case 3: // credits
    std::cout << "CASE 3: CREDITS" << "\n";
    creditsScreen();
    break;
  case 4: // instructions
    std::cout << "CASE 4: INSTRUCTIONS" << "\n";
    instructionsScreen();
    break;
  case 5: // end screen
    std::cout << "CASE 5: END" << "\n";
    endScreen();
    break;
  case 6: // quit
    std::cout << "CASE 6: QUIT" << "\n";
    return -1;
    break;
  }
}
