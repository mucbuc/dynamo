## dynamo

### Objective:

Dispatch work to agents. 

### Interface: 
```
namespace om636 {
namespace control {

    template <typename... T>
    class Batch {
    public:
        typedef std::function<void(T...)> function_type;
        typedef std::shared_ptr<function_type> agent_type;
        typedef agent_type listener_type;

        virtual ~Batch() = default;
        virtual agent_type hook(function_type) = 0;
        virtual agent_type hook_once(function_type) = 0;
        virtual void invoke(T...) = 0;
    };

} // control
} // om636
```

### Dependencies

Dynamo uses Circuit for thread syncronization

### Plan

Instead of copy and insert elements inside of invok, push the elements one by one as they get traversed (obviosly don't add elements that are dead)...

![doc header](https://s3-us-west-2.amazonaws.com/mod-resources/mod-header.svg)
