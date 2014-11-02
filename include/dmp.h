struct dmp {
	struct stack *free_elements;
	size_t element_size;
};


/******************************************************************************/
struct dmp * dmp_new(size_t element_size);
void dmp_delete(struct dmp *this);

/******************************************************************************/
void * dmp_acquire(struct dmp *this);
int32_t dmp_release(struct dmp *this, void *element);

