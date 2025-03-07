#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main ()
{
	int infile;
	int outfile;

	infile  = open("infile.txt", O_RDONLY);
	if(infile == -1)
		perror("Failed to open infile");
	outfile = open("outfile.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if(outfile == -1)
		perror("Failed to open outfile");
	printf("Before: infile[%d], outfile[%d]\n", infile, outfile);
	if (dup2(infile, outfile) == -1)
	{
		perror("dup2 failed");
		close(infile);
		close(outfile);
		return(1);
	}
	printf("After: infile[%d], outfile[%d]\n", infile, outfile);
	close(infile);
	close(outfile);
	return (0);
}
