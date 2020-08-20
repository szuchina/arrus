#ifndef ARRUS_CORE_COMMON_COMPILER_H
#define ARRUS_CORE_COMMON_COMPILER_H

#define IGNORE_UNUSED(x) do {(void)(x);} while(0)

#ifdef _MSC_VER
#define COMPILER_PUSH_DIAGNOSTIC_STATE  __pragma(warning(push))
#define COMPILER_POP_DIAGNOSTIC_STATE __pragma(warning(pop))
#define COMPILER_IGNORE_UNUSED  __pragma(warning(disable: 4100 4101))
#else
#define COMPILER_PUSH_DIAGNOSTIC_STATE _Pragma("GCC diagnostic push")
#define COMPILER_POP_DIAGNOSTIC_STATE _Pragma("GCC diagnostic pop")
#define COMPILER_IGNORE_UNUSED  _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")  _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#endif

namespace arrus {

template<typename TargetType, typename InType>
inline bool isInstanceOf(const InType *in){
    return dynamic_cast<const TargetType*>(in) != nullptr;
}

}

#endif //ARRUS_CORE_COMMON_COMPILER_H
