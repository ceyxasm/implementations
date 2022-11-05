#include <bits/stdc++.h>
using namespace std;
int num_process, vir_addr_space, phy_addr_space, tlb_size;
queue<pair<int, int>> lru;

int generate_pid(int n, vector<int> &terminated_processes)
{
    int pid= rand() % n + 1;
    while (find(terminated_processes.begin(), terminated_processes.end(), pid) != terminated_processes.end())
        pid = rand() % n + 1;
    return pid;
}

int page_count(int vas)
{
    return rand() % vas + 1;
}


vector<int> TLB_init(int tlb_size, int pages)
{
    vector<int> pages_in_tlb;
    while (pages_in_tlb.size() < tlb_size)
    {
        int x = rand() % pages + 1;
        if (find(pages_in_tlb.begin(), pages_in_tlb.end(), x) == pages_in_tlb.end())
            pages_in_tlb.push_back(x);
    }
    return pages_in_tlb;
}


vector<int> generate_reference_string( int pages_in_process, int vas) 
{
    int span = 8 * vas;
    int length = rand() % span + 2*vas; //length varying from 2*vas to 10*vas
    vector<int> reference_string;
    for (int i = 0; i < length; i++)
    {
        int page = rand() % pages_in_process + 1;
        reference_string.push_back(page);
    }
    return reference_string;
}


int main()
{
    printf("Enter total number of processes:\n ");
    cin>>num_process;
    printf("Enter virtual address space (total number of pages):\n ");
    cin>>vir_addr_space;
    printf("Enter physical address space (total number of frames):\n ");
    cin>>phy_addr_space;
    printf("Enter size of TLB:\n ");
    cin>>tlb_size;
    int tlb_content=0;

    vector<int> terminated_processes;
    int i = num_process;
    int total_page_faults=0;
    int total_page_hits=0;
    int total_tlb_hits=0;
    int total_tlb_misses=0;
    while (i > 0)
    {
        int pid = generate_pid(num_process, terminated_processes);
        int pages_in_process = page_count(vir_addr_space);
        terminated_processes.push_back(pid);
        int page_faults = 0, tlb_hits = 0, page_hits=0, pap = 0; //pap = page access pointer
        vector<bool> avilable_frames(phy_addr_space, true);

        printf("Process %d has %d pages\n", pid, pages_in_process);
        map<pair<int, int>, int> page_table, TLB;
        vector<int> pages_in_TLB = TLB_init(tlb_size, pages_in_process);
        vector<int> reference_string = generate_reference_string(pages_in_process, vir_addr_space);

        for (auto pg : reference_string)
        {
            // if in TLB
            if (TLB.find({pid, pg}) != TLB.end())
            {
                printf("page %d of process PID: %d found in TLB\n", pg, pid);
                lru.push({pid, pg});
                tlb_hits++;
            }

            // if not in TLB
            else
            {
                // if in page table
                if (page_table.find({pid, pg}) != page_table.end() && pap <= phy_addr_space)
                {
                    printf("page %d of process PID: %d found in page table\n", pg, pid);
                    avilable_frames[page_table[{pid, pg}]] = true;
                    lru.push({pid, pg});
                    page_hits++;

                    if (TLB.find({pid, pg}) == TLB.end()) //if not in TLB, put in TLB
                    {
                        tlb_content++;
                        if( tlb_content> tlb_size)
                        {
                            pair<int, int> temp = lru.front();
                            lru.pop();
                            TLB.erase(temp);
                            tlb_content--;
                        }
                        TLB[{pid, pg}] = page_table[{pid, pg}];
                        
                    }
                }

                // not in page table
                else
                {
                    page_faults++;
                    if (pap < phy_addr_space)
                    {
                        int frame = -1;
                        int i = 0;
                        while(i < phy_addr_space)  //finding available frame
                        {
                            if (avilable_frames[i])
                            {
                                frame = i;
                                break;
                            }
                            i++;
                        }

                        if (TLB.find({pid, pg}) == TLB.end()) //putting in TLB
                            {
                                tlb_content++;
                                if( tlb_content> tlb_size)
                                {
                                    pair<int, int> temp = lru.front();
                                    lru.pop();
                                    TLB.erase(temp);
                                    tlb_content--;
                                }
                                TLB[{pid, pg}] = frame;
                            }

                        pap++; //increasing ram size
                        if(pap> phy_addr_space)
                        {
                            pair<int, int> temp = lru.front();
                            lru.pop();
                            page_table.erase(temp);
                            pap--;
                        }
                        page_table[{pid, pg}] = frame; //putting in page table
                        avilable_frames[frame] = false;
                        printf("page %d of process PID: %d not found in page table, page fault occured, free frame: %d availabe and was allocated\n", pg, pid, frame);
                        lru.push({pid, pg});
                    }

                    else
                    {
                        pair<int, int> fr = lru.front();
                        int victim_pid = fr.first, victim_page = fr.second; //to be ejected
                        lru.pop();
                        int frame = page_table[{victim_pid, victim_page}]; //frame to be ejected
                        page_table.erase({victim_pid, victim_page}); //clearing the page table entry
                        TLB.erase({victim_pid, victim_page}); //clearing the TLB entry
                        page_table[{pid, pg}] = frame;
                        printf("page %d of process PID: %d not found in page table, page fault occured; moreover free frame was not available and Least recently used page was swapped\n", pg, pid);
                        lru.push({pid, pg});
                        if (TLB.find({pid, pg}) == TLB.end())
                        {
                                tlb_content++;
                                if( tlb_content> tlb_size)
                                {
                                    pair<int, int> temp = lru.front();
                                    lru.pop();
                                    TLB.erase(temp);
                                    tlb_content--;
                                }
                                TLB[{pid, pg}] = frame;
                        }
                    }
                }
            }
        }
        printf("\n\npage faults for process %d: %d\n", pid, page_faults);
        total_page_faults += page_faults;
        total_tlb_hits+=tlb_hits;
        total_page_hits+=page_hits;
        i--;
    }

    printf("\n\nTotal page faults: %d\n", total_page_faults);
    printf("Total page hits: %d\n", total_page_hits);
    printf("Total TLB hits: %d\n", total_tlb_hits);
    return 0;
}