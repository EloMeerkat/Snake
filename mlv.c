#include <MLV/MLV_all.h>
#include <time.h>

// On défini un nouveau type qu'on nomme "Coordonnees" qui permet de définir des coordonnées 
typedef  struct{
	int x; // Coorodonée de l'axe des abscisses
	int y; // Coorodonée de l'axe des ordonnéees
} Coordonnees;

// On défini un nouveau type qu'on nomme "Clist" qui permet de définir des listes de coordonnées
typedef struct cordlist{ 
	int x; // Coorodonée de l'axe des abscisses
	int y; // Coorodonée de l'axe des ordonnéees
	struct cordlist *suiv; // Permet d'allé aux coorodonées suivantes dans la liste
} *Clist;

// On definir une fonction nous permettant de créer un nouveau maillon dans une liste de coordonnée
// Cette fonction prend comme argument des coordonnée et renvoie un liste de coordonée
Clist newmaillon(Coordonnees point){
	Clist n = (Clist)malloc(sizeof(Clist)); // On créé le nouveau maillon (une liste)
	n->suiv = NULL; // On dit que les coordonnées suivantes est NULL
	n->x = point.x; // On dit que la variable qui pointe sur le x dans la structure prend la valeur de la position de x 
	n->y = point.y; // On dit que la variable qui pointe sur le y dans la structure prend la valeur de la position de y
	return n; // On retourne le nouveau maillon
}

// Fonction qui permet d'ajouter un maillon au debut de la liste "l"
// Cette fonction prend comme argument des coorodonées et la liste de coorodonée à laquelle les ajouter.
// Elle renvoie la liste de coordonnées ainsi créée
Clist ajout(Clist l, Coordonnees point){
	Clist t = newmaillon(point); // On definie une liste "t" qui est un nouveau maillon qui contient "point"
	t->suiv = l; // Les coorodnées suivantes dans "t" sont la liste "l"
	return t; // On retroune t qui est la liste "l" avec le nouveau maillon "t" devant
}

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

// Permet dessiner des carrés à partir d'une liste de coordonnées
void AffSerpent(Clist Snake, int dim){
	// i et j vont permettre d'obtenir les coordonnées du premier pixel de la case dans laquelle se trouve le point
	int i, j; 
	
	// On initialise i et j avec les coordonnées du premier pixel de la case contenant la tête du serpent
	i = Snake->x/dim * (dim+1) +1;
	j = Snake->y/dim * (dim+1) +1;
	MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_RED); // Dessine un rectangle rouge pour afficher la tête du serpent 
	
	Snake=Snake->suiv; // On passe au coordonées suivantes de la liste
	
	for(; Snake; Snake=Snake->suiv){ // Si "Snake" n'est pas NULL, chaque tour de la boucle, on passe aux Coordonées suivantes
		i = Snake->x/dim * (dim+1) +1;
		j = Snake->y/dim * (dim+1) +1;

		MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_GREEN); // Dessine un rectangle vert pour afficher le corps du serpent 
	}
}

// Cette fonction permet d'effacer le serpent de l'écran
void EffSerpent(Clist Snake, int dim){
	for(; Snake; Snake=Snake->suiv){ // Si "Snake" n'est pas NULL, chaque tour de la boucle, on passe aux Coordonnées suivantes
		// i et j vont permettre d'obtenir les coordonnées du premier pixel de la case dans laquelle se trouve le point
		int i, j;
		i = Snake->x/dim * (dim+1) +1;
		j = Snake->y/dim * (dim+1) +1;
		
		// On dessine un carré noir pour effacer le serpent
		MLV_draw_filled_rectangle(i, j, dim, dim, MLV_COLOR_BLACK);
	}
}

// Cette fonction permet d'effacer le dernier maillon d'une liste de coordonnées
// Elle prend comme argument une liste de coordonnées et renvoie une liste de coordonnées
Clist EffDernier(Clist l){
	Clist n = NULL, m = NULL; 
	Coordonnees pt;
	
	// On parcours la liste l jusqu'aux avant-dernières coordonnées
	for(; l->suiv; l=l->suiv){
			// Les Coordonnées "pt" prend la valeur des coordonées compris dans la liste
			pt.x = l->x;
			pt.y = l->y;
			n = ajout(n, pt); // On ajoute "pt" au début de la liste n
	}
	
	// Comme "n" est dans le sens inverse de l, on parcours n pour remplir m qui sera alors dans le même sens que l
	for(; n; n=n->suiv){
			// Les Coordonnées "pt" prend la valeur des coordonées compris dans la liste
			pt.x = n->x;
			pt.y = n->y;
			m = ajout(m, pt);// On ajoute "pt" au début de la liste m
	}
	return m; // On retourne m
}

// Cette fonction permet de vérifier si la tête du serpent "ne se mord pas"
// Elle prend comme argument les coodononnées de la tête (point), le serpent (Snake) et la dimmension d'une cade en pixel (dim)
// Elle renvoie 1 si le serpend se mord et 0 sinon
int Jmemange (Coordonnees point, Clist Snake, int dim){
	// On initialise la liste aux seconde coordonnées (le début du corps)
	Snake = Snake -> suiv;
	
	// On parcours le serpent
	for(; Snake; Snake=Snake->suiv){
		// Si la tête et un carré qui compose le corps sont dans la même case, on retourne 1
		if(point.x/dim == Snake->x/dim &&  point.y/dim == Snake->y/dim) return 1;
	}
	return 0; // Si on a parcours tout le serpent sans problème, on retourne 0
}

// Permet d'afficher l'objectif que le serpent doit manger
// Elle prend comme argument le nombre de carré à dessiner (Nb) et leur dimmension en pixel (dim)
// Et renvoie les coodonnées de l'objectif
Coordonnees AffObjet(int dim, int Nb){
	MLV_Image *Apple; // Apple permettra de charger en mémoire un fichier image
	Coordonnees objet;
	int i, j;
	Apple = MLV_load_image("objectif.png"); // On charge en mémoire un fichier image
	
	// Creer les coordonnées aléatoire de l'objectif
	srand(time(NULL)); // Initialise une valeur de départ
	objet.x = (((double)rand())/RAND_MAX) * (dim+1)*Nb +1; // initialise un nombre aléatoire compris entre 1 et (dim+1)*Nb
	objet.y = (((double)rand())/RAND_MAX) * (dim+1)*Nb +1; // initialise un nombre aléatoire compris entre 1 et (dim+1)*Nb
	
	// Si l'une des coordonnées de l'objet se trouve sur une ligne, on décrémente la coordonnée en question
	if(objet.x%dim == 0){
		objet.x=objet.x-1;
	}
	if(objet.y%dim == 0){
		objet.y=objet.y-1;
	}
	
	// i et j vont permettre d'obtenir les coordonnées du premier pixel de la case dans laquelle se trouve l'objectif
	i = objet.x/dim * (dim+1) +1;
	j = objet.y/dim * (dim+1) +1;
	
	MLV_resize_image_with_proportions(Apple, dim, dim); // On redimensionne les images

	MLV_draw_image(Apple, i, j); // On affiche l'image

	MLV_actualise_window(); // Met à jour l'affichage
    MLV_wait_milliseconds(100);
    MLV_free_image(Apple); // Libère l'image qui a été créée
    
    return objet; // On retourne les coordonnées de l'objectif
}


int main(int argc, char *argv[]){
	// dim : dimmension d'un carré en pixel
	// Nb : nombre de carré dans une ligne
	// t : temps d'attente initiale entre deux déplacements du serpent (en milliseconde)
	// a prendra la valeur d'un quart de t
	int dim = 20, Nb = 30, t=500, a;
	
	Coordonnees point, objet;
	// Initilisation des coordonnée de point au milieu de la fenêtre
	point.x = dim*Nb/2;
	point.y = dim*Nb/2;
	
	Clist Snake = NULL;
	// Intialisation du snake en ajoutant le point dans la liste "Snake"
	Snake = ajout(Snake, point);
	Snake = ajout(Snake, point);
	
	MLV_Event event_type = MLV_KEY;// Intialisation de l'événement (évémenement provenant du clavier)
	MLV_Keyboard_button touche = MLV_KEYBOARD_RIGHT;// Initilisation de "touche" à la flèche doite du clavier
    
	AffCadrillage(dim, Nb);// Ouvre la fenêtre et d'affiche le cadrillage.
	objet = AffObjet(dim, Nb);// Affiche l'objectif.
	MLV_actualise_window();// Actualise la fenêtre
	
	//Deplacement du serpent
	while(event_type != MLV_KEY || touche != MLV_KEYBOARD_ESCAPE){
		
		// On efface le serpent
		EffSerpent(Snake, dim);
		
		// On recupère l'évenement provenant du clavier le plus récent
		event_type = MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		
		// On déplace le serpend dans la direction indiquée par "touche" en modifiant la valeur de "point"
		// Haut
		if(touche == MLV_KEYBOARD_UP){
			if(point.y != 0){
				point.y = point.y-dim;
				Snake = ajout(Snake, point); // On ajoute "point" à "Snake"
			}
			else break;
		}
		
		// Bas
		else if(touche == MLV_KEYBOARD_DOWN){
			if(point.y != (dim*Nb)-dim){
				point.y = point.y+dim;
				Snake = ajout(Snake, point); // On ajoute "point" à "Snake"
			}
			else break;
		}
		
		// Gauche
		else if(touche == MLV_KEYBOARD_LEFT){
			if(point.x != 0){
				point.x = point.x-dim;
				Snake = ajout(Snake, point); // On ajoute "point" à "Snake"
			}
			else break;
		}
		
		// Droite
		else if(touche == MLV_KEYBOARD_RIGHT){
			if(point.x != (dim*Nb)-dim){
				point.x = point.x+dim;
				Snake = ajout(Snake, point); // On ajoute "point" à "Snake"
			}
			else break;
		}
		
		// On vérifie si le serpent ne se mord pas et s'il se mord on sort de la boucle
		if(Jmemange(point, Snake, dim))break;
		
		// Si le serpent mange l'objectif
		if(objet.x/dim == Snake->x/dim &&  objet.y/dim == Snake->y/dim){
			// On affiche un nouvel objectif
			objet = AffObjet(dim, Nb);
			
			// si la valeur du temps moins son quart n'est pas nul on le décrémente de son quart
			if(t-t/4){
				a = t/4;
				t = t-a;
			}
		}
		// Sinon, on efface le dernier maillon de la liste Snake
		else{
			Snake = EffDernier(Snake);
		}
		
		// On affiche le nouveau serpent qui a avancé (et peut-être grandi)
		AffSerpent(Snake, dim);
		MLV_actualise_window(); // On actualise la fenêtre
		MLV_wait_milliseconds(t); // On attend "t" milliseconde
	}
	
	MLV_free_window();	// Fermer la fenêtre
	return 0;
}
