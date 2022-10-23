#include <iostream>
#include <map>
#include <memory>

class IBase
{
public:
    virtual ~IBase() = default;
    virtual int Get() const = 0;
    virtual void Set(int) = 0;
};

class Derived: public IBase
{
public:
    explicit Derived(int Value_) : Value{Value_} {}
    int Get() const override { return Value; }
    void Set(int Value_) override { Value = Value_; }
private:
    int Value;
};

using MyMap1 = std::map<std::size_t, std::shared_ptr<IBase>>;
void Print1(MyMap1& Map)
{
    Map.erase(1u);

    // type of [Key, Value] = struct std::pair<const unsigned long, std::shared_ptr<IBase>>
    for(auto& [Key, Value] : Map)
    {
        // Key *= 2; // Not allowed under all circumstances because key is const
        Value.reset(new Derived(100));
        Value->Set(2 * Value->Get());
        std::cout << Key << " " << Value->Get() << std::endl;
    }
}

using MyMap2 = std::map<std::size_t, const std::shared_ptr<const IBase>>;
void Print2(const MyMap2& Map)
{
    // Not allowed because Print takes by const&
    // Map.erase(1u);

    // type of [Key, Value] = struct const std::pair<const unsigned long, const std::shared_ptr<const IBase>>
    for(auto& [Key, Value] : Map)
    {
        // Key *= 2; // Not allowed under all circumstances because key is const

        // Not allowed because
        // 1. Print takes by const& AND
        // 2. shared pointer is const
        // Value.reset(new Derived(100));

        // Not allowed because IBase is const
        // Value->Set(2 * Value->Get());

        std::cout << Key << " " << Value->Get() << std::endl;
    }
}

class Buffer
{
public:
    using MyMap = std::map<std::size_t, std::shared_ptr<const IBase>>;
    Buffer()
    {
        Value.emplace(1u, std::make_shared<Derived>(10));
        Value.emplace(3u, std::make_shared<Derived>(30));
        Value.emplace(2u, std::make_shared<Derived>(20));
    }
    MyMap& Get() const { return Value; }
private:
    mutable MyMap Value;
};

void InspectBuffer(const Buffer::MyMap& Map)
{
    std::cout << std::endl;
    for(const auto& [Key, Value] : Map)
    {
        std::cout << Key << " " << Value->Get() << " " << Value.use_count() << std::endl;
    }
}

void ChangeBuffer(Buffer::MyMap& Map)
{
    std::cout << std::endl;
    Map.emplace(4u, std::make_shared<Derived>(40));
    for(auto& [Key, Value] : Map)
    {
        std::cout << Key << " " << Value->Get() << " " << Value.use_count() << std::endl;
    }
}

int main()
{
    MyMap1 Map;
    Map.emplace(1u, std::make_shared<Derived>(10));
    Map.emplace(3u, std::make_shared<Derived>(30));
    Map.emplace(2u, std::make_shared<Derived>(20));
    Print1(Map);

    Buffer Buf;
    InspectBuffer(Buf.Get());
    ChangeBuffer(Buf.Get());
    InspectBuffer(Buf.Get());

    return 0;
}
