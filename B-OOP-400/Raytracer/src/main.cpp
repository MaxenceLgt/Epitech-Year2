/*
** EPITECH PROJECT, 2024
** PRIVATE_RAYTRACER
** File description:
** main
*/

#include "Camera.hpp"
#include "PrimList.hpp"
#include <memory>
#include "builder/builder.hpp"

static void print_usage()
{
    std::cout << "USAGE: ./raytracer [config_file]" << std::endl;
}

int main(int ac, char **av)
{

    if (ac != 2) {
        print_usage();
        return 84;
    }
    if (std::string(av[1]) == "-h") {
        print_usage();
        return 0;
    }
    try {
        PrimList world;

        Camera cam;
        Builder builder(av[1]);
        Settings settings = builder.getSettings();
        cam = builder.getCamera();
        auto materials = builder.getMaterials();

        auto primitives = builder.getPrimitives(materials);
        cam.render(primitives, settings);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
