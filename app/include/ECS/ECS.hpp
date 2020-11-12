/*
** EPITECH PROJECT, 2020
** ECS [WSL: Ubuntu]
** File description:
** ECS
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>
#include <initializer_list>
#include <cstring>
#include <string>
#include <exception>
#include <stdlib.h>
#include <algorithm>

#define CACHE_LINE 64

#ifdef WINDOWS
    #define ALLOC_ALIGNED(align, size) _aligned_malloc(size, align)
    #define REALLOC_ALIGNED(block, size, align) _aligned_realloc(block, size, align)
    #define FREE_ALIGNED(block) _aligned_free(block)
#else
    #include <malloc.h>
    #define ALLOC_ALIGNED(align, size) ::aligned_alloc(align, size)
    #define REALLOC_ALIGNED(block, size, align) aligned_realloc(block, size, align)
    #define FREE_ALIGNED(block) ::free(block)

    static void* aligned_realloc(void* ptr, size_t size, size_t align)
    {
        size_t old_size = malloc_usable_size(ptr);
        void* nptr = ::aligned_alloc(align, size);

        if (old_size < size) {
            ::memcpy(nptr, ptr, old_size);
        } else {
            ::memcpy(nptr, ptr, size);
        }
        free(ptr);
        return nptr;
    }
#endif

using ECSID = std::size_t;

static size_t nextPower2(size_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;
}

class ECSException : public std::exception {
    public:
        ECSException(const std::string _str) : str(_str) {}
        ~ECSException() {}
        virtual const char *what() const throw() {
            return this->str.c_str();
        }
    private:
        const std::string str;
};

static size_t nextSize(size_t v)
{
    if (v < 128)
    {
        static const size_t values[] = {1, 2, 4, 8, 16, 24, 32, 48, 64, 96, 128};
        for (int i = 0; i < 11; i++)
        {
            if (values[i] > v)
                return values[i];
        }
    }
    return nextPower2(v);
}

template <typename R, typename ...P>
struct Functor {
    using type = typename std::function<R(P...)>;
};

class EntityModel
{
public:
    EntityModel(const std::string &name) : m_name(name) {}

    ~EntityModel()
    {
    }

    template <typename... Args>
    EntityModel &addComponents()
    {
        if constexpr (sizeof...(Args) > 0)
            addComponent<Args...>();
        std::sort(types.begin(), types.end(), sortTypes);

        return *this;
    }

    size_t countComponents() {
        return types.size();
    }

    size_t getComponentSize(size_t index) {
        return types[index].m_size;
    }

    size_t getComponentAlign(size_t index) {
        return types[index].m_align;
    }

    bool hasComponent(size_t component) {
        for (Meta &meta : types) {
            if (meta.m_id == component) {
                return true;
            }
        }
        return false;
    }

    template <typename... Args>
    bool hasComponents()
    {
        return sizeof...(Args) == hasComponent<Args...>();
    }

    const std::string &getName() {
        return this->m_name;
    }

    template <typename T>
    std::size_t getComponentOffset()
    {
        ECSID id = typeid(T).hash_code();
        for (Meta &meta : types)
        {
            if (meta.m_id == id)
            {
                return meta.m_align;
            }
        }
        throw "Component does not exists";
    }

    void addTag(const std::string &tag) {
        tags.push_back(std::hash<std::string>()(tag));
    }

    bool hasTag(const std::string &tag) {
        return hasTag(std::hash<std::string>()(tag));
    }

    bool hasTag(size_t hash) {
        for (size_t tag : tags) {
            if (tag == hash)
                return true;
        }
        return false;
    }

    template<typename T>
    int getComponentIndex() {
        ECSID id = typeid(T).hash_code();
        for (size_t i = 0; i < types.size(); i++) {
            if (id == types[i].m_id) {
                return i;
                break;
            }
        }
        return -1;
    }

private:
    const std::string m_name;
    struct Meta
    {
        size_t m_id;
        size_t m_size;
        size_t m_align;
    };
    std::vector<Meta> types;
    std::vector<size_t> tags;

    template <typename T, typename... Args>
    size_t hasComponent()
    {
        ECSID id = typeid(T).hash_code();
        size_t found = 0;
        for (Meta &meta : types)
        {
            if (meta.m_id == id)
            {
                found = 1;
                break;
            }
        }
        if constexpr (sizeof...(Args) > 0)
        {
            return hasComponent<Args...>() + found;
        }
        return found;
    }
    template <typename T, typename... Args>
    void addComponent()
    {
        ECSID id = typeid(T).hash_code();
        std::size_t size = sizeof(T);
        for (Meta &meta : types)
        {
            if (meta.m_id == id)
            {
                throw ECSException("Component already exists");
            }
        }

        types.push_back({id, size, nextPower2(size) - size});

        if constexpr (sizeof...(Args) > 0)
        {
            addComponent<Args...>();
        }
    }

    static bool sortTypes(const Meta &a, const Meta b)
    {
        return a.m_align > b.m_align;
    }
};

class UnorderedEntityArray
{
public:
    UnorderedEntityArray(EntityModel *entity, std::size_t reserve) : m_entity(entity)
    {
        if (m_entity == nullptr) {
            throw ECSException("Failed to create UnorderedEntityArray from non existing model");
        }

        m_reserved = reserve < 1 ? 16 : reserve;

        for (size_t i = 0; i < m_entity->countComponents(); i++) {
            size_t componentSize = m_entity->getComponentSize(i) + m_entity->getComponentAlign(i);
            void* mem = ALLOC_ALIGNED(CACHE_LINE, componentSize * m_reserved);
            m_componentMemory.push_back(reinterpret_cast<char *>(mem));
            if (componentSize > m_maxComponentSize) {
                m_maxComponentSize = componentSize;
            }
        }
    }

    ~UnorderedEntityArray()
    {
        for (int i = 0; i < m_componentMemory.size(); i++) {
            FREE_ALIGNED(m_componentMemory[i]);
        }
    }

    void *at(std::size_t index, size_t componentIndex)
    {
        if (index >= m_size)
        {
            return nullptr;
        }

        if (componentIndex >= m_componentMemory.size()) {
            return nullptr;
        }

        size_t componentSize = m_entity->getComponentSize(componentIndex) + m_entity->getComponentAlign(componentIndex);
        return m_componentMemory[componentIndex] + (index * componentSize) + m_entity->getComponentAlign(componentIndex);
    }

    void remove(std::size_t index)
    {
        if (index >= m_size)
            return;

        for (size_t i = 0; i < m_entity->countComponents(); i++) {
            size_t componentSize = m_entity->getComponentSize(i) + m_entity->getComponentAlign(i);

            size_t posIndex = index * componentSize;
            size_t posLast = (m_size - 1) * componentSize;

            ::memcpy(m_componentMemory[i] + posIndex, m_componentMemory[i] + posLast, componentSize);
        }

        m_size -= 1;
    }

    void reserve(std::size_t size)
    {
        if (m_size + size > m_reserved)
        {
            grow(m_size + size - m_reserved);
        }
    }

    void grow(std::size_t elements)
    {
        if (SIZE_MAX - elements < m_size)
        {
            throw ECSException("Fail to grow size, overflow");
        }

        m_reserved += elements;

        for (size_t i = 0; i < m_entity->countComponents(); i++) {
            size_t componentSize = m_entity->getComponentSize(i) + m_entity->getComponentAlign(i);
            m_componentMemory[i] = reinterpret_cast<char *>(REALLOC_ALIGNED(m_componentMemory[i], componentSize * m_reserved, CACHE_LINE));

            if (m_componentMemory[i] == nullptr)
            {
                throw ECSException("Failed to realloc array");
            }
        }
    }

    template <typename... Args>
    void instanciate(std::size_t elements, const Args... args)
    {
        if (elements < 1)
            return;
        if (m_size + elements > m_reserved)
        {
            grow(m_size + elements - m_reserved);
        }

        if constexpr (sizeof...(Args) > 0)
        {
            genBaseEntity(elements, args...);
        }
        else
        {
            for (int i = 0; i < m_entity->countComponents(); i++) {
                size_t componentSize = m_entity->getComponentSize(i) + m_entity->getComponentAlign(i);
                ::memset(m_componentMemory[i] + m_size * componentSize, 0, elements * componentSize);
            }
        }

        m_size += elements;
    }

    template <typename T>
    T *getComponent(size_t index)
    {
        size_t componentIndex = m_entity->getComponentIndex<T>();
        void *ptr = at(index, componentIndex);
        if (ptr == nullptr)
            return nullptr;
        return reinterpret_cast<T *>(ptr);
    }

    std::size_t size()
    {
        return m_size;
    }

    EntityModel *getEntityModel() {
        return m_entity;
    }

private:
    std::size_t m_reserved = 0;
    std::size_t m_size = 0;
    EntityModel *m_entity = nullptr;
    std::vector<char*> m_componentMemory;
    size_t m_maxComponentSize = 0;

    template <typename T, typename... Args>
    void genBaseEntity(size_t elements, const T first, const Args... args)
    {
        void *mem = nullptr;

        if constexpr (std::is_reference<T>::value)
        {
            mem = const_cast<typename std::add_pointer<typename std::remove_reference<T>::type>::type>(&first);
        }
        else if constexpr (std::is_pointer<T>::value)
        {
            mem = const_cast<T>(first);
        }
        else if constexpr (std::is_compound<T>::value)
        {
            mem = const_cast<T *>(&first);
        }
        else if constexpr (std::is_scalar<T>::value)
        {
            mem = const_cast<T *>(&first);
        }
        else
        {
            throw ECSException("Invalid type");
        }

        int index = m_entity->getComponentIndex<typename std::remove_reference<typename std::remove_pointer<T>::type>::type>();
        if (index < 0) {
            throw ECSException("Trying to instanciate a component on an entity that doesn't have it.");
        }
        size_t offset = m_entity->getComponentAlign(index);
        size_t size = m_entity->getComponentSize(index);
        size_t componentSize = size + offset;

        for (std::size_t i = 0; i < elements; i++) {
            ::memcpy(m_componentMemory[index] + (m_size + i) * componentSize + offset, mem, size);
        }

        if constexpr (sizeof...(args) > 0)
        {
            return genBaseEntity(elements, args...);
        }
    }
};

template<typename ...Args>
class EntityIterator {
    public:
        EntityIterator(UnorderedEntityArray *entities, size_t hash) : m_entities(entities), entityHash(hash) {
            setupOffset<0, Args...>();
        }
        ~EntityIterator() {}

        template<typename T>
        typename std::add_pointer<T>::type getComponent(size_t index) {
            if (m_entities->size() == 0)
                return nullptr;
            return reinterpret_cast<typename std::add_pointer<T>::type>(m_entities->at(entity_index, indexes[index]));
        }

        size_t getEntityType() {
            return entityHash;
        }

        const std::string &getName() {
            return m_entities->getEntityModel()->getName();
        }

        size_t getSize() {
            return m_entities->size();
        }

        bool hasNext() {
            if (first)
                return entity_index < m_entities->size();
            return (entity_index + 1) < m_entities->size();
        }

        void next() {
            if (first) {
                first = false;
                return;
            }
            entity_index += 1;
        }

        void reset() {
            entity_index = 0;
            first = true;
        }

        void remove() {
            m_entities->remove(entity_index);
            first = true;
        }

        EntityModel *getEntityModel() {
            return m_entities->getEntityModel();
        }


    private:
        size_t indexes[sizeof...(Args)] = {0};
        UnorderedEntityArray *m_entities = nullptr;
        size_t entityHash;
        bool first = true;
        size_t entity_index = 0;
        template<int N, typename T, typename ...TArgs>
        void setupOffset() {
            indexes[N] = m_entities->getEntityModel()->getComponentIndex<T>();
            if constexpr(sizeof...(TArgs) > 0) {
                setupOffset<N+1, TArgs...>();
            }
        }
};


class EntityGenerator
{
public:
    EntityGenerator(UnorderedEntityArray *array)
    : m_array(array) {}

    ~EntityGenerator() {}

    template <typename... Args>
    EntityGenerator &instanciate(size_t elements, Args... args)
    {
        m_array->instanciate(elements, args...);
        return *this;
    }

    EntityGenerator &grow(size_t size)
    {
        m_array->grow(size);
        return *this;
    }

    EntityGenerator &reserve(size_t size)
    {
        m_array->reserve(size);
        return *this;
    }

private:
    UnorderedEntityArray *m_array = nullptr;
};

class ECS
{
public:
    size_t getHash(const std::string &name)
    {
        return std::hash<std::string>()(name);
    }

    ECS()
    {
    }

    ~ECS()
    {
        for (EntityType &entity : entities)
        {
            auto it = map_entities.find(entity.hash);
            if (it != map_entities.end())
            {
                delete it->second;
            }
            delete entity.model;
        }

        for (EntitySystem *system : systems)
        {
            delete system;
        }
    }

private:
    template<typename ...Args>
    class EntityModelBuilder
    {
        public:
            EntityModelBuilder(ECS &ecs, size_t hash, const std::string &name) : m_hash(hash), m_ecs(ecs) {
                m_model = new EntityModel(name);
                m_model->addComponents<Args...>();
            }

            ~EntityModelBuilder() {
                finish();
            }

            EntityModelBuilder<Args...> &addTags(std::initializer_list<const std::string> tags) {
                if (finished)
                    return *this;
                for(const std::string &elem : tags) {
                    m_model->addTag(elem);
                }
                return *this;
            }

            void finish() {
                if (!finished) {
                    finished = true;
                    m_ecs.entities.push_back({m_hash, m_model});
                }
            }

        private:
            bool finished = false;
            ECS &m_ecs;
            size_t m_hash;
            EntityModel *m_model = nullptr;
    };

    struct EntitySystem {
        std::vector<size_t> components;
        std::vector<size_t> tags;
        std::vector<size_t> rejectTags;
        ECS &m_ecs;
        std::vector<size_t> models;
        std::function<void(EntitySystem *, float)> func;
        EntitySystem(ECS &ecs) : m_ecs(ecs) {}
        ~EntitySystem() {}
    };

    template<typename ...Args>
    class SystemBuilder
    {
        public:
            SystemBuilder(ECS &ecs, size_t hash) : m_hash(hash), m_ecs(ecs) {
                system = new EntitySystem(ecs);
                getComponent<Args...>();
            }

            ~SystemBuilder() {
                finish();
            }

            SystemBuilder<Args...> &withTags(std::initializer_list<const std::string> tags) {
                if (finished)
                    return *this;
                for (const std::string &elem : tags) {
                    system->tags.push_back(std::hash<std::string>()(elem));
                }
                return *this;
            }

            SystemBuilder<Args...> &withoutTags(std::initializer_list<const std::string> tags) {
                if (finished)
                    return *this;
                for (const std::string &elem : tags) {
                    system->rejectTags.push_back(std::hash<std::string>()(elem));
                }
                return *this;
            }

            SystemBuilder<Args...> &each(typename Functor<void, float, EntityIterator<Args...>&>::type func) {
                if (finished)
                    return *this;
                system->func = [func](EntitySystem *system, float delta) {
                    for (size_t model : system->models) {
                        UnorderedEntityArray *entities = system->m_ecs.getEntityMap(model);
                        if (entities != nullptr) {
                            EntityIterator<Args...> it(entities, model);
                            func(delta, it);
                        }
                    }
                };
                return *this;
            }

            void finish() {
                if (!finished) {
                    finished = true;
                    m_ecs.systems.push_back(system);
                }
            }

        private:
            bool finished = false;
            ECS &m_ecs;
            size_t m_hash;
            EntitySystem *system = nullptr;
            template<typename T, typename ...CArgs>
            void getComponent() {
                ECSID id = typeid(T).hash_code();
                system->components.push_back(id);
                if constexpr(sizeof...(CArgs) > 0)
                    getComponent<CArgs...>();
            }
    };

    struct EntityType
    {
        size_t hash;
        EntityModel *model;
    };
    std::vector<EntityType> entities;
    std::vector<EntitySystem *> systems;
    std::unordered_map<size_t, UnorderedEntityArray *> map_entities;
    std::unordered_map<std::string, size_t> hash_map;

public:
    template<typename ...Args>
    EntityIterator<Args...> lookup(const std::string &name) {
        size_t hash = std::hash<std::string>()(name);
        if (map_entities.find(hash) != map_entities.end()) {
            return EntityIterator<Args...>(map_entities[hash], hash);
        } else {
            for (EntityType &type : entities) {
                if (type.hash == hash) {
                    UnorderedEntityArray *entityArray = new UnorderedEntityArray(type.model, 8);
                    if (entityArray == nullptr) {
                        throw ECSException("Generator failed to create a new UnorderedEntityArray");
                    }
                    map_entities.insert({hash, entityArray});
                    return EntityIterator<Args...>(entityArray, hash);
                }
            }
        }
        throw ECSException("Cannot lookup unexisting entity");
    }
    void compile() {
        for (EntitySystem *system : systems) {
            system->models.clear();
            for (EntityType &type : entities) {
                bool found = true;

                for (size_t component : system->components) {
                    if (!type.model->hasComponent(component)) {
                        found = false;
                        break;
                    }
                }

                if (!found)
                    continue;

                for (size_t tag : system->tags) {
                    if (!type.model->hasTag(tag)) {
                        found = false;
                        break;
                    }
                }

                if (!found)
                    continue;

                for (size_t tag : system->rejectTags) {
                    if (type.model->hasTag(tag)) {
                        found = false;
                        break;
                    }
                }

                if (!found)
                    continue;

                system->models.push_back(type.hash);
            }
        }
    }

    UnorderedEntityArray *getEntityMap(size_t hash) {
        if (map_entities.find(hash) != map_entities.end()) {
            return map_entities[hash];
        }
        return nullptr;
    }

    void update(float delta) {
        for (EntitySystem *system : systems) {
            system->func(system, delta);
        }
    }

    template <typename ...Args>
    EntityModelBuilder<Args...> newEntityModel(const std::string &name)
    {
        size_t hash = std::hash<std::string>()(name);
        return newEntityModel<Args...>(hash, name);
    }

    template <typename ...Args>
    EntityModelBuilder<Args...> newEntityModel(size_t hash, const std::string &name)
    {
        for (EntityType &entity : entities)
        {
            if (entity.hash == hash)
            {
                throw ECSException("There is already an entity with the same name");
            }
        }
        return EntityModelBuilder<Args...>(*this, hash, name);
    }

    template <typename ...Args>
    SystemBuilder<Args...> newSystem(const std::string &name)
    {
        size_t hash = std::hash<std::string>()(name);
        return newSystem<Args...>(hash);
    }

    template <typename ...Args>
    SystemBuilder<Args...> newSystem(size_t hash)
    {
        for (EntityType &entity : entities)
        {
            if (entity.hash == hash)
            {
                throw ECSException("There is already a system with the same name");
            }
        }
        return SystemBuilder<Args...>(*this, hash);
    }

    EntityGenerator getEntityGenerator(const std::string &name)
    {
        size_t hash = std::hash<std::string>()(name);
        return getEntityGenerator(hash);
    }

    EntityGenerator getEntityGenerator(size_t hash)
    {
        for (EntityType &entity : entities)
        {
            if (entity.hash == hash)
            {
                UnorderedEntityArray *entityArray = nullptr;
                auto it = map_entities.find(hash);
                if (it == map_entities.end())
                {
                    entityArray = new UnorderedEntityArray(entity.model, 8);
                    if (entityArray == nullptr) {
                        throw ECSException("Generator failed to create a new UnorderedEntityArray");
                    }
                    map_entities.insert({hash, entityArray});
                }
                else
                {
                    entityArray = it->second;
                    if (entityArray == nullptr) {
                        throw ECSException("Generator failed to retrieve UnorderedEntityArray");
                    }
                }
                return EntityGenerator(entityArray);
            }
        }
        throw ECSException("Cannot get a Generator for an non existant entity model");
    }

protected:
};

#endif /* !ECS_HPP_ */