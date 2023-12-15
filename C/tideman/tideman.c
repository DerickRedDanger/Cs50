#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int point; // added by the student to help sort the pairs
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

//which candidates was at the reciving end of a pair/ added by the student to help lock the pairs and find the winners
int receiver[9];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, &ranks[j]))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO

    for (int k = 0; k < candidate_count; k++)
    {
        if ( strcasecmp(candidates[k], name) == 0)
        {

            ranks[rank] = k;

            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int k = 0; k < candidate_count; k++)
    {
        for(int l = k +1; l < candidate_count; l++)
        {
            preferences[ranks[k]] [ranks[l]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
                pairs[pair_count - 1].point = (preferences[i][j] - preferences[j][i]);
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
pair sorting[1];
    for ( int x = 0; x < pair_count; x++)
    {
        for (int y = x+1; y < pair_count; y++)
        {
                if (pairs[x].point < pairs[y].point)
            {
                sorting[0] = pairs[x];
                pairs[x] = pairs[y];
                pairs[y] = sorting[0];
            }
            }
        }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // TODO
     for (int i = 0; i < pair_count; i++)
    {
        int totallocked = 0;

        for (int j = 0; j < candidate_count; i++ )
        {
            if (locked[j][pairs[i].loser] == true)
            {
                receiver[pairs[i].loser] = 1;
            }
        }
        for (int j = 0; j < candidate_count; i++ )
        {
         if (receiver[j] == 1)
         {totallocked ++;}
        }
        if (totallocked < (candidate_count -1 ) )
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        if (totallocked == (candidate_count -1 ) && receiver[pairs[i].loser] == 1 )
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int winner[9] ={10,10,10,10,10,10,10,10,10};
    int v = 0;
    for (int j = 0; j < candidate_count; j++ )
        {
            if (receiver[j] == 0)
            {
                winner[v] = j;
                v++;
            }
        }
    if( v == 1)
    {
        printf("the winner is %s\n", candidates[winner[0]]);
    }
    else
    {
        printf("it's a tie between the candidates:\n");
        for (int j = 0; j < candidate_count; j++ )
            {
                if (winner[j] != 10)
                {
                    printf("candidate %s\n", candidates[winner[j]]);
                }
            }
    }
    return;
}
