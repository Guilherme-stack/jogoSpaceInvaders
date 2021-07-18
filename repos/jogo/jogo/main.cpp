#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
//****************VARIAVEIS GLOBAIS******************
const int largura_t = 600;
const int altura_t = 700;
const int FPS = 60;
const int num_balas = 5;
const int num_cometas = 80;
bool fim = false;
bool inicio = true;
bool logica = false;
bool game = false;
int pontos = 0;

int separa1 = 0, separa2 = 0, separa3 = 0, separa4= 0, separa5 = 0, separa6 = 0, separa7 = 0, separa8= 0;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0, p7 = 0, p8 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;
int compara1 = 1, compara2 = 1, compara3 = 1, compara4 = 1, compara5 = 1, compara6 = 1, compara7 = 1, compara8 = 1;
int parar1 = 120, parar2 = 120, parar3 = 120, parar4 = 120, parar5 = 120, parar6 = 120, parar7 = 120, parar8 = 120;

bool pos1[] = { false ,false,false};
enum TECLAS
{
	 DIREITA, ESQUERDA, ESPACE
};
 
//_______________________________________________________
struct Cometas
{	
	int id;
	int x;
	int y;
	int velocidade;
	bool ativo;
	int borda_x;
	bool azul;
	int borda_y;
	
};
struct NaveSpacial
{
	int x;
	int y;
	int borda_x;
	int borda_y;
	int velocidade;
	int pontos;

};
struct Projeteis
{
	int x;
	int y;
	int velocidade;
	bool ativo;
	int borda_x;
	int borda_y;
};
struct num_inimigos
{
	int p1 = 0;
};
 
void iniciar_nave(NaveSpacial &nave);
void tela_inicial(void);
 
void MoveNaveEsquerda(NaveSpacial &nave);
void MoveNaveDireita(NaveSpacial &nave);

void iniciar_balas(Projeteis balas[],int tamanho);
void atira_balas(Projeteis balas[], int tamanho, NaveSpacial nave);
void atualiza_balas(Projeteis balas[], int tamanho);
void desenha_balas(Projeteis balas[],int tamanho);

void bala_colidida(Projeteis balas[], int b_tamanho, Cometas cometas[], int c_tamanho);

void iniciar_cometas(Cometas cometas[], int tamanho);
void libera_cometas(Cometas cometas[], int tamanho, num_inimigos inimigos );
void atualizar_cometas(Cometas cometas[], int tamanho );
void desenha_cometas(Cometas cometas[], int tamanho);

void desenha_trincheira(num_inimigos inimigos);
void desenha_asteroid(bool pos[]);

void fim_de_jogo(int numero);
void desenha_pontos(int pontos);

 

int main() {
	al_init();
	//--------------- VARIAVEIS DO JOGO -------------------
		
	 

	 
	bool teclas[] = { false,false,false };
	 
	 
	 
	//_____________________________________________________

	//--------- INICIALIZA플O DE OBJETOS ------------------
	NaveSpacial nave;
	Projeteis balas[num_balas];
	Cometas cometas[num_cometas];
	num_inimigos inimigos;
	//_____________________________________________________

	//------ INICIALIZA플O DA ALLEGRO E DO DISPLAY --------
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *imagem = NULL;
	ALLEGRO_EVENT_QUEUE *evento_mouse = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *eventos = NULL;	 
	ALLEGRO_BITMAP *player = NULL;
	 
	//ALLEGRO_FONT* font2 = al_load_font("font.ttf", 30, NULL);

	display = al_create_display(largura_t, altura_t);
	 
	//_____________________________________________________

	//---------- INICIALIZA합ES DE ADDONS E INSTALA합ES ---
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	//_____________________________________________________

	// -------- CRIA플O DA FILA E DEMAIS DISPOSITIVOS -----
	eventos = al_create_event_queue();
	evento_mouse = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	//_____________________________________________________

	//--------- REGISTRO DE SOURCES -----------------------
	al_register_event_source(evento_mouse, al_get_mouse_event_source());
	al_register_event_source(evento_mouse, al_get_display_event_source(display));
	al_register_event_source(eventos, al_get_display_event_source(display));
	al_register_event_source(eventos, al_get_timer_event_source(timer));
	al_register_event_source(eventos, al_get_keyboard_event_source());
	//_____________________________________________________

	// ------------ FUN함ES INICIAIS ----------------------
	iniciar_nave(nave);
	iniciar_balas(balas, num_balas);
	iniciar_cometas(cometas,num_cometas);
	 
	 
	srand(time(NULL));
	bool desenho = true;
	tela_inicial();
	//_____________________________________________________

	//----------- LOOP PRINCIPAL --------------------------
	al_start_timer(timer);
	player = al_load_bitmap("nave.png");

	while (fim == false)
	{	
		if (inicio == true)
		{
			tela_inicial();
			logica = false;
			ALLEGRO_EVENT ev_teclado;

			al_wait_for_event(eventos, &ev_teclado);
			if (ev_teclado.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev_teclado.keyboard.keycode)
				{
				 
				case ALLEGRO_KEY_ENTER:
					logica = true;
					inicio = false;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_scaled_bitmap(player, 0, 0, al_get_bitmap_width(player), al_get_bitmap_height(player), nave.x - 20, nave.y - 20, 50, 50, 0);
					al_flip_display();
					break;

				}
			}
	 	 
		}
		if(logica == true)
		{
			 
				ALLEGRO_EVENT ev_teclado;

				al_wait_for_event(eventos, &ev_teclado);
				if (ev_teclado.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (ev_teclado.keyboard.keycode)
					{
					case ALLEGRO_KEY_LEFT:
						teclas[ESQUERDA] = true;
						break;
					case ALLEGRO_KEY_RIGHT:
						teclas[DIREITA] = true;
						break;
					case ALLEGRO_KEY_SPACE:
						teclas[ESPACE] = true;
						atira_balas(balas, num_balas, nave);
						break;
					}
				}
				else if (ev_teclado.type == ALLEGRO_EVENT_KEY_UP)
				{
					switch (ev_teclado.keyboard.keycode)
					{
					case ALLEGRO_KEY_LEFT:
						teclas[ESQUERDA] = false;
						break;
					case ALLEGRO_KEY_RIGHT:
						teclas[DIREITA] = false;
						break;

					}
				}
				 
				else if (ev_teclado.type = ALLEGRO_EVENT_TIMER) {
					desenho = true;
					if (teclas[ESQUERDA])
					{
						MoveNaveEsquerda(nave);
					}
					if (teclas[DIREITA])
					{
						MoveNaveDireita(nave);
					}
					if (teclas[ESPACE])
					{
						atualiza_balas(balas, num_balas);
					}
					libera_cometas(cometas, num_cometas, inimigos);
					atualizar_cometas(cometas, num_cometas);
					//desenha_cometas(cometas, num_cometas);
					bala_colidida(balas, num_balas, cometas, num_cometas);
				}
				desenho = true;
				if (desenho && al_is_event_queue_empty(eventos))
				{
					desenha_trincheira(inimigos);
					desenho = false;
					desenha_pontos(pontos);
					desenha_cometas(cometas, num_cometas);
					desenha_balas(balas, num_balas);


					//desenha_asteroid(num);
					al_draw_scaled_bitmap(player, 0, 0, al_get_bitmap_width(player), al_get_bitmap_height(player), nave.x - 20, nave.y - 20, 50, 50, 0);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
				}

			 
		}

		if (game == true)
		{	

			iniciar_nave(nave);
			iniciar_balas(balas, num_balas);
			iniciar_cometas(cometas, num_cometas);
			pontos = 0;
			separa1 = 0, separa2 = 0, separa3 = 0, separa4 = 0, separa5 = 0, separa6 = 0, separa7 = 0, separa8 = 0;
			p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0, p7 = 0, p8 = 0;
			c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;
			compara1 = 1, compara2 = 1, compara3 = 1, compara4 = 1, compara5 = 1, compara6 = 1, compara7 = 1, compara8 = 1;
			parar1 = 120, parar2 = 120, parar3 = 120, parar4 = 120, parar5 = 120, parar6 = 120, parar7 = 120, parar8 = 120;
			 
			ALLEGRO_EVENT ev_teclado;

			al_wait_for_event(eventos, &ev_teclado);
			if (ev_teclado.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev_teclado.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					game = false;
					inicio = false;
					logica = false;
					fim = true;
					 
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));

					break;
				case ALLEGRO_KEY_ENTER:
					game = false;
					inicio = false;
					logica = true;
					 
					desenha_trincheira(inimigos);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					break;
				 
				}
			}
		}
		

	}
	//_____________________________________________________
	 
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(evento_mouse);
	al_destroy_event_queue(eventos);
	return 0;
 }
 
 void desenha_trincheira(num_inimigos inimigos) {
	 al_draw_rectangle(35,altura_t - 230,105,altura_t-90,al_map_rgb(255,255,255),4);

	 al_draw_rectangle(100, altura_t - 230, 170, altura_t - 90, al_map_rgb(255, 255, 255), 4);

	 al_draw_rectangle(165, altura_t - 230, 235, altura_t - 90, al_map_rgb(255, 255, 255), 4);

	 al_draw_rectangle(230, altura_t - 230, 300, altura_t - 90, al_map_rgb(255, 255, 255), 4);

	 al_draw_rectangle(295, altura_t - 230, 365, altura_t - 90, al_map_rgb(255, 255, 255), 4);

	 al_draw_rectangle(360, altura_t - 230, 430, altura_t - 90, al_map_rgb(255, 255, 255), 4);

	 al_draw_rectangle(425, altura_t - 230, 495, altura_t - 90, al_map_rgb(255, 255, 255), 4);
	 
	 al_draw_rectangle(490, altura_t - 230, 560, altura_t - 90, al_map_rgb(255, 255, 255), 4);
 
 }
  
 //----------- ASTEROIDES ---------------

 void iniciar_cometas(Cometas cometas[], int tamanho) {
	 for (int i = 0; i < tamanho; i++)
	 {
		 cometas[i].azul = false;
		 cometas[i].ativo = false;
		 cometas[i].velocidade = 1;
		 cometas[i].borda_x = 18;
		 cometas[i].borda_y = 18;
		 cometas[i].y = -30;
		  
	 }
 }
 void libera_cometas(Cometas cometas[], int tamanho, num_inimigos inimigos) {
	 int number;
	 

	 for (int i = 0; i < tamanho; i++)
	 {
		 if (!cometas[i].ativo)
		 {	
			  
			 if (rand() % 1500 == 0)
			 {	
				  
				 number = rand() % 8;
				 if (number == 0 && p1 < 3)
				 {
					 cometas[i].x = 70;
					 cometas[i].y = -separa1;
					 separa1 += 40;
					 p1++;
						cometas[i].ativo = true;
				 }
				 if (number == 1 && p2 < 3)
				 {
					 cometas[i].x = 135;
					 cometas[i].y = -separa2;
					 separa2 += 40;
					 p2++;
						 cometas[i].ativo = true;
 
				 }
				 if (number == 2 && p3 < 3)
				 {
					 cometas[i].x = 200;
					 cometas[i].y = -separa3;
					 separa3 += 40;
					 p3++;
						 cometas[i].ativo = true;
  
				 }
				 if (number == 3 && p4 < 3)
				 {
					 cometas[i].x = 265;
					 cometas[i].y = -separa4;
					 separa4 += 40;
					 p4++;
						 cometas[i].ativo = true;
 
				 }
				 if (number == 4 && p5 < 3)
				 {
					 cometas[i].x = 330;
					 cometas[i].y = -separa5;
					 separa5 += 40;
					 p5++;
						 cometas[i].ativo = true;
   
				 }
				 if (number == 5 && p6 < 3)
				 {
					 cometas[i].x = 395;
					 cometas[i].y = -separa6;
					 separa6 += 40;
					 p6++;
						 cometas[i].ativo = true;
 
				 }
				 if (number == 6 && p7 < 3)
				 {
					 cometas[i].x = 460;
					 cometas[i].y = -separa7;
					 separa7 += 40;
					 p7++;
					 cometas[i].ativo = true;
				 }
				 if (number == 7 && p8 < 3)
				 {
					 cometas[i].x = 525;
					 cometas[i].y = -separa8;
					 separa8 += 40;
					 p8++;
					 cometas[i].ativo = true;
  
				 }

			 }
		 }
	 }
 }
 void atualizar_cometas(Cometas cometas[], int tamanho ) {
	 int x = 1;
	 for (int i = 0; i < tamanho; i++)
	 {	
		  
		 if (cometas[i].ativo == true  ) {

			 if (cometas[i].x == 70 && cometas[i].y <= altura_t - parar1)
			 {
				  
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				  
				 if (cometas[i].y >= altura_t - parar1)
				 {
					  
					 parar1 += 40;  
					 c1++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {	
						  
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
						  
					 }
				 }
			 }
			 if (cometas[i].x == 135 && cometas[i].y <= altura_t - parar2)
			 {
				 //p1++;
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar2)
				 {	
					 parar2 += 40;
					 c2++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						  
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }
				 }
			 }
			 if (cometas[i].x == 200 && cometas[i].y <= altura_t - parar3)
			 {
				 //p1++;

				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade ;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar3)
				 {
					 parar3 += 40;
					 c3++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }

				 }
			 }
			 if (cometas[i].x == 265 && cometas[i].y <= altura_t - parar4)
			 {
				 //p1++;
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade ;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar4)
				 {
					 parar4 += 40;
					 c4++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }

				 }
			 }
			 if (cometas[i].x == 330 && cometas[i].y <= altura_t - parar5)
			 {
				 //p1++;
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar5)
				 {
					 parar5 += 40;
					 c5++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }

				 }
			 }
			 if (cometas[i].x == 395 && cometas[i].y <= altura_t - parar6)
			 {
				 //p1++;
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar6)
				 {
					 parar6 += 40;
					 c6++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }

				 }
			 }
			 if (cometas[i].x == 460 && cometas[i].y <= altura_t - parar7)
			 {
				 //p1++;
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade ;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar7)
				 {
					 parar7 += 40;
					 c7++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }

				 }
			 }
			 if (cometas[i].x == 525 && cometas[i].y <= altura_t - parar8)
			 {
				 //p1++;
				 if (cometas[i].azul == true)
				 {
					 cometas[i].y += cometas[i].velocidade ;
				 }
				 else if (cometas[i].azul == false) {
					 cometas[i].y += cometas[i].velocidade;
				 }
				 if (cometas[i].y >= altura_t - parar8)
				 {
					 parar8 += 40;
					 c8++;
					 if ((c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8) == 24)
					 {
						 game = true;
						 inicio = false;
						 logica = false;
						 fim_de_jogo(pontos);
						  
					 }

				 }
			 }
	  
		 }
		  

	 }
	 
 }
 void desenha_cometas(Cometas cometas[], int tamanho) {
	  
	 for (int i = 0; i < tamanho; i++)
	 {
		 if (cometas[i].azul == true)
		 {
			 al_draw_filled_circle(cometas[i].x, cometas[i].y, 20, al_map_rgb(0, 127, 255));
		 }
		 else if (cometas[i].azul == false) {
			 al_draw_filled_circle(cometas[i].x, cometas[i].y, 20, al_map_rgb(255, 0, 0));
		 }
	 }
 }
 //_____________________________________
 // ---------- BALAS ------------
 void bala_colidida(Projeteis balas[], int b_tamanho, Cometas cometas[], int c_tamanho) {
	 for (int i = 0; i < b_tamanho; i++)
	 {
		 if (balas[i].ativo)
		 {
			 for (int j = 0; j < c_tamanho; j++)
			 {
				 if (cometas[j].ativo)
				 {
					 if (balas[i].y > (cometas[j].y - cometas[j].borda_y) && 
						 balas[i].y < (cometas[j].y + cometas[j].borda_y) &&
						 balas[i].x > (cometas[j].x - cometas[j].borda_x) &&
						 balas[i].x < (cometas[j].x + cometas[j].borda_x))
					 {	
						  	  
						 if (cometas[j].y <= altura_t  - 230 && cometas[j].azul == false )
						 {
							 balas[i].ativo = false;
							 //cometas[j].ativo = false;
							 cometas[j].azul = true;
							 pontos++;
						 }
						 else if (cometas[j].y >= altura_t - 230  ) {
							 balas[i].ativo = true;
							 //cometas[j].ativo = false;
							 //cometas[j].azul = false;
						 }
						  
					 }
				 }
			 }
		 }
	 }
 }

 void iniciar_balas(Projeteis balas[], int tamanho) {
	 for (int i = 0; i < tamanho; i++)
	 {
		 balas[i].velocidade = 13;
		 balas[i].ativo = false;
	 }
 }
 void atira_balas(Projeteis balas[], int tamanho, NaveSpacial nave) {
	 for ( int i = 0;  i < tamanho; i++)
	 {
		 if (!balas[i].ativo) {
			 balas[i].x = nave.x;
			 balas[i].y = nave.y;
			 balas[i].ativo = true;
			 break;
		 }

	 }
 }
 void atualiza_balas(Projeteis balas[], int tamanho) {
	 for (int i = 0; i < tamanho; i++)
	 {
		 if (balas[i].ativo)
		 {
			 balas[i].y -= balas[i].velocidade;
			if (balas[i].y < 0)
			 {
				balas[i].ativo = false;
			 }
		 }
	 }
 }
 void desenha_balas(Projeteis balas[], int tamanho) {
	 for (int i = 0; i < tamanho; i++)
	 {
		 if (balas[i].ativo) {
			 al_draw_filled_circle(balas[i].x+5, balas[i].y, 2, al_map_rgb(255, 255, 255));
		 }
	 }
 }
 //_____________________________________
// ----------- NAVE ----------
void iniciar_nave(NaveSpacial &nave) {
	nave.x = largura_t / 2;
	nave.y = altura_t - 32;
	nave.velocidade = 10;
	nave.pontos = 0;
}
 
void MoveNaveEsquerda(NaveSpacial &nave) {
	 
	nave.x -= nave.velocidade;

	if (nave.x<18 )
	{
		nave.x = 18;
	}
}
void MoveNaveDireita(NaveSpacial &nave) {
	nave.x += nave.velocidade;
	if (nave.x > largura_t-26)
	{
		nave.x = largura_t-26;
	}
}
//_______________________________________________________
void tela_inicial() {
	 
		ALLEGRO_FONT* font2 = al_load_font("Baxoe.ttf", 22, NULL);
		al_draw_text(font2, al_map_rgb(255, 255, 255), largura_t / 2, altura_t/2, ALLEGRO_ALIGN_CENTRE, "PRESSIONE ENTER PARA INICIAR");
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_destroy_font(font2);		 
}

void fim_de_jogo(int pontos) {
	 
	ALLEGRO_FONT* font1 = al_load_font("Baxoe.ttf", 31, NULL);
	ALLEGRO_FONT* font2 = al_load_font("Baxoe.ttf", 34, NULL);
	if (pontos >= 15)
	{
		al_draw_text(font2, al_map_rgb(255, 255, 255), largura_t / 2, 300, ALLEGRO_ALIGN_CENTER, "  VOCE  GANHOU  ! !  ");
	}else
	{
		al_draw_text(font2, al_map_rgb(255, 255, 255), largura_t / 2, 300, ALLEGRO_ALIGN_CENTER, "  VOCE  PERDEU  ! !  ");
	}
	 
	 
	//al_draw_textf(font2, al_map_rgb(255, 255, 255), largura_t / 2, 345, ALLEGRO_ALIGN_CENTER, "Pontuacao: %i", numero);
	al_draw_text(font1, al_map_rgb(255, 255, 255), largura_t /2, 380, ALLEGRO_ALIGN_CENTER, "  TECLE  ENTER  PARA  JOGAR  NOVAMENTE  ");
	al_draw_text(font1, al_map_rgb(255, 255, 255), largura_t /2, 430, ALLEGRO_ALIGN_CENTER, "  TECLE  ESC  PARA  SAIR  ");
	al_flip_display();
	 
	al_destroy_font(font1);
	al_destroy_font(font2);
}
void desenha_pontos(int pontos) {
	ALLEGRO_FONT *font2 = al_load_font("Baxoe.ttf", 22, NULL);
	al_draw_textf(font2, al_map_rgb(255, 255, 255), 15, 15, NULL,"Pontos: %d", pontos);
	al_draw_text(font2, al_map_rgb(255, 255, 255), 15,50, NULL, "Pontuacao minima para ganhar: 15");
	al_destroy_font(font2);
}