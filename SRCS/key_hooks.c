#include "../includes/miniRT.h"

int	key_hook(int keycode, t_miniRT *miniRT)
{
	if (keycode == 'a'){ // "a"
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(-1.5,0,0,0));
    printf("moved left\n");
  }
	if (keycode == 'd') // "d"
  {
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(1.5,0,0,0));
    printf("moved right\n");
  }
  if (keycode == 's'){ // "s"
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,0,-1.5,0));
    printf("moved back\n");
  }
	if (keycode == 'w') // "w"
  {
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,0,1.5,0));
    printf("moved forward\n");
  }
  if (keycode == 'e') // "e"
  {
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,1.5,0,0));
    printf("moved forward\n");
  }
  if (keycode == 'q') // "e"
  {
		miniRT->camera.view_point = vct_add(miniRT->camera.view_point, set_vct(0,-1.5,0,0));
    printf("moved forward\n");
  }
	ft_miniRT(miniRT);
	return (0);
}