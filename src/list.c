#include "list.h"

void RMIUtilPushIntoList(RMI_list* p_list,void *thing)
{
    RMI_list_object* new = malloc(sizeof(RMI_list_object));

    new->data = thing;

    if (!p_list->start || !p_list->end){
        p_list->start = new;
        p_list->end = new;
    }
}