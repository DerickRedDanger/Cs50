#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)// i,j,name
{
    // TODO
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcasecmp(candidates[k].name, name) == 0) // comparing the candidates name on the list for the one from name
        {
            preferences[voter][rank] = k; //if the name is on the list, the candidates get a point
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        int k = 1;
        for (int j = 0; j < k; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
            }
            else if (k < candidate_count)
            {
                k++;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int loser[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10}; // creating a list to put the number of the loser or losers if more than one tie at lowest, using 10 as "0" as the number from the canidadates range from 0-9
    int v = 0;
    int lowest = 100; // lowest score found so far, will keep updating as a new lowest appears
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            if (lowest > candidates[j].votes) // if the candidate has less vote than lowest
            {
                lowest = candidates[j].votes; // their vote becomes the lowest
                for (int k = 0; k <= j; k++ ) // the winner list gets reseted
                {
                    loser[k] = 10;
                }
                v = 1;
                loser[0] = j; // and the candidate is now included in the list
            }
            else if (lowest == candidates[j].votes) // if the candidate has the same amount of votes as the highest
            {
                loser[v] = j; // his name is added to the winners list
                v++;
            }
        }
    }

    return lowest;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int in = 0;
    int tie = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            in++;
            if (candidates[j].votes == min)
            {
                tie ++;
            }
        }

    }
    if (in == tie)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            if (candidates[j].votes == min)
            {
                candidates[j].eliminated = true;
            }
        }
    }
    return;
}