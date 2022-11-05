#include<bits/stdc++.h>
using namespace std;

int random(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

string generate_ref_string(int length)
{
    string ref_string = "10";
    for (int i = 0; i < length; i++)
    {
        ref_string = ref_string+"."+ to_string(random(1, 30));
    }
    return ref_string;
}

vector<int> split(string str, char delimiter) {
    vector<int> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(stoi(tok));
    }

    return internal;
}


/*function that accepts the reference string and the frame size and returns the number of page faults as per optimal page replacement algorithm*/
int count_opt_page_faults(string ref_string, int frame_size)
{
    vector<int> ref_string_arr = split(ref_string, '.');
    int page_faults = 0;
    vector<int> page_table;
    for (int i = 0; i < ref_string_arr.size(); i++)
    {
        int page_num = ref_string_arr[i];
        if (page_table.size() < frame_size)
        {
            if (find(page_table.begin(), page_table.end(), page_num) == page_table.end())
            {
                page_faults++;
                page_table.push_back(page_num);
                continue;
            }
        }
        if (find(page_table.begin(), page_table.end(), page_num) == page_table.end())
        {
            page_faults++;
            int to_rem = -1, max_ind = -1;
            for (int j = 0; j < page_table.size(); j++)
            {
                int k = i + 1;
                while (k < ref_string_arr.size())
                {
                    if (ref_string_arr[k] == page_table[j])
                    {
                        break;
                    }
                    k++;
                }

                if (k == ref_string_arr.size())
                {
                    to_rem = page_table[j];
                    break;
                }
                else
                {
                    if (max_ind < k)
                    {
                        to_rem = page_table[j];
                        max_ind = k;
                    }
                }
            }
            int itr = 0;
            while (page_table[itr] != to_rem)
            {
                itr++;
                if (itr == page_table.size())
                {
                    break;
                }
            }
            page_table.erase(page_table.begin() + itr);
            page_table.push_back(page_num);
        }
    }
    return page_faults;
}


int main()
{
    int sims, frames, pages;
    printf("Enter number of simulations: ");
    scanf("%d", &sims);
    printf("Enter the upper limit of frame size( for a particular ref str; frame size varies from 3 to this upper limit): ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages); 
    int itr=0;
    int page_faults_total[frames+1];
    for(int i=0;i<=frames;i++)
    {
        page_faults_total[i]=0;
    }

    while(itr<sims)
    {
        string ref_string = generate_ref_string(pages);
        vector<int> ref_string_vec = split(ref_string, '.');
        for(int i=3;i<=frames;i++)
        {
            page_faults_total[i] += count_opt_page_faults(ref_string, i);
        }
        itr++;
    }
    for(int i=3;i<=frames;i++)
    {
        printf("Average page faults for frame size %d: %d\n", i, page_faults_total[i]/sims);
    }
    return 0;
}