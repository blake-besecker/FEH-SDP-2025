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
//  images and sprites
//  bg, player, bosses
FEHImage tile("images/tile.png");
FEHImage bad_tile("images/tile_warn.png");

FEHImage background1("images/bg_1.png");
FEHImage menuBackground("images/menubg.png");
FEHImage difficultyBackground("images/castledoor.png");
// FEHImage background2("bg_2.png");
// FEHImage background3("bg_3.png");

FEHImage boss1("images/boss.png");
// FEHImage boss2("boss_2.png");
// FEHImage boss3("boss_3.png");

FEHImage player1("images/player.png");
FEHImage hurt_player("images/player_hurt.png");

class Game {
private:
  // game duration and difficuilty variables
  float startTime, duration;
  int difficulty;
  // hit variables
  float hitCD, lastHit;
  int hp, damage;
  // player variables
  int x, y;
  const int max_x = 150, min_x = 100, max_y = 130, min_y = 80, increment = 10;
  // boss variables
  int attack_state, attack_progress, attack_type;
  // stats (given declarations because they are kept through multiple runs)
  int wins = 0, runs = 0;
  float timeSurvived = 0.0;
  // flow control variables
  int state;
  bool success;

public:
  Game();
  void resestVariables();
  int check_hit();
  void draw_map();
  void move(char lastkey);
  void gameloop();
  void menuLoop();
  void difficultyScreen();
  void statsScreen();
  void creditsScreen();
  void guideScreen();
  int endScreen();
  int stateMachine();
};

int main() {
  Game main;
  main.resestVariables();
  // state machine active until quit case
  while (main.stateMachine() != -1) {
  }
  return 0;
}

Game::Game() {}

void Game::resestVariables() {
  difficulty = 1;

  hitCD = 0.9;
  lastHit = TimeNow();
  hp = 10;
  damage = 10;

  x = 100;
  y = 80;

  attack_state = 0;
  attack_progress = 0;
  attack_type = 3;

  state = 0;
}

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
  float currentTime = TimeNow() - startTime;
  LCD.WriteAt((currentTime), 90, 30);
  timeSurvived += currentTime;
}

void Game::gameloop() {
  // the main loop of the game
  // attack progress is the progress towards an attack happening. increases by
  // 1000 a second attack state. 0, nothing happens. 1, warning. 2, attack is
  // going on attack type, 1-4. each one does something different
  switch (difficulty) {
  case 1:
    duration = 30;
    break;
  case 2:
    duration = 60;
    break;
  case 3:
    duration = 90;
    break;
  }

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
    if (hp <= 0) {
      success = false;
      state = 6;
      return;
    }
    hp -= check_hit();
    LCD.Update();
    Sleep(0.01);
  }
  success = true;
  wins++;
  state = 6;
}

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
  LCD.WriteAt("GAME TITLE", 38, 30);
  LCD.WriteAt("GAME TITLE", 39, 31);
  LCD.SetFontColor(BLUE);
  LCD.WriteAt("GAME TITLE", 40, 32);
  LCD.SetFontScale(1.0);
  LCD.Update();

  // wait for touch allowing user to quit with ESC and selecting buttons under
  // cursor
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

void Game::difficultyScreen() {
  // Clear screen and draw end screen
  LCD.Clear();
  difficultyBackground.Draw(0, 0);
  FEHIcon::Icon difficultySelect[3];
  char difficulties[3][20] = {"EASY", "MEDIUM", "HARD"};
  FEHIcon::DrawIconArray(difficultySelect, 3, 1, 100, 10, 60, 60, difficulties,
                         PURPLE, BLUE);
  LCD.Update();

  // Wait for touch and select button under cursor
  float x, y;
  while (!LCD.Touch(&x, &y)) {
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
  LCD.WriteAt(runs, 280, 30);
  LCD.WriteAt("Wins: ", 120, 40);
  LCD.WriteAt(wins, 280, 40);
  LCD.WriteAt("Total Time Survived: ", 120, 50);
  LCD.WriteAt(timeSurvived, 280, 50);
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

int Game::endScreen() {
  resestVariables();
  // Clear screen and draw end screen
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
    result.SetProperties(resultText[1], 60, 10, 200, 65, BLACK, RED);
  }
  result.Draw();
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
    }
  }
}

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
