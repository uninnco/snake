#include"common.h"

int main()
{
    system("clear");

        struct fb_var_screeninfo  vinfo;

        int fd = open("/dev/fb0", O_RDWR);
        if(fd < 0)
    {
        perror("open err. \n");
                exit(EXIT_FAILURE);
        }
        int fret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
        if(fret < 0)
    {
                perror("ioctl err. \n");
                exit(EXIT_FAILURE);
        }


    unsigned long* addr = mmap(NULL, (vinfo.xres*vinfo.yres*vinfo.bits_per_pixel)>>3,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 


    S *head = NULL;
    F *f = malloc(sizeof(F));
    draw_rim(addr);
    create_snake(&head);
    create_food(f,head);
    draw_snake(addr,head);
    draw_food(addr,f);

    int key, ret;
    char choose='d';
    int speed = 1;

    ret = init_keyboard();
    if(ret < 0)
        return -1;

    while(1)
    {
        key = get_key();
        if(is_left(key))
        {
            if(move_judge_snake('a',choose))
                choose = 'a';
        }
        if(is_right(key))
        {
            if(move_judge_snake('d',choose))
                choose = 'd';
        }
        if(is_up(key))
        {
            if(move_judge_snake('w',choose))
                choose = 'w';
        }
        if(is_down(key))
        {
            if(move_judge_snake('s',choose))
                choose = 's';
        }
        if(is_space(key))
        {
            if(speed)
                speed = 0;
            else
                speed = 1;
        }

        if(is_esc(key)){
            printf("esc\n");
            break;
        }
        if(key == 'q')
            break;
        eat(head,f);
        move_snake(choose,head);
        gameover(head);

        mclear(addr);
        draw_snake(addr,head);
        draw_food(addr,f);
        if(speed)
            usleep(300000);
        else
            usleep(250000);

    }

        recover_keyboard();
        return 0;
}
