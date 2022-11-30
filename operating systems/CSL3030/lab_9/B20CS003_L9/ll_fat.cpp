#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
using namespace std;

int cur_dir;
int prev_dir;
struct directory
{
	string name;
	int index;
};

struct block1
{
	int *fat;
};

struct block2
{
	vector<directory> dir;
};

struct block
{
	char *data;
};

struct super_block
{
	int file_size, block_size, n_blocks, n_files;
	int *free_block;
	string name;
	block2 *ptr;
};

struct file_sys
{
	super_block sp;
	block1 b1;
	block2 b2;
	block *b;
};

struct FD_t
{
	int valid;
	int dir_no;
	int my_no;
	int current_block;
	int current_offset;
	int current_wblock;
	int current_woffset;
};

int file_size, block_size, n_blocks;
file_sys file;
vector<FD_t> FD;

void init(int a, int b, int c)
{
	::file_size = a;
	::block_size = b;
	::n_blocks = c;

	int i;

	file.b = (block *)malloc((::n_blocks - 3) * sizeof(block));

	for (i = 0; i < (::n_blocks)-3; i++)
		file.b[i].data = (char *)malloc(::block_size * 1024 * sizeof(char));

	file.sp.file_size = ::file_size;
	file.sp.block_size = ::block_size;
	file.sp.n_blocks = ::n_blocks;
	file.sp.n_files = 0;
	file.sp.name = "FAT";
	file.sp.free_block = (int *)malloc(::n_blocks * sizeof(int));
	file.b1.fat = (int *)malloc((::n_blocks - 3) * sizeof(int));
	file.sp.ptr = &(file.b2);
	int blocksbyfat = sizeof(file.b1.fat) / ::block_size;

	file.sp.free_block[0] = 1;
	file.sp.free_block[1] = 1;
	file.sp.free_block[2] = 1;
	int j;
	for (j = 0; j < blocksbyfat - 1; j++)
		file.sp.free_block[3 + j] = 1;

	for (i = j; i < (::n_blocks); i++)
		file.sp.free_block[i] = 0;

	for (i = 0; i < (::n_blocks)-3; i++)
		file.b1.fat[i] = -1;

	cur_dir = 0;
    prev_dir = -1;
}

int my_open(string str)
{
	if (file.sp.n_files)
	{
		int i;
		int found_location = -1;
		for (i = 0; i < file.b2.dir.size(); i++)
		{
			directory d = file.b2.dir[i];
			if (d.name == str)
			{
				found_location = i;
				break;
			}
		}
		if (found_location != -1)
		{
			for (int i = 0; i < FD.size(); i++)
			{
				if (FD[i].valid == 0)
				{
					FD[i].valid = 1;
					FD[i].dir_no = found_location;
					FD[i].current_block = file.b2.dir[found_location].index;
					FD[i].current_offset = 0;
					FD[i].current_wblock = file.b2.dir[found_location].index;
					FD[i].current_woffset = 0;
					FD[i].my_no = i;
					return i;
				}
			}
			FD_t tempfd;
			tempfd.valid = 1;
			tempfd.dir_no = found_location;
			tempfd.current_block = file.b2.dir[found_location].index;
			tempfd.current_offset = 0;
			tempfd.current_wblock = file.b2.dir[found_location].index;
			tempfd.current_woffset = 0;
			tempfd.my_no = FD.size();
			FD.push_back(tempfd);
			return (tempfd.my_no);
		}
	}

	int n = file.sp.n_files;
	int r;
	do
	{
		r = rand() % (file.sp.n_blocks - 3);
	} while (file.sp.free_block[r + 3] != 0);

	directory d;
	d.name = str;
	d.index = r;
	file.b2.dir.push_back(d);
	file.sp.n_files++;
	file.sp.free_block[r + 3] = 1;

	for (int i = 0; i < FD.size(); i++)
	{
		if (FD[i].valid == 0)
		{
			FD[i].valid = 1;
			FD[i].dir_no = file.b2.dir.size() - 1;
			FD[i].current_block = file.b2.dir[file.b2.dir.size() - 1].index;
			FD[i].current_offset = 0;
			FD[i].current_wblock = file.b2.dir[file.b2.dir.size() - 1].index;
			FD[i].current_woffset = 0;
			FD[i].my_no = i;
			return i;
		}
	}
	FD_t tempfd;
	tempfd.valid = 1;
	tempfd.dir_no = file.b2.dir.size() - 1;
	tempfd.current_block = file.b2.dir[tempfd.dir_no].index;
	tempfd.current_offset = 0;
	tempfd.current_wblock = file.b2.dir[tempfd.dir_no].index;
	tempfd.current_woffset = 0;
	tempfd.my_no = FD.size();

	FD.push_back(tempfd);
	return (tempfd.my_no);
}

int my_read(int fd, char *buf, int count)
{
	if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
	{
		return -1;
	}
	int i = 0;
	int bufpointer = 0;
	for (i; i < count; i++)
	{
		buf[bufpointer++] = file.b[FD[fd].current_block].data[FD[fd].current_offset];
		if (buf[bufpointer - 1] == '\0')
			break;
		FD[fd].current_offset++;
		if (FD[fd].current_offset >= block_size)
		{
			if (file.b1.fat[FD[fd].current_block] == -1)
			{
				break;
			}
			else
			{
				int nextblock = file.b1.fat[FD[fd].current_block];
				FD[fd].current_block = nextblock;
				FD[fd].current_offset = 0;
				if (file.sp.free_block[nextblock + 3] == 0)
					break;
				continue;
			}
		}
	}
	return bufpointer;
}

int my_write(int fd, const char *buf, size_t count)
{
	if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
	{
		return -1;
	}
	int i = 0;
	int bufpointer = 0;
	for (i; i < count; i++)
	{
		file.b[FD[fd].current_wblock].data[FD[fd].current_woffset] = buf[bufpointer++];
		if (buf[bufpointer - 1] == '\0')
			break;
		file.sp.free_block[FD[fd].current_wblock + 3] = 1;
		FD[fd].current_woffset++;
		if (FD[fd].current_woffset >= block_size)
		{
			if (file.b1.fat[FD[fd].current_wblock] == -1)
			{
				int r;
				do
				{
					r = rand() % (file.sp.n_blocks - 3);
				} while (file.sp.free_block[r + 3] != 0);
				file.b1.fat[FD[fd].current_wblock] = r;
				FD[fd].current_wblock = r;
				FD[fd].current_woffset = 0;
				continue;
			}
			else
			{
				int nextblock = file.b1.fat[FD[fd].current_wblock];
				FD[fd].current_wblock = nextblock;
				FD[fd].current_woffset = 0;
				continue;
			}
		}
	}
	return bufpointer;
}

int my_close(int fd)
{
	if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
	{
		return -1;
	}
	else
	{
		FD[fd].valid = 0;
		return 1;
	}
}

int my_copy(int fd, int linuxfd, int flag)
{
	if (flag == 0)
	{
		if (fd >= FD.size() || fd < 0 || FD[fd].valid == 0)
		{
			return -1;
		}
		int i = 0;
		int bufpointer = 0;
		int on = 1;
		char ch[1];
		int c;
		while (on)
		{
			c = read(linuxfd, ch, 1);
			if (c < 1)
				break;
			file.b[FD[fd].current_wblock].data[FD[fd].current_woffset] = ch[0];
			file.sp.free_block[FD[fd].current_wblock + 3] = 1;
			FD[fd].current_woffset++;
			if (FD[fd].current_woffset >= block_size)
			{
				if (file.b1.fat[FD[fd].current_wblock] == -1)
				{
					int r;
					do
					{
						r = rand() % (file.sp.n_blocks - 3);
					} while (file.sp.free_block[r + 3] != 0);
					file.b1.fat[FD[fd].current_wblock] = r;
					FD[fd].current_wblock = r;
					FD[fd].current_woffset = 0;
					continue;
				}
				else
				{
					int nextblock = file.b1.fat[FD[fd].current_wblock];
					FD[fd].current_wblock = nextblock;
					FD[fd].current_woffset = 0;
					continue;
				}
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
		int i = 0;
		int bufpointer = 0;
		int c;
		char ch;
		while (1)
		{
			ch = file.b[FD[fd].current_block].data[FD[fd].current_offset];
			if (ch == '\0')
				break;
			c = write(linuxfd, &ch, 1);
			if (c < 1)
				break;
			FD[fd].current_offset++;
			if (FD[fd].current_offset >= block_size)
			{
				if (file.b1.fat[FD[fd].current_block] == -1)
				{
					break;
				}
				else
				{
					int nextblock = file.b1.fat[FD[fd].current_block];
					FD[fd].current_block = nextblock;
					FD[fd].current_offset = 0;
					if (file.sp.free_block[nextblock + 3] == 0)
						break;
					continue;
				}
			}
		}
		return bufpointer;
	}
	else
	{
		return -1;
	}
}

int main()
{
	srand(time(NULL));
	int exit = 0;
	string option;
	string filename;
	int i, file_size, block_size, n_blocks;
	char dir[14];

	while (exit != 1)
	{
		cout << endl;
		cout<<"________________________________\n";
		cout << "COMMAND_LIST : " << endl;
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

			cout << "Enter filename: ";
			cin >> filename;

			cout << "Enter file size in MB: ";
			cin >> file_size;
			cout << "Enter block size in KB: ";
			cin >> block_size;

			n_blocks = (file_size * 1024) / block_size;
			init(file_size, block_size, n_blocks);
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
			char readFile[7];
			my_read(fd, readFile, 7);
			cout << "Content in File " << filename << ":\n"
				 << readFile << endl;
		}
		else if (option == "my_write")
		{
			int fd = my_open(filename);

			char writeFile[1000];
			cout << "Enter content to write in file: ";
			cin >> writeFile;
			my_write(fd, writeFile, strlen(writeFile));
			cout << "Data written in file !!" << endl;
		}
		else if (option == "my_mkdir")
        {
			cout << "Enter directory name: ";
			cin >> dir;
            //my_mkdir(dir);
			cout<<"Directory created !!"<<endl;
        }
        else if (option == "my_chdir")
        {
			cout << "Enter directory name: ";
			cin >> dir;
			cout << "Directory changed !!" << endl;
        }
        else if (option == "my_rmdir")
        {
			cout << "Enter directory name: ";
			cin >> dir;
			cout << "Directory removed !!" << endl;
        }
		else if (option == "my_copy")
		{
			int fd = my_open(filename);
			string newfilename = filename + ".txt";
			char newfileName[100];
			strcpy(newfileName, newfilename.c_str());
			int linuxfd = open(newfileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			my_copy(fd, linuxfd, 1);
			cout << "File copied between Linux file system our file system !!" << endl;
			cout << "Filename is file.txt" << endl;
		}
	}
	return 0;
}