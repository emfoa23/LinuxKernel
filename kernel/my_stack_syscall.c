#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/linkage.h>

#define MAX 10
int stack[MAX]; //make the stack
int top = -1;	//stack pointer
int i;
bool exist;	//variable cheking whether the input is already in the stack

SYSCALL_DEFINE1(oslab_push,int,a){
	for(i = top; i>=0; i--){
		if(stack[i] == a){
			exist = true;
			break;
		}
		exist = false;
	}	//check whether the input is already in the stack
	if(exist == false){
		stack[++top] = a;
		printk("[System call] oslab_push(): Push %d",a);
	}	//push input if the input is not in the stack
	else {
		printk("[System call] oslab_push(): Push %d -> Fail (%d already exists in the stack)",a,a);
		return -1;
	}	//return -1 if the input is already in the stack
	printk("Stack Top ----------\n");
	for(i = top; i>=0; i--){
		printk("%d",stack[i]);
	}
	printk("Stack Bottom -------\n");	//print values in the stack

	return a;	//return the value pushed in the stack
}

SYSCALL_DEFINE0(oslab_pop){
	if(top>=0){
		printk("[System call] oslab_pop(): Pop %d\n",stack[top--]);
	}	//pop the value if the stack is not empty
	else{
		printk("[System call] oslab_pop(): Pop -> Fail (Stack Underflow)\n");
		return -1;
	}	//return -1 if the stack is empty
	printk("Stack Top ----------\n");
	for(i = top; i>=0; i--){
		printk("%d",stack[i]);
	}
	printk("Stack Bottom -------\n");	//print values in the stack
                 
	return stack[top+1];	//return the value popped from the stack
}
