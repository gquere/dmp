#define MAX_STACK_SIZE	8192*8

struct stack {
	void *elems[MAX_STACK_SIZE];
	int32_t nb_elems;
    sem_t lock;
};


/******************************************************************************/
struct stack * stack_new(void);
void stack_delete(struct stack *this);

/******************************************************************************/
int32_t stack_push(struct stack *this, void *elem_addr);
void * stack_pop(struct stack *this);

