#include <iostream>
#include <thread>
#include <vector>

#include "MLX42.h"

mlx_t* MLX = 0;

void func(mlx_image_t* image) {
    mlx_image_to_window(MLX, image, 0, 0);
    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 1000; ++j) {
            mlx_put_pixel(image, i, j, rand());
        }
    }
}

void draw_loop(void* img) {
    mlx_image_t** images = (mlx_image_t**)img;
    std::vector<std::thread> threads;
    threads.reserve(10);
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(func, images[i]));
    for (int i = 0; i < 10; ++i)
        threads[i].join();
    for (int i = 0; i < 10; ++i)
        mlx_image_to_window(MLX, images[i], 100 * i, 0);
    std::cout << (60 / MLX->delta_time) << std::endl;
}

int main(void) {
    MLX = mlx_init(1000, 1000, "hi", false);
    mlx_image_t* images[10];
    for (int i = 0; i < 10; ++i)
        images[i] = mlx_new_image(MLX, 100, 1000);
    mlx_loop_hook(MLX, draw_loop, images);
    mlx_loop(MLX);
    return 0;
}
