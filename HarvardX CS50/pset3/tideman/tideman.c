#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int start, int next);
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

    // Clear preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
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

            if (!vote(j, name, ranks))
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
    for (int i = 0; i < candidate_count; i++)
    {
        // check if this is a valid candidate
        if (strcmp(candidates[i], name) == 0)
        {
            // check if this candidate has already been ranked by this voter
            for (int j = 0; j < rank; j++)
            {
                if (ranks[j] == i)
                {
                    return false;
                }
            }
            // add candidate to voter's ranks
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // selection sort
    for (int i = 0; i < pair_count; i++)
    {
        pair swap_pair; // create pair placeholder for swaps
        int swap_votes = 0; // get the vote count for that pair
        int p = i; // get the position of the pair to swap, starting with current location

        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > swap_votes)
            {
                swap_votes = preferences[pairs[j].winner][pairs[j].loser];
                swap_pair = pairs[j];
                p = j;
            }
        }

        // if a higher-ranked pair found...
        if (p > i)
        {
            pairs[p] = pairs[i];
            pairs[i] = swap_pair;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int p = 0; p < pair_count; p++)
    {
        if (check_cycle(pairs[p].winner, pairs[p].loser))
        {
            locked[pairs[p].winner][pairs[p].loser] = true;
        }
    }
    return;
}

// Check if a pair has a downstream chain that cycles back on its starting point
bool check_cycle(int start, int next)
{
    // if it loops back to the original (start) candidate, fail
    if (locked[next][start])
    {
        return false;
    }

    // otherwise continue looking for links recursively
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[next][i])
        {
            return check_cycle(start, i);
        }
    }

    return true; // passes if no loops detected
}

// Print the winner of the election
void print_winner(void)
{
    int lose_count;

    for (int i = 0; i < candidate_count; i++)
    {
        lose_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                lose_count++;
            }
        }

        // if this candidate doesn't lose to anyone, chances are they're the source
        if (lose_count == 0)
        {
            // double check that they've beaten at least 1 other candidate
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[i][j])
                {
                    printf("%s\n", candidates[i]);
                    return;
                }
            }
        }
    }
}

