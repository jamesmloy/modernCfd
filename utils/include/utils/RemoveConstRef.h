#ifndef _REMOVE_CONST_REF_H_
#define _REMOVE_CONST_REF_H_

namespace Utils
{

  template <typename T>
  using RemoveConstRef =
    std::remove_const_t<std::remove_reference_t<T>>;

}
#endif