#include <bits/stdc++.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define SAME_DIR -5
#define REGULAR 1
#define DIRECTORY 2

using namespace std;

int cur_dir;
int prev_dir;

struct super_block
{
    long long int file_sys_size, block_size, n_blocks, n_inodes;
    char name[6];
    int first_free_block;
    bool *free_inode;
};

struct inode
{
    int type;
    int last_data_block;
    vector<int> dp;
    int sip;
    int dip;
};

struct block1
{
    inode *iNode;
};

struct data_block
{
    int next;
    char *data;
};

struct file_sys
{
    super_block sp;
    block1 b_inode;
    data_block *b;
};

struct FD_t
{
    int valid;
    int dir_inode_no;
    int inode_no;

    int indirection_type;
    int directoffset;
    int index_sip;
    int index_dip1;
    int index_dip2;

    int windirection_type;
    int wdirectoffset;
    int windex_sip;
    int windex_dip1;
    int windex_dip2;

    int current_block;
    int current_offset;
    int current_wblock;
    int current_woffset;
};

long long int file_size, block_size, n_blocks;
file_sys file;
vector<FD_t> FD;

void init(long long int a, long long int b, long long int c)
{
    ::file_size = a;
    ::block_size = b;
    ::n_blocks = c;

    int i;

    file.sp.file_sys_size = a;
    file.sp.block_size = b;
    file.sp.n_blocks = c;
    file.sp.n_inodes = 2 * (b / sizeof(inode));
    strcpy(file.sp.name, "INODE");
    file.sp.first_free_block = 3;

    file.b_inode.iNode = (inode *)malloc(file.sp.n_inodes * sizeof(inode));
    file.sp.free_inode = (bool *)malloc(file.sp.n_inodes * sizeof(bool));

    bool topush = true;

    for (i = 0; i < file.sp.n_inodes; i++)
        file.sp.free_inode[i] = true;

    file.b = (data_block *)malloc((c - 3) * sizeof(data_block));

    for (i = 0; i < (c - 3); i++)
    {
        file.b[i].next = i + 4;
        file.b[i].data = (char *)malloc((b * 1024) * sizeof(char));
        for (int j = 0; j < 1024; j++)
            file.b[i].data[j] = '\0';
    }

    file.sp.free_inode[0] = false;

    int tp = -1;
    file.b_inode.iNode[0].dp.resize(5, tp);
    file.b_inode.iNode[0].dp[0] = SAME_DIR;
    file.b_inode.iNode[0].dp[1] = file.sp.first_free_block;
    file.sp.first_free_block = file.b[file.sp.first_free_block - 3].next;
    file.b_inode.iNode[0].sip = file.b_inode.iNode[0].dip = -1;
    cur_dir = 0;
    prev_dir = -1;
}

int getpointertonextentry(int inodeno, int moveby, int *currentdatablockno, int *currentdatablockoffset, int *indirectiontype, int *directoffset, int *sipblockoffset, int *dipblockoffset1, int *dipblockoffset2)
{
    if (*currentdatablockoffset + moveby < block_size)
    {
        *currentdatablockoffset = *currentdatablockoffset + moveby;
        if (file.b[*(currentdatablockno)-3].data[*currentdatablockoffset] == '\0')
            return (-3);
        return (*indirectiontype);
    }
    else if (*currentdatablockno == file.b_inode.iNode[inodeno].last_data_block)
    {
        return -1;
    }
    else if (*indirectiontype == 0 && *directoffset < 4)
    {
        *directoffset++;
        *currentdatablockno = file.b_inode.iNode[inodeno].dp[*directoffset];
        *currentdatablockoffset = 0;
        return 0;
    }
    else if (*indirectiontype == 0 && *directoffset == 4)
    {
        *indirectiontype = 1;
        *sipblockoffset = 0;
        int *ptr = (int *)file.b[file.b_inode.iNode[inodeno].sip - 3].data;
        *currentdatablockno = *ptr;
        *currentdatablockoffset = 0;
        return (*indirectiontype);
    }
    else if (*indirectiontype == 1 && (*sipblockoffset + sizeof(int)) < block_size)
    {
        *sipblockoffset += sizeof(int);
        int *ptr = (int *)((char *)file.b[file.b_inode.iNode[inodeno].sip - 3].data + sizeof(int));
        *currentdatablockno = *ptr;
        *currentdatablockoffset = 0;
        return (*indirectiontype);
    }
    else if (*indirectiontype == 1 && (*sipblockoffset + sizeof(int)) >= block_size)
    {
        *indirectiontype = 2;
        *dipblockoffset1 = 0;
        *dipblockoffset2 = 0;
        int dipblockno = file.b_inode.iNode[inodeno].dip;
        int *tempptr = (int *)((char *)file.b[dipblockno - 3].data + *dipblockoffset1);
        int actualsearchinblock = *tempptr;
        int *tempptr2 = (int *)((char *)file.b[actualsearchinblock - 3].data + *dipblockoffset2);
        *currentdatablockno = *tempptr2;
        *currentdatablockoffset = 0;
        return (*indirectiontype);
    }
    else if (*indirectiontype == 2 && (*dipblockoffset2 + sizeof(int)) < block_size)
    {
        *dipblockoffset2 += sizeof(int);
        int dipblockno = file.b_inode.iNode[inodeno].dip;
        int *tempptr = (int *)((char *)file.b[dipblockno - 3].data + *dipblockoffset1);
        int actualsearchinblock = *tempptr;
        int *tempptr2 = (int *)((char *)file.b[actualsearchinblock - 3].data + *dipblockoffset2);
        *currentdatablockno = *tempptr2;
        *currentdatablockoffset = 0;
        return (*indirectiontype);
    }
    else if (*indirectiontype == 2 && (*dipblockoffset2 + sizeof(int)) >= block_size && (*dipblockoffset1 + sizeof(int)) < block_size)
    {
        *dipblockoffset1 += sizeof(int);
        *dipblockoffset2 = 0;
        int dipblockno = file.b_inode.iNode[inodeno].dip;
        int *tempptr = (int *)((char *)file.b[dipblockno - 3].data + *dipblockoffset1);
        int actualsearchinblock = *tempptr;
        int *tempptr2 = (int *)((char *)file.b[actualsearchinblock - 3].data + *dipblockoffset2);
        *currentdatablockno = *tempptr2;
        *currentdatablockoffset = 0;
        return (*indirectiontype);
    }
    else
    {
        return -2;
    }
}

int my_mkdir(char *str)
{
    if (!strcmp(str, ".") || !strcmp(str, ".."))
        return -1;

    int inodeno = cur_dir;
    int currentdatablockno;
    if (inodeno == 0)
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[1];
    else
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[2];

    int currentdatablockoffset = 0;
    int indirectiontype = 0;
    int directoffset = 0;
    int sipblockoffset = 0;
    int dipblockoffset1 = 0;
    int dipblockoffset2 = 0;

    int found = 0;
    int rv;
    int foundinodeno;

    do
    {
        char filename[15];
        for (int i = 0; i < 14; i++)
        {
            filename[i] = file.b[currentdatablockno - 3].data[currentdatablockoffset + i];
        }
        filename[14] = '\0';
        if (!strcmp(filename, str))
        {
            found = 1;
            int foundinodeno = *(short int *)(file.b[currentdatablockno - 3].data + (int)(currentdatablockoffset) + 14);
            break;
        }
        rv = getpointertonextentry(cur_dir, 16, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);
    } while (rv != -1 && rv != -3);

    if (found == 0)
    {
        if (currentdatablockoffset + 16 < block_size)
        {
            for (int i = 0; i < 14; i++)
            {
                file.b[currentdatablockno - 3].data[currentdatablockoffset + i] = str[i];
            }
        }
        short int freeinode = -1;
        for (int i = 0; i < file.sp.n_inodes; i++)
        {
            if (file.sp.free_inode[i] == true)
            {
                freeinode = (short int)i;
                break;
            }
        }
        if (freeinode == -1)
            return -1;
        file.b_inode.iNode[freeinode].dp.resize(5, -1);
        file.b_inode.iNode[freeinode].dp[0] = SAME_DIR;
        file.b_inode.iNode[freeinode].dp[1] = cur_dir;
        file.b_inode.iNode[freeinode].dp[2] = file.sp.first_free_block;
        file.b_inode.iNode[freeinode].last_data_block = file.sp.first_free_block;
        file.sp.first_free_block = file.b[file.sp.first_free_block - 3].next;
        file.sp.free_inode[freeinode] = false;
        char *ptr = file.b[currentdatablockno - 3].data + currentdatablockoffset + 14;

        sprintf(ptr, "%02hd", (short int)freeinode);
        for (int i = 0; i < 2; i++)
        {
            file.b[currentdatablockno].data[currentdatablockoffset + 14 + i] = ptr[i];
        }
    }
    else
    {
        cout << "Same name file/directory already exists in the current directory" << endl;
        return -1;
    }

	return 0;
}

int my_rmdir(char *str)
{
    if (!strcmp(str, ".") || !strcmp(str, ".."))
        return -1;

    int inodeno = cur_dir;
    int currentdatablockno;
    if (inodeno == 0)
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[1];
    else
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[2];

    int currentdatablockoffset = 0;
    int indirectiontype = 0;
    int directoffset = 0;
    int sipblockoffset = 0;
    int dipblockoffset1 = 0;
    int dipblockoffset2 = 0;

    int found = 0;
    int rv;
    int foundinodeno;
    do
    {
        char filename[15];
        for (int i = 0; i < 14; i++)
        {
            filename[i] = file.b[currentdatablockno - 3].data[currentdatablockoffset + i];
        }
        filename[14] = '\0';
        if (!strcmp(filename, str))
        {
            found = 1;
            int foundinodeno = *(short int *)(file.b[currentdatablockno - 3].data + (int)(currentdatablockoffset) + 14);
            break;
        }
        rv = getpointertonextentry(cur_dir, 16, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);
    } while (rv != -1 && rv != -3);

    int dirtodelete;

    if (found == 1)
    {
        char ptr[3];
        for (int i = 0; i < 2; i++)
        {
            ptr[i] = file.b[currentdatablockno].data[currentdatablockoffset + 14 + i];
        }

        ptr[2] = '\0';

        dirtodelete = atoi(ptr);
        for (int i = 0; i < 16; i++)
            file.b[currentdatablockno - 3].data[currentdatablockoffset + i] = -2;
        int inodeno1 = dirtodelete;
        int _currentdatablockno;
        if (inodeno1 == 0)
            _currentdatablockno = file.b_inode.iNode[inodeno1].dp[1];
        else
            _currentdatablockno = file.b_inode.iNode[inodeno1].dp[2];
        int _currentdatablockoffset = 0;
        int _indirectiontype = 0;
        int _directoffset = 0;
        int _sipblockoffset = 0;
        int _dipblockoffset1 = 0;
        int _dipblockoffset2 = 0;

        int rv;
        int foundinodeno;
        do
        {
            for (int i = 0; i < 16; i++)
                file.b[_currentdatablockno - 3].data[_currentdatablockoffset + i] = -2;
            rv = getpointertonextentry(inodeno1, 16, &_currentdatablockno, &_currentdatablockoffset, &_indirectiontype, &_directoffset, &_sipblockoffset, &_dipblockoffset1, &_dipblockoffset2);
        } while (rv != -1 && rv != -3);

        return cur_dir;
    }
    else
    {
        cout << "Same name file/directory does not exist in the current directory" << endl;
        return -1;
    }
}

int my_chdir(char *str)
{
    if (!strcmp(str, "."))
        return cur_dir;

    if (!strcmp(str, ".."))
    {
        int a = cur_dir;
        cur_dir = (prev_dir == -1) ? -1 : prev_dir;
        if (cur_dir == -1)
        {
            cur_dir = a;
            cout << "This is home directory" << endl;
            return cur_dir;
        }
        prev_dir = file.b_inode.iNode[cur_dir].dp[1];
    }
    int inodeno = cur_dir;
    int currentdatablockno;
    if (inodeno == 0)
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[1];
    else
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[2];

    int currentdatablockoffset = 0;
    int indirectiontype = 0;
    int directoffset = 0;
    int sipblockoffset = 0;
    int dipblockoffset1 = 0;
    int dipblockoffset2 = 0;

    int found = 0;
    int rv;
    int foundinodeno;

    do
    {
        char filename[15];
        for (int i = 0; i < 14; i++)
        {
            filename[i] = file.b[currentdatablockno - 3].data[currentdatablockoffset + i];
        }
        filename[14] = '\0';
        if (!strcmp(filename, str))
        {
            found = 1;
            int foundinodeno = *(short int *)(file.b[currentdatablockno - 3].data + (int)(currentdatablockoffset) + 14);
            break;
        }
        rv = getpointertonextentry(cur_dir, 16, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);
    } while (rv != -1 && rv != -3);

    if (found == 1)
    {
        prev_dir = cur_dir;
        char ptr[3];
        for (int i = 0; i < 2; i++)
        {
            ptr[i] = file.b[currentdatablockno].data[currentdatablockoffset + 14 + i];
        }
        ptr[2] = '\0';

        cur_dir = atoi(ptr);

        return cur_dir;
    }
    else
    {
        cout << "Same name file/directory does not exist in the current directory" << endl;
        return -1;
    }
}

int my_open(char *str)
{
    int inodeno = cur_dir;
    int currentdatablockno;
    if (cur_dir == 0)
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[1];
    else
        currentdatablockno = file.b_inode.iNode[cur_dir].dp[2];
    int currentdatablockoffset = 0;
    int indirectiontype = 0;
    int directoffset = 0;
    int sipblockoffset = 0;
    int dipblockoffset1 = 0;
    int dipblockoffset2 = 0;

    int found = 0;
    int rv;
    int foundinodeno;
    do
    {
        char filename[15];
        for (int i = 0; i < 14; i++)
        {
            filename[i] = file.b[currentdatablockno - 3].data[currentdatablockoffset + i];
        }
        filename[14] = '\0';
        if (!strcmp(filename, str))
        {
            found = 1;
            int foundinodeno = *(short int *)(file.b[currentdatablockno - 3].data + (int)(currentdatablockoffset) + 14);
            break;
        }
        rv = getpointertonextentry(cur_dir, 16, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);
    } while (rv != -1 && rv != -3);

    if (found == 0)
    {
        for (int j = 0; j < FD.size(); j++)
        {
            if (FD[j].valid == 0)
            {
                FD[j].valid = 1;

                short int freeinode = -1;
                for (int i = 0; i < file.sp.n_inodes; i++)
                {
                    if (file.sp.free_inode[i] == true)
                    {
                        freeinode = (short int)i;
                        break;
                    }
                }

                if (freeinode == -1)
                    return -1;
                FD[j].inode_no = freeinode;
                file.b_inode.iNode[freeinode].dp.resize(5, -1);
                file.b_inode.iNode[freeinode].dp[0] = file.sp.first_free_block;
                file.b_inode.iNode[freeinode].last_data_block = file.sp.first_free_block;
                file.sp.first_free_block = file.b[file.sp.first_free_block - 3].next;
                file.sp.free_inode[freeinode] = false;
                FD[j].current_block = file.b_inode.iNode[freeinode].dp[0];
                FD[j].current_offset = 0;
                FD[j].current_wblock = file.b_inode.iNode[freeinode].dp[0];
                FD[j].current_woffset = 0;
                return j;
            }
        }
        FD_t tempfd;
        tempfd.valid = 1;
        short int freeinode = -1;
        int i;
        for (i = 0; i < file.sp.n_inodes; i++)
        {
            if (file.sp.free_inode[i] == true)
            {
                freeinode = (short int)i;
                break;
            }
        }

        if (freeinode == -1)
            return -1;

        tempfd.inode_no = freeinode;
        file.b_inode.iNode[freeinode].dp.resize(5, -1);
        file.b_inode.iNode[freeinode].dp[0] = file.sp.first_free_block;
        file.b_inode.iNode[freeinode].last_data_block = file.sp.first_free_block;

        tempfd.current_block = file.b_inode.iNode[freeinode].dp[0];
        tempfd.current_offset = 0;

        file.sp.first_free_block = file.b[file.sp.first_free_block - 3].next;
        file.sp.free_inode[freeinode] = false;

        tempfd.current_wblock = file.b_inode.iNode[freeinode].dp[0];
        tempfd.current_woffset = 0;

        FD.push_back(tempfd);
        return (FD.size() - 1);
    }
    else
    {

        int i;
        for (i = 0; i < FD.size(); i++)
        {
            if (FD[i].valid == 0)
            {
                FD[i].valid = 1;
                short int freeinode = foundinodeno;
                FD[i].inode_no = freeinode;

                file.b_inode.iNode[freeinode].dp.resize(5, -1);
                file.b_inode.iNode[freeinode].dp[0] = file.sp.first_free_block;

                FD[i].current_block = file.b_inode.iNode[freeinode].dp[0];
                file.b_inode.iNode[freeinode].dp[0] = file.sp.first_free_block;
                file.b_inode.iNode[freeinode].last_data_block = file.sp.first_free_block;
                file.sp.first_free_block = file.b[file.sp.first_free_block - 3].next;
                file.sp.free_inode[freeinode] = false;
                FD[i].current_offset = 0;
                FD[i].current_wblock = file.b_inode.iNode[freeinode].dp[0];
                FD[i].current_woffset = 0;
                return i;
            }
        }
        FD_t tempfd;
        tempfd.valid = 1;

        short int freeinode = foundinodeno;

        FD[i].inode_no = freeinode;
        file.b_inode.iNode[freeinode].dp.resize(5, -1);
        file.b_inode.iNode[freeinode].dp[0] = file.sp.first_free_block;
        file.b_inode.iNode[freeinode].last_data_block = file.sp.first_free_block;

        tempfd.current_block = file.b_inode.iNode[freeinode].dp[0];
        tempfd.current_offset = 0;

        file.sp.first_free_block = file.b[file.sp.first_free_block - 3].next;
        file.sp.free_inode[freeinode] = false;

        tempfd.current_wblock = file.b_inode.iNode[freeinode].dp[0];
        tempfd.current_woffset = 0;

        FD.push_back(tempfd);
        return (FD.size() - 1);
    }
}

int my_read(int fd, char *buf, int count)
{
    int inodeno = FD[fd].inode_no;
    int currentdatablockno = FD[fd].current_block;
    int currentdatablockoffset = FD[fd].current_offset;
    int indirectiontype = FD[fd].indirection_type;
    int directoffset = FD[fd].directoffset;
    int sipblockoffset = FD[fd].index_sip;
    int dipblockoffset1 = FD[fd].index_dip1;
    int dipblockoffset2 = FD[fd].index_dip2;

    if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
    {
        return -1;
    }

    int i;
    int bufpointer = 0;
    for (i = 0; i < count; i++)
    {
        buf[bufpointer++] = file.b[FD[fd].current_block - 3].data[FD[fd].current_offset];
        if (buf[bufpointer - 1] == '\0')
            break;

        indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

        FD[fd].current_block = currentdatablockno;
        FD[fd].current_offset = currentdatablockoffset;
        FD[fd].indirection_type = indirectiontype;
        FD[fd].directoffset = directoffset;
        FD[fd].index_sip = sipblockoffset;
        FD[fd].index_dip1 = dipblockoffset1;
        FD[fd].index_dip2 = dipblockoffset2;

        if (indirectiontype == -2)
            return -1;
        if (indirectiontype == -1)
        {
            int freeblock = file.sp.first_free_block;
            file.sp.first_free_block = file.b[freeblock - 3].next;

            if (directoffset < 4)
            {
                file.b_inode.iNode[inodeno].dp[directoffset + 1] = freeblock;
            }
            file.b_inode.iNode[inodeno].last_data_block = freeblock;

            indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

            FD[fd].current_block = currentdatablockno;
            FD[fd].current_offset = currentdatablockoffset;
            FD[fd].indirection_type = indirectiontype;
            FD[fd].directoffset = directoffset;
            FD[fd].index_sip = sipblockoffset;
            FD[fd].index_dip1 = dipblockoffset1;
            FD[fd].index_dip2 = dipblockoffset2;
        }
    }
    buf[bufpointer] = '\0';
    return bufpointer;
}

int my_write(int fd, char *buf, int count)
{
    int inodeno = FD[fd].inode_no;
    int currentdatablockno = FD[fd].current_wblock;
    int currentdatablockoffset = FD[fd].current_woffset;
    int indirectiontype = FD[fd].windirection_type;
    int directoffset = FD[fd].wdirectoffset;
    int sipblockoffset = FD[fd].windex_sip;
    int dipblockoffset1 = FD[fd].windex_dip1;
    int dipblockoffset2 = FD[fd].windex_dip2;

    if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
    {
        return -1;
    }

    int i;
    int bufpointer = 0;
    for (i = 0; i < count; i++)
    {
        if (file.sp.block_size - currentdatablockoffset >= 1)
        {

            file.b[FD[fd].current_block - 3].data[FD[fd].current_woffset] = buf[bufpointer++];
            if (buf[bufpointer - 1] == '\0')
                break;
            indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

            FD[fd].current_wblock = currentdatablockno;
            FD[fd].current_woffset = currentdatablockoffset;
            FD[fd].windirection_type = indirectiontype;
            FD[fd].wdirectoffset = directoffset;
            FD[fd].windex_sip = sipblockoffset;
            FD[fd].windex_dip1 = dipblockoffset1;
            FD[fd].windex_dip2 = dipblockoffset2;

            if (indirectiontype == -2)
                return -1;
        }
        else
        {
            int freeblock = file.sp.first_free_block;
            file.sp.first_free_block = file.b[freeblock - 3].next;

            if (directoffset < 4)
            {
                file.b_inode.iNode[inodeno].dp[directoffset + 1] = freeblock;
            }
            file.b_inode.iNode[inodeno].last_data_block = freeblock;

            file.b[FD[fd].current_block - 3].data[FD[fd].current_woffset] = buf[bufpointer++];
            if (buf[bufpointer - 1] == '\0')
                break;
            indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

            FD[fd].current_wblock = currentdatablockno;
            FD[fd].current_woffset = currentdatablockoffset;
            FD[fd].windirection_type = indirectiontype;
            FD[fd].wdirectoffset = directoffset;
            FD[fd].windex_sip = sipblockoffset;
            FD[fd].windex_dip1 = dipblockoffset1;
            FD[fd].windex_dip2 = dipblockoffset2;

            if (indirectiontype == -2)
                return -1;
        }
    }
    return bufpointer;
}

int my_close(int fd)
{
    int inodeno = cur_dir;
    int currentdatablockno = file.b_inode.iNode[cur_dir].dp[1];
    int currentdatablockoffset = 0;
    int indirectiontype = 0;
    int directoffset = 0;
    int sipblockoffset = 0;
    int dipblockoffset1 = 0;
    int dipblockoffset2 = 0;

    if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
    {
        return -1;
    }

    FD[fd].valid = 0;
    return 1;
}

int my_copy(int fd, int linuxfd, int flag)
{
    if (flag == 0)
    {

        if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
        {
            return -1;
        }

        char ch;
        int c;
        int bufpointer = 0;

        int inodeno = FD[fd].inode_no;
        int currentdatablockno = FD[fd].current_wblock;
        int currentdatablockoffset = FD[fd].current_woffset;
        int indirectiontype = FD[fd].windirection_type;
        int directoffset = FD[fd].wdirectoffset;
        int sipblockoffset = FD[fd].windex_sip;
        int dipblockoffset1 = FD[fd].windex_dip1;
        int dipblockoffset2 = FD[fd].windex_dip2;

        while (1)
        {
            c = read(linuxfd, &ch, 1);
            bufpointer += c;
            if (c < 1)
                break;

            if (file.sp.block_size - currentdatablockoffset >= 1)
            {

                file.b[FD[fd].current_block - 3].data[FD[fd].current_woffset] = ch;
                indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

                FD[fd].current_wblock = currentdatablockno;
                FD[fd].current_woffset = currentdatablockoffset;
                FD[fd].windirection_type = indirectiontype;
                FD[fd].wdirectoffset = directoffset;
                FD[fd].windex_sip = sipblockoffset;
                FD[fd].windex_dip1 = dipblockoffset1;
                FD[fd].windex_dip2 = dipblockoffset2;

                if (indirectiontype == -2)
                    return -1;
            }
            else
            {
                int freeblock = file.sp.first_free_block;
                file.sp.first_free_block = file.b[freeblock - 3].next;

                if (directoffset < 4)
                {
                    file.b_inode.iNode[inodeno].dp[directoffset + 1] = freeblock;
                }
                file.b_inode.iNode[inodeno].last_data_block = freeblock;

                file.b[FD[fd].current_block - 3].data[FD[fd].current_woffset] = ch;

                indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

                FD[fd].current_wblock = currentdatablockno;
                FD[fd].current_woffset = currentdatablockoffset;
                FD[fd].windirection_type = indirectiontype;
                FD[fd].wdirectoffset = directoffset;
                FD[fd].windex_sip = sipblockoffset;
                FD[fd].windex_dip1 = dipblockoffset1;
                FD[fd].windex_dip2 = dipblockoffset2;

                if (indirectiontype == -2)
                    return -1;
            }
        }
        return bufpointer;
    }

    else if (flag == 1)
    {
        if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
        {
            return -1;
        }

        char ch;
        int c;
        int bufpointer = 0;

        int inodeno = FD[fd].inode_no;
        int currentdatablockno = file.b_inode.iNode[FD[fd].inode_no].dp[0];
        int currentdatablockoffset = 0;
        int indirectiontype = 0;
        int directoffset = 0;
        int sipblockoffset = 0;
        int dipblockoffset1 = 0;
        int dipblockoffset2 = 0;

        while (1)
        {
            ch = file.b[currentdatablockno - 3].data[currentdatablockoffset];
            if (ch == '\0')
                break;
            c = write(linuxfd, &ch, 1);
            bufpointer += 1;
            if (c < 1)
                break;

            indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);

            if (indirectiontype == -2)
                return -1;
            if (indirectiontype == -1)
            {
                int freeblock = file.sp.first_free_block;
                file.sp.first_free_block = file.b[freeblock - 3].next;

                if (directoffset < 4)
                {
                    file.b_inode.iNode[inodeno].dp[directoffset + 1] = freeblock;
                }
                file.b_inode.iNode[inodeno].last_data_block = freeblock;

                indirectiontype = getpointertonextentry(inodeno, 1, &currentdatablockno, &currentdatablockoffset, &indirectiontype, &directoffset, &sipblockoffset, &dipblockoffset1, &dipblockoffset2);
                continue;
            }
        }
        return bufpointer;
    }
    else
        return -1;
}

int main()
{
    srand(time(NULL));
    int exit = 0;
    string option;
    int i, file_size, block_size, n_blocks;
    char dir[14];
    char filename[100];

    while (exit != 1)
    {
        cout << endl;
        cout << "Enter the follow : " << endl;
        cout << "my_open" << endl;
        cout << "my_close" << endl;
        cout << "my_read" << endl;
        cout << "my_write" << endl;
        cout << "my_mkdir" << endl;
        cout << "my_chdir" << endl;
        cout << "my_rmdir" << endl;
        cout << "my_copy" << endl;
        cout << "1 : for exit" << endl;
        cout << endl;
        cin >> option;

        if (option == "1")
        {
            exit = 1;
            cout << "Exiting...";
            return 0;
        }
        else if (option == "my_open")
        {
            cout << "Enter file size in MB: ";
            cin >> file_size;
            cout << "Enter block size in KB: ";
            cin >> block_size;

            n_blocks = (file_size * 1024) / block_size;
            init(file_size * 1024 * 1024, block_size * 1024, n_blocks);
            cout << "Enter filename: ";
            cin >> filename;
            int fd = my_open(filename);
            cout << "File opened !!" << endl;
        }
        else if (option == "my_close")
        {
            int fd = my_open(filename);
            my_close(fd);
            cout << "File closed !!" << endl;
        }
        else if (option == "my_read")
        {
            int fd = my_open(filename);
            char readFile[1000];
            my_read(fd, readFile, 1000);
            cout << "Content in File " << filename << ":\n"
                 << readFile << endl;
        }
        else if (option == "my_write")
        {
            int fd = my_open(filename);
            char writeFile[1000] ;
            cout << "Enter content to write in file: ";
            cin >> writeFile;
            my_write(fd, writeFile, strlen(writeFile));
            cout << "Data written in file !!" << endl;
        }
        else if (option == "my_mkdir")
        {   
            cout << "Enter directory name: ";
            cin >> dir;
            my_mkdir(dir);
            cout << "Directory Created with name dirName" << endl;
        }
        else if (option == "my_chdir")
        {
            my_chdir(dir);
            cout << "moved into directory with name dirName" << endl;
        }
        else if (option == "my_rmdir")
        {
            my_rmdir(dir);
            cout << "Directory removed with name dirName" << endl;
        }
        else if (option == "my_copy")
        {
            int fd = my_open(filename);
            string name = string(filename);
            string newfilename = name + ".txt";
            char newfileName[100];
            strcpy(newfileName, newfilename.c_str());
            int linuxfd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
            my_copy(fd, linuxfd, 1);
            cout << "File copied between Linux file system our file system !!" << endl;
            cout << "Filename is file.txt" << endl;
        }
    }
    return 0;
}