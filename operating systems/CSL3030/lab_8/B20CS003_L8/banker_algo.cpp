#include<bits/stdc++.h>
using namespace std;

void checkSafe(int n, int m, vector<vector<int>>&allocation, 
            vector<int>&res_available,vector<vector<int>>&res_needed,bool check_init)
{
    vector<int> safe_sequence;
    vector<bool>completed(n,false);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(!completed[j])
            {
                bool check = true;
                for(int k=0;k<m;k++)
                {    
                    if(res_available[k]<res_needed[j][k])
                    {
                        check = check_init;
                        break;
                    }
                }
                if(check==true)
                {
                    safe_sequence.push_back(j);

                    for(int l=0;l<m;l++){
                        res_available[l] = res_available[l] + allocation[j][l];
                    }
                    completed[j] = !check_init;
                }
            }
        }
    }

    bool final_check = !check_init;
    for(int i=0;i<n;i++)
    {
        final_check = final_check && completed[i];
    }


    if(final_check)
    {
        cout<<"Provided state is safe\n";
        cout<<"The safe sequence is : ";
        int sizee = safe_sequence.size();
        for(int i=0;i<sizee;i++){
            cout<<safe_sequence[i]<<" ";
        }
        cout<<endl;
    } else
    {
        cout<<"Provided input State is not safe";
        cout<<endl;
    }
    cout<<endl;
}




int main()
{  
    int n, m;
    cout<<"Enter total number of processes: ";
    cin>>n;
    cout<<"Enter total number of resources: ";
    cin>>m;

    vector<vector<int>>max,allocation,res_needed;
    vector<int>old_res_available,res_available,request;
    cout<<"Enter the available instances for each of "<<m<<" resources in space seperated manner"<<endl;


    for(int i=0;i<m;i++){

        int ele;
        cin >>ele;
        res_available.push_back(ele);
        old_res_available.push_back(ele);

    }

    cout <<endl;

    cout<<"Enter the amount of each resource currently allocated to the processes in matrix format "<<endl;

    for(int i=0;i<n;i++){

        vector<int>temp;

        for(int j=0;j<m;j++){

            int ele;
            cin >>ele;
            temp.push_back(ele);

        }

        allocation.push_back(temp);
    }

    cout<<endl;

    cout<<"Enter the maximum instance each resource processes for completion of them in matrix format \n(process X resource needed)"<<endl;
    for(int i=0;i<n;i++){
        vector<int>temp;
        for(int j=0;j<m;j++){
            int ele;
            cin >>ele;
            temp.push_back(ele);
        }

        max.push_back(temp);
    }

    cout<<endl;
    for(int i=0;i<n;i++){
        vector<int>temp;
        for(int j=0;j<m;j++)
        {
            int val = (max[i][j] -  allocation[i][j]);
            temp.push_back(val);
        }
        res_needed.push_back(temp);
    }

    checkSafe(n, m,allocation,res_available,res_needed,false);
    for(int i=0;i<m;i++){
        res_available[i]=old_res_available[i];
    }

    int pi;
    cout<<"Enter the process id  for new process( 0 indexed) : ";
    cin>>pi;
    cout<<endl;
    cout<<"Enter the number of required instances for each resource type (space seperated): ";
    cout<<endl;

    for(int i=0;i<m;i++){
        int ele;
        cin >>ele;
        request.push_back(ele);
    }

    cout <<endl;
    for(int i=0;i<m;i++)
    {
        if(request[i]>res_needed[pi][i])
        {
            cout<<"Error! At resource index "<<i<<" request is more than needed"<<endl;
            exit(1);
        }

        if(res_available[i]<request[i])
        {
            cout<<"Error! At resource index "<<i<<" request is more than the available resource"<<endl;
            exit(1);            
        }
    }



    for(int i=0;i<m;i++)
    {    
        res_needed[pi][i] = res_needed[pi][i] - request[i];
        res_available[i] = res_available[i] - request[i];
        allocation[pi][i] = allocation[pi][i] + request[i];
    }

    checkSafe(n, m,allocation,res_available,res_needed,false);
    return 0;
}