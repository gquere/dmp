struct memory_pool {
	size_t element_size;
	struct stack *free_elements;
	struct memory_pool *next;
};

struct dmp {
	struct memory_pool *first;
};


/******************************************************************************/
struct dmp * dmp_new(int count, ...);
void dmp_delete(struct dmp *this);

/******************************************************************************/
void * dmp_acquire(struct dmp *this, size_t element_size);
int32_t dmp_release(struct dmp *this, void *element);

