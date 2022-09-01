#include <stdio.h>
#include <stdlib.h>
#include <combaseapi.h>
#include <sys/stat.h>

#include "fileintegrator.h"

/* References to the integrated binary file. */
extern unsigned char _binary_binres_test_bin_end;
extern unsigned char _binary_binres_test_bin_start;
extern unsigned char _binary_binres_test_bin_size;

/* Union to convert a long unsigned int to two unsigned shorts and make the two parts accessible. */
union Data
{
	long unsigned int a;
	unsigned short b[2];
};


int extractintegratedfile(){

	/* Declare start and end pointer. */
	unsigned char* pStart;
	unsigned char* pEnd;

	/* Declare file pointer to destination file. */
 	FILE *pFile;

	/* Declare field for the generated GUID. */
	char sGUID[40];

	/* Declare the destination path. */
	char path[MAX_PATH];

	/* Initialize the union to convert a long unsigned integer to two unsigned shorts. */
	union Data d;

	/* Declare the GUID. */
	GUID guid;

	/* Create a GUID. */
	CoCreateGuid(&guid);

	/* Fill the Data1 member into the union. */
	d.a = guid.Data1;

	/* Fill the character array with the data from the union and from the Guid */
	sprintf(sGUID, "%04x%04x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", d.b[0], d.b[1], guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	
	/* Copy the value of the %TEMP% environment variable to the character array referenced by the variable "path". */
	strcpy(path, getenv("TEMP"));

	/* Copy a trailing backslash to the character array referenced by the variable "path". */
	strcat(path, "\\");
	
	/* Copy the GUID string to the character array referenced by the variable "path". */
	strcat(path, sGUID);

	/* Create the directory. */
	mkdir(path);
	
	/* Print out the path */
	printf("%s directory created\n", path);

	/* Add a trailing backslash and the filename to the character array referenced by the variable "path". */
	strcat(path, "\\");
	strcat(path, "test.bin");

	/* Open and write the integrated (linked) binary file into the newly generated directory. */
	pFile = fopen(path, "wb");
	pEnd = &_binary_binres_test_bin_end;
	for (pStart = &_binary_binres_test_bin_start; pStart < pEnd; pStart++)
	{
		fwrite(pStart, 1, 1, pFile);
	}

	/* Close the file. */
	fclose(pFile);

	return EXIT_SUCCESS;
}