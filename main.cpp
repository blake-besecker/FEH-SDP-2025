#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "FEHLCD.h"
#include "FEHKeyboard.h"
//images and sprites
//bg, player, bosses

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
float startTime, duration = difficulty*3, difficulty = 1;
int hp = 100, x, y;
public:
    Game() {
        //constructor(may not be necessary)
    }

    int startScreen() {
        LCD.Clear();
        //the beginning screen. should have an option for stats, options, etc.
        //returns difficulty (1,2,3 for easy, medium, hard)
        background1.Draw(0,0);
        player1.Draw(0, 100);
        boss1.Draw(0, 50);
        LCD.Update();
        Sleep(0.5);
    }

    int endScreen(bool success=false) {
        LCD.Clear();
        //the end screen. should offer to play again. returns 1 to play again, and 0 to close
        //takes in a success variable(true is a win, false is a lose)
        LCD.Update();
    }

    void draw_map(int attack_type) { 
        for (int i = 120; i<260; i+=20) {
            for (int j = 120; j<260; j+=20) {
                tile.Draw(i, j);
            }
        }
        LCD.Update();
    }

    void attack(bool danger, int attack_type) {
        LCD.Clear();
        draw_map();

        //initiate an attack. depending on the type, does a different type. 
        // if danger is true, then highlight tiles as in "danger".
        // danger tiles are highlighted to signify that an attack is coming so the player can move
        // if danger is false, then set tiles as "hurt"
        // while player is within these tiles, decrement hp
    }

    void move(char lastKey) {
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

    void mainloop() {
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

};



int main()
{
    Game main;
    main.mainloop();
    return 0;
}
