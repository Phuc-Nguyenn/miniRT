#include "../includes/miniRT.h"

int	key_hook(int keycode, t_miniRT *miniRT)
{
    switch(keycode) {
        case 'a':
            miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(-1.5,0,0,0));
            printf("moved left\n");
            break;
        case 'd':
            miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(1.5,0,0,0));
            printf("moved right\n");
            break;
        case 's':
            miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,0,-1.5,0));
            printf("moved back\n");
            break;
        case 'w':
            miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,0,1.5,0));
            printf("moved down\n");
            break;
        case 'e':
            miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,1.5,0,0));
            printf("moved up\n");
            break;
        case 'q':
		    miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,-1.5,0,0));
            printf("moved forward\n");
            break;
        case 'k':
            miniRT->camera.orientation = rotateX(miniRT->camera.orientation, 15.0);
            printf("turned up\n");
            break;
        case 'i':
            miniRT->camera.orientation = rotateX(miniRT->camera.orientation, -15.0);
            printf("turned down\n");
            break;
        case 'j':
            miniRT->camera.orientation = rotateY(miniRT->camera.orientation, -15.0);
            printf("turned left\n");
            break;
        case 'l':
            miniRT->camera.orientation = rotateY(miniRT->camera.orientation, 15.0);
            printf("turned right\n");
            break;
    }
	ft_miniRT(miniRT);
	return (0);
}