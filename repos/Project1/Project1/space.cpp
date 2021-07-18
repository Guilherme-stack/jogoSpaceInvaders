#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>


int main()
{

    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_BITMAP* imagem = NULL;

    al_init();
    al_init_image_addon();


    display = al_create_display(640, 400);
    imagem = al_load_bitmap("instagram.png");
    al_draw_bitmap(imagem, 50, 50, 50);


    al_flip_display();
    al_rest(10.0);
    al_destroy_display(display);


    return 0;
}