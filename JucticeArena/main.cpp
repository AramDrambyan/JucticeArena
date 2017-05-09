#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include "RangeHero.h"
#include "Map.h"
#include "MapInfo.h"
#include <cstdlib>
#include <time.h>
#include <iostream>



Hero* make_hero(std::string& s, Rect r)
{
    if (s == "shen" || s == "Shen")
    {
        Hero* h1 = new Shen(r);
        return h1;
    }
    if (s == "caitlyn" || s == "Caitlyn")
    {
        Hero* h1 = new Caitlyn(r);
        return h1;
    }
    if (s == "ryze" || s == "Ryze")
    {
        Hero* h1 = new Ryze(r);
        return h1;
    }
    if (s == "karma" || s == "Karma")
    {
        Hero* h1 = new Karma(r);
        return h1;
    }
	if (s == "leesin" || s == "LeeSin")
	{
		Hero* h1 = new LeeSin(r);
		return h1;
	}
	if (s == "zed" || s == "Zed")
	{
		Hero* h1 = new Zed(r);
		return h1;
	}
}
bool shen_spec(Shen& shen_bot,Hero* hero, Map& map, int i, int range)
{
    if (abs(shen_bot.boundary.p.x - hero->boundary.p.x) < 50)
    {
        int dist = shen_bot.boundary.p.y - hero->boundary.p.y;

        if (dist <= range && dist > 0)
        {
            if (shen_bot.dir == UP)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(UP);
            }
            return true;
        }
        else if (dist >= -range && dist < 0)
        {
            if (shen_bot.dir == DOWN)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(DOWN);
            }
            return true;
        }
    }
    else if (abs(shen_bot.boundary.p.y - hero->boundary.p.y) < 50)
    {
        int dist = shen_bot.boundary.p.x - hero->boundary.p.x;

        if (dist <= range && dist > 0)
        {
            if (shen_bot.dir == LEFT)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(LEFT);
            }
            return true;
        }
        else if (dist >= -range && dist < 0)
        {
            if (shen_bot.dir == RIGHT)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(RIGHT);
            }
            return true;
        }
    }
    return false;
}
bool karma_spec(Karma& shen_bot, Hero* hero, Map& map, int i, int range)
{
    if (abs(shen_bot.boundary.p.x - hero->boundary.p.x) < 50)
    {
        int dist = shen_bot.boundary.p.y - hero->boundary.p.y;
		
        if (dist <= range && dist > 0)
        {
            if (shen_bot.dir == UP)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(UP);
            }
            return true;
        }
        else if (dist >= -range && dist < 0)
        {
            if (shen_bot.dir == DOWN)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(DOWN);
            }
            return true;
        }
    }
    else if (abs(shen_bot.boundary.p.y - hero->boundary.p.y) < 50)
    {
        int dist = shen_bot.boundary.p.x - hero->boundary.p.x;

        if (dist <= range && dist > 0)
        {
            if (shen_bot.dir == LEFT)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(LEFT);
            }
            return true;
        }
        else if (dist >= -range && dist < 0)
        {
            if (shen_bot.dir == RIGHT)
            {
                if (i == 1)
                    map.abilities2.push_back(shen_bot.spec1(*hero));
                else
                    map.abilities2.push_back(shen_bot.spec2(*hero));
            }
            else
            {
                shen_bot.move(RIGHT);
            }
            return true;
        }
    }
    return false;
}

void PvP()
{
    std::cout << "Choose Heroes\n";
    std::string s1, s2;
    std::cin >> s1 >> s2;

    al_init();

    ALLEGRO_DISPLAY* display = al_create_display(MAP_WIDTH, MAP_HEIGHT);

    al_init_image_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(1);

    ALLEGRO_KEYBOARD_STATE key_state1, key_state2;
    ALLEGRO_TIMER* timer = al_create_timer(FPS);
    ALLEGRO_FONT* font = al_load_font("orbitron-bold.otf", 12, NULL);
    ALLEGRO_FONT* big_font = al_load_font("orbitron-bold.otf", 35, NULL);
    
    ALLEGRO_SAMPLE* song = al_load_sample("background.wav");
    ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    Hero* h1 = make_hero(s1, Rect(Point(0, 750), 50, 50));
    Hero* h2 = make_hero(s2, Rect(Point(1150, 0), 50, 50));

    Map map(h1, h2);
    add_walls();
    add_water();

	al_play_sample_instance(song_instance);
    al_start_timer(timer);

    while (true)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&key_state1);
        al_get_keyboard_state(&key_state2);

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (events.type == ALLEGRO_EVENT_TIMER)
        {
            // first hero move
            if (al_key_down(&key_state1, ALLEGRO_KEY_S))
            {
                map.hero_1->move(DOWN);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_W))
            {
                map.hero_1->move(UP);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_A))
            {
                map.hero_1->move(LEFT);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_D))
            {
                map.hero_1->move(RIGHT);
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_1))
            {
                map.abilities1.push_back(map.hero_1->spec1(*map.hero_2));
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_2))
            {
                if (map.hero_1->name == "zed")
                {
                    map.abilities2.push_back(map.hero_1->spec2(*map.hero_2));
                }
                else
                {
                    map.abilities1.push_back(map.hero_1->spec2(*map.hero_2));
                }
            }
            else if (al_key_down(&key_state1, ALLEGRO_KEY_SPACE))
            {
                if (map.hero_1->is_able_to_attack(*map.hero_2))
                {
                    map.hero_1->autoattack(*map.hero_2);
                }
            }
            else
            {
                if (map.hero_1->state != ATTACK)
                {
                    map.hero_1->state = IDLE;
                }
            }

            //  second hero move
            if (al_key_down(&key_state2, ALLEGRO_KEY_DOWN))
            {
                map.hero_2->move(DOWN);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_UP))
            {
                map.hero_2->move(UP);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_LEFT))
            {
                map.hero_2->move(LEFT);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_RIGHT))
            {
                map.hero_2->move(RIGHT);
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_1))
            {
                map.abilities2.push_back(map.hero_2->spec1(*map.hero_1));
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_2))
            {
                if (map.hero_2->name == "zed")
                {
                    map.abilities1.push_back(map.hero_2->spec2(*map.hero_1));
                }
                else
                {
                    map.abilities2.push_back(map.hero_2->spec2(*map.hero_1));
                }
            }
            else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_0))
            {
                if (map.hero_2->is_able_to_attack(*map.hero_1))
                {
                    map.hero_2->autoattack(*map.hero_1);
                }
            }
            else
            {
                if (map.hero_2->state != ATTACK)
                {
                    map.hero_2->state = IDLE;
                }
            }

            // checking passive
            if (map.hero_1->is_alive())
            {
                map.hero_1->passive(*map.hero_2);
            }
            if (map.hero_2->is_alive())
            {
                map.hero_2->passive(*map.hero_1);
            }

            // moving abilities 
            map.move_abilities();

            map.draw();
            print_health(1, map.hero_1->health, font, 20, 810);
            print_damage(1, map.hero_1->damage, font, 20, 830);
            print_spec(1, 1, map.hero_1->spec1_state, font, 20, 850);
            print_spec(1, 2, map.hero_1->spec2_state, font, 20, 870);

            print_health(2, map.hero_2->health, font, 1030, 810);
            print_damage(2, map.hero_2->damage, font, 1030, 830);
            print_spec(2, 1, map.hero_2->spec1_state, font, 1030, 850);
            print_spec(2, 2, map.hero_2->spec2_state, font, 1030, 870);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

        if (!map.hero_1->is_alive() || !map.hero_2->is_alive())
        {
            if (!map.hero_1->is_alive())
            {
                al_draw_text(big_font, al_map_rgb(250, 20, 20), MAP_WIDTH / 2,
                    MAP_HEIGHT / 2, ALLEGRO_ALIGN_CENTER,
                    "PLAYER 2 WON!!");
                al_flip_display();
            }
            else
            {
                al_draw_text(big_font, al_map_rgb(250, 20, 20), MAP_WIDTH / 2,
                    MAP_HEIGHT / 2, ALLEGRO_ALIGN_CENTER,
                    "PLAYER 1 WON!!");
                al_flip_display();
            }
            al_rest(5);
            break;
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
void vsBots()
{
    std::cout << "Choose Heroes\n";
    std::string s1, s2;
    std::cin >> s1 >> s2;

    al_init();

    ALLEGRO_DISPLAY* display = al_create_display(MAP_WIDTH, MAP_HEIGHT);

    al_init_image_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(1);

    ALLEGRO_KEYBOARD_STATE key_state1, key_state2;
    ALLEGRO_TIMER* timer = al_create_timer(FPS);
    ALLEGRO_FONT* font = al_load_font("orbitron-bold.otf", 12, NULL);
    ALLEGRO_FONT* big_font = al_load_font("orbitron-bold.otf", 35, NULL);

    ALLEGRO_SAMPLE* song = al_load_sample("background.wav");
    ALLEGRO_SAMPLE_INSTANCE* song_instance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    Hero* h1 = make_hero(s1, Rect(Point(0, 750), 50, 50));
    Hero* h2 = make_hero(s2, Rect(Point(1050, 750), 50, 50));

    Map map(h1, h2);
    add_walls();
    add_water();

    Shen shen_bot(Rect(Point(100, 150), 50, 50));
    Karma karma_bot(Rect(Point(1150, 0), 50, 50));
    std::vector<Direction> shen_moves;
    std::vector<Direction> karma_moves;

    al_play_sample_instance(song_instance);
    al_start_timer(timer);

    while (true)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&key_state1);
        al_get_keyboard_state(&key_state2);

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (events.type == ALLEGRO_EVENT_TIMER)
        {
            // first hero move
            if (map.hero_1->is_alive())
            {
                if (al_key_down(&key_state1, ALLEGRO_KEY_S))
                {
                    map.hero_1->move(DOWN);
                }
                else if (al_key_down(&key_state1, ALLEGRO_KEY_W))
                {
                    map.hero_1->move(UP);
                }
                else if (al_key_down(&key_state1, ALLEGRO_KEY_A))
                {
                    map.hero_1->move(LEFT);
                }
                else if (al_key_down(&key_state1, ALLEGRO_KEY_D))
                {
                    map.hero_1->move(RIGHT);
                }
                else if (al_key_down(&key_state1, ALLEGRO_KEY_1))
                {
                    map.abilities1.push_back(map.hero_1->spec1(shen_bot, karma_bot));
                }
                else if (al_key_down(&key_state1, ALLEGRO_KEY_2))
                {
                    if (map.hero_1->name == "zed")
                        map.abilities2.push_back(map.hero_1->spec2(shen_bot, karma_bot));
                    else
                        map.abilities1.push_back(map.hero_1->spec2(shen_bot, karma_bot));
                }
                else if (al_key_down(&key_state1, ALLEGRO_KEY_SPACE))
                {
                    if (map.hero_1->is_able_to_attack(shen_bot))
                    {
                        map.hero_1->autoattack(shen_bot);
                    }
                    else if (map.hero_1->is_able_to_attack(karma_bot))
                    {
                        map.hero_1->autoattack(karma_bot);
                    }
                }
                else
                {
                    if (map.hero_1->state != ATTACK)
                    {
                        map.hero_1->state = IDLE;
                    }
                }
            }
            else
            {
                map.hero_1->boundary.p.x = -100;
                map.hero_1->boundary.p.y = -100;
            }

            //  second hero move
            if (map.hero_2->is_alive())
            {
                if (al_key_down(&key_state2, ALLEGRO_KEY_DOWN))
                {
                    map.hero_2->move(DOWN);
                }
                else if (al_key_down(&key_state2, ALLEGRO_KEY_UP))
                {
                    map.hero_2->move(UP);
                }
                else if (al_key_down(&key_state2, ALLEGRO_KEY_LEFT))
                {
                    map.hero_2->move(LEFT);
                }
                else if (al_key_down(&key_state2, ALLEGRO_KEY_RIGHT))
                {
                    map.hero_2->move(RIGHT);
                }
                else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_1))
                {
                    map.abilities1.push_back(map.hero_2->spec1(shen_bot, karma_bot));
                }
                else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_2))
                {
                    if (map.hero_2->name == "zed")
                        map.abilities2.push_back(map.hero_2->spec2(shen_bot, karma_bot));
                    else
                        map.abilities1.push_back(map.hero_2->spec2(shen_bot, karma_bot));
                }
                else if (al_key_down(&key_state2, ALLEGRO_KEY_PAD_0))
                {
                    if (map.hero_2->is_able_to_attack(shen_bot))
                    {
                        map.hero_2->autoattack(shen_bot);
                    }
                    else if (map.hero_2->is_able_to_attack(karma_bot))
                    {
                        map.hero_2->autoattack(karma_bot);
                    }
                }
                else
                {
                    if (map.hero_2->state != ATTACK)
                    {
                        map.hero_2->state = IDLE;
                    }
                }
            }
            else
            {
                map.hero_2->boundary.p.x = -100;
                map.hero_2->boundary.p.y = -100;
            }

            // checking passive
            if (map.hero_1->is_alive())
            {
                map.hero_1->passive(shen_bot, karma_bot);
            }
            if (map.hero_2->is_alive())
            {
                map.hero_2->passive(shen_bot, karma_bot);
            }

            //  bots behaviour
            //  shen
            if (shen_bot.is_alive())
            {
                //  spec 1
                if (shen_bot.spec1_state == 0 &&
                    (abs(shen_bot.boundary.p.y - map.hero_1->boundary.p.y) < 50 ||
                    abs(shen_bot.boundary.p.x - map.hero_1->boundary.p.x) < 50)
                    && shen_spec(shen_bot, map.hero_1, map, 1, 200))
                {
                }
                else if (shen_bot.spec1_state == 0 &&
                    (abs(shen_bot.boundary.p.y - map.hero_2->boundary.p.y) < 50 ||
                    abs(shen_bot.boundary.p.x - map.hero_2->boundary.p.x) < 50) &&
                    shen_spec(shen_bot, map.hero_2, map, 1, 200))
                {
                }
                //  spec 2
                else if (shen_bot.spec2_state == 0 &&
                    (abs(shen_bot.boundary.p.y - map.hero_1->boundary.p.y) < 50 ||
                    abs(shen_bot.boundary.p.x - map.hero_1->boundary.p.x) < 50) &&
                    shen_spec(shen_bot, map.hero_1, map, 2, 180))
                {
                }
                else if (shen_bot.spec2_state == 0 &&
                    (abs(shen_bot.boundary.p.y - map.hero_2->boundary.p.y) < 50 ||
                    abs(shen_bot.boundary.p.x - map.hero_2->boundary.p.x) < 50) &&
                    shen_spec(shen_bot, map.hero_2, map, 2, 180))
                {
                }
                // autoattack
                else if (shen_bot.is_able_to_attack(*map.hero_1))
                {
                    shen_bot.autoattack(*map.hero_1);
                }
                else if (shen_bot.is_able_to_attack(*map.hero_2))
                {
                    shen_bot.autoattack(*map.hero_2);
                }
                //  move
                else
                {
                    if (!shen_moves.empty())
                    {
                        shen_bot.move(shen_moves[0]);
                        shen_moves.pop_back();
                    }
                    else
                    {
                        shen_bot.state = IDLE;
                        int d = rand() % 4;
                        for (int i = 0; i < 10; ++i)
                        {
                            shen_moves.push_back(to_dir(d));
                        }
                    }
                }
                // passive
                shen_bot.passive(*map.hero_1, *map.hero_2);
            }

            //  karma
            if (karma_bot.is_alive())
            {
                //  spec 1
                if (karma_bot.spec1_state == 0 &&
                    (abs(karma_bot.boundary.p.y - map.hero_1->boundary.p.y) < 50 ||
                    abs(karma_bot.boundary.p.x - map.hero_1->boundary.p.x) < 50)
                    && karma_spec(karma_bot, map.hero_1, map, 1, 300))
                {
                }
                else if (karma_bot.spec1_state == 0 &&
                    (abs(karma_bot.boundary.p.y - map.hero_2->boundary.p.y) < 50 ||
                    abs(karma_bot.boundary.p.x - map.hero_2->boundary.p.x) < 50) &&
                    karma_spec(karma_bot, map.hero_2, map, 1, 200))
                {
                }
                // spec 2
                else if (karma_bot.health != K_HEALTH && karma_bot.spec2_state == 0)
                {
                    map.abilities2.push_back(karma_bot.spec2(*map.hero_1));
                }
                //  autoattack
                else if (karma_bot.is_able_to_attack(*map.hero_1))
                {
                    karma_bot.autoattack(*map.hero_1);
                }
                else if (karma_bot.is_able_to_attack(*map.hero_2))
                {
                    karma_bot.autoattack(*map.hero_2);
                }
                //  move
                else
                {
                    if (!karma_moves.empty())
                    {
                        karma_bot.move(karma_moves[0]);
                        karma_moves.pop_back();
                    }
                    else
                    {
                        karma_bot.state = IDLE;
                        int d = rand() % 4;
                        for (int i = 0; i < 10; ++i)
                        {
                            karma_moves.push_back(to_dir(d));
                        }
                    }
                }
                // passive
                karma_bot.passive(*map.hero_1, *map.hero_2);
            }

            // moving abilities 
            map.move_abilities(shen_bot, karma_bot);
            
            // drawing
            map.draw();
            if (shen_bot.is_alive())
            {
                shen_bot.draw();
            }
            if (karma_bot.is_alive())
            {
                karma_bot.draw();
            }

            print_health(1, map.hero_1->health, font, 20, 810);
            print_damage(1, map.hero_1->damage, font, 20, 830);
            print_spec(1, 1, map.hero_1->spec1_state, font, 20, 850);
            print_spec(1, 2, map.hero_1->spec2_state, font, 20, 870);

            print_health(2, map.hero_2->health, font, 1030, 810);
            print_damage(2, map.hero_2->damage, font, 1030, 830);
            print_spec(2, 1, map.hero_2->spec1_state, font, 1030, 850);
            print_spec(2, 2, map.hero_2->spec2_state, font, 1030, 870);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

       
            if (map.hero_1->health <= 0 && map.hero_2->health <= 0)
            {
                al_draw_text(big_font, al_map_rgb(250, 20, 20), MAP_WIDTH / 2,
                    MAP_HEIGHT / 2, ALLEGRO_ALIGN_CENTER,
                    "BOTS WIN!!");
                al_flip_display();
                al_rest(5);
                break;
            }
            else if (shen_bot.health <= 0 && karma_bot.health <= 0)
            {
                al_draw_text(big_font, al_map_rgb(250, 20, 20), MAP_WIDTH / 2,
                    MAP_HEIGHT / 2, ALLEGRO_ALIGN_CENTER,
                    "YOU WIN!!");
                al_flip_display();
                al_rest(5);
                break;
            }    
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

int main()
{
    srand(time(NULL));

    std::cout << "choose:\n1.PvP\n2.vsBots\n";

    std::string str;
    std::cin >> str;
    if (str == "PvP" || str == "pvp")
    {
        PvP();
    }
    else if (str == "vsbots" || "vsBots")
    {
        vsBots();
    }
}
