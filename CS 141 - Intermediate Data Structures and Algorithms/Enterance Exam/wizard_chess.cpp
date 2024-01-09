#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct node
{
    public:
    int x,y,d;
    node(){}
    node(int x_pos, int y_pos, int distance)
    {
        x = x_pos;
        y = y_pos;
        d = distance;
    }
};

//janky way of converting first letter to number
int letter_to_number(string str)
{
    char first_letter = str.at(0);
    if(first_letter == 'a')
    {
        return 1;
    }
    else if(first_letter == 'b')
    {
        return 2;
    }
    else if(first_letter == 'c')
    {
        return 3;
    }
    else if(first_letter == 'd')
    {
        return 4;
    }
    else if(first_letter == 'e')
    {
        return 5;
    }
    else if(first_letter == 'f')
    {
        return 6;
    }
    else if(first_letter == 'g')
    {
        return 7;
    }
    else if(first_letter == 'h')
    {
        return 8;
    }
};

bool is_valid(int x, int y, vector<node> taken)
{
    if(x >= 1 && x <= 8 && y >= 1 && y <= 8) //check on board
    {
        for(int i = 0; i < taken.size(); ++i)
        {
            if(x == taken[i].x && y == taken[i].y)
            {
                return false;
            }
        }
        return true;
    }
    return false;
};

int main()
{
    int occ_num = 0, coord1, coord2, board_num = 1;
    string taken_square,start_square,end_square;
    vector<node> taken_squares;
    while(true)
    {
        //gather all of the info
        cin >> occ_num;
        if(occ_num == -1)
        {
            return 0;
        }
        for(int i = 0; i < occ_num; ++i)
        {
            cin >> taken_square;
            coord1 = letter_to_number(taken_square);
            coord2 = int(taken_square.at(1))-48;
            node taken(coord1,coord2,0);
            taken_squares.push_back(taken);
        }

        cin >> start_square >> end_square;
        
        coord1 = letter_to_number(start_square);
        coord2 = int(start_square.at(1))-48;
        node s_square(coord1,coord2,0);

        coord1 = letter_to_number(end_square);
        coord2 = int(end_square.at(1))-48;
        node e_square(coord1,coord2,0);

       // cout << "hello" << endl;
       // cout << "c1 " << coord1 << " c2 " << coord2 << endl;
        
        //find the shortest path
        int x,y,moves=0;
        bool visited[9][9];
        //possible moves from the internet (by squares)
        int move_horiz[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
        int move_vert[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
        //make nodes false
        for(int i = 1; i <= 8; ++i)
        {
            for(int j = 1; j <= 8; ++j)
            {
                visited[i][j] = false;
            }
        }

        visited[s_square.x][s_square.y] = true;

        queue<node> queue;
        queue.push(node(s_square.x,s_square.y,0));
        node temp;
        int c = 0;
        while(!queue.empty())
        {
            //cout << c << endl;
            //c++;
            temp = queue.front();
            queue.pop();
           // cout << "here2" << endl;
            if(temp.x == e_square.x && temp.y == e_square.y)
            {
                cout << "Board " << board_num << ": " << temp.d << " moves" << endl;
                ++c;
                break;
            }

            for(int i = 0; i < 8; ++i)
            {
               // cout << "here3" << endl;
                x = temp.x + move_horiz[i];
                y = temp.y + move_vert[i];


                if(is_valid(x,y,taken_squares) && !visited[x][y])
                {
                   // cout << "x " << x << " y " << y << endl;
                    visited[x][y] = true;
                    queue.push(node(x,y,temp.d+1));
                }
            }
        }
        if(queue.empty())
        {
            if(c == 0)
            {
                cout << "Board " << board_num << ": not reachable" << endl;
            }
        }
        c = 0;
        board_num++;
    }
    return 0;
};