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

int main()
{
    int frame_size_upper_limit;
    string ref_string;
    int pages;
    printf("Enter the pages to be in our reference string: ");
    cin >> pages;
    printf("enter the upper limit on frame size ULFS (for a particular reference string; frame size will be varied from 3 to UFSL): ");
    cin >> frame_size_upper_limit;
    int n;
    cout<<"Enter the number of times execution should be run: ";
    cin>>n;
    int total_faults=0;


    int itr=0;
    int page_faults_total[frame_size_upper_limit+1];
    for(int i=0;i<=frame_size_upper_limit;i++){
        page_faults_total[i]=0;
    }

    while ( itr < n) //simulation runs n times
    {

        ref_string = generate_ref_string(pages);
        vector<int> ref_vec= split(ref_string, '.');


        for(int frame_size=3; frame_size <= frame_size_upper_limit; frame_size++)
        {
            int page_faults = 0;
            unordered_set<int> page_table;
            for (int i = 0; i < ref_vec.size(); i++) //looping through the entire reference string
            {
                int page_num = ref_vec[i]; //current page
                if (page_table.size() < frame_size) //if page table is not full
                {
                    if (page_table.find(page_num) == page_table.end()) //if page not in the table
                    {
                        page_faults++;
                        page_table.insert(page_num);
                        continue;
                    }
                }
                if (page_table.find(page_num) == page_table.end()) //table full and page not in table
                {
                    page_faults++;
                    page_table.erase(page_table.begin());
                    page_table.insert(page_num);
                }
            }
            page_faults_total[frame_size] += page_faults;
        }
        itr++;
    }

    for(int frame_size=3; frame_size <= frame_size_upper_limit; frame_size++)
    {
        cout<<"Average page faults for frame size "<<frame_size<<" is "<<page_faults_total[frame_size]/n<<endl;
    }
    return 0;
}