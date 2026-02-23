#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "obj.h"

void loadOBJ(RMI_obj* obj,const char* fileName){
    FILE* file = fopen(fileName,"r");

    if (!file){
        fprintf(stderr,"Could not open %s\n",fileName);
    };

    int vCount = 0;
    int fCount = 0;

    fpos_t pos;
    fgetpos(file,&pos);

    char buffer[255];
    while (fgets(buffer,255,file) != NULL){
        char type[12];
        sscanf(buffer,"%s",type);
        if(strcmp(type,"v") == 0){
            vCount++;
        }
        if(strcmp(type,"f") == 0){
            fCount++;
        }
    };

    fsetpos(file,&pos);

    int vPos = 0;
    float* verts = malloc(sizeof(float)*3*vCount);

    int fPos = 0;
    unsigned int* faces = malloc(sizeof(unsigned int)*3*fCount);

    //printf("%d\n",fCount);

    while (fgets(buffer,255,file) != NULL){
        char type[12];
        sscanf(buffer,"%s",type);
        if(strcmp(type,"v") == 0){
            float x,y,z;
            sscanf(buffer,"%*s %f %f %f",&x,&y,&z);
            verts[vPos++] = x;
            verts[vPos++] = y;
            verts[vPos++] = z;
        }
        if(strcmp(type,"f") == 0){
            char one[12], two[12], three[12];
            sscanf(buffer,"%*s %s %s %s",one, two, three);
            //printf("%s %s %s\n",one ,two,three);
            int x,y,z;
            sscanf(one,"%d %*c %*d %*c %*d",&x);
            sscanf(two,"%d %*c %*d %*c %*d",&y);
            sscanf(three,"%d %*c %*d %*c %*d",&z);

            //printf("%d %d %d\n",x,y,z);

            faces[fPos++] = x -1;
            faces[fPos++] = y -1;
            faces[fPos++] = z -1;
        }
    };


/*     for (int i = 0 ; i < vCount * 3 ; i++){
        printf("%f ",verts[i]);
    }
    printf("\n");
    for (int i = 0 ; i < fCount * 3 ; i++){
        printf("%d ",faces[i]);
    }
    printf("\n"); */

    obj->verts = verts;
    obj->indexes = faces;

    obj->indexAmnt = fCount * 3;
    obj->vertsAmnt = vCount * 3;

    fclose(file);
    return;
}