#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "FEHLCD.h"
#include "FEHKeyboard.h"
//images and sprites
//bg, player, bosses
FEHImage background1("images/bg_1.png");
//FEHImage background2("bg_2.png");
//FEHImage background3("bg_3.png");

FEHImage boss1("images/boss_1.png");
//FEHImage boss2("boss_2.png");
//FEHImage boss3("boss_3.png");

FEHImage player1("images/player_1.png");
//FEHImage player2("player2_2.png");
//FEHImage player3("player_3.png");

//attack images
FEHImage line("images/line.png");
FEHImage zone("images/zone.png");
FEHImage selector("images/selector.png");

class Game {
private:
float startTime, duration = 30, difficulty = 1;
int hp = 100;
public:
    Game() {
        //constructor(may not be necessary)
    }

    int line_attack() {
        //constructs a line on screen with a zone around it. also moves a 'selector'
        //selector traverses the line, stopping when it gets to the end
        //user must press space before it gets to the end AND within the zone
        //accumulates 'fails' up to 3 (one per round)
        //returns this value times ten so we can calculate HP loss within the loop
        int zone_place;
        int selector_place = 10;
        int round = 1;
        int fails = 0;
        float round_time;
        
        
        
        while (round <= 3) {

            round_time = TimeNow();
            selector_place = 100;
            zone_place = int(120 + (Random.RandInt()/32767.0) * 60);
            
            while (!Keyboard.isPressed(KEY_SPACE) && selector_place<240) {
                LCD.Clear();
                update(true);
                line.Draw(80,190);
                zone.Draw(zone_place,190);
                selector.Draw(selector_place,180);
                selector_place+=(2*difficulty);
                LCD.Update();
                Sleep(0.01);
                
            }
            Sleep(0.1);
            if (selector_place < zone_place-20 || selector_place > zone_place+20) {
                fails++;
            }
            round++;
        }
        LCD.Clear();
        update(false);
        return fails*10;
    }

    int startScreen() {
        LCD.Clear();
        //the beginning screen. should have an option for stats, options, etc.
        //returns difficulty (1,2,3 for easy, medium, hard)
        background1.Draw(0,0);
        player1.Draw(120, 130);
        boss1.Draw(180, 130);
        LCD.Update();
        Sleep(2.0);
    }

    int endScreen(bool success=false) {
        LCD.Clear();
        //the end screen. should offer to play again. returns 1 to play again, and 0 to close
        //takes in a success variable(true is a win, false is a lose)
        LCD.Update();
    }

    void attack() {
        //initiate an attack. depending on the type, does a different type
    }

    void update(bool inAttack=false) {
        LCD.Clear();
        float time = TimeNow()-startTime;
        if (hp <= 0) {
            endScreen();
            return;
        }
        //update visual elements(background, boss sprite, player, sprite, music, etc)
        int stage;
        if (time < duration/3) {
            background1.Draw(0,0);
            if (!inAttack) {
            //player1.Draw(0,0);
            //boss1.Draw(0,0);
            }

        } else if (time < ((2 * duration) / 3)) {
            background1.Draw(0,0);
            if (!inAttack) {
            //player2.Draw(0,0);
            //boss2.Draw(0,0);
            }
        }
        else {
            background1.Draw(0,0);
            if (!inAttack) {
            //player3.Draw(0,0);
            //boss3.Draw(0,0);
            }
        }
        if (!inAttack) LCD.Update();
    }

    void mainloop() {
        //the main loop of the game
        startTime = TimeNow();
        startScreen();
        while (TimeNow()-startTime <= duration) {

            line_attack();

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