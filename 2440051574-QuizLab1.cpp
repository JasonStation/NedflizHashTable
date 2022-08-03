//[NIM - NAMA] 2440051574 - Jason Leonardo Sutioso

//Chaining - Hash Tables

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

int currId = 0;

struct hashNode{
    char id[7];
    char title[21];
    char genre[11];
    double rating;
    int year;
    struct hashNode * next;
};

struct hashNode *head[SIZE], *v;


int hashFunction(){
    return currId;
}

void insertHash(char id[], char title[], char genre[], double rating, int year){
    struct hashNode *newNode = (struct hashNode*)malloc(sizeof(struct hashNode));

    int i = hashFunction();
    strcpy(newNode->id, id);
    strcpy(newNode->title, title);
    strcpy(newNode->genre, genre);
    newNode->rating = rating;
    newNode->year = year;
    newNode -> next = NULL;

    if(head[i] == NULL) head[i] = newNode;
    else{
        v = head[i];
        while(v->next != NULL) v = v->next;
        v->next = newNode;
    }

}

void deleteHash(char id[], int entry){
    int i = entry;
    char ph;
        for(v = head[i]; v != NULL; v = v->next){
            if(strcmp(v->id, id) == 0){
                printf("%s - %s has been deleted!\nType any key to continue >> ", id, v->title);
                scanf(" %c", &ph);
                free(head[i]);
                head[i] = NULL;
            }
            if(v == NULL){
                printf("Not found\n");
                scanf(" %c", &ph);
            }
        }

}

void viewMovies(){

    if(head[0] == NULL) printf("\nNo data!!!\n\n");
    else{
        printf("\nLIST OF FILMS\n================\n\n");
    }
     for(int i = 0; i < SIZE; ++i){
        if(head[i] == NULL) continue;
        else{
            for(v = head[i]; v != NULL; v = v->next){
                printf("ID: %s\nMovie Title: %s\nGenre: %s\nRating: %.1lf\nYear Released: %d",
                       v->id, v->title, v->genre, v->rating, v->year);

            }
            printf("\n\n");
        }
     }
}

void inputInsert(){
    char title[21], genre[11];
    double rating;
    int year;
    do{
        printf("Enter movie title [5 - 20 characters] >> ");
        scanf(" %[^\n]", title);
    }while(strlen(title) < 5 || strlen(title) > 20);

    do{
        printf("Enter genre [Adventure | Romance | Comedies] CASE SENSITIVE >> ");
        scanf(" %[^\n]", genre);
    }while(strcmp(genre, "Adventure") != 0 && strcmp(genre, "Romance") != 0 && strcmp(genre, "Comedies"));
    do{
        printf("Enter rating [0.0 - 5.0] >> ");
        scanf("%lf", &rating);
    }while(rating < 0 || rating > 5);
    do{
        printf("Enter year the movie was released [1900 - 2020] >> ");
        scanf("%d", &year);
    }while(year < 1900 || year > 2020);

    char movieId[6];
    if(strcmp(genre, "Adventure") == 0){
        movieId[0] = 'A';
        movieId[1] = 'E';
    }
    else if(strcmp(genre, "Romance") == 0){
        movieId[0] = 'R';
        movieId[1] = 'E';
    }
    else{
        movieId[0] = 'C';
        movieId[1] = 'S';
    }
    movieId[2] = (currId / 100) % 10 + '0';
    movieId[3] = (currId/ 10) % 10 + '0';
    movieId[4] = currId % 10 + '0';
    insertHash(movieId, title, genre, rating, year);
    currId++;
}

int main()
{

	int res;
	char menu;
	char name[21];
	do{
		system("cls");
		printf("[NIM - NAMA] 2440051574 - Jason Leonardo Sutioso\n\n");
		printf("NEDFLIZ\n(c)Nedfliz Inc.\n");
		printf("\nWhat would you like to do?\n");
		printf("1. Insert Movie\n");
		printf("2. View Movies\n");
		printf("3. Delete Movie\n");
        printf("4. Exit\n\n");
		printf("Enter menu >> "); scanf(" %c", &menu);
		getchar();
		switch(menu)
		{
			case '1':
				inputInsert();
				break;
			case '2':
				viewMovies();
				printf("Type in any key to continue >> ");
				char ph[11];
				scanf(" %s", ph);
				break;
			case '3':
				char searchId[7];
				viewMovies();
                    do{
                    printf("Enter ID to delete [AEXXX | REXXX | CSXXX] >> ");
                    scanf(" %[^\n]", searchId);
                    }while(strncmp(searchId, "AE", 2) != 0 && strncmp(searchId, "RE", 2) && strncmp(searchId, "CS", 2));
                    int entry = (searchId[3] - 48) * 10 + (searchId[4] - 48);
                   // char ph;
                   // scanf(" %c", &ph);
                    deleteHash(searchId, entry);
                    break;
		}

	}
	while(menu != '4');
	return 0;
}
