#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>

#include "utils.h"

#include <iostream>
using namespace std;
//#include "utils.h"

/* read VRML file info into two arrays for coordinate and normal vector information
   read info of indices of vectors forming polygons and corresponding normals
*/

/* Function to test for equal strings */
bool EQUALCHARSTRINGS(char* t, char* s) {
    int i = 0;
    bool equ = false;
    while (t[i] != '\0' && s[i] != '\0') {
        if (s[i] != t[i]) return false;
        i++;
    }
    if (t[i] == '\0' && s[i] == '\0')
        return true;
    return false;
}

/* Function to read next line, skipping white spaces*/
bool ReadNextLine(FILE* fp, char* line)
{
    int i = 0;
    char c;
    //cout << "readin FC" << fp;

    //int err = ferror(fp);
    //cout << err;
    c = getc(fp);



    while (c != EOF && c != '\n' && c != '{' && c != '[') {
        if (c != ' ' && c != '\t') {
            line[i] = c; i++;
        }
        // cout << "readin OTH FC";
        c = getc(fp);
    }
    if (c == EOF) return false;
    if (c == '{' || c == '[') {
        //cout << "oh god";
        line[i] = c; i++; getc(fp);
        //cout << "Not getting here";
    }
    line[i] = '\0';
    return true;
}

/* Actual ReadVRML file function */
int ReadVRML(const char* filename,
    GLfloat* coordinates, GLfloat* normals,
    GLint* indices, GLint* nindices,
    GLint* noofpoly, int MAXSHAPES, int MAXCOORDS)
{
    FILE* fp;          /* Open file pointer */

    char    line[500], c;
    int     i, j, temp;
    GLfloat* coords;
    GLint* ind, * nind;
    GLfloat* norms;

    // Try opening the file; use "rb" mode to read a binary file. 
    //cout << "reading";
    errno_t err = fopen_s(&fp, filename, "r");
    /*if ((fopen_s(&fp, filename, "r")) == NULL) {
        cout << "no exist";
        return 0;
    }*/
    //cout << "reading lines" << err;
    /*
    switch (errno) {
    case EACCES:
        cout << "Access";
        break;
    case EBADF:
        cout << "EBADF ";
            break;
    case EINTR:
        cout << "EINTR ";
            break;
    case EIO:
        cout << "EIO";
            break;
    case EISDIR:
        cout << "EISDIR ";
            break;
    case ENOMEM:
        cout << "ENOMEM ";
            break;
    case ENXIO:
        cout << "ENXIO ";
            break;
    case EOVERFLOW:
        cout << "EOVERFLOW ";
            break;
    case EWOULDBLOCK:
        cout << "EWOULDBLOCK ";
            break;
    }
    */

    if (!ReadNextLine(fp, line)) {
        //cout << "empty file";
        return 0; // file is empty
    }
    // Initialize coordinate arrays
    j = 0;
    coords = coordinates;
    ind = indices;
    nind = nindices;
    norms = normals;
    //cout << "the while";
    while (ReadNextLine(fp, line)) {
        std::string str = "point[";
        char* cstr = &str[0];
        std::string str2 = "Normal{";
        char* cstr2 = &str2[0];
        std::string str3 = "normalNormal{";
        char* cstr3 = &str3[0];
        std::string str4 = "coordIndex[";
        char* cstr4 = &str4[0];
        std::string str5 = "normalIndex[";
        char* cstr5 = &str5[0];
        if (EQUALCHARSTRINGS(line, cstr)) {//"point[")) {
            i = 0; c = ' ';
            while (c != ']') {
                fscanf_s(fp, "%f %f %f", &(coords[i]), &(coords[i + 1]), &coords[i + 2]);
                i = i + 3; c = getc(fp);
                if (c == EOF) return j + 1;
            }
        }
        else  if (EQUALCHARSTRINGS(line, cstr2) || EQUALCHARSTRINGS(line, cstr3))
        {
            ReadNextLine(fp, line);
            c = ' '; i = 0;
            while (c != ']') {
                fscanf_s(fp, "%f %f %f", &(norms[i]), &(norms[i + 1]), &norms[i + 2]);
                i = i + 3;
                c = getc(fp);
                if (c == EOF) return j + 1;
            }
        }
        else if (EQUALCHARSTRINGS(line, cstr4))
        {
            c = ' '; i = 0;
            noofpoly[j] = 0;
            while (c != ']') {
                fscanf_s(fp, "%d, %d, %d, %d", &(ind[i]), &(ind[i + 1]), &ind[i + 2], &temp);
                noofpoly[j]++;
                /* To calculate normal vectors using cross products
                GLfloat v1[3], v2[3];
                vecsub(&(coords[3*ind[i+1]]), &(coords[3*ind[i]]), v1);
                vecsub(&(coords[3*ind[i+2]]), &(coords[3*ind[i+1]]), v2);
                crossproduct(v1,v2, &norms[i]);*/
                i = i + 3; c = getc(fp);
                if (c == EOF) return j + 1;

            }
        }
        else if (EQUALCHARSTRINGS(line, cstr5))
        {
            c = ' '; i = 0;
            while (c != ']') {
                fscanf_s(fp, "%d, %d, %d, %d", &(nind[i]), &(nind[i + 1]), &(nind[i + 2]), &temp);
                i = i + 3; c = getc(fp);
                if (c == EOF) return j + 1;
            }
            if (j == (MAXSHAPES - 1)) return MAXSHAPES;
            j++;
            coords = coordinates + j * (3 * MAXCOORDS);
            ind = indices + j * (3 * MAXCOORDS);
            nind = nindices + j * (3 * MAXCOORDS);
            norms = normals + j * (3 * MAXCOORDS);
        }
    }
    fclose(fp);
    return j;
}