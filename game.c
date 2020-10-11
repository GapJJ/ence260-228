#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "custFONT.h"
#include "pacer.h"
#include "ir_uart.h"
#include "display.h"

char options[3] = {'R','P','S'};
int nav_pos = 0; // options[nav_pos] = Rock

void nav_next(void)
{
    if(nav_pos >= 2){
        nav_pos = 0;
    } else {
        nav_pos++;
    }
    char text = options[nav_pos];
    tinygl_text (text);
    tinygl_update ();
}

void nav_prev(void){
    if(nav_pos <= 0){
        nav_pos = 2;
    } else {
        nav_pos++;
    }
    tinygl_text ("S");
    tinygl_update ();
}

int referee(char ours, char theirs){
    //referee compares our selection to theirs.
    if (ours == theirs) {
        return 0;
    }
    else
    {
      return 1;
    }
}

int main (void)
{
    char state;

    system_init ();
    tinygl_init (500);
    tinygl_font_set (&custFONT);
    tinygl_text_speed_set (10);
    navswitch_init ();
    display_init();


    system_init ();
    // Initialising tinygl display //
    tinygl_init (500);
    tinygl_text_speed_set (10);

    // Initialising navswitch driver//
    navswitch_init ();

    // Initialising IR driver//
    ir_uart_init ();


    state = '1'; // 1-Play, 2-Send, 3-Handshake?
    pacer_init (500);


    while (1)
    {
//need to select rock, paper, scissor.

//once sent, need to wait for an input.

//Send WIN/LOSS and wait to recieve inverse (handshake)

        switch(state) {
            case '1':
                //Playing, user can select between options
                while (1)
                {
                    pacer_wait ();
                    navswitch_update ();

                    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                        nav_prev ();
                    }

                    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                        nav_next ();
                    }

                    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
                        state = 2; // begin sending our selection over IR.
                        break;
                    }

                }

            case '2':

                while (1)
                {
                    pacer_wait ();
                    ir_uart_putc (options[nav_pos]);

                    if (ir_uart_read_ready_p ())
                    {
                        uint8_t incomming;
                        incomming = ir_uart_getc ();

                        if(referee(options[nav_pos], incomming) == 1) {
                            //we won, send won message and switch to handshake
                            ir_uart_putc ('W');
                            state = 3; // Winning state, waiting for loser to admit their losses.
                            break;
                        } else if (options[nav_pos] == incomming) {
                            //draw, send draw message and switch to handshake
                            ir_uart_putc ('D');
                            state = 4; // Drawing state, waiting for opponent to agree.
                            break;
                        } else if (referee(options[nav_pos], incomming) == 0) {
                            //Lost, sending lose message and switch to handshake
                            ir_uart_putc ('L');
                            state = 5; // Lose state, waiting for opponent to
                            break;
                        }
                    }

                }

            case '3':

                while (1)
                {
                    pacer_wait ();
                    if (ir_uart_read_ready_p ())
                    {
                        uint8_t incomming;
                        incomming = ir_uart_getc ();
                        if(incomming == 'L') {
                            //Handshake!
                            //Output W on screen????
                            state = 1; // get ready for another round.
                            break;
                        }
                }
              }

            case '4':

                while (1)
                {
                    pacer_wait ();
                    if (ir_uart_read_ready_p ())
                    {
                        uint8_t incomming;
                        incomming = ir_uart_getc ();
                        if(incomming == 'D') {
                            //Handshake!
                            //Output D on screen????
                            state = 1; // get ready for another round.
                            break;
                        }
                }
              }

            case '5':

                while (1)
                {
                    pacer_wait ();
                    if (ir_uart_read_ready_p ())
                    {
                        uint8_t incomming;
                        incomming = ir_uart_getc ();
                        if(incomming == 'W') {
                            //Handshake!
                            //Output L on screen????
                            state = 1; // get ready for another round.
                            break;

                          }
                    }
                  }

    }
  }
}
