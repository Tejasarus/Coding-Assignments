#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int num;
    string name, house_name;
    vector<string> g,h,s,r;
    cin >> num;
    for(int i = 0; i < num; ++i)
    {
        cin >> name >> house_name;
        if(house_name == "Gryffindor")
        {
            g.push_back(name);
        }
        else if(house_name == "Hufflepuff")
        {
            h.push_back(name);
        }
        else if(house_name == "Ravenclaw")
        {
            r.push_back(name);
        }
        else if(house_name == "Slytherin")
        {
            s.push_back(name);
        }
    }
    sort(g.begin(),g.end());
    sort(h.begin(),h.end());
    sort(r.begin(),r.end());
    sort(s.begin(),s.end());

    cout << "Gryffindor" << endl;
    for(int i = 0; i < g.size(); ++i)
    {
        cout << g.at(i) << endl;
    }
    cout << "Hufflepuff" << endl;
    for(int i = 0; i < h.size(); ++i)
    {
        cout << h.at(i) << endl;
    }
    cout << "Ravenclaw" << endl;
    for(int i = 0; i < r.size(); ++i)
    {
        cout << r.at(i) << endl;
    }
    cout << "Slytherin" << endl;
    for(int i = 0; i < s.size(); ++i)
    {
        cout << s.at(i) << endl;
    }
    return 0;  
};