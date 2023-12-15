#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcasecmp(candidates[k].name, name) == 0) // comparing the candidates name on the list for the one from name
        {
            candidates[k].votes++; //if the name is on the list, the candidates get a point
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)

{
    // TODO
    int winner[MAX] = {10, 10, 10, 10, 10, 10, 10, 10, 10}; // creating a list to put the number of the winner or winners if more than one tie, using 10 as "0" as the number from the canidadates range from 0-9
    int v = 0;
    int highest = 0; // highest score found so far, will keep updating as a new highest appears
    for (int j = 0; j < candidate_count; j++ )
    {
        if ( highest < candidates[j].votes) // if the candidate has more vote thn highest
        {
            highest = candidates[j].votes; // their vote becomes the highest
            for (int k = 0; k <= j; k++ ) // the winner list gets reseted
            {
                winner[k] = 10;
            }
            v = 1;
            winner[0] = j; // and the candidate is now included in the list
        }
        else if ( highest == candidates[j].votes) // if the candidate has the same amount of votes as the highest
        {
            winner[v] = j; // his name is added to the winners list
            v++;
        }
    }
    if( v == 1)
    {
        printf("%s\n", candidates[winner[0]].name);
    }
    else if ( v > 1)
    {
        printf("\n");
        for (int j = 0; j < candidate_count; j++ )
        {
            if (winner[j] != 10)
            {
                printf("%s\n", candidates[winner[j]].name);
            }
        }
    }
    return;
}