/*
 * ----------------------------------------
 *	assembler Module �̐錾
 * ----------------------------------------
 */

#ifndef _MACHIN_H_
#define _MACHIN_H_

void	OnGraphic(void);

void	H_ERA(void);
void	H_PRINT(char *, char *, char *);
void	H_PRINT2(char *, char *, char *);
void	H_INIT(void);
void	LDIRL(VIDEO *, VIDEO *, int);

void	key_rep_off(void);
void	key_rep_on(void);
void	key_vect_set(void);
void	key_vect_reset(void);

#endif /* _MACHIN_H_ */
