#include <MLV/MLV_all.h>

typedef  struct {
	int x;
	int y;
} Coordonnees;

// Cette fonction permet d'ouvrir une fenêtre et d'afficher un cadrillage sur celle-ci
// Elle prend comme argument le nombre de carré à dessiner (Nb) et leur dimmension en pixel (dim)
void AffCadrillage(int dim, int Nb){
	
	MLV_create_window( "beginner - 2 - shapes", "shapes", (dim+1)*Nb, (dim+1)*Nb); // Ouvre une fenêtre de dimension (dim+1)*Nb
	int i; //On utilisera "i" pour se déplacer dans le fenêtre
	
	// On parcours la fenêtre en incrémentant "i" de la dimension d'une case 
	//(+1 car on ne compte pas les lignes dans la dimension de la case) jusqu'au bord de la fenêtre
	for(i=0; i<((dim+1)*Nb); i=i+dim+1){ 
		MLV_draw_line(0, i, (dim+1)*Nb, i, MLV_COLOR_WHITE ); // On dessine une ligne verticale d'ordonnées i
		MLV_draw_line(i, 0, i, (dim+1)*Nb, MLV_COLOR_WHITE ); // On dessine une ligne horizontale d'abscisse i
	}
	MLV_actualise_window(); // On actualise la fenêtre
}

void CreateRectangle(Coordonnees point, int dim){
	int i, j;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_PINK);
}

void EffaceRectangle(Coordonnees point, int dim){
	int i=0, j=0 ;
	i = point.x/dim * (dim+1) +1;
	j = point.y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_BLACK);
}

int main(int argc, char *argv[]){

	int dim=20, Nb=30;
	Coordonnees point;
	point.x=0;
	point.y=0;
	MLV_Event event_type=MLV_NONE;
	MLV_Keyboard_button touche;
        
	AffCadrillage(dim, Nb);
	CreateRectangle(point, dim);
	MLV_actualise_window();
	
	while( event_type!=MLV_KEY || touche != MLV_KEYBOARD_ESCAPE ){
		event_type = MLV_wait_keyboard_or_mouse( &touche, NULL, NULL, NULL, NULL);
		if(touche == MLV_KEYBOARD_UP){
			if(point.y != 0){
				EffaceRectangle(point, dim);
				point.y = point.y-dim;
			}
			CreateRectangle(point, dim);
		}
		else if(touche == MLV_KEYBOARD_DOWN){
			if(point.y != (dim*Nb)-dim){
				EffaceRectangle(point, dim);
				point.y = point.y+dim;
			}
			CreateRectangle(point, dim);
		}
		else if(touche == MLV_KEYBOARD_LEFT){
			if(point.x != 0){
				EffaceRectangle(point, dim);
				point.x = point.x-dim;
			}
			CreateRectangle(point, dim);
		}
		else if(touche == MLV_KEYBOARD_RIGHT){
			if(point.x != (dim*Nb)-dim){
				EffaceRectangle(point, dim);
				point.x = point.x+dim;
			}
			CreateRectangle(point, dim);
		}
		MLV_actualise_window();
	}

	// Fermer la fenêtre
	MLV_free_window();
	return 0;
}
