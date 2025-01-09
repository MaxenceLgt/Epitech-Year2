/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include <sstream>
#include <fstream>
#include <mutex>
#include <atomic>

Camera::Camera()
{
    aspect_ratio      = 16.0 / 9.0; // Obligatoire
    image_width       = 400; // obligatoire
    samples_per_pixel = 200;
    max_depth         = 50;

    vfov = 90; // Obligatoire
    lookfrom = Point3(-2,2,1); // obligatoire
    lookat = Point3(0,0,-1); // obligatoire
    vup = Vec3(0,1,0);

    defocus_angle = 0.0;
    focus_dist    = 1.0;
}

Camera::Camera(const libconfig::Setting &settings)
{
    aspect_ratio = Utils::settings_get_ratio(settings["aspect_ratio"]);
    settings.lookupValue("image_width", image_width);
    settings.lookupValue("vfov", vfov);
    lookfrom = Vec3::parseVec3(settings["lookfrom"]);
    lookat = Vec3::parseVec3(settings["lookat"]);

    if (settings.exists("vup"))
        vup = Vec3::parseVec3(settings["vup"]);
    if (settings.exists("defocus_angle"))
        defocus_angle = Utils::settings_get_double(settings, "defocus_angle");
    if (settings.exists("focus_dist"))
        focus_dist = Utils::settings_get_double(settings, "focus_dist");
    if (settings.exists("samples_per_pixel"))
        samples_per_pixel = Utils::settings_get_double(settings, "samples_per_pixel");
    if (settings.exists("max_depth"))
        max_depth= Utils::settings_get_int(settings, "max_depth");
    if (settings.exists("background"))
        background = Vec3::parseVec3(settings["background"]);
    initialize();
}

Camera::~Camera()
{
}

bool Camera::display_preview(Preview &preview, const IPrimitive& world)
{
    for (int j = 0; j < preview.image_height; j++) {
        for (int i = 0; i < preview.image_width; i++) {
            Color pixel_color(0,0,0);
            for (int sample = 0; sample < 40; sample++) {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            pixel_color *= pixel_samples_scale;
            pixel_color *= 4;
            preview.image.setPixel(i, j, sf::Color(
                static_cast<sf::Uint8>(255.999 * pixel_color.x()),
                static_cast<sf::Uint8>(255.999 * pixel_color.y()),
                static_cast<sf::Uint8>(255.999 * pixel_color.z())
            ));
        }
    }
    std::cout << "Preview done" << std::endl;
    return preview.display();
}


void Camera::render(const IPrimitive &world, Settings &settings)

{
    Preview preview(image_width, image_height);
    if (!display_preview(preview, world))
        return;
    if (settings.getMultithreading())
        renderMultithread(world, settings);
    else
        renderPPM(world, settings);
}

void Camera::renderPPM(const IPrimitive &world, Settings &settings)
{
    Color pixel_color(0,0,0);
    std::ofstream out (settings.getOutputPath(), std::ios::out);
    out << "P6\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            pixel_color.reset();
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(out, pixel_samples_scale * pixel_color);
        }
    }
    out.close();
    std::clog << "\rDone.                 \n";
}


std::mutex render_mutex;

void Camera::render_section(const IPrimitive& world, const Camera& cam, std::vector<std::vector<Pixel>>& buffer, int startX, int endX, int startY, int endY, int id)
{
    Ray r;
    Color pixel_color(0, 0, 0);
    Color tmp_pixel;
    for (int j = startY; j < endY; j++) {
        buffer[j].resize(image_width);
        for (int i = startX; i < endX; i++) {
            pixel_color.reset();
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, max_depth, world);
            }
            std::lock_guard<std::mutex> guard(render_mutex);
            buffer[j][i] = color_to_pixel(pixel_samples_scale * pixel_color);
        }
    }
    std::cout << "Thread " << id << " done" << std::endl;
}

void Camera::renderMultithread(const IPrimitive &world, Settings &settings)
{
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 8;


    std::vector<std::thread> threads;
    std::vector<std::vector<Pixel>> buffer(image_height);
    int sectionHeight = image_height / num_threads;
    if (sectionHeight < 50) {
        sectionHeight = 50;
        num_threads = image_height / sectionHeight;
    }

    std::cout << "height: " << image_height << " sectionHeight: " << sectionHeight << " num_threads: " << num_threads << std::endl;

    for (unsigned int i = 0; i < num_threads; i++) {
        int startY = i * sectionHeight;
        int endY = (i + 1) * sectionHeight;
        if (i == num_threads - 1)
            endY = image_height;
        std::cout << "Thread " << i << " : " << startY << " -> " << endY << std::endl;
        threads.emplace_back(&Camera::render_section, this, std::ref(world), *this, std::ref(buffer), 0, image_width, startY, endY, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::ofstream out(settings.getOutputPath(), std::ios::out | std::ios::binary);
    out << "P6\n" << image_width << " " << image_height << std::endl <<"255" << std::endl;
    for (const auto& color : buffer) {
        for (const auto& pixel : color)
            write_color(out, pixel);
    }
    out.close();

    std::clog << "\rDone." << std::endl;
}

void Camera::initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    auto theta = Utils::degrees_to_radians(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = viewport_height * -v;
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = focus_dist * tan(Utils::degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

Ray Camera::get_ray(int i, int j) const {

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                        + ((i + offset.x()) * pixel_delta_u)
                        + ((j + offset.y()) * pixel_delta_v);
    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return {ray_origin, ray_direction};
}

Vec3 Camera::sample_square() const
{
    return {Utils::random_double() - 0.5, Utils::random_double() - 0.5, 0};
}

Color Camera::ray_color(const Ray& r, int depth, const IPrimitive& world) const
{
    Ray scattered;
    HitRecord rec;
    static Color attenuation;
    static Vec3 unit_direction;

    if (depth <= 0)
        return {0,0,0};
    if (!world.hit(r, Interval(0.001, infinity), rec))
        return background;
    Color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat->scatter(r, rec, attenuation, scattered))
        return color_from_emission;

    Color color_from_scatter = attenuation * ray_color(scattered, depth-1, world);

    return color_from_emission + color_from_scatter;
}

Point3 Camera::defocus_disk_sample() const
{
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}
