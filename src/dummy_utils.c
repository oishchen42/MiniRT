#include <minirt.h>

void 	free_double(char **split)
{
	int i = -1;
	while (split[++i])
	{
		free(split[i]);
	}
	free(split);
}

void	pirnt_split_content(char **split)
{
	int i = -1;
	while (split[++i])
	{
		printf("%s\n", split[i]);
	}
}

void	default_world(t_world *wrld)
{
	t_obj *sp1;
	t_matirial mat1;
	t_light	*light;
	t_vcpnt l_pnt;
	t_vcpnt	l_intens;

	l_pnt = (t_vcpnt){-10, 10, -10, 1};
	l_intens = (t_vcpnt){1, 1, 1, 1};
	light = create_light(&l_pnt, &l_intens);
	wadd_obj(wrld, light, NULL);

	mat1.color = (t_vcpnt){0.8, 1.0, 0.6, 1};
	mat1.diffuse = 0.7;
	mat1.specular = 0.2;
	mat1.shiness = 200;
	mat1.ambient = 0.5;
	sp1 = sphere(&mat1, NULL);
	wadd_obj(wrld, NULL, sp1);

	t_vcpnt trans_ints = {0.5, 0.5, 0.5, 1};
	t_mtx4	scl = scale4(&trans_ints);
	t_obj	*sp2 = sphere(NULL, NULL);
	create_transform_mtx4(&sp2->data.sp.transform, &scl);
	wadd_obj(wrld, NULL, sp2);
}
