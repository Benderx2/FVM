#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fvm/classloader.h>
#include <fvm/classes.h>
class_t* curclass;
class_t* head;
int numberofclasses = 0;
void add_class(class_t* class)
{
	if(numberofclasses == 0)
	{
		curclass = class;
		head = class;	
	}
	else {
		/** Add the class to the linked list **/
		curclass->next = class;	
		class->next = NULL:
		curclass = class;	
	}
}

