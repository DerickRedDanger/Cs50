#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char word [24 + 1]; // for a name with up to 23 characters plus the null
    struct node *next;
}
node;

void freehashtable(node *node1); // custom funtion to free the malloc
void insert (node *node1,node *node2, string name);// custom function to insert more nodes in the harshtable

int main(void)
{
    node *hashtable[26];

    for (int x=0; x<=25; x++) //initializing the list with the alphabeth and next = NULL
    {
        hashtable[x] = malloc(sizeof(node));
        for (int y=0; y<=23; y++)
        {
            hashtable[x]->word[0] = ' ';
        }
        hashtable[x]->word[0] = 65 + x;
        hashtable[x]->word[24] = '\0';
        hashtable[x]->next = NULL;
    }

    node *n = malloc(sizeof(node));
    free(n);
    int z = 1;
    string abort = "done";
    while (z==1)
    {
        string name = get_string ("name ? write done to continue.");

        if (strcmp(name, abort)==0)
        {
            z=0;
        }
        else if ( 65 <= name[0] && name[0] <= 90)
        {
            if(hashtable[name[0]- 65]->next == NULL)
            {
                n = malloc(sizeof(node));
                if (n==NULL)
                {
                    for (int x=0; x<26; x++)
                    {
                        freehashtable(hashtable[x]);
                    }
                    return 1;
                }
                for (int x=0; x<26; x++)
                    {
                        if (name[x]=='\0')
                        {
                            break;
                        }
                        n->word[x] = name[x];
                        printf(" %c \n", n->word[x]);
                    }

                n->next= NULL;
                hashtable[name[0]- 65]->next = n;
            }
            else
            {
                n = malloc(sizeof(node));
                if (n==NULL)
                {
                    for (int x=0; x<26; x++)
                    {
                        freehashtable(hashtable[x]);
                    }
                    return 1;
                }
                insert (hashtable[name[0]- 65], n, name);
            }
        }
    }
    for (int x=0; x<26; x++)
    {
        node *list = NULL;
        printf ("%s ", hashtable[x]->word);
        list = hashtable[x]->next;
        while(list!= NULL)
        {
            printf ("%s ", list->word);
            list = list->next;
        }
        printf ("\n");
    }
}

void freehashtable(node *node1)
{
        node *list = NULL;
        list = node1->next;
        while(list!= NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
}

void insert (node *node1,node *node2,string name)
{
    if (node1->next == NULL)
    {
        node1->next = node2;
        strcpy(node1->word,name);
        node1->next->next = NULL;
    }
    else
    return insert (node1->next,node2,name);
}