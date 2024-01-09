enunm states{start, temp} state
//A0 = desired
//A1 = temp sensor
//flame = 0-99
int boiler[
    switch(state)
    {
        case start:
            state = temp;
            flame = 50;
            break;

        case temp:
            state = temp;
    }
    switch(state)
    {
        case temp:
            if(A1 > A0)
            {
                flame++;
                break;
            }
            if(A1 < A0)
            {
                flame--;
                break
            }
    }
]