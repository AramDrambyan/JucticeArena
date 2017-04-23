#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "RangeHero.h"


// trial movement of Hero

int main()
{
   /* al_init();
    ALLEGRO_DISPLAY* display = al_create_display(800, 800);

    bool done = false;

    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_KEYBOARD_STATE key_state;

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 10);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    RangeHero hero(Rect(Point(50, 50), 69.5, 139), Texture("jnx.png", Point(), 4, 4), Texture("aa1.png"), 7, 1000, 300, 400, 3);

    while (!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&key_state);

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (events.type == ALLEGRO_EVENT_TIMER)
        {
            
            if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
            {
                hero.move(DOWN);
            }
            else if (al_key_down(&key_state, ALLEGRO_KEY_UP))
            {
                hero.move(UP);
            }
            else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
            {
                hero.move(LEFT);
            }
            else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
            {
                hero.move(RIGHT);
            }
            else
            {
                hero.state = IDLE;
            }

            hero.draw();
            al_flip_display();
            al_clear_to_color(al_map_rgb(100, 20, 25));
        }
    }
    
    hero.texture.destroy();
    hero.autoattack_animation.destroy();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);*/
}