
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

unsigned long int Cur_pos = 0;

const int T_num = 1;
const int T_operator = 2;

int get_go(char *buff);///
int get_n(char *buff);///
int get_t(char *buff);///
int get_p(char *buff);
int get_e(char *buff);///

char *pre_preobraz(void);

struct tree_brunch *brunch_creator(int val, int operator_type, struct tree_brunch *left_br, struct tree_brunch *right_br, struct tree_brunch *parent);

struct tree_brunch
{
    struct tree_brunch* parent;
    int data_type;
    int data;
    struct tree_brunch* left;
    struct tree_brunch* right;
};


//!======================================================================================
//!
//! This program comp my lang to tree
//!
//! Author: Vladimir Gribanov
//!
//! UPD(v 0.0.1) - I have ylitochka preobrazovatel
//!
//! v - 0.0.1
//!
//!======================================================================================
int main()
{
    char *main_buff = pre_preobraz();

    printf("\n\nPreobraz string {%s}\n", main_buff);

    int otvet = get_go(main_buff);

    printf("otvet = %d\n", otvet);

    return 0;
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
int get_go(char *buff)
{
    int val = get_e(buff);
    assert(buff[Cur_pos] == '@');
    return val;
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
int get_e(char *buff)
{
    int val = get_t(buff);
    int val2;

    while(buff[Cur_pos] == '+' || buff[Cur_pos] == '-')
    {
        int oper = buff[Cur_pos];
        Cur_pos++;

        while(buff[Cur_pos] == '#')
            Cur_pos++;

        val2 = get_t(buff);

        if(oper == '+')
        {
            val = val + val2;
        }
        else if(oper == '-')
        {
            val = val - val2;
        }
    }

    return val;
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
int get_t(char *buff)
{
    int val = get_p(buff);
    int val2;

    while(buff[Cur_pos] == '*' || buff[Cur_pos] == '/')
    {
        int oper = buff[Cur_pos];
        Cur_pos++;

        while(buff[Cur_pos] == '#')
            Cur_pos++;

        val2 = get_p(buff);

        if(oper == '*')
        {
            val = val * val2;
        }
        else if(oper == '/')
        {
            val = val / val2;
        }
    }
    return val;
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
int get_n(char *buff)
{
    int val = 0;

    if((buff[Cur_pos] == '#') || ('0' <= buff[Cur_pos] && buff[Cur_pos] <= '9'))
    {
        while(buff[Cur_pos] == '#')
            Cur_pos++;

        while('0' <= buff[Cur_pos] && buff[Cur_pos] <= '9')
        {
            val = val * 10 + (buff[Cur_pos] - '0');

            Cur_pos++;
        }

        while(buff[Cur_pos] == '#')
            Cur_pos++;

        return val;
    }
    else
    {
        assert(false);
    }
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
int get_p(char *buff)
{
    while(buff[Cur_pos] == '#')
            Cur_pos++;

    if(buff[Cur_pos] == '(')
    {
        Cur_pos++;

        while(buff[Cur_pos] == '#')
            Cur_pos++;

        int val = get_e(buff);
        while(buff[Cur_pos] == '#')
            Cur_pos++;

        assert(buff[Cur_pos] == ')');
        Cur_pos++;
        while(buff[Cur_pos] == '#')
            Cur_pos++;

        return val;
    }
    else
        return get_n(buff);
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
struct tree_brunch *brunch_creator(int val, int d_type, struct tree_brunch *left_br, struct tree_brunch *right_br, struct tree_brunch *parent)
{
    struct tree_brunch *cur_br = (struct tree_brunch*) calloc(1, sizeof(struct tree_brunch));

    cur_br->data = val;
    cur_br->data_type = d_type;

    if(d_type == T_num)
    {
        cur_br->left = NULL;
        cur_br->right = NULL;
    }
    else
    {
        cur_br->left = left_br;
        cur_br->right = right_br;
        left_br->parent = cur_br;
        right_br->parent = cur_br;
    }

    cur_br->parent = parent;
}

//!--------------------------------------------------------------------------------------
//!
//!
//!
//!--------------------------------------------------------------------------------------
char *pre_preobraz(void)
{
    FILE *prog = fopen("prog.txt","r");

    long int max_len = 0;
    long int max_hig = 0;
    long int cur_hig = 0;

    printf("\t\t\t{V}--------------------------------------------------{B}\n"
           "\t\t\t{#}    Hello I am compiler in ylitochka language     {A}\n"
           "\t\t\t{G}  I want to see only square programs with only    {N}\n"
           "\t\t\t{R}    odd high and long of program. Dont ask why!   {O}\n"
           "\t\t\t{I}--------------------------------------------------{V}\n");
    printf(">>> Length and high of program = ");
    scanf("%ld", &max_len);

    max_hig = max_len;

    char **non_comp_buff = (char **) calloc(max_hig, sizeof(char**));

    while(cur_hig <= max_hig)
    {
        non_comp_buff[cur_hig++] = (char*) calloc(max_len, sizeof(char*));
    }

    cur_hig = 0;

    while(cur_hig <= max_hig)
    {
        fscanf(prog, "%[^\n]", non_comp_buff[cur_hig]);

        fgetc(prog);

        cur_hig++;
    }

    fclose(prog);

    int i = 0;

    while(i <= max_len)
    {
        printf(":");
        printf("%s", non_comp_buff[i++]);
        printf(":\n");
    }

    cur_hig = 0;

    const long int c_max_hig = max_hig;
    const long int c_max_len = max_len;

    long int cur_len = 0;
    long int pos_in_buff = 0;
    long int max_in_buff = (max_hig + 1) * (max_len + 1);

    char *comp_buff = (char*)calloc(max_in_buff, sizeof(char*));

    max_hig--;

    while(pos_in_buff != max_in_buff - 1)
    {
        while(cur_len <= max_len)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig][cur_len++];

        cur_len--;
        cur_hig++;

        while(cur_hig <= max_hig)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig++][cur_len];

        cur_hig--;
        cur_hig++;

        while(cur_len >= c_max_len - max_len)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig][cur_len--];

        cur_len++;
        max_len--;
        cur_hig--;

        while(cur_hig >= c_max_hig - max_hig)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig--][cur_len];

        cur_hig++;
        cur_len++;
        max_hig--;
    }

    comp_buff[max_in_buff-1] = '@';

    return comp_buff;
}







