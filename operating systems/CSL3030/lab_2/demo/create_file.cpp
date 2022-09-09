#include <bits/stdc++.h>
using namespace std;

static void appendLineToFile(string filepath, string line) 
{
    std::ofstream file;
    //can't enable exception now because of gcc bug that raises ios_base::failure with useless message
    //file.exceptions(file.exceptions() | std::ios::failbit);
    file.open(filepath, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(std::strerror(errno));

    //make sure write fails with exception if something is wrong
    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    file << line << std::endl;
}


int main(int argc, char* argv[])
{
	const char* fileptr= argv[1];
	string filename="";
	int i=0;
	while(fileptr[i++] ) filename+= fileptr[i-1];
	string line= "yup append this line gg";
	appendLineToFile( filename, line);

/////////////////////////

//
/*
    std::ofstream file;
    //can't enable exception now because of gcc bug that raises ios_base::failure with useless message
    //file.exceptions(file.exceptions() | std::ios::failbit);
    file.open(filename, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(std::strerror(errno));

    //make sure write fails with exception if something is wrong
    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);
	
    const char* line="kuch b karne ka";
    filename << line << std::endl;
*/
/////////////////////////



/*
	FILE *fp;
	fp = fopen( filename, "w"); //0 for read
				 //1 for write
				 //2 for both
*/	
	string bs="to be added in my file";
	/*
	if( fp <0) 
	{
		fp= create( filename, 'w');
	}
	n_written= write( fp, bs, bs.length());
	*/

	//filename<< bs<<endl;
//	fclose(fp);
	

	return 0;
}
