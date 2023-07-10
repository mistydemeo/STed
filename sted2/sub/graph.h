/* graph.h

   dummy header file for X680x0 compatible

   Made by Studio Breeze. 1998

*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

/* defines */

#ifndef PI
#define PI M_PI
#endif /* PI */

#ifndef PID2
#define PID2 PI/2
#endif /* PID2 */

void g_print( int x, int y, char *str, int col );
void rev_area( int r_ad, int r_ln, int edit_scr );
void tg_copy( int edit_scr );
void tg_copy2( int edit_scr );
void t_scrw( int x1, int y1, int xs, int ys, int x2, int y2 );
void txcur( int a, int b, int c1, int c2, int cs );

#endif /* _GRAPH_H_ */
