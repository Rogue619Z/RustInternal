template<typename type>
class List
{
public:
    type get(std::uint32_t idx)
    {
        const auto internal_list = reinterpret_cast<std::uintptr_t>(this + 0x20);
        return *reinterpret_cast<type*>(internal_list + idx * sizeof(type));
    }

    type value(std::uint32_t idx)
    {
        const auto list = *reinterpret_cast<std::uintptr_t*>(this + 0x10);
        const auto internal_list = list + 0x20;
        return *reinterpret_cast<type*>(internal_list + idx * sizeof(type));
    }

    auto size() -> const std::uint32_t { return *reinterpret_cast<std::uint32_t*>(this + 0x18); }
};
template<typename T = void*>
class Array {
public:
    uint32_t size() {
        if (!this) return 0;
        return *reinterpret_cast<uint32_t*>(this + 0x18);
    }
    T get(int idx) {
        if (!this) return T{};
        return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
    }
    void add(int idx, T value) {
        if (!this) return;
        *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
    }
};
class BufferList
{
public:
    char pad_0000[0x10];
    std::int32_t size;
    char pad_0014[0x4];
    void* buffer;


    template<typename T = void*>
    T get(int idx)
    {
        if (!this) return nullptr;
        return *reinterpret_cast<T*>(reinterpret_cast<std::uint64_t>(this->buffer) + (0x20 + sizeof(void*) * idx));
    }
};

class ListDictionary
{
public:
    char pad_0000[0x20];
    BufferList* keys;
    BufferList* vals;
};