#include <fvm/v_stack/v_stack.h>
int PushtoStack(v_stack* stack, int object);
int PopFromStack(v_stack* stack);
int GetItem(v_stack* stack, int idx);
v_stack* CreateStack(void);
int Duplicate(v_stack* stack);
void init_stack(void)
{
	Stack.Duplicate = &Duplicate;
	Stack.GetItem = &GetItem;
	Stack.Push = &PushtoStack;
	Stack.Pop = &PopFromStack;
	Stack.Create = &CreateStack;
}
int Duplicate(v_stack* stack)
{
	PushtoStack(stack, stack->content[stack->no]);
	return 0;
}
int GetItem(v_stack* stack, int idx)
{
	if(idx > stack->no){ return -1; }
	else { return (stack->content[idx]); }
}
v_stack* CreateStack(void)
{	
	v_stack* new_stack = (v_stack*)malloc(sizeof(v_stack)); // Allocate stack structure
	new_stack->content = NULL;
	new_stack->no = 0 ;
	return new_stack;
}
int PushtoStack(v_stack* stack, int object)
{
	int* new_content_stk = (int*)malloc((stack->no+1)*sizeof(int));
	for(int i = 0; i < stack->no; i++)
	{
		new_content_stk[i] = stack->content[i];
	}
	stack->no++;
	new_content_stk[stack->no] = object;
	free(stack->content);
	stack->content = new_content_stk;
	return 0;
}
int PopFromStack(v_stack* stack)
{
	stack->content[stack->no] = 0;
	stack->no--;
	int* new_content_stk = (int*)malloc(stack->no * sizeof(int));
	for(int i = 0; i < stack->no-1; i++)
	{
		new_content_stk[i] = stack->content[i];
	}
	free(stack->content);
	stack->content = new_content_stk;
	return 0;
}
