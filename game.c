#include <stdio.h>
#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void menu(board *copy){
	int val=0;
	do{
		printf("\033[36;01m  ________      ___.  ___.   .__          __\n");
	  printf(" /  _____/  ____\\_ |__\\_ |__ |  |   _____/  |_  ______\n");
	  printf("/   \\  ___ /  _ \\| __ \\| __ \\|  | _/ __ \\   __\\/  ___/\n");
	  printf("\\    \\_\\  (  <_> ) \\_\\ \\ \\_\\ \\  |_\\  ___/|  |  \\___ \\ \n");
	  printf(" \\______  /\\____/|___  /___  /____/\\___  >__| /____  >\n");
	  printf("        \\/           \\/    \\/          \\/          \\/ \n");
	  printf("  ________      ___.  ___.   .__                       \n");
	  printf(" /  _____/  ____\\_ |__\\_ |__ |  |   ___________  ______\n");
	  printf("/   \\  ___ /  _ \\| __ \\| __ \\|  | _/ __ \\_  __ \\/  ___/\n");
	  printf("\\    \\_\\  (  <_> ) \\_\\ \\ \\_\\ \\  |_\\  ___/|  | \\/\\___ \\ \n");
	  printf(" \\______  /\\____/|___  /___  /____/\\___  >__|  /____  >\n");
	  printf("        \\/           \\/    \\/          \\/           \\/ \n\n");
		int val=0;
		printf("\033[35;01m   Menu\n    \033[34;01m1 - Jouer\n    \033[0;01m2 - Options\n    \033[31;01m3 - Quitter\n\n\033[37;01m");
		scanf("%d",&val);

		switch(val){
			case 1:
				printf("\033[H\033[2J");
				return;
				break;
			case 2:
				printf("\033[H\033[2J");
				printf("\033[31;01mIl n'y a pas d'options pour le moment\033[0;01m\n");
				break;
			case 3:
				printf("\033[H\033[2J");
				destroy_game(*copy);
				exit(0);
			default:
				printf("\033[H\033[2J");
				break;
			}
	}while(val!=1);
}

//+--------------------------------------------------------------------------------------------------------------------------------------+

void affiche(board game){
	printf("\n	     A   B   C");
	for(int j=0;j<3;j++){
			printf("\n	   ");
			for(int k=0;k<3;k++)printf("+---");
			printf("+\n	");
			printf("%d  ",j+1);
			for(int k=0;k<3;k++){
				printf("\033[0;01m| ");
				if(get_place_holder(game, j, k)==PLAYER_1)printf("\033[33;01m");
				if(get_place_holder(game, j, k)==PLAYER_2)printf("\033[34;01m");
				if(get_piece_size(game,j, k)!=NONE){
					if(get_piece_size(game,j, k)!=1){
						if(get_piece_size(game,j, k)!=2)printf("■ ");
						else{
							printf("▲ ");
						}
					}
					else{
						printf("● ");
					}
				}
				else{
					printf("  ");
				}
			printf("\033[00m");
			}
			printf("| ");
			if(j==0){
				printf("    Contenu des maisons:");
			}
			else{
				printf("      ");
				if(j==1){
					printf("\033[33;01m");
					for(int p=0;p<get_nb_piece_in_house(game, PLAYER_1, SMALL);p++){
						printf("● ");
					}
					for(int p=2;p>get_nb_piece_in_house(game, PLAYER_1, SMALL);p--){
						printf("  ");
					}
					for(int p=0;p<get_nb_piece_in_house(game, PLAYER_1, MEDIUM);p++){
						printf("▲ ");
					}
					for(int p=2;p>get_nb_piece_in_house(game, PLAYER_1, MEDIUM);p--){
						printf("  ");
					}
					for(int p=0;p<get_nb_piece_in_house(game, PLAYER_1, LARGE);p++){
						printf("■ ");
					}
					for(int p=2;p>get_nb_piece_in_house(game, PLAYER_1, LARGE);p--){
						printf("  ");
					}
				}
				else{
					printf("\033[34;01m");
					for(int p=0;p<get_nb_piece_in_house(game, PLAYER_2, SMALL);p++){
						printf("● ");
					}
					for(int p=2;p>get_nb_piece_in_house(game, PLAYER_2, SMALL);p--){
						printf("  ");
					}
					for(int p=0;p<get_nb_piece_in_house(game, PLAYER_2, MEDIUM);p++){
						printf("▲ ");
					}
					for(int p=2;p>get_nb_piece_in_house(game, PLAYER_2, MEDIUM);p--){
						printf("  ");
					}
					for(int p=0;p<get_nb_piece_in_house(game, PLAYER_2, LARGE);p++){
						printf("■ ");
					}
					for(int p=2;p>get_nb_piece_in_house(game, PLAYER_2, LARGE);p--){
						printf("  ");
					}
				}
				printf("\033[00m");
			}
	}
	printf("\n	   ");
	for(int k=0;k<3;k++)printf("+---");//affiche une ligne +---+---+---+
	printf("+\n\n");
}

void nom(char *nom, int numJoueur){
	printf("Veuillez rentrer le nom du joueur %d (20 caractères maximum, 3 caractères minimum) ",numJoueur);
	int nbcar=0;
	scanf(" ");
	do{
		if(nom[nbcar-1]=='\n'){ //permet d'éviter une erreur avec le menu (s'affiche 2 fois sinon)
			nbcar=0;
			printf("Veuillez rentrer le nom du joueur %d (20 caractères maximum, 3 caractères minimum) ",numJoueur);
		}
		scanf("%c",nom+nbcar);
		nbcar++;
	}while(nom[nbcar-1]!='\n'||nbcar>=22||nbcar<=3);
	nom[nbcar-1]='\0';
}

//+--------------------------------------------------------------------------------------------------------------------------------------+

int verification(char action, int nbtours, player current_player,board game){
	int x,y,taille,sx,sy,echec=0;
	char temp;
	if(action=='D'||action=='d'){
		if(nbtours<=2){
			echec=1;
		}else{
			do{
				printf("Veuillez saisir le chiffre de la ligne sur laquelle se situe la pièce à déplacer ");
				scanf("%d",&sx);
			}while(sx!=1&&sx!=2&&sx!=3);
			do{
				printf("Veuillez saisir la lettre de la colonne sur laquelle se situe la pièce à déplacer ");
				scanf(" %c",&temp);
			}while(temp!='a'&&temp!='b'&&temp!='c'&&temp!='A'&&temp!='B'&&temp!='C');
			switch (temp) {
				case 'a':
					sy=0;
					break;
				case 'A':
					sy=0;
					break;
				case 'b':
					sy=1;
					break;
				case 'B':
					sy=1;
					break;
				case 'c':
					sy=2;
					break;
				case 'C':
					sy=2;
					break;
			}
			if(get_place_holder(game, sx-1, sy)==current_player){
				echec = move_piece(game,sx-1,sy,5,5);
			}else{
				echec=4;
			}
		}
	}
	printf("\n");
	if(echec==1){
			printf("\033[H\033[2J");
			printf("\033[31;01mErreur\nVous ne pouvez pas déplacer de pièce car vous n'avez pas de pièce placée sur le plateau\n\n");
	}else{
		if(echec==4){
			printf("\033[H\033[2J");
			printf("\033[31;01mErreur\nVotre pièce est cachée par une autre ou vous n'avez pas de pièce à cet emplacement\n\n");
		}else{
			do{
				printf("Veuillez saisir le chiffre de la ligne sur laquelle vous voulez placer votre pièce ");
				scanf("%d",&x);
			}while(x!=1&&x!=2&&x!=3);
			temp=' ';
			do{
				printf("Veuillez saisir la lettre de la colonne sur laquelle vous voulez placer votre pièce ");
				scanf(" %c",&temp);
			}while(temp!='a'&&temp!='b'&&temp!='c'&&temp!='A'&&temp!='B'&&temp!='C');
			switch (temp) {
				case 'a':
					y=0;
					break;
				case 'A':
					y=0;
					break;
				case 'b':
					y=1;
					break;
				case 'B':
					y=1;
					break;
				case 'c':
					y=2;
					break;
				case 'C':
					y=2;
					break;
			}
			if(action=='p'||action=='P'){
				do{
					printf("Veuillez saisir la taille de la pièce que vous voulez placer\n(1:petit,2:moyen,3:grand) ");
					scanf("%d",&taille);
				}while(taille!=1&&taille!=2&&taille!=3);
				echec=place_piece(game,current_player,taille,x-1,y);
			}else{
				echec=move_piece(game,sx-1,sy,x-1,y);
			}
			printf("\033[H\033[2J");
			switch(echec){
				case 0:
					break;
				case 1:
					printf("\033[31;01mErreur:\n");
					printf("La pièce sélectionnée ne peut être placée\n\n");
					break;
				case 2:
					printf("\033[31;01mErreur:\n");
					printf("Vous ne pouvez pas placer votre pièce sur la case indiquée\n\n");
					break;
				case 3:
					printf("\033[31;01mErreur:\n");
					printf("Vous avez indiqué un emplacement inexistant\n\n");
					break;
			}
			printf("\033[0;01m");
		}
	}
	return echec;
}

//+--------------------------------------------------------------------------------------------------------------------------------------+

int main(int args, char **argv){
	int fin,nbtours;
	bool save=false;
	char action;
  srand(time(NULL));
	board copy=new_game();
	char *nomP1;
	char *nomP2;
	char *gagnant;
	player current_player;
	board game = new_game();
	nomP1=malloc(21*sizeof(char));
	nomP2=malloc(21*sizeof(char));
	while(true){
		printf("\033[H\033[2J");
		menu(&copy);
		if(save){
			game= copy_game(copy);
			printf("Reprise de la partie en cours");
			fin=0;
		}
		else{
			fin=0,nbtours=1;
			nom(nomP1,1);
			printf("\033[H\033[2J");
			nom(nomP2,2);
			printf("\033[H\033[2J");
			int random = rand()%2;
			printf("\033[36;01mLe hasard a décidé que le joueur qui commence serait ");
			if(random==1){
				printf("%s",nomP1);
				current_player=PLAYER_1;
			}
			else{
				printf("%s",nomP2);
				current_player=PLAYER_2;
			}
		}
		printf("\n\n");
	  while(fin==0){//boucle qui se répète tant qu'il n'y a pas de gagnant
			if(current_player==1)printf("\033[33;01m%s",nomP1);//Change la couleur selon le joueur qui joue
			else{
				printf("\033[34;01m%s",nomP2);//Change la couleur selon le joueur qui joue
			}
	    printf("\033[0;01m, à vous de jouer :\n");//Affiche le nom du joueur
			affiche(game);
			do{//demande l'action que veut faire le joueur (placer ou déplacer)
				printf("Voulez vous placer (P) ou déplacer (D) une pièce ? (A pour abandonner, S pour sauvegarder) ");
				scanf(" %c",&action);
			}while(action!='p'&&action!='P'&&action!='d'&&action!='D'&&action!='a'&&action!='A'&&action=='S'&&action=='s');
			if(action=='A'||action=='a'){
				current_player=next_player(current_player);
				fin=current_player;
			}else if(action=='S'||action=='s'){
				copy=copy_game(game);
				save=true;
				fin=3;
			}
			else{
				if(verification(action,nbtours,current_player,game)==0){
					nbtours++;
					current_player = next_player(current_player);
					fin=get_winner(game);
				}
			}
	  }
		printf("\033[H\033[2J");
		if(fin==1)gagnant=nomP1;
		else{
			gagnant=nomP2;
		}
		if(fin!=3){
			affiche(game);
			printf("\n");
			printf("\033[32;01mBravo, vous avez gagné %s après %d tours\033[0;01m\n\n",gagnant, nbtours);
			free(nomP1);
			free(nomP2);
			sleep(5);
		}
		destroy_game(game);
	}
	return 0;
}
