#ifndef SNAKE_COMPONENT_POINTER_HEADER
#define SNAKE_COMPONENT_POINTER_HEADER

#include <memory>
#include <functional>
#include <scene/component/component.hpp>

namespace snk {

/// Indirect Component Resource that can point to any component subclass.
class ComponentPointer : public Resource {
public:

    typedef std::function<std::unique_ptr<Component>()> Factory;

public:

    ComponentPointer();
    void reset();

    void setComponent(const Factory& factory);
    Component& getComponent();
    const Component& getComponent() const;

private: 

    std::unique_ptr<Component> mComponent;

};

} // namespace snk

#endif