#include "Draw.h"
#include "Table.h"
#include "genlib.h" /*import bool*/
#include "graphics.h"

#define max(a,b) ((a)>(b)?(a):(b)) /* max功能*/
#define min(a,b) ((a)<(b)?(a):(b)) /* min功能*/

extern Table* Mytable;             /* Mytable: 当前数据表*/
extern int current_col;            /* current_col: 当前选中列*/
extern int current_row;            /* current_row: 当前选中行*/

static double last_mid_x;          /* last_mid_x: 前一个区间里中间的x坐标，用于画点连线*/
static double last_x;              /* last_x: 前一个区间的x坐标的开头*/
static double draw_large_rate_y;   /* draw_large_rate_y: 最终画y时乘上的系数*/

static double y_max;               /* y_max: 显示在框内的点的最大值*/
static double y_min;               /* y_min: 显示在框内的点的最小值*/
static double bili;                /* bili:  数值长度映射成英寸比例*/
/*
* Function: show_bar
* 功能: 判断某行是否柱状显示
* 参数: num: 第几行
* 返回值: bool, 是否柱状显示
* 创建人: Parfait
*/
static bool show_bar(int num) {
    return query_if_show_bar(Mytable, num);
}

/*
* Function: show_line
* 功能: 判断某行是否折线显示
* 参数: num: 第几行
* 返回值: bool, 是否折线显示
* 创建人: Parfait
*/
static bool show_line(int num) {
    return query_if_show_line(Mytable,num);
}

/*
* Function: show_dot
* 功能: 判断某行是否点阵显示
* 参数: num: 第几行
* 返回值: bool, 是否点阵显示
* 创建人: Parfait
*/
static bool show_dot(int num) {
    return query_if_show_dot(Mytable,num);
}

/*
* Function: test_table
* 功能: 查询数据表某个点的值
* 参数: num: 第几列
*       i:   第几列
* 返回值: double, 指定点的数值
* 创建人: Parfait
*/
static double test_table(int num, int i) {
    if (i == 0 || num == 0) return 0;
    return table(Mytable,i,num)->num;
}

/*
* Function: abss
* 功能: 绝对数函数
* 参数: a: 一个浮点数
* 返回值: double, |a|
* 创建人: Parfait
*/
static double abss(double a) {
    if (a < 0) return -1 * a;
    else return a;
}

/*
* Function: sum_of_col
* 功能: 求某一列的和
* 参数: num: 多少列
* 返回值: double, 列的和
* 创建人: Parfait
*/
static double sum_of_col(int num) {
    double sum = 0; /* sum: 记录和*/
    int i;
    for (i = 1; i <= query_row_num(Mytable); i++) {
        double temp_y = abss(test_table(num, i));
        sum += temp_y;
    }
    return sum;
}

/*
* Function: sum_of_row
* 功能: 求某一行的和
* 参数: num: 多少行
* 返回值: double, 行的和
* 创建人: Parfait
*/
static double sum_of_row(int num) {
    double sum = 0;/* sum: 记录和*/
    int i;
    for (i = 1; i <= query_col_num(Mytable); i++) {
        double temp_y = abss(test_table(i, num));
        sum += temp_y;
    }
    return sum;
}

/*
    将显示的颜色初始化
    Deep1  - Deep9
    Light1 - Light9
    Pie1   - Pie9
*/
void init_color() {
    DefineColor("Deep1", 0.470, 0.212, 0.344); //120,54,88
    DefineColor("Light1", 0.639, 0.414, 0.533); //163,106,136
    DefineColor("Pie1", 0.909, 0.737, 0.831); //232,188,212
    DefineColor("Deep2", 0.388, 0.212, 0.470); //99,54,120
    DefineColor("Light2", 0.5686, 0.414, 0.639); //145,106,163
    DefineColor("Pie2", 0.863, 0.745, 0.909); //220，190，232
    DefineColor("Deep3", 0.184, 0.247, 0.557); //47,63,142
    DefineColor("Light3", 0.414, 0.453, 0.639); //106,116,163
    DefineColor("Pie3", 0.737, 0.792, 0.909); //188,202，232
    DefineColor("Deep4", 0.176, 0.384, 0.557); //45,98,142
    DefineColor("Light4", 0.415, 0.537, 0.639); //106,137,163
    DefineColor("Pie4", 0.737, 0.812, 0.909); //188,207，232
    DefineColor("Deep5", 0.125, 0.557, 0.486); //32,142,124
    DefineColor("Light5", 0.415, 0.639, 0.604); //106,163,154
    DefineColor("Pie5", 0.737, 0.909, 0.863); //188,232，220
    DefineColor("Deep6", 0.215, 0.478, 0.051); //55,122,13
    DefineColor("Light6", 0.501, 0.639, 0.415); //128,163,106
    DefineColor("Pie6", 0.819, 0.909, 0.737); //209,232，188
    DefineColor("Deep7", 0.478, 0.4313, 0.133); //123,110,34
    DefineColor("Light7", 0.639, 0.608, 0.415); //163,155,106
    DefineColor("Pie7", 0.909, 0.995, 0.737); //232,224，188
    DefineColor("Deep8", 0.538, 0.322, 0.102); //121,82,27
    DefineColor("Light8", 0.761, 0.584, 0.341); //194,149,87
    DefineColor("Pie8", 0.909, 0.792, 0.651); //232,202，166
    DefineColor("Deep9", 0.474, 0.207, 0.145); //122,53,37
    DefineColor("Light9", 0.760, 0.415, 0.341); //194,106,87
    DefineColor("Pie9", 0.992, 0.808, 0.769); //253,206，196
}

void start_draw() {
    init_color();//初始化颜色
    show_pie = 0;
    show_axis = 1;
    draw_begin_x = axis_begin_x;
    draw_begin_y = axis_begin_y;
    large_rate_x = 1;
    large_rate_y = 1;
}

/*
* Function: find_y_max
* 功能: 求显示在框内的点(柱子)的最大值
* 参数: 无
* 返回值: double, 最大值
* 创建人: Parfait
*/
static double find_y_max() {
    double local_last_x = draw_begin_x;
    double local_last_mid_x = local_last_x + (width_x / 2);

    int j;
    double highest = -1e18;
    for (j = 1; j <= query_col_num(Mytable); j++) {
        if (local_last_x < axis_begin_x) {
            local_last_x += width_x;
            local_last_mid_x += width_x;
            continue;
        }
        //遍历一遍在图中的求y最大值
        int i = 1;
        double temp_x = local_last_x + 0.5 * each_bar_width;
        for (i = 1; i <= query_row_num(Mytable); i++) {
            if (show_bar(i)) {
                if (temp_x < axis_begin_x) {
                    temp_x += each_bar_width;
                    continue;
                }
                if (temp_x > axis_end_x)
                    break;
            }
            else if (show_dot(i) || show_line(i)) {
                if (local_last_mid_x < axis_begin_x) {
                    continue;
                }
                if (local_last_mid_x > axis_end_x)
                    break;
            }
            double temp_y = test_table(j, i) ;
            if (highest <= temp_y ) {
                highest = temp_y;
            }
            temp_x += each_bar_width;
        }
        local_last_x += width_x;
        local_last_mid_x += width_x;
    }
    return highest;
}

/*
* Function: find_y_min
* 功能: 求显示在框内的点(柱子)的最小值
* 参数: 无
* 返回值: double, 最小值
* 创建人: Parfait
*/
static double find_y_min() {
    double local_last_x = draw_begin_x;
    double local_last_mid_x = local_last_x + (width_x / 2);
    int j;
    double lowest = 1e18;
    for (j = 1; j <= query_col_num(Mytable); j++) {
        if (local_last_x < axis_begin_x) {
            local_last_x += width_x;
            local_last_mid_x += width_x;
            continue;
        }
        //遍历一遍在图中的求y最大值
        int i = 1;
        double temp_x = local_last_x + 0.5 * each_bar_width;
        for (i = 1; i <= query_row_num(Mytable); i++) {
            if (show_bar(i)) {
                if (temp_x < axis_begin_x) {
                    temp_x += each_bar_width;
                    continue;
                }
                if (temp_x > axis_end_x)
                    break;
            }
            else if (show_dot(i) || show_line(i)) {
                if (local_last_mid_x < axis_begin_x) {
                    continue;
                }
                if (local_last_mid_x > axis_end_x)
                    break;
            }
            double temp_y = test_table(j, i);
            if (lowest >= temp_y) {
                lowest = temp_y;
            }
            temp_x += each_bar_width;
        }
        local_last_x += width_x;
        local_last_mid_x += width_x;
    }
    return lowest;
}

/*
* Function: adapt_the_rate_y
* 功能: 求适应的比例
* 参数: 无
* 返回值: double, 最小值
* 创建人: Parfait
*/
void adapt_the_rate_y() {
    y_min = min(0, find_y_min());
    y_max = find_y_max();

    bili = (abss(y_max) + abss(y_min) < 1e-18) ? 1 : (axis_end_y - axis_begin_y) / (y_max - y_min);
}

/*
* Function: init_draw
* 功能: 重新画图初始化，init改xy初始，画图的时候空余间距小一点，到每根柱子的宽度
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
static void init_draw() {
    MovePen(draw_begin_x, draw_begin_y);
    width_x = (axis_end_x - axis_begin_x) / (double)query_col_num(Mytable);
    width_x *= large_rate_x;
    last_x = draw_begin_x;
    last_mid_x = last_x +  (width_x/ 2);
    each_bar_width = width_x / (show_row_num() + 1);
    draw_large_rate_y = large_rate_y * bili;
    if (y_min < 0)draw_begin_y = axis_begin_y - y_min * draw_large_rate_y;
    if (col_or_row == 0)
        draw_pie_num = current_col;
    else
        draw_pie_num = current_row;
}

/*
* Function: draw_bar
* 功能: 画柱形图
* 参数: num: 用第几列的数据
* 返回值: 无
* 创建人: Parfait
*/
static void draw_bar(int num) {
    MovePen(last_x, draw_begin_y);
    int i = 1;
    double temp_x=last_x+0.5*each_bar_width;/* temp_x: 当前画的位置x*/
    for (i = 1; i <= query_row_num(Mytable); i++) {
        if (show_bar(i)) {
            if (temp_x < axis_begin_x) {
                temp_x += each_bar_width;
                continue;
            }
            double temp_y = test_table(num, i) * draw_large_rate_y;
            temp_y = min(temp_y, axis_end_y - draw_begin_y);

            char* bar_color = (char*)malloc(7 * sizeof(char));
            bar_color[0] = 'L';
            bar_color[1] = 'i';
            bar_color[2] = 'g';
            bar_color[3] = 'h';
            bar_color[4] = 't';
            bar_color[5] = 48 + i;
            bar_color[6] = 0;
            if (num == current_col && i == current_row) mySetPenColor("NYPink");
            else mySetPenColor(bar_color);
            MovePen(temp_x, draw_begin_y);
            drawRectangle(temp_x, draw_begin_y, 0.7*each_bar_width, temp_y, 1);

            temp_x+=each_bar_width;
        }   
    }
}

/*
* Function: MyDrawLine
* 功能: 画断断续续的直线
* 参数: x: 长度
*       y: 高度
* 返回值: 无
* 创建人: Zerokei
*/
static void MyDrawLine(double x, double y) {
    double dx = 0.03, dy  = dx * y / x; /* dx: 虚线的宽度, dy: 虚线的高度*/
    int i;
    for (i = 1; x >= dx/2; ++i, x-= dx) {
        if (i & 1) {
            DrawLine(dx, dy);
        }
        else {
            MovePen(GetCurrentX() + dx, GetCurrentY() + dy);
        }
    }
}

/*
* Function: draw_bar
* 功能: 画折线图里的折线
* 参数: num: 用第几列的数据
* 返回值: 无
* 创建人: Parfait
*/
static void draw_line(int num) {
    SetPenSize(2);
    int i;
    for (i = 1; i <= query_row_num(Mytable); i++) {
        if (show_line(i) == 0) 
            continue;
       
        double last_y = test_table(num, i) * draw_large_rate_y;
        double temp_y = test_table(num + 1, i) * draw_large_rate_y;

        MovePen(last_mid_x, draw_begin_y + last_y);
        char* line_color = (char*)malloc(7 * sizeof(char));
        line_color[0] = 'D';
        line_color[1] = 'e';
        line_color[2] = 'e';
        line_color[3] = 'p';
        line_color[4] = 48 + i;
        line_color[5] = 0;
        line_color[6] = 0;
        mySetPenColor(line_color);

        if (last_mid_x < axis_begin_x) {
            MovePen(last_mid_x + width_x, draw_begin_y + temp_y);
            double k = 1.0 * (width_x - (axis_begin_x - last_mid_x)) / (width_x);
            MyDrawLine(-width_x * k, -(temp_y - last_y) * k);
        }
        else if (last_y > axis_end_y - draw_begin_y && temp_y > axis_end_y - draw_begin_y) 
            continue; //超出范围不画
        else if (last_mid_x < axis_begin_x) {
            MovePen(last_mid_x + width_x, draw_begin_y + temp_y);
            double k = 1.0 * (width_x -(axis_begin_x- last_mid_x)) / (width_x);
            MyDrawLine(-width_x * k, -(temp_y - last_y) * k);
        }
        else if (last_y > axis_end_y - draw_begin_y) {//前面一段不画
            MovePen(last_mid_x + width_x, draw_begin_y + temp_y);
            double k = 1.0 * (axis_end_y - draw_begin_y - temp_y) / (last_y - temp_y);
            MyDrawLine(-width_x * k, -(temp_y - last_y) * k);
        }
        
        else if (temp_y > axis_end_y - draw_begin_y) {
            double k = 1.0 * (axis_end_y - draw_begin_y - last_y) / (temp_y - last_y);
            MyDrawLine(width_x * k, (temp_y - last_y) * k);
        }
        else {
            MyDrawLine(width_x, temp_y - last_y);
        }
    }
    SetPenSize(1);
}

/*
* Function: draw_dot
* 功能: 画点阵(折线)图里的点
* 参数: num: 用第几列的数据
* 返回值: 无
* 创建人: Parfait
*/
static void draw_dot(int num) {
    int i;
    for (i = 1; i <= query_row_num(Mytable); i++) {
        if (show_dot(i) == 0 && show_line(i) == 0) continue;
        double temp_y = test_table(num, i) * draw_large_rate_y;
        if (temp_y > axis_end_y - draw_begin_y) continue; //不画

        double r;
        for (r = 0; r <= dot_r; r += 0.001) {
            MovePen(last_mid_x + r, draw_begin_y + temp_y);
            char* bar_color = (char*)malloc(6 * sizeof(char));
            bar_color[0] = 'D';
            bar_color[1] = 'e';
            bar_color[2] = 'e';
            bar_color[3] = 'p';
            bar_color[4] = 48 + i;
            bar_color[5] = 0;
            mySetPenColor(bar_color);
            DrawArc(r, 0, 360);
        }
        if (num == current_col && i == current_row) {
            MovePen(last_mid_x + dot_r + 0.05, draw_begin_y + temp_y);
            mySetPenColor("SunsetOrange");
            DrawArc(dot_r + 0.05, 0, 360);
        }
    }
}

/*
* Function: draw_pie
* 功能: 画饼形图
* 参数: num: 用第几列(列)的数据
*       col_row: 利用行还是列 0:列 1:行
* 返回值: 无
* 创建人: Parfait
*/
static void draw_pie(int num, int col_row) {//col_row=1选中后显示该row，col_row=0选中后显示该col
    double pie_x = axis_begin_x + (axis_end_x - axis_begin_x) / 2;
    double pie_y = axis_begin_y + (axis_end_y - axis_begin_y) / 2;
    MovePen(pie_x + pie_r, pie_y);
    DrawArc(pie_r, 0, 360);
    int i;
    double angle = 0;

    MovePen(pie_x + pie_r, pie_y);
    if (col_or_row == 0) {
        double sum = sum_of_col(num);
        for (i = 1; i <= query_row_num(Mytable); i++) {//画彩色背景
            double temp_y = abss(test_table(num, i));
            double temp_rad = (temp_y / sum) * 2 * PI;

            char* pie_color = (char*)malloc(6 * sizeof(char));
            pie_color[0] = 'P';
            pie_color[1] = 'i';
            pie_color[2] = 'e';
            pie_color[3] = 49 + i;
            pie_color[4] = 0;
            pie_color[5] = 0;
            if (num == current_col && i == current_row) mySetPenColor("NYPink");
            else  mySetPenColor(pie_color);

            StartFilledRegion(1);
            DrawArc(pie_r, angle / 2 / PI * 360, temp_rad / 2 / PI * 360);
            double px = GetCurrentX(), py = GetCurrentY();
            DrawLine(pie_x - GetCurrentX(), pie_y - GetCurrentY());
            EndFilledRegion();
            MovePen(px, py);
            angle += temp_rad;
        }
    }
    else if (col_or_row == 1) {
        double sum = sum_of_row(num);
        for (i = 1; i <= query_col_num(Mytable); i++) {//画彩色背景
            double temp_y = abss(test_table(i, num));
            double temp_rad = (temp_y / sum) * 2 * PI;

            char* pie_color = (char*)malloc(6 * sizeof(char));
            pie_color[0] = 'P';
            pie_color[1] = 'i';
            pie_color[2] = 'e';
            pie_color[3] = 49 + i;
            pie_color[4] = 0;
            pie_color[5] = 0;
            if (i == current_col && num == current_row) mySetPenColor("NYPink");
            else  mySetPenColor(pie_color);

            StartFilledRegion(1);
            DrawArc(pie_r, angle / 2 / PI * 360, temp_rad / 2 / PI * 360);
            double px = GetCurrentX(), py = GetCurrentY();
            DrawLine(pie_x - GetCurrentX(), pie_y - GetCurrentY());
            EndFilledRegion();
            MovePen(px, py);
            angle += temp_rad;
        }
    }
}

/*
* Function: draw_y_text
* 功能: 画y轴坐标上的数值
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
static void draw_y_text() {
    mySetPenColor("black");
    double axishigh = (axis_end_y - axis_begin_y); /* axishigh: 坐标轴高度*/
    double avehigh = axishigh / 5;                 /* avehigh: 高度的1/5，用于标注刻度*/
    int i;
    for (i = 0; i <= 5; i++) {
        double maxy = i * (avehigh / draw_large_rate_y) + y_min;
        char* y_text = (char*)malloc(10 * sizeof(char));
        int u = 0;
        sprintf(y_text, "%.2f", maxy);
        MovePen(axis_begin_x - strlen(y_text) * 0.11 - 0.2, axis_begin_y + i * avehigh - 0.1);
        DrawTextString(y_text);
    }
    if (find_y_min() < 0) {
        double zerohigh = abss(find_y_min()) / draw_large_rate_y;
        MovePen(axis_begin_x - 0.43, axis_begin_y + zerohigh - 0.1);
        DrawTextString("0");
        MovePen(axis_begin_x, axis_begin_y + zerohigh - 0.1);
        DrawLine(axis_end_x - axis_begin_x, 0);
    }
    MovePen(axis_begin_x - 0.72, axis_end_y + 0.3);
    DrawTextString(Mytable->data_name);
}

/*
* Function: draw_axis_back
* 功能: 画坐标轴的背景
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
static void draw_axis_back() {
    SetPenColor("white");
    double axis_width_x = axis_end_x - axis_begin_x;
    double axis_width_y = axis_end_y - axis_begin_y;
    drawRectangle(axis_begin_x - 0.2, axis_begin_y - 0.2, axis_width_x + 1, axis_width_y + 1, 1);
}

/*
* Function: draw_axis
* 功能: 画坐标轴
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
static void draw_axis() {
    mySetPenColor("Black");
    MovePen(axis_begin_x, axis_begin_y);
    DrawLine(0, axis_end_y - axis_begin_y + 0.35);
    MovePen(axis_begin_x, axis_end_y + 0.35);
    DrawLine(-array_width, -array_width);
    MovePen(axis_begin_x, axis_end_y + 0.35);
    DrawLine(array_width, -array_width);
    MovePen(axis_begin_x, draw_begin_y);
    DrawLine(axis_end_x - axis_begin_x,0);
    MovePen(axis_end_x, draw_begin_y);
    DrawLine(-array_width, -array_width);
    MovePen(axis_end_x, draw_begin_y);
    DrawLine(-array_width, array_width);
} 

/*
* Function: draw_blank
* 功能: 画整个的背景
* 参数: 无
* 返回值: 无
* 创建人: Parfait
*/
static void draw_blank() {//左右0.3,上下0.5
    mySetPenColor(background_color);
    drawRectangle(axis_begin_x-0.3, axis_end_y+0.2, 10.6, 0.2, 1);//上
    mySetPenColor(background_color);
    drawRectangle(axis_begin_x-0.3, axis_begin_y-0.5,10.6, 0.3,1 );//下
    mySetPenColor(background_color);
    drawRectangle(axis_end_x + 0.2, axis_begin_y - 0.5,0.1,6, 1);//右
    mySetPenColor("white");
    drawRectangle(axis_end_x + 0.3, axis_begin_y - 0.5,1, 6, 1);//右
    mySetPenColor(background_color);
    drawRectangle(axis_begin_x - 0.3, axis_begin_y - 0.5,0.1, 5.6, 1);//左
}

/*
* Function: click
* 功能: 根据鼠标所在的位置, 判断有没有选中元素
* 参数: a: 鼠标点击的位置x
*       b: 鼠标点击的位置y
* 返回值: 是否有选中的元素
*         *a: 选中的行
*         *b: 选中的列
* 创建人: Parfait
*/
bool click(double* a, double* b) {
    if (show_pie) {

        double x = *a, y = *b;
        double pie_x = axis_begin_x + (axis_end_x - axis_begin_x) / 2;
        double pie_y = axis_begin_y + (axis_end_y - axis_begin_y) / 2;
        double tan_theta, theta; 

        if (((x - pie_x) * (x - pie_x) + (y - pie_y) * (y - pie_y)) > (pie_r * pie_r)) return FALSE;

        if (x - pie_x == 0 && y - pie_y > 0) theta = PI / 2;
        if (x - pie_x == 0 && y - pie_y < 0) theta = 3 * PI / 2;
        else {
            tan_theta = (y - pie_y) / (x - pie_x);
            theta = atan(tan_theta);
            if (x - pie_x < 0) theta += PI;
            else if (y - pie_y < 0 && x - pie_x>0) theta += 2 * PI;
        }
        double angle = 0;
        int i;


        if (col_or_row == 0) {
            double sum = sum_of_col(draw_pie_num);
            for (i = 1; i <= query_row_num(Mytable); i++) {//画彩色背景
                double temp_y = abss(test_table(draw_pie_num, i));
                double temp_rad = (temp_y / sum) * 2 * PI;
                if (theta >= angle && theta < angle + temp_rad) {
                    *a = draw_pie_num;
                    *b = i;
                    return TRUE;
                }
                angle += temp_rad;
            }
        }
        else if (col_or_row == 1) {
            double sum = sum_of_row(draw_pie_num);
            for (i = 1; i <= query_col_num(Mytable); i++) {//画彩色背景
                double temp_y = abss(test_table(i, draw_pie_num));
                double temp_rad = (temp_y / sum) * 2 * PI;
                if (theta >= angle && theta < angle + temp_rad) {
                    *a = i;
                    *b = draw_pie_num;
                    return TRUE;
                }
                angle += temp_rad;
            }
        }

        
        return FALSE;
    }
    else if (show_axis) {
        double x = *a, y = *b;
        int j;
        last_x = draw_begin_x;
        last_mid_x = last_x + (width_x / 2);
        for (j = 1; j <= query_col_num(Mytable); j++) {
            if (last_x < axis_begin_x) {
                last_x += width_x;
                last_mid_x += width_x;
                continue;
            }
            //先看是否在每列中间，是否属于每个点
            if (x > last_mid_x - click_dot_r && x <= last_mid_x + click_dot_r) {
                int i;
                for (i = 1; i <= query_row_num(Mytable); i++) {
                    if (show_dot(i) == 0) continue;//如果这个没有画出来就选中不了
                    double temp_y = test_table(j, i) * draw_large_rate_y;
                    if (abss(temp_y) < 1e-18) {
                        temp_y = min_height * (temp_y < 0 ? -1 : 1);
                    }
                    if ((y - draw_begin_y - temp_y + click_dot_r) * (y - draw_begin_y - temp_y - click_dot_r) <= 0) {
                        *a = j;
                        *b = i;
                        return TRUE;
                        //return temp2;
                    }
                }
                //只能在不显示点的地方选中折线
                for (i = 1; i <= query_row_num(Mytable); i++) {
                    if (show_line(i) == 0) continue;//如果这个没有画出来就选中不了
                    double temp_y = test_table(j, i) * draw_large_rate_y;
                    if (abss(temp_y) < 1e-18) {
                        temp_y = min_height * (temp_y < 0 ? -1 : 1);
                    }
                    if ((y - draw_begin_y - temp_y + click_dot_r) * (y - draw_begin_y - temp_y - click_dot_r) <= 0) {
                        *a = j;
                        *b = i;
                        return TRUE;
                        //return temp2;
                    }
                }
            }
            //再看是否在每个柱子的里面
            if (x > last_x && x < last_x + width_x) {
                int i = 1;
                double temp_x = last_x + 0.5 * each_bar_width;
                for (i = 1; i <= query_row_num(Mytable); i++) {
                    if (show_bar(i) == 0) continue;//如果没有画出来就显示不了
                    if (x >= temp_x && x < temp_x + 0.7 * each_bar_width) {
                        double temp_y = test_table(j, i) * draw_large_rate_y;
                        if (abss(temp_y) < 1e-18) {
                            temp_y = min_height * (temp_y < 0 ? -1 : 1);
                        }
                        if ((y - temp_y - draw_begin_y) * (y - draw_begin_y) <= 0) {
                            *a = j;
                            *b = i;
                            return TRUE;
                        }
                    }
                    temp_x += each_bar_width;
                }
            }
            last_x += width_x;
            last_mid_x += width_x;
        }
        return FALSE;
    }
}

/*
*  Function: show_row_num
*  功能: 表示柱状图里显示出的数量，用来算柱状图宽度
*  参数: 无
*  返回值: int, 柱状图里显示出的数量
*  创建人: Parfait
*/
int show_row_num() {
    int i,sum=0;
    for (i = 1; i <= query_row_num(Mytable); i++) {
        if (show_bar(i)) {
            sum++;
        } 
    }
    return sum;
}

/*
*  Function: draw_color_menu
*  功能: 画颜色菜单
*  参数: 无
*  返回值: 无
*  创建人: Parfait
*/
void draw_color_menu() {
    MovePen(color_menu_begin_x, color_menu_begin_y);
    mySetPenColor(backgraph_color);
    drawRectangle(color_menu_begin_x, color_menu_begin_y,color_menu_end_x- color_menu_begin_x,color_menu_end_y- color_menu_begin_y, 1);
    int i;
    double color_width;
    color_width = color_menu_end_x - color_menu_begin_x;
    color_width /= (query_row_num(Mytable));
    double color_height = color_menu_end_y - color_menu_begin_y;
    color_height /= 2;
    double x = color_menu_begin_x;
    double y = color_menu_begin_y;
    for (i = 1; i <= query_row_num(Mytable); i++) {
        if (x == color_menu_end_x) {
            y += color_height;
            x = color_menu_begin_x;
        }
        {
            MovePen(x,y);
            char* line_color = (char*)malloc(7 * sizeof(char));
            line_color[0] = 'D';
            line_color[1] = 'e';
            line_color[2] = 'e';
            line_color[3] = 'p';
            line_color[4] = 48 + i;
            line_color[5] = 0;
            line_color[6] = 0;
            mySetPenColor(line_color);
            drawRectangle(x, y, color_box, color_box, 1);
        }
        //deep color box
        {
            MovePen(x, y+ color_box);
            char* bar_color = (char*)malloc(7 * sizeof(char));
            bar_color[0] = 'L';
            bar_color[1] = 'i';
            bar_color[2] = 'g';
            bar_color[3] = 'h';
            bar_color[4] = 't';
            bar_color[5] = 48 + i;
            bar_color[6] = 0;
            mySetPenColor(bar_color);
            drawRectangle(x, y + color_box, color_box, color_box, 1);
        }
        //mid color box
        {
            MovePen(x, y + 2*color_box);
            char* pie_color = (char*)malloc(6 * sizeof(char));
            pie_color[0] = 'P';
            pie_color[1] = 'i';
            pie_color[2] = 'e';
            pie_color[3] = 49 + i;
            pie_color[4] = 0;
            pie_color[5] = 0;
            mySetPenColor(pie_color);
            drawRectangle(x, y + 2*color_box, color_box, color_box, 1);
        }
        //light color box
        mySetPenColor("black");
        MovePen(x + color_box + 0.1, y);
        DrawTextString( query_row_name(Mytable, i) );
        x = x+ color_width;
    }
}

/*
*  Function: draw_text
*  功能: 画颜色菜单旁的文字（列的名字）
*  参数: num: 哪一列
*  返回值: 无
*  创建人: Parfait
*/
void draw_text(int num) {
    mySetPenColor("black");
    double length = TextStringWidth(query_col_name(Mytable, num));
    if ((last_mid_x - length / 2) < axis_begin_x) return ;
    if ((last_mid_x - length / 2) > axis_begin_x && (last_mid_x - length / 2) < axis_end_x) {
        MovePen(last_mid_x-length/2, axis_begin_y -0.3);
        DrawTextString( query_col_name(Mytable, num) );
    }  
}

/*
*  Function: draw_again
*  功能: 数据可视化核心功能，将数据表里的数据画在框图里
*  参数: 无
*  返回值: 无
*  创建人: Parfait
*/
void draw_again()
{
    if (!Mytable || Mytable->col_size == 0 || Mytable->row_size == 0)return;

    init_draw();
    if (show_pie) {
        draw_pie(draw_pie_num, col_or_row);
    }
    else if (show_axis) {
        int i;
        for (i = 1; i <= query_col_num(Mytable); i++) {
            if (last_x < axis_begin_x - width_x) {
                last_x += width_x;
                last_mid_x += width_x;
                continue;
            }
            if (width_x > 0.01 && width_x < 12.0) draw_bar(i);//画柱状图
        
            if (i < query_col_num(Mytable))draw_line(i);//画线
            if(last_mid_x > axis_begin_x) draw_dot(i);//画点

            last_x += width_x;
            last_mid_x += width_x;
        }
        //exit(0);
        draw_blank();
        draw_axis();
        init_draw();
        for (i = 1; i <= query_col_num(Mytable); i++) {
            if (last_x < axis_begin_x - width_x) {
                last_x += width_x;
                last_mid_x += width_x;
                continue;
            }
            draw_text(i);
            last_x += width_x;
            last_mid_x += width_x;
        }  
        draw_y_text();
    }
    draw_color_menu();
}