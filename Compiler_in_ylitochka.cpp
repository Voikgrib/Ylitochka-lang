
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

char *pre_preobraz(void);

char *after_preobraz(char **nc_buff, long int max_len, long int max_hig);


//!======================================================================================
//!
//! This program comp my lang to tree
//!
//! Author: Vladimir Gribanov
//!
//!======================================================================================
int main()
{
    char *buff = pre_preobraz();

    printf("--> %s\n", buff);

    return 0;
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

    printf("qqqq \n");

    printf(">>> Length of program = ");
    scanf("%ld", &max_len);
    printf(">>> High of program = ");
    scanf("%ld", &max_hig);

    //max_hig = 4;
    //max_len = 4;

    printf("mlen = %ld -+-+- mhigh = %ld\n\n\n", max_len, max_hig);

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

    printf("1\n");

    fclose(prog);

    //
    int i = 0;

    while(i <= max_len)
    {
        printf(":");
        printf("%s", non_comp_buff[i++]);
        printf(":\n");
    }
    //

    //return after_preobraz(non_comp_buff, max_len, max_hig);

    ////////////////////////////////////////////////////////////////////////////////////////

    const long int c_max_hig = max_hig;
    const long int c_max_len = max_len;

    long int cur_len = 0;
    cur_hig = 0;
    long int pos_in_buff = 0;
    long int max_in_buff = (max_hig + 1) * (max_len + 1);

    char *comp_buff = (char*)calloc(max_in_buff, sizeof(char*));

    printf("buf size = %ld\n", max_in_buff);

    max_hig--;

    while(pos_in_buff != max_in_buff)
    {
        while(cur_len <= max_len)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig][cur_len++];

        cur_hig++;

        while(cur_hig <= max_hig)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig++][cur_len];

        cur_hig++;

        while(cur_len >= c_max_len - max_len)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig][cur_len--];

        max_len--;
        cur_hig--;

        while(cur_hig >= c_max_hig - max_hig)
            comp_buff[pos_in_buff++] = non_comp_buff[cur_hig--][cur_len];

        cur_len++;
        max_hig--;
    }

    ////////////////////////////////////////////////////////
}

//!----------------------------------------------------------------------------------------
//!
//!
//!
//!----------------------------------------------------------------------------------------
char *after_preobraz(char **nc_buff, long int max_len, long int max_hig)
{
    const long int c_max_hig = max_hig;
    const long int c_max_len = max_len;

    long int cur_len = 0;
    long int cur_hig = 0;
    long int pos_in_buff = 0;
    long int max_in_buff = (max_hig + 1) * (max_len + 1);

    char *comp_buff = (char*)calloc(max_in_buff, sizeof(char*));

    printf("buf size = %ld\n", max_in_buff);

    max_hig--;

    while(pos_in_buff != max_in_buff)
    {
        while(cur_len <= max_len)
            comp_buff[pos_in_buff++] = nc_buff[cur_hig][cur_len++];

        cur_hig++;

        while(cur_hig <= max_hig)
            comp_buff[pos_in_buff++] = nc_buff[cur_hig++][cur_len];

        cur_hig++;

        while(cur_len >= c_max_len - max_len)
            comp_buff[pos_in_buff++] = nc_buff[cur_hig][cur_len--];

        max_len--;
        cur_hig--;

        while(cur_hig >= c_max_hig - max_hig)
            comp_buff[pos_in_buff++] = nc_buff[cur_hig--][cur_len];

        cur_len++;
        max_hig--;
    }
        /*while((c_max_hig - max_hig) <= cur_hig && cur_hig <= max_hig)
        {
            comp_buff[pos_in_buff++] = nc_buff[cur_hig][cur_len];
            printf("# %c, len = %ld, high = %ld, buf poz = %ld\n", nc_buff[cur_len][cur_hig], cur_len, cur_hig, pos_in_buff-1);///
            cur_hig = cur_hig + (cur_mode_hig);
        }

        cur_len = cur_len - (cur_mode_hig);
        cur_hig = cur_hig - (cur_mode_hig);
        max_hig--;

        //printf("\\ len = %ld, high = %ld, buf poz = %ld\n", cur_len, cur_hig, pos_in_buff-1);///

        if(cur_mode_hig == up)
            cur_mode_hig = down;
        else
            cur_mode_hig = up;

        while((c_max_len - max_len) <= cur_len && cur_len <= max_len)
        {
            comp_buff[pos_in_buff++] = nc_buff[cur_hig][cur_len];
            printf("- %c, len = %ld, high = %ld, buf poz = %ld\n", nc_buff[cur_len][cur_hig], cur_len, cur_hig, pos_in_buff-1);///
            cur_len = cur_len + (cur_mode_len);
        }

        cur_hig = cur_hig + (cur_mode_len);
        cur_len = cur_len - (cur_mode_len);
        max_len--;

        if(cur_mode_len == up)
            cur_mode_len = down;
        else
            cur_mode_len = up;*/


    free(nc_buff);

    return comp_buff;
}






