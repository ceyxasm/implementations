#include <bits/stdc++.h>
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



int count_lru_page_faults(vector<int> ref_string, int frame_size)
{
    //cout<<"in call"<<endl;
    queue<int> lru;
    int page_faults = 0;
    unordered_set<int> page_table;
    for(int i=0;i<ref_string.size();i++) //looping all the pages in RS
    {
        int page_num = ref_string[i] ; //page number
        if(page_table.size() < frame_size) //if page table not full
        {
            if(page_table.find(page_num) == page_table.end()) //if page not in table
            {
                page_faults++;
                page_table.insert(page_num);
                lru.push(page_num);
            }
            else
            {
                queue<int> dupli;
                while(!lru.empty()){
                    if(lru.front() == page_num){
                        lru.pop();
                    }
                    else{
                        dupli.push(lru.front());
                        lru.pop();
                    }
                }
                dupli.push(page_num);
                while(!dupli.empty()){
                    lru.push(dupli.front());
                    dupli.pop();
                }
            }
            continue;
        }
        if(page_table.find(page_num) == page_table.end()) //if page table full and not in table
        {
            page_faults++;
            lru.push(page_num);
            int first_page = lru.front();
            lru.pop();
            page_table.erase(first_page);
            page_table.insert(page_num);
        }
        else{
            queue<int> dupli;
            while(!lru.empty()){
                if(lru.front() == page_num){
                    lru.pop();
                }
                else{
                    dupli.push(lru.front());
                    lru.pop();
                }
            }
            dupli.push(page_num);
            while(!dupli.empty()){
                lru.push(dupli.front());
                dupli.pop();
            }
        }
    }
    

   // printf("Page Faults: %d\n", page_faults);
    return page_faults;
}

int main()
{

    int sims, frame_size_upper_length, pages;
    printf("Enter the number of simulations: ");
    cin >> sims;
    printf("Enter the pages to be in our reference string: ");
    cin >> pages;
    printf("enter the upper limit on frame size ULFS (for a particular reference string; frame size will be varied from 3 to UFSL): ");
    cin >> frame_size_upper_length;

    int itr, page_faults_total[frame_size_upper_length+1];
    for(int i=0;i<=frame_size_upper_length;i++){
        page_faults_total[i]=0;
    }

    itr=0;

    while(itr< sims)
    {
        string ref_string = generate_ref_string(pages);
        vector<int> ref_vec= split(ref_string, '.');

        for(int frame_size=3;frame_size<=frame_size_upper_length;frame_size++)
        {
            //cout<<"in main"<<endl;
            page_faults_total[frame_size] += count_lru_page_faults(ref_vec, frame_size);
        }

    itr++;
    }

    for(int i=3;i<=frame_size_upper_length;i++)
    {
        printf("average page faults for frame size %d: %d \n", i, page_faults_total[i]/sims);
    }
}