#include <stdio.h>
#include <stdlib.h>

typedef struct __node {
    struct __node * next;
    int * val;
} llist;

llist * push_node( llist * list, int val );
void delete_list( llist * list );
void print_list( llist * list );
void print_reverse( llist * list );

int main( int argc, char ** argv ) {
    llist * list = NULL;
    
    int i = 0;
    for( ; i < 20; ++i )
    {
        list = push_node( list, i );
    }
    print_list( list );
    printf( "\nPrinting in reverse...\n" );
    print_reverse( list );
    delete_list( list );
    return 0;
}

void print_reverse( llist * list ) {
    if( list ==  NULL )
        return;
    else
    {
        print_reverse( (*list).next );
        printf("%d\n", *((*list).val) );
    }
}

void print_list( llist * list ) {
    llist * tmp = list;
    while( tmp != NULL )
    {
        fprintf( stdout, "%d\n", *((*tmp).val) );
        tmp = (*tmp).next;
    }
    return;
}

llist * push_node( llist * list, int val ) {
    if( list == NULL )
    {
        list = (llist*) malloc( sizeof( llist ) );
        if( list == NULL )
        {
            printf("error\n");
            return list;
        }
        (*list).next = NULL;
        (*list).val = (int*) malloc( sizeof( int ) );
        if( (*list).val == NULL )
        {
            printf("error\n");
            return list;
        }
        *((*list).val) = val;
    }
    else
    {
        llist * tmp = list;
        for( ; (*tmp).next != NULL; tmp = (*tmp).next );
        (*tmp).next = (llist*) malloc( sizeof( llist ) );
        if( (*tmp).next == NULL )
        {
            printf("Error\n");
            return list;
        }
        tmp = (*tmp).next;
        (*tmp).next = NULL;
        (*tmp).val = (int*) malloc( sizeof( int ) );
        *((*tmp).val) = val;
    }
    return list;
}

void delete_list( llist * list ) {
    llist * tmp = list;
    while( tmp != NULL )
    {
        tmp = (*list).next;
        free( list );
        list = tmp;
    }
}
