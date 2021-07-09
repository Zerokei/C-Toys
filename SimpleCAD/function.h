/**************************
* written by Zerokei
* start date: 2021.4.19
* last date: 2021.4.21
***************************/

#ifndef FUNCTION_H
#define FUNCTION_H

#include "type.h"

/*	generate a rectangle randomly*/
Rect* generate_rect(Rect_list* p);
/*	generate a line randomly*/
Line* generate_line(Line_list* p);
/*	generate a circle randomly*/
Circ* generate_circ(Circ_list* p);
/*	generate a text randomly*/
Text* generate_text(Text_list* p);


/*	delete a circle from the list*/
void delete_list_circ(Circ_list* p, Circ* tar);
/*	delete a line from the list*/
void delete_list_line(Line_list* p, Line* tar);
/*	delete a rectangle from the list*/
void delete_list_rect(Rect_list* p, Rect* tar);
/*	delete a text from the list*/
void delete_list_text(Text_list* p, Text* tar);

/*	Rewrite all the images*/
void Rewrite(Line_list* p1, Rect_list* p2, Circ_list* p3, Text_list* p4);
/*	Clear the window*/
void ClearAll();


/*	judge if the cursor is in the line*/
Line* find_line(double nx, double ny, Line_list * p);
/*	judge if the cursor is in the text*/
Text* find_text(double nx, double ny, Text_list* p);
/*	judge if the cursor is in the rectangle*/
Rect* find_rect(double nx, double ny, Rect_list* p);
/*	judge if the cursor is in the circle*/
Circ* find_circ(double nx, double ny, Circ_list* p);

/*	move the cursor to the left position*/
void cursor_left(Text* a);
/*	move the cursor to the right position*/
void cursor_right(Text* a);
/*	calculate the length and width of the text*/
void calc_l_and_r(Text* a);
/*	delete the text after the cursor*/
void delete_c_after_cursor(Text* a);
/*	delete the text before the cursor*/
void delete_c_before_cursor(Text* a);
/*	insert a text after the cursor*/
void insert_c_after_cursor(Text* a, char c);
/*	draw cursor*/
void draw_cursor(Text* a);
/*	clear cursor*/
void clear_cursor(Text* a);

/*calculate the function*/
double dist(double x1, double y1, double x2, double y2);
#endif // !FUNCTION_H