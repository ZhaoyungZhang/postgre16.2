#include <stdio.h>     
#include <stdlib.h>     

int values[] = {40, 10, 100, 90, 20, 25, 30};

int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

typedef struct f_smgr
{
	void		(*smgr_init) (void);	/* may be NULL */
	void		(*smgr_shutdown) (void);	/* may be NULL */
	void		(*smgr_open) (void);
	void		(*smgr_close) (void);
	void		(*smgr_create) (void);
	void		(*smgr_unlink) (void);
	void		(*smgr_extend)(void);
	void		(*smgr_zeroextend) (void);
	void		(*smgr_read) (void);
	void		(*smgr_write) (void);
	void		(*smgr_writeback) (void);
	void		(*smgr_truncate) (void);
	void		(*smgr_immedsync) (void);
} f_smgr;

static const f_smgr smgrsw[] = {
	/* magnetic disk */
	{
		.smgr_init = NULL,
		.smgr_shutdown = NULL,
		.smgr_open = NULL,
		.smgr_close = NULL,
		.smgr_create = NULL,
		.smgr_unlink = NULL,
		.smgr_extend = NULL,
		.smgr_zeroextend = NULL,
		.smgr_read = NULL,
		.smgr_write = NULL,
		.smgr_writeback = NULL,
		.smgr_truncate = NULL,
		.smgr_immedsync = NULL,
	}
};
#define lengthof(array) (sizeof (array) / sizeof ((array)[0]))
static const int NSmgr = lengthof(smgrsw);

int main ()
{
  int n;
  printf ("%d ",NSmgr);
  printf ("%ld  %ld" ,sizeof (smgrsw), sizeof (smgrsw[0]));
  return 0;
}