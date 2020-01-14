#ifndef TWICE_SIZE_INTERFACE_H_0494LLJLKJ23
#define TWICE_SIZE_INTERFACE_H_0494LLJLKJ23

namespace om636 {
namespace twice_size {

    template <class T>
    struct Circuit {
        typedef T value_type;

        virtual ~Circuit() = default;
        virtual void push(value_type&&) = 0;
        virtual bool check_pop(value_type&) = 0;
        virtual void wait_pop(value_type&) = 0;
    };

} // twice_size
} // om636

#endif // TWICE_SIZE_INTERFACE_H_0494LLJLKJ23
