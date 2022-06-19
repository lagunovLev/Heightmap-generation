#include "generate_map.h"
#include "noise.h"


Mesh* generate_map(size_t size, float*** heights)
{
	PerlinNoise perlin(0.3, 0.035, 50, 16, rand());

	float* vertices = new float[size * size * 5];
	int* indices = new int[(size - 1) * (size - 1) * 6];

	int attrs[] = {
		3, 2, 0
	};

	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			vertices[count + 0] = i;
			vertices[count + 1] = perlin.GetHeight(i, j);
			vertices[count + 2] = j;

			vertices[count + 3] = (float)i / 8;
			vertices[count + 4] = (float)j / 8;

			(*heights)[i][j] = vertices[count + 1];
			count += 5;
		}
	}

	int vert = 0;
	int tris = 0;

	for (int z = 0; z < size - 1; z++)
	{
		for (int x = 0; x < size - 1; x++)
		{
			indices[tris + 0] = vert + 0;
			indices[tris + 1] = vert + size - 1 + 1;
			indices[tris + 2] = vert + 1;
			indices[tris + 3] = vert + 1;
			indices[tris + 4] = vert + size - 1 + 1;
			indices[tris + 5] = vert + size - 1 + 2;

			vert++;
			tris += 6;
		}
		vert++;
	}

	return new Mesh(glm::mat4(1.0), vertices, attrs, size * size, indices, (size - 1) * (size - 1) * 6 * sizeof(int));
}