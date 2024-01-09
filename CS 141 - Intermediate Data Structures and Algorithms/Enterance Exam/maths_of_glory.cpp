#include <iostream>
using namespace std;

int main()
{
    int puzzle_num, rounds, p1, p2, p3, p4, team1, team2;
    cin >> puzzle_num >> rounds;
    team1 = puzzle_num;
    team2 = puzzle_num;

    for(int i=0; i < rounds; ++i)
    {
        cin >> p1 >> p2 >> p3 >> p4;
        team1 = team1 - (p1 * p2);
        team2 = team2 - (p3 * p4);
        
        if(team1 <= 0 && team2 <= 0)
        {
   
                cout << "It's a tie at round " << i+1 << "!" << endl;
                return 0;;
        }
        else if(team1 <= 0)
        {

                cout << "Team 1 wins at round " << i+1 << "!" << endl;
                return 0;;
        }
        else if(team2 <= 0)
        {
                cout << "Team 2 wins at round " << i+1 << "!" << endl;
                return 0;
        }

    }
   
        cout << "Oh no!" << endl;
    

    return 0;
};