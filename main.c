#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

struct city{
    char cityName[14];
    int plate;
    char region[2];
    int number_of_neigbour;
    struct city *next;
    struct neigbour *next2;
};

struct neigbour{
    int plate;
    struct neigbour *next;
};

struct city *first = NULL,*last = NULL;
struct neigbour *first2 = NULL,*last2 = NULL;

void add_end(struct city *ct){
	struct city *newc = (struct city*) malloc(sizeof(struct city));

	newc ->plate = ct->plate;
	strcpy(newc->cityName,ct->cityName);
	strcpy(newc->region,ct->region);
	newc ->number_of_neigbour = ct->number_of_neigbour;

	if(first==NULL){
		first=newc;
		last=newc;
		last->next=NULL;
	}
	else{
		last->next=newc;
		last=newc;
		last->next=NULL;
	}
}

void add_head(struct city *ct){
	struct city *newc1 = (struct city*) malloc(sizeof(struct city));

	newc1 ->plate = ct->plate;
	strcpy(newc1->cityName,ct->cityName);
	strcpy(newc1->region,ct->region);
	newc1 ->number_of_neigbour = ct->number_of_neigbour;

	if(first==NULL){
		first=newc1;
		first->next=NULL;
		last=first;
	}
	else{
		newc1->next=first;
		first=newc1;
	}
}

void add_end2(struct neigbour *neig){
	struct neigbour *newc2 = (struct neigbour*) malloc(sizeof(struct neigbour));

	newc2 ->plate = neig->plate;

	if(first2==NULL){
		first2=newc2;
		last2=newc2;
		last2->next=NULL;
	}
	else{
		last2->next=newc2;
		last2=newc2;
		last2->next=NULL;
	}
}

int search(int plate){
    struct city *list;
    struct neigbour *list2;

    list = first;
    list2 = first2;

    while(list != NULL){
        if(list->plate == plate){
            //int numeric_limits = list->plate;

            printf("%d %s %3s %d ",list->plate,list->cityName,
            list->region,list->number_of_neigbour);

            for(int i=0;i<list->number_of_neigbour;i++){
                printf("-%d",list2->plate);
                list2 = list2->next;
            }

            printf("\n");
            return 1;
            break;
        }
        for(int j=0;j<list->number_of_neigbour;j++){
            list2 = list2->next;
        }
        list = list->next;


    }

	return -1;
}

void add_sequential(struct city *ct){
	struct city *newc4 = (struct city*) malloc(sizeof(struct city));

	newc4 ->plate = ct->plate;
	strcpy(newc4->cityName,ct->cityName);
	strcpy(newc4->region,ct->region);
	newc4->number_of_neigbour = ct->number_of_neigbour;

	if(first==NULL){
		first=newc4;
		last=newc4;
		newc4->next=NULL;
	}else{
		if(newc4->plate < first->plate)
		add_head(newc4);
        else if(newc4->plate > last->plate)
        add_end(newc4);
		else{
			struct city *seq=first;

            if(seq->next->plate > newc4->plate){
            seq = seq->next;
            newc4->next = seq->next;
            seq->next = newc4;
            }

		}
	}

}

void swaping(struct city *a, struct city *b){
    struct city *temp;
    temp = (struct city*)malloc(sizeof(struct city));

    temp = a;
    a = b;
    b = temp;
}

void buble_link(){
    int swapped;
    struct city *ptr_fun;

    if (first == NULL)
        return;

    do
    {
        swapped = 0;
        ptr_fun = first;

        while (ptr_fun->next != last)
        {
            if (ptr_fun->plate > ptr_fun->next->plate)
            {
                swaping(ptr_fun,ptr_fun->next);
                swapped = 1;
            }
            ptr_fun = ptr_fun->next;
        }
        last = ptr_fun;
    }
    while (swapped);
}

void list(FILE* outfile){
    struct city *list;
    struct neigbour *list2;

    list2 = first2;

    list = first;

    fprintf(outfile,"Cities int this file: \n");

    while(list != NULL){
        fprintf(outfile,"%d %15s %3s %d ",list->plate,list->cityName,
            list->region,list->number_of_neigbour);

        for(int i=0;i<list->number_of_neigbour;i++){
            fprintf(outfile,"->%d",list2->plate);
            list2 = list2->next;
        }

        fprintf(outfile,"\n");

        fprintf(outfile,"|\n");

        list = list->next;
    }
}

void delete_city(struct city *ct,int plate){
	struct city *del=first, *pre=NULL;

	while(del!=NULL){
		if(del->plate == ct->plate){
           break;
		}
		else{
			pre=del;
			del=del->next;
		}
	}

    if(del!=NULL){
        if(del==first){
            first=first->next;
		}
        else if(del==last){
            last=pre;
            pre->next=NULL;
        }
        else{
            pre->next=del->next;
        }
    free(del);
    }
}

void list_region(char region[]){
    struct city *list ;

    list =first;

    while(list != NULL){
        if(strcmp(list->region , region) == 0){
            printf("%d %15s %3s %d\n",list->plate,list->cityName,
               list->region,list->number_of_neigbour);
        }
        list = list->next;
    }
}

void list_number_of_neig(int n){
    struct city *list;

    list=first;

    while(list != NULL){
        if(list->number_of_neigbour > n){
            printf("%d %15s %3s %d\n",list->plate,list->cityName,
               list->region,list->number_of_neigbour);
        }
        list = list->next;
    }
}

int main()
{
    DIR *dir;
    struct dirent *sd;
    char search1[]=".txt";
    dir = opendir(".");
    char str[100];

    if(!dir){
        printf("Directory was not found!\n");
        exit(1);
    }

    char filename[12];

    while( (sd=readdir(dir)) != NULL){
        char *ptr;
        ptr = strstr(sd -> d_name , search1);
        if(ptr != NULL){
            strcpy(filename,sd->d_name);
        }
    }

    rewinddir(dir);

    FILE* infile;
    FILE* outfile;
    infile = fopen(filename,"r");
    outfile = fopen("output.txt","w");

    static int number_of_city=0;

    while(!feof(infile)){
        while(fgets(str,100,infile)){
            number_of_city ++;
        }
    }

    printf("Number of city in this file :%d\n",number_of_city);

    rewind(infile);

    int k=0;
    char buffer[number_of_city][90];

    struct city *ct;
    ct = malloc(number_of_city*sizeof(struct city));

    char cityName[number_of_city][15];
    char region[number_of_city][3];

    while(!feof(infile)){
        fscanf(infile,"%[^\n]\n",buffer[k]);

        const char *token = strtok(buffer[k],",");
        int line = 0;
        while(token != NULL){
            if(line == 1){
                strcpy(cityName[k],token);
            }else if(line == 2){
                strcpy(region[k],token);
            }
            line ++;
            token = strtok(NULL,",");
        }
        ct[k].number_of_neigbour = line-3;
        k++;
    }

    buble_link();

    for(int i=0;i<number_of_city;i++){
        ct[i].plate = atoi(buffer[i]);
        strcpy(ct[i].cityName,cityName[i]);
        strcpy(ct[i].region,region[i]);

        add_sequential(&ct[i]);
    }

    rewind(infile);

    int n=0;

    char neigbours[number_of_city][12][15];

    while(!feof(infile)){
        fscanf(infile,"%[^\n]\n",buffer[n]);

        const char *trace = strtok(buffer[n],",");
        int line = 0;
        int index = 2;

        while(trace != NULL){
            if(line > index ){
                strcpy(neigbours[n][index-2],trace);
                index ++;
            }
            line ++;
            trace = strtok(NULL,",");
        }
        n++;
    }

    struct neigbour *neig;
    neig = malloc(number_of_city*sizeof(struct neigbour));

    for(int i=0;i<number_of_city;i++){
        printf("%s neigbours: ",ct[i].cityName);
        for(int j=0;j<ct[i].number_of_neigbour;j++){
            printf("%s-",neigbours[i][j]);
            for(int k=0;k<number_of_city;k++){
                if(strcmp(ct[k].cityName,neigbours[i][j]) == 0){
                    printf("%d ",ct[k].plate);
                    neig[j].plate = ct[k].plate;
                }
            }
            add_end2(&neig[j]);
        }
        printf("\n");
    }

    char buffer2[90];
    char buffer3[90];
    char buffer4[90];
    char buffer5[90];
    char answer[2];
    char reg[2];
    int ans;

    char neigbours2[10][12][15];
    static int n2 = 0;

    bool flag_to_exit = true;

    while(flag_to_exit == true){
        int choice;

        printf("1.Add City\n2.Remove City\n3.Search City\n");
        printf("4.List City\n5.List Region\n6.Neigbor\n7.Exit\n");
        printf("Please enter choice: ");

        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Please enter city info to add it: ");
                scanf("%s",buffer2);
                int result_of4 = search(atoi(buffer2));

                if(result_of4 != 1){
                    number_of_city ++;

                    ct = realloc(ct,number_of_city*sizeof(struct city));
                    neig = realloc(neig,number_of_city*sizeof(struct neigbour));

                    const char *token2 = strtok(buffer2,",");
                    int line2 = 0;

                    while(token2 != NULL){
                        if(line2 == 1){
                            strcpy(ct[number_of_city-1].cityName,token2);
                        }else if(line2 == 2){
                            strcpy(ct[number_of_city-1].region,token2);
                        }
                        line2 ++;
                        token2 = strtok(NULL,",");
                    }

                    ct[number_of_city-1].number_of_neigbour = line2-3;
                    ct[number_of_city-1].plate = atoi(buffer2);

                    int line3 = 0;
                    int index3 = 2;

                    while(token2 != NULL){
                        if(line3 > index3 ){
                            strcpy(neigbours2[n2][index3-2],token2);
                            index3 ++;
                        }
                    line3 ++;
                    token2 = strtok(NULL,",");
                    }

                    n2 ++;

                    for(int j=0;j<ct[number_of_city-1].number_of_neigbour;j++){
                        for(int k=0;k<number_of_city;k++){
                            if(strcmp(ct[k].cityName,neigbours2[n2-1][j]) == 0){
                                neig[j].plate = ct[k].plate;
                            }
                        }
                    add_end2(&neig[j]);
                    }
                }
                add_sequential(&ct[number_of_city-1]);

                break;

            case 2:
                printf("Please enter city info to delete it: ");
                scanf("%s",buffer4);
                int result_of5 = search(atoi(buffer4));

                if(result_of5 != -1){
                    delete_city(ct,result_of5);
                }

                break;

            case 3:
                printf("Please enter city info to search it: ");
                scanf("%s",buffer5);
                int result_of6 = search(atoi(buffer5));

                if(result_of6 != 1){
                    printf("The city did not find! would you like to add it? Y/N: ");
                    scanf("%s",answer);

                    if(strcmp(answer,"Y") == 0){
                        printf("Please enter city info to add it:");
                        scanf("%s",buffer3);
                        number_of_city ++;

                        ct = realloc(ct,number_of_city*sizeof(struct city));
                        neig = realloc(neig,number_of_city*sizeof(struct neigbour));

                        const char *token3 = strtok(buffer3,",");
                        int line5 = 0;
                        while(token3 != NULL){
                            if(line5 == 1){
                                strcpy(ct[number_of_city-1].cityName,token3);
                            }else if(line5 == 2){
                                strcpy(ct[number_of_city-1].region,token3);
                            }

                            line5 ++;
                            token3 = strtok(NULL,",");
                        }

                        ct[number_of_city-1].plate = atoi(buffer3);
                        ct[number_of_city-1].number_of_neigbour = line5-3;

                        int line6 = 0;
                        int index6 = 2;

                        while(token3 != NULL){
                            if(line6 > index6 ){
                                strcpy(neigbours2[n2][index6-2],token3);
                                index6 ++;
                            }
                        line6 ++;
                        token3 = strtok(NULL,",");
                        }

                        n2 ++;

                        for(int j=0;j<ct[number_of_city-1].number_of_neigbour;j++){
                            for(int k=0;k<number_of_city;k++){
                                if(strcmp(ct[k].cityName,neigbours2[n2-1][j]) == 0){
                                    neig[j].plate = ct[k].plate;
                                }
                            }
                        add_end2(&neig[j]);
                        }
                    }else{
                        printf("Do nothing!\n");
                    }
                }else{
                    printf("The city has been found!\n");
                }
                add_sequential(&ct[number_of_city-1]);

                break;

            case 4:
                list(outfile);
                break;
            case 5:
                printf("Which region would you like to search? :");
                scanf("%s",reg);

                list_region(reg);

                break;

            case 6:
                printf("The city has number of neigbour that bigger than ans: ");
                scanf("%d",&ans);

                list_number_of_neig(ans);

                break;

            case 7:
                flag_to_exit = false;

                break;

        }
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
