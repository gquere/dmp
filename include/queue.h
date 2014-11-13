#define MAX_QUEUE_SIZE	8192

struct queue {
	void *elems[MAX_QUEUE_SIZE];
	int32_t nb_elems;
	int32_t current_read;
	int32_t current_write;
};


/******************************************************************************/
struct queue * queue_new(void);
void queue_delete(struct queue *this);

/******************************************************************************/
int32_t queue_push(struct queue *this, void *elem_addr);
void * queue_pop(struct queue *this);

