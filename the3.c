#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

/*
INPUT:
    Node **meals_head: reference of the meal's linked list
    char *name: name of the meal
    int count: number of the meals

METHOD:
    Creates a meal and a node containing that meal. Append it to meal's linked list end.
*/
void add_meal(Node **meals_head, char *name, int count){
    Meal *data;
    Node *meal,*last;
    last = *meals_head;
    meal=(Node *)malloc(sizeof(Node));
    meal->node=(Meal *)malloc(sizeof(Meal));
    data = meal->node;
    meal->next = NULL;
    data->name = name;
    data->count = count;
    if(*meals_head == NULL){
        *meals_head = meal;
    }
    else{
        while (last->next){
            last = last->next;
        }
        last->next = meal;
    }
}


/*
INPUT:
    Node **philosophers_head: reference of the philosopher's linked list
    char *name: name of the philosopher
    char *favorite_meal: favorite meal
    int age: age of the philosopher

METHOD:
    Creates a philosopher and a node containing that philosopher.
    Append it to philosopher's linked list end.
*/
void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age){
    Philosopher *data;
    Node *philo,*last;
    last = *philosophers_head;
    philo=(Node *)malloc(sizeof(Node));
    philo->node=(Philosopher *)malloc(sizeof(Philosopher));
    data = philo->node;
    philo->next = NULL;
    data->name = name;
    data->favorite_meal = favorite_meal;
    data->age = age;
    if(*philosophers_head == NULL){
        *philosophers_head = philo;
    }
    else{
        while (last->next){
            last = last->next;
        }
        last->next = philo;
    }
}

/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    Node *philosophers: philosopher's linked list

METHOD:
    Places philosophers into a circular linked list in ascending order of ages.
*/

void place_philosophers(Node **table_head, Node *philosophers){
    Node *new_node,*head,*sort;
    Philosopher *s,*hold;
    int age,len,i;
    void *newn;
    len = get_length(philosophers);
    head = *table_head;
    for(i=0;i<len;i++){
        for(age=9999,sort = philosophers;sort;sort=sort->next){
            s = (Philosopher *)(sort->node);
            if((int)(s->age) < age && s->sitting != 1){
                hold = s;
                age = (int)(hold->age);
                newn = sort->node;
            }
        }
        hold->sitting = 1;
        new_node = (Node *)malloc(sizeof(Node));
        new_node->node = newn;
        new_node->next = NULL;
        if(i==0){
            *table_head = new_node;
            head = *table_head;
        }
        else{
            head->next = new_node;
            head = head->next;
        }
    }
    head->next = *table_head;
}


/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    int index: index of the philosopher to be removed
    int size_of_table: number of philosophers in the table

METHOD:
    Removes a philosopher from table.
*/
void remove_philosopher(Node **table_head, int index, int size_of_table){
    Node *head,*hold,*n;
    int i;
    head = *table_head;
    if(index == 0){
        for(i=0;i<size_of_table-1;i++){
            head=head->next;
        }
        hold = (*table_head)->next;
        head->next = hold;
        *table_head = hold;
    }
    else{
        for(i=0;i<index-1;i++){
            head=head->next;
        }
        n=head->next;
        hold=n->next;
        head->next = hold;
    }
}

/*
INPUT:
    Node *table: Circular linked list
    Node *meals: Meal's linked list

METHOD:
    Serves favorite meals and reduce their counts. Use strcmp function from string.h
*/

void serve_meals(Node *table, Node *meals){
    Node *last,*check;
    Philosopher *philo;
    Meal *meal;
    int len,res,i;
    len = get_length(meals);
    last = table->next;
    for(;last!=table;last=last->next){
        philo = (Philosopher *)last->node;
        for(i=0,check = meals;i<len;i++){
            meal = (Meal *)check->node;
            res = strcmp(philo->favorite_meal,meal->name);
            if(res == 0){
                meal->count--;
                break;
            }
            else{
                check=check->next;
            }
        }
    }
    philo = (Philosopher *)table->node;
    for(i=0,check = meals;i<len;i++){
        meal = (Meal *)check->node;
        res = strcmp(philo->favorite_meal,meal->name);
        if(res == 0){
            meal->count--;
            break;
        }
        else{
            check=check->next;
        }
    }
}

/*
INPUT:
    Node *list: A linked list
    void (*helper_print)(void *): Reference of a helper print function

METHOD:
    Prints items in the linked list using helper print function
*/
void print_list(Node *list, void (*helper_print)(void *)){
    Node *last;
    last = list;
    for(;last;last=last->next){
        helper_print(last);
    }
}

/*
INPUT:
    void *meal: void meal pointer

METHOD:
    Cast void pointer to a meal pointer and prints it's content
*/
void print_meal_node(void *meal){
    Node *last;
    Meal *tmp;
    last = (Node *)meal;
    tmp = (Meal *)(last->node);
    printf("Name: %s, count: %d\n",(char *)(tmp->name),(int)(tmp->count));
}

/*
INPUT:
    void *philosopher: void philosopher pointer

METHOD:
    Cast void pointer to a philosopher pointer and prints it's content
*/
void print_philosopher_node(void *philosopher){
    Node *last;
    Philosopher *tmp;
    last = (Node *)philosopher;
    tmp = (Philosopher *)(last->node);
    printf("Name: %s, favorite meal: %s, age: %d\n",(char *)(tmp->name),(char *)(tmp->favorite_meal),(int)(tmp->age));
}

/*
INPUT:
    Node *table: Circular linked list

METHOD:
    Prints the formation as <prev> <current> <next>
*/
void helper_print(Node *last){
    Node *temp,*f;
    Philosopher *a,*b,*c;
    a = (Philosopher *)(last->node);
    f = last->next;
    b = (Philosopher *)(f->node);
    for(temp = last;temp->next!=last;temp=temp->next);
    c = (Philosopher *)(temp->node);
    printf("%s -> %s -> %s\n",c->name,a->name,b->name);
}

void print_table(Node *table){
    Node *last;
    helper_print(table);
    for(last=table->next;last!=table;last=last->next){
        helper_print(last);
    }
}


/*
INPUT:
    Node *list: A linked list

OUTPUT:
    Size of the linked list in an integer format

METHOD:
    Calculates the size of the linked list and returns it.
 */
int get_length(Node *list){
    int result=0;
    Node *temp;
    temp = list;
    for(;temp;temp=temp->next){
        result++;
    }

    return result;
}

/*
INPUT:
    Node *philosophers: Philosopher's linked list

OUTPUT:
    Philosopher pointer at given index.

METHOD:
    Finds the philosopher at given index and returns it's reference.
*/
Philosopher *get_philosopher(Node *philosophers, int index){
    Philosopher *result;
    Node *tmp;
    int i;
    tmp = philosophers;
    for(i=0;i<index;i++){
        tmp = tmp->next;
    }
    result = tmp->node;
    return result;
}





/*PLEASE COPY YOUR SOLUTION HERE*/
