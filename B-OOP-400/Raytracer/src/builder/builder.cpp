/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** builder
*/
#include "Rotate.hpp"
#include "Trans.hpp"
#include "builder.hpp"

Builder::Builder(const char *path)
{
    try {
        _cfg.readFile(path);
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Builder: error on reading file." << std::endl;
        throw fioex;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parsing error  " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        throw libconfig::ParseException(pex);
    }
}

Builder::Builder(std::string path)
{
    try {
        _cfg.readFile(path.c_str());
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Builder: error on reading file." << std::endl;
        throw fioex;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parsing error  " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        throw libconfig::ParseException(pex);
    }
}

std::map<std::string, shared_ptr<IMaterial>> Builder::getMaterials()
{
    std::map<std::string, shared_ptr<IMaterial>> materials;
    const libconfig::Setting &root = _cfg.getRoot();
    const libconfig::Setting &materials_cfg = root["materials"];
    int count = materials_cfg.getLength();

    for (int i = 0; i < count; i++) {
        const libconfig::Setting &material = materials_cfg[i];
        std::string name = material.getName();
        std::string type;
        shared_ptr<IMaterial> mat;
        if (!material.exists("type") || !material.lookupValue("type", type)) {
            std::cerr << "Builder: error on reading material." << std::endl;
            throw std::runtime_error("Builder: error on reading material.");
        }
        try {
            mat = std::shared_ptr<IMaterial>(this->getObjectFromLib<IMaterial *>(type, material));
        } catch (const CLibEncapsulation::LibException &e) {
            std::cerr << "Builder: error on reading material :" << e.what() << std::endl;
            throw BuilderError("Builder: error on reading material.");
        }
        materials[name] = mat;
    }
    return materials;
}

PrimList Builder::getPrimitives(std::map<std::string, shared_ptr<IMaterial>> &materials)
{
    PrimList primitives;
    const libconfig::Setting &root = _cfg.getRoot();
    const libconfig::Setting &primitives_cfg = root["primitives"];
    int count = primitives_cfg.getLength();

    for (int i = 0; i < count; i++) {
        const libconfig::Setting &prim_list = primitives_cfg[i];
        std::string type = prim_list.getName();
        for (int j = 0; j < prim_list.getLength(); j++) {
            const libconfig::Setting &prim_cfg = prim_list[j];
            try {
                APrimitive *prim = this->getObjectFromLib<APrimitive *>(type, prim_cfg);
                auto shared_prim = std::shared_ptr<APrimitive>(prim);
                if (prim_cfg.exists("material")) {
                    this->setMaterials(materials, shared_prim, prim_cfg);
                } else if (prim_cfg.exists("color")) {
                    setColor(prim_cfg["color"], shared_prim);
                } else
                    throw BuilderError("Builder: error on reading prim_list: no material or color.");
                setTransform(prim_cfg, shared_prim);
                primitives.add(shared_prim);
            } catch (const CLibEncapsulation::LibException &e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cerr << "Builder: error on reading prim_list." << std::endl;
                throw BuilderError("Builder: error on reading prim_list.");
            }
        }
    }
    return primitives;
}

void Builder::setColor(const libconfig::Setting &setting, std::shared_ptr<APrimitive> &primitive)
{
    try {
        Color color = Vec3::parseVec3(setting);
        ColorMat* colorMatPtr = new ColorMat(color);
        std::shared_ptr<IMaterial> materialPtr = std::shared_ptr<IMaterial>(reinterpret_cast<IMaterial*>(colorMatPtr));
        primitive->setMaterial(materialPtr);
    } catch (const libconfig::SettingNotFoundException &e) {
        throw BuilderError("Builder: error on reading color.");
    }
}

void Builder::setMaterials(std::map<std::string, shared_ptr<IMaterial>> &materials, std::shared_ptr<APrimitive> primitive, const libconfig::Setting &materialSettings)
{
    std::string name;
    try {
        if (!materialSettings.lookupValue("material", name))
            throw BuilderError("Builder: error on reading material: too many settings.");
        if (materials.find(name) == materials.end())
            throw BuilderError("Builder: error on reading material: material not found.");
        primitive->setMaterial(materials[name]);
    } catch (const libconfig::SettingNotFoundException &e) {
        throw BuilderError("Builder: error on reading material.");
    }
}

Camera Builder::getCamera()
{
    const libconfig::Setting &root = _cfg.getRoot();

    try {
        if (!root.exists("camera")) {
            throw BuilderError("Builder: camera not found.");
        }
        const libconfig::Setting &camera_cfg = root["camera"];
        Camera camera(camera_cfg);
        return camera;
    } catch (const libconfig::SettingNotFoundException &e) {
        throw BuilderError("Builder: error on reading camera : " + std::string(e.what()));
    }
}

void Builder::setTransform(const libconfig::Setting &setting, std::shared_ptr<APrimitive> &primitive)
{
    if (setting.exists("translation")) {
        Vec3 trans = Vec3::parseVec3(setting["translation"]);
        primitive = make_shared<Trans>(primitive, trans);
    }
    if (setting.exists("rotation")) {
        primitive = make_shared<Rotate>(primitive, Utils::settings_get_double(setting, "rotation"));
    }
}

Settings Builder::getSettings()
{
    const libconfig::Setting &root = _cfg.getRoot();

    return Settings(root);
}
