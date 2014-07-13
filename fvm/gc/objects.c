#include <fvm/gc/objects.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int total_number_of_objects;
Object* head_obj;
Object* tail_obj;
Object* VM_CreateObject(int type, uint32_t value)
{
	Object* new_obj = malloc(sizeof(Object));
	printf("Creating Object, ID is $%d, Address : $%p, Value is $%d, Type is $%d\n", total_number_of_objects, (void*)new_obj, value, type);
	new_obj->marked = IS_MARKED;
	new_obj->value = value;
	new_obj->type = type;
	new_obj->index = total_number_of_objects;
	new_obj->next = NULL;
	new_obj->prev = (struct sObject*)tail_obj;
	if(total_number_of_objects > 0)
	{
		tail_obj->next =  (struct sObject*)new_obj;
	}
		tail_obj = new_obj;
	if(total_number_of_objects == 0)
	{
		head_obj = new_obj;
	}
	total_number_of_objects++;
	return new_obj;
}
int getnumberofObjects(void)
{
	return total_number_of_objects;
}
Object* gettail(void)
{
	return tail_obj;
}
Object* gethead(void)
{
	return head_obj;
}
Object* getObjectbyindex(int index)
{
	Object* temp = NULL;	
	for(int i = 0; i  <= total_number_of_objects; i++)
	{
		temp = temp->next;
		if(temp == NULL)
		{
			printf("Requested index is not found\n");
			return NULL;
		}
		else if(temp->index == index){
			return temp;
		}
	}
	return NULL;
}
bool ismarked(Object* object)
{
	if(object->marked == IS_MARKED)
	{
		return true;
	}
	return false;
}
int VM_DestroyObject(int index)
{
	if(index > total_number_of_objects)
	{	
		printf("Requested object index is out of bounds\n");
		return -2;
	}
	Object* temp = NULL;
	temp = temp->next;
	for(int i = 0; i < index; i++)
	{
		/** Search the linked list **/
		temp = temp->next;
		if(temp == NULL)
		{
			printf("fatal: item or requested object not found!\n");
			return -1;
		}
		if(temp->index == index)
		{
			temp->next->prev = (struct sObject*)temp->prev;
			temp->prev->next = (struct sObject*)temp->next;
			free(temp); /** Free it? **/
		}
	}
	total_number_of_objects--;
	// We're done!
	return 0;
}
