#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR (-1)
#define MONOTONY_OPT "-monotony\0"
#define RANGES_OPT "-ranges\0"
#define DEF_NAME "Student\0"
#define MAX_NAME_LEN 8
#define FIRST_CODE 97
#define LAST_CODE 122

int main(int argc, const char **argv)
{
	int sz, i, j, monotony = 0, ranges = 0, len;
	const char *filename;
	char buff[MAX_NAME_LEN];
	FILE *out;

	if( (argc!=3 || (sz = atoi(argv[2]))<=0) && (argc!=4 || (sz = atoi(argv[2]))<=0 || ( !(monotony = (strcmp(argv[3], MONOTONY_OPT)==0)) && !(ranges = (strcmp(argv[3], RANGES_OPT)==0)) )) )
	{
		fprintf(stderr, "Usage:\t%s filename size [%s | %s]\n", argv[0], MONOTONY_OPT, RANGES_OPT);
		return ERROR;
	}
	filename = argv[1];

	if( !(out = fopen(filename, "w")) )
	{
		fprintf(stderr, "Can not open %s!\n", filename);
		return ERROR;
	}

	if( monotony )
	{
		for( i = 0; i<sz; i++ )
			fprintf(out, "%s\t%d\n", DEF_NAME, i);

		fclose(out);
		return 0;
	}

	if( ranges )
	{
		int value, width, max_width, diff;

		for( i = 8*sizeof(int) - 1; i>=0; i-- )
		{
			if( sz&(1<<i) )
			{
				diff = 1<<i;
				break;
			}
		}

		fprintf(out, "%s\t%d\n", DEF_NAME, 0);
		width = 1;
		max_width = 2;
		value = -diff/2;
		for( i = 1; i<sz; i++ )
		{
			fprintf(out, "%s\t%d\n", DEF_NAME, value);
			width++;
			if( width>max_width )
			{
				diff /= 2;
				width = 1;
				max_width *= 2;
				value = -value - diff/2;
				continue;
			}
			value += diff;
		}

		fclose(out);
		return 0;
	}

	for( i = 0; i<sz; i++ )
	{
		len = rand()%MAX_NAME_LEN + 1;

		for( j = 0; j<(len - 1); j++ )
			buff[j] = (char)(FIRST_CODE + rand()%(LAST_CODE - FIRST_CODE + 1));
		buff[len] = '\0';

		fprintf(out, "%s\t%d\n", buff, rand());
	}

	fclose(out);

	return 0;
}
